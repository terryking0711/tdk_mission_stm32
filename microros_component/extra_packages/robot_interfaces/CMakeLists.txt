cmake_minimum_required(VERSION 3.5)
project(robot_interfaces)

if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/MechanismCommand.msg"
)

ament_export_dependencies(rosidl_default_runtime)

ament_package()
