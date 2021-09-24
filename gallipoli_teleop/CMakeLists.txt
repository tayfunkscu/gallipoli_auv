cmake_minimum_required(VERSION 3.0.2)
project(gallipoli_teleop)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  gallipoli_msgs
  darknet_ros_msgs
)


catkin_package(
  INCLUDE_DIRS include
  LIBRARIES gallipoli_teleop
  CATKIN_DEPENDS roscpp rospy std_msgs gallipoli_msgs darknet_ros_msgs
  DEPENDS system_lib
)

include_directories(
  #include
   ${catkin_INCLUDE_DIRS}
)

add_executable(depth_zero src/depth_zero.cpp)
target_link_libraries(depth_zero ${catkin_LIBRARIES})
add_dependencies(depth_zero gallipoli_msgs_generate_messages_cpp)

add_executable(go_to_gate src/go_to_gate.cpp)
target_link_libraries(go_to_gate ${catkin_LIBRARIES})
add_dependencies(go_to_gate gallipoli_msgs_generate_messages_cpp darknet_ros_msgs_generate_messages_cpp)

add_executable(teleop_key src/teleop_key.cpp)
target_link_libraries(teleop_key ${catkin_LIBRARIES})

add_executable(teleop_to_pwm src/teleop_to_pwm.cpp)
target_link_libraries(teleop_to_pwm ${catkin_LIBRARIES})
add_dependencies(teleop_to_pwm gallipoli_msgs_generate_messages_cpp)

add_executable(depth_pwm_tracker src/set_depth_pwm.cpp)
target_link_libraries(depth_pwm_tracker ${catkin_LIBRARIES})
add_dependencies(depth_pwm_tracker gallipoli_msgs_generate_messages_cpp)

add_executable(stop_depth src/stop_depth.cpp)
target_link_libraries(stop_depth ${catkin_LIBRARIES})
add_dependencies(stop_depth gallipoli_msgs_generate_messages_cpp)
