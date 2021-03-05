cmake_minimum_required(VERSION 2.4)
ADD_LIBRARY(DemodulateMathLib STATIC lib/DemodulateLibMath.h lib/DemodulateLibMath.cpp lib/DemodulateLibTypes.h)

SET(APP_EXE DemodulationDemo)

include_directories(.)

ADD_EXECUTABLE(${APP_EXE}
				exe/main.cpp)
				
TARGET_LINK_LIBRARIES( ${APP_EXE}
                DemodulateMathLib )