cmake_minimum_required(VERSION 3.0.2)
project(turtlebot_control)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  nav_msgs
  tf2
  tf2_ros
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES turtlebot_control
  CATKIN_DEPENDS roscpp geometry_msgs nav_msgs tf2 tf2_ros std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(odom src/odom.cpp)
target_link_libraries(odom ${catkin_LIBRARIES})

add_executable(keyboard_control src/keyboard_control.cpp)
target_link_libraries(keyboard_control ${catkin_LIBRARIES})
