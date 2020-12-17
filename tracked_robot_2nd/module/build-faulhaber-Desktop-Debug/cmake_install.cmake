# Install script for directory: /home/cirlab/catkin_ws/src/tracked_robot_2nd/module/faulhaber

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "=/home/cirlab/catkin_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
        file(MAKE_DIRECTORY "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
      endif()
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin")
        file(WRITE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin" "")
      endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/=/home/cirlab/catkin_ws/install" TYPE PROGRAM FILES "/home/cirlab/catkin_ws/src/tracked_robot_2nd/module/build-faulhaber-Desktop-Debug/catkin_generated/installspace/_setup_util.py")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/=/home/cirlab/catkin_ws/install" TYPE PROGRAM FILES "/home/cirlab/catkin_ws/src/tracked_robot_2nd/module/build-faulhaber-Desktop-Debug/catkin_generated/installspace/env.sh")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/=/home/cirlab/catkin_ws/install" TYPE FILE FILES
    "/home/cirlab/catkin_ws/src/tracked_robot_2nd/module/build-faulhaber-Desktop-Debug/catkin_generated/installspace/setup.bash"
    "/home/cirlab/catkin_ws/src/tracked_robot_2nd/module/build-faulhaber-Desktop-Debug/catkin_generated/installspace/local_setup.bash"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/=/home/cirlab/catkin_ws/install" TYPE FILE FILES
    "/home/cirlab/catkin_ws/src/tracked_robot_2nd/module/build-faulhaber-Desktop-Debug/catkin_generated/installspace/setup.sh"
    "/home/cirlab/catkin_ws/src/tracked_robot_2nd/module/build-faulhaber-Desktop-Debug/catkin_generated/installspace/local_setup.sh"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/=/home/cirlab/catkin_ws/install" TYPE FILE FILES
    "/home/cirlab/catkin_ws/src/tracked_robot_2nd/module/build-faulhaber-Desktop-Debug/catkin_generated/installspace/setup.zsh"
    "/home/cirlab/catkin_ws/src/tracked_robot_2nd/module/build-faulhaber-Desktop-Debug/catkin_generated/installspace/local_setup.zsh"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/=/home/cirlab/catkin_ws/install" TYPE FILE FILES "/home/cirlab/catkin_ws/src/tracked_robot_2nd/module/build-faulhaber-Desktop-Debug/catkin_generated/installspace/.rosinstall")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/cirlab/catkin_ws/src/tracked_robot_2nd/module/build-faulhaber-Desktop-Debug/catkin_generated/installspace/faulhaber.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/faulhaber/cmake" TYPE FILE FILES
    "/home/cirlab/catkin_ws/src/tracked_robot_2nd/module/build-faulhaber-Desktop-Debug/catkin_generated/installspace/faulhaberConfig.cmake"
    "/home/cirlab/catkin_ws/src/tracked_robot_2nd/module/build-faulhaber-Desktop-Debug/catkin_generated/installspace/faulhaberConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/faulhaber" TYPE FILE FILES "/home/cirlab/catkin_ws/src/tracked_robot_2nd/module/faulhaber/package.xml")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/cirlab/catkin_ws/src/tracked_robot_2nd/module/build-faulhaber-Desktop-Debug/gtest/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/cirlab/catkin_ws/src/tracked_robot_2nd/module/build-faulhaber-Desktop-Debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
