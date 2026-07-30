/*
 * uros_init.c
 *
 *  Created on: Jul 15, 2026
 *      Author: hsuanjung
 */




#include "uros_init.h"
#include <math.h>
#include <string.h>
#include <rmw_microros/time_sync.h>

rcl_subscription_t                          mechanism_command_sub;
robot_interfaces__msg__MechanismCommand     mechanism_command_msg;

volatile uint16_t  mechanism_command_id = 0;
volatile bool      mechanism_command_pending = false;
volatile uint32_t  mechanism_command_rx_count = 0;

rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_init_options_t init_options;
rclc_executor_t executor;

agent_status_t status = AGENT_WAITING;


int ping_fail_count = 0;
#define MAX_PING_FAIL_COUNT 5

extern UART_HandleTypeDef huart3;


void uros_init(void) {
  // Initialize micro-ROS
  rmw_uros_set_custom_transport(
    true,
    (void *) &huart3,
    cubemx_transport_open,
    cubemx_transport_close,
    cubemx_transport_write,
    cubemx_transport_read);

  rcl_allocator_t freeRTOS_allocator = rcutils_get_zero_initialized_allocator();

  freeRTOS_allocator.allocate = microros_allocate;
  freeRTOS_allocator.deallocate = microros_deallocate;
  freeRTOS_allocator.reallocate = microros_reallocate;
  freeRTOS_allocator.zero_allocate =  microros_zero_allocate;

  if (!rcutils_set_default_allocator(&freeRTOS_allocator)) {
  printf("Error on default allocators (line %d)\n", __LINE__);
  }
}

void uros_agent_status_check(void) {
  switch (status) {
    case AGENT_WAITING:
      handle_state_agent_waiting();
      break;
    case AGENT_AVAILABLE:
      handle_state_agent_available();
      break;
    case AGENT_CONNECTED:
      handle_state_agent_connected();
      break;
    case AGENT_TRYING:
      handle_state_agent_trying();
      break;
    case AGENT_DISCONNECTED:
      handle_state_agent_disconnected();
      break;
    default:
      break;
  }
}

void handle_state_agent_waiting(void) {
  status = (rmw_uros_ping_agent(100, 10) == RMW_RET_OK) ? AGENT_AVAILABLE : AGENT_WAITING;
}
void handle_state_agent_available(void) {
  uros_create_entities();
  status = AGENT_CONNECTED;
}
void handle_state_agent_connected(void) {
  if(rmw_uros_ping_agent(20, 5) == RMW_RET_OK){
    rclc_executor_spin_some(&executor, RCL_MS_TO_NS(10));
    ping_fail_count = 0; // Reset ping fail count
  } else {
    ping_fail_count++;
    if(ping_fail_count >= MAX_PING_FAIL_COUNT){
      status = AGENT_TRYING;
    }
  }
}
void handle_state_agent_trying(void) {
  if(rmw_uros_ping_agent(50, 10) == RMW_RET_OK){
    status = AGENT_CONNECTED;
    ping_fail_count = 0; // Reset ping fail count
  } else {
    ping_fail_count++;
    if(ping_fail_count >= MAX_PING_FAIL_COUNT){
      status = AGENT_DISCONNECTED;
      ping_fail_count = 0;
    }
  }
}
void handle_state_agent_disconnected(void) {
  uros_destroy_entities();
  status = AGENT_WAITING;
}

void uros_create_entities(void) {
  rcl_ret_t rc;

  allocator = rcl_get_default_allocator();

  init_options = rcl_get_zero_initialized_init_options();
  rcl_init_options_init(&init_options, allocator);
  rcl_init_options_set_domain_id(&init_options, DOMAIN_ID);

  rc = rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator); // Initialize support structure
  if (rc != RCL_RET_OK) {
    printf("[uros] support_init failed: %d\n", (int)rc);
  }

  rcl_init_options_fini(&init_options);

  rc = rclc_node_init_default(&node, NODE_NAME, "", &support);                       // Initialize node
  if (rc != RCL_RET_OK) {
    printf("[uros] node_init failed: %d\n", (int)rc);
  }

  // MechanismCommand 帶有 string 欄位 (command_name / arg_json)，訂閱前要先 init
  // 讓 rosidl 配置好用來承接 deserialize 時動態配置字串記憶體的狀態
  bool init_ok = robot_interfaces__msg__MechanismCommand__init(&mechanism_command_msg);
  if (!init_ok) {
    printf("[uros] MechanismCommand__init failed\n");
  }

  rc = rclc_subscription_init_default(                                               // Initialize subscriber for mechanism command
    &mechanism_command_sub,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(robot_interfaces, msg, MechanismCommand),
    "/mechanism/command");
  if (rc != RCL_RET_OK) {
    printf("[uros] subscription_init failed: %d\n", (int)rc);
  }

  rc = rclc_executor_init(&executor, &support.context, 1, &allocator); // Create executor (0 timer + 1 subscriptions)
  if (rc != RCL_RET_OK) {
    printf("[uros] executor_init failed: %d\n", (int)rc);
  }

  rc = rclc_executor_add_subscription(&executor, &mechanism_command_sub, &mechanism_command_msg, &mechanism_command_cb, ON_NEW_DATA); // Add subscriber to executor
  if (rc != RCL_RET_OK) {
    printf("[uros] executor_add_subscription failed: %d\n", (int)rc);
  }
}

void uros_destroy_entities(void) {
  rmw_context_t* rmw_context = rcl_context_get_rmw_context(&support.context);
  (void) rmw_uros_set_context_entity_destroy_session_timeout(rmw_context, 0);

  // Destroy subscriber
  rcl_subscription_fini(&mechanism_command_sub, &node);
  robot_interfaces__msg__MechanismCommand__fini(&mechanism_command_msg);

  // Destroy executor
  rclc_executor_fini(&executor);

  // Destroy node
  rcl_node_fini(&node);
  rclc_support_fini(&support);
}

void mechanism_command_cb(const void *msgin){
    const robot_interfaces__msg__MechanismCommand *msg =
        (const robot_interfaces__msg__MechanismCommand *)msgin;
    if (msg == NULL){
        return;
    }

    mechanism_command_rx_count++;

    // 只搬 command_id 出去給 rtos_main.c 的 StartTask02 做 dispatch，
    // command_name / arg_json 目前沒用到，之後要用再從 mechanism_command_msg 讀
    mechanism_command_id = msg->command_id;
    mechanism_command_pending = true;
}
