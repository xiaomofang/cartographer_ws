cmake_minimum_required(VERSION 3.0.2)
project(trajectory_test)

# add_compile_options(-std=c++11)
SET(CMAKE_BUILD_TYPE Debug)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  nav_msgs
  tf
  message_generation
)
add_message_files(
  FILES
  odom2tum.msg
)
generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS roscpp nav_msgs tf
  message_runtime
)

# find_package(OpenCV  REQUIRED)
# find_package(aruco  REQUIRED )


include_directories(
  ${catkin_INCLUDE_DIRS}
#   ${OpenCV_INCLUDE_DIRS}
#   ${aruco_INCLUDE_DIRS}
)
include_directories(/usr/include/eigen3)

add_executable(carto_odom src/carto_odom.cpp)
target_link_libraries(carto_odom
  ${catkin_LIBRARIES}
#   ${OpenCV_LIBS}
#   ${aruco_LIBS}
)
# add_dependencies(aruco_test ${PROJECT_NAME}_gencpp)

add_executable(wheel_odom src/wheel_odom.cpp)
target_link_libraries(wheel_odom
  ${catkin_LIBRARIES}
#   ${OpenCV_LIBS}
#   ${aruco_LIBS}
)
# add_dependencies(aruco_test ${PROJECT_NAME}_gencpp)

add_executable(odom2path src/odom2path.cpp)
target_link_libraries(odom2path
  ${catkin_LIBRARIES}
#   ${OpenCV_LIBS}
#   ${aruco_LIBS}
)
# add_dependencies(aruco_test ${PROJECT_NAME}_gencpp)
#TODO odom2tum need a .h file but i can't find it
add_executable(odom2tum src/odom2tum.cpp)
target_link_libraries(odom2tum
  ${catkin_LIBRARIES}
#   ${OpenCV_LIBS}
#   ${aruco_LIBS}
)
add_dependencies(odom2tum ${PROJECT_NAME}_gencpp)