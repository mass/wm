CMAKE_MINIMUM_REQUIRED(VERSION 3.5.1)

PROJECT(mwm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wconversion -g -ggdb")

# Locate libraries
FIND_PACKAGE(X11 REQUIRED)

set(SOURCES mwm.cpp Manager.cpp)

INCLUDE_DIRECTORIES(${X11_INCLUDE_DIR} ${X11_Xrandr_INCLUDE_PATH})

ADD_EXECUTABLE(mwm ${SOURCES})

# Link libraries
TARGET_LINK_LIBRARIES(mwm ${X11_LIBRARIES} ${X11_Xrandr_LIB})
