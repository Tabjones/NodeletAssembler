cmake_minimum_required(VERSION 2.8.3)
project(rqt_nodelet_assembler)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  pluginlib
  roscpp
  rqt_gui
  rqt_gui_cpp
  roslib
)

## System dependencies are found with CMake's conventions
find_package(Qt4 REQUIRED COMPONENTS QtCore QtGui)

include (${QT_USE_FILE})

set(rqt_nodelet_assembler_INCLUDE_DIRECTORIES
    include
    ${CMAKE_CURRENT_BINARY_DIR}
)
set(rqt_nodelet_assembler_SRC
    src/rqt_nodelet_assembler.cpp
)
set(rqt_nodelet_assembler_HDR
    include/rqt_nodelet_assembler/rqt_nodelet_assembler.h
)
set(rqt_nodelet_assembler_UI
    src/rqt_nodelet_assembler.ui
)
## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
    INCLUDE_DIRS ${rqt_nodelet_assembler_INCLUDE_DIRECTORIES}
    LIBRARIES ${PROJECT_NAME}
    CATKIN_DEPENDS pluginlib roscpp rqt_gui rqt_gui_cpp roslib
#  DEPENDS system_lib
)

qt4_wrap_cpp(rqt_nodelet_assembler_MOC ${rqt_nodelet_assembler_HDR})
qt4_wrap_ui(rqt_nodelet_assembler_UI_H ${rqt_nodelet_assembler_UI})

###########
## Build ##
###########

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${rqt_nodelet_assembler_INCLUDE_DIRECTORIES}
)

add_library(${PROJECT_NAME}
    ${rqt_nodelet_assembler_SRC} ${rqt_nodelet_assembler_MOC} ${rqt_nodelet_assembler_UI_H}
)
target_link_libraries(${PROJECT_NAME}
    ${catkin_LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY}
)
find_package(class_loader)
class_loader_hide_library_symbols(${PROJECT_NAME})

#############
## Install ##
#############

install(FILES rqt_plugin.xml
    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
    DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
