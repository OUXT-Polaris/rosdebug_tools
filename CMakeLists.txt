cmake_minimum_required(VERSION 2.8.3)
project(rosdebug_tools)

add_compile_options(-std=c++14)

include(glog-toolchain.cmake)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  std_msgs
  rosbag
)

add_message_files(
  FILES
  LoggedData.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES rosdebug_tools
  CATKIN_DEPENDS message_generation roscpp std_msgs
  #DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(rosdebug_tools src/rosdebug_tools.cpp src/message_buffer.cpp src/rosbag_writer.cpp)
target_link_libraries(rosdebug_tools ${catkin_LIBRARIES} ${GLOG_LIBRARIES})
add_dependencies(rosdebug_tools rosdebug_tools_generate_messages_cpp)

install(TARGETS rosdebug_tools
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

foreach(dir msg)
  install(DIRECTORY ${dir}/
    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)