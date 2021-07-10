cmake_minimum_required(VERSION 3.0.2)
project(gallipoli_auv_control)

find_package(catkin REQUIRED COMPONENTS
  controller_manager
  hardware_interface
  roscpp
  sensor_msgs
  transmission_interface
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES gallipoli_auv_control
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)


include_directories(
# include
# ${catkin_INCLUDE_DIRS}
)






