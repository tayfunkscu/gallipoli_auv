cmake_minimum_required(VERSION 3.0.2)
project(gallipoli_auv_description)

find_package(catkin REQUIRED)

catkin_package()

install(DIRECTORY meshes robots urdf launch
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
        PATTERN "*~" EXCLUDE)
