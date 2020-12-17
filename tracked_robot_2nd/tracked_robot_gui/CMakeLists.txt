##############################################################################
# CMake
##############################################################################

cmake_minimum_required(VERSION 3.0.2)
project(tracked_robot_gui)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_compile_options(-std=c++11)

##############################################################################
# Catkin
##############################################################################

# qt_build provides the qt cmake glue, roscpp the comms for a default talker
find_package(catkin REQUIRED COMPONENTS qt_build roscpp rviz)

## This setting causes Qt's "MOC" generation to happen automatically.
set(CMAKE_AUTOMOC ON)

## This plugin includes Qt widgets, so we must include Qt.
## We'll use the version that rviz used so they are compatible.
if(rviz_QT_VERSION VERSION_LESS "5")
  message(STATUS "Using Qt4 based on the rviz_QT_VERSION: ${rviz_QT_VERSION}")
  find_package(Qt4 ${rviz_QT_VERSION} EXACT REQUIRED QtCore QtGui)
  ## pull in all required include dirs, define QT_LIBRARIES, etc.
  include(${QT_USE_FILE})
else()
  message(STATUS "Using Qt5 based on the rviz_QT_VERSION: ${rviz_QT_VERSION}")
  find_package(Qt5 ${rviz_QT_VERSION} EXACT REQUIRED Core Widgets)
  ## make target_link_libraries(${QT_LIBRARIES}) pull in all required dependencies
  set(QT_LIBRARIES Qt5::Widgets)
endif()

# Use this to define what the package will export (e.g. libs, headers).
# Since the default here is to produce only a binary, we don't worry about
# exporting anything.
include_directories(${catkin_INCLUDE_DIRS})
link_directories(${catkin_LIBRARY_DIRS})
catkin_package()

##############################################################################
# Qt Environment
##############################################################################

## I prefer the Qt signals and slots to avoid defining "emit", "slots",
## etc because they can conflict with boost signals, so define QT_NO_KEYWORDS here.
add_definitions(-DQT_NO_KEYWORDS)

## Here we specify the list of source files, including the output of
## the previous command which is stored in ``${MOC_FILES}``.
#set(
#    SRC_FILES
#        src/laser.cpp
#        src/camera.cpp
#        src/rviz_on_gui.cpp
#        src/main.cpp
#)

##############################################################################
# Sections
##############################################################################

file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
#file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/tracked_robot_gui/*.h)

## We are using QT5 !!

#QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC})

##############################################################################
# Sources
##############################################################################

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)

##############################################################################
# Binaries
##############################################################################

## Add the "tracked_robot_gui" executable and specify the list of source files we
## collected above in "${SRC_FILES}".
#add_executable(tracked_robot_gui ${QT_SOURCES} ${QT_FORMS_HPP} ${QT_MOC_HPP})

## Link the tracked_robot_gui executable with whatever Qt libraries have been defined by
## the "find_package(Qt4 ...)" line above, or by the
## "set(QT_LIBRARIES Qt5::Widgets)", and with whatever libraries
## catkin has included.
#target_link_libraries(tracked_robot_gui ${QT_LIBRARIES} ${catkin_LIBRARIES})

## Install
#install(TARGETS tracked_robot_gui RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

