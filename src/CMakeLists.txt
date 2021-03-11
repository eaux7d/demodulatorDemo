cmake_minimum_required(VERSION 2.4)
project(DemodulatorDemo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

if(CMAKE_COMPILER_IS_GNUCXX)
	message(STATUS "GCC detected")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Wfloat-conversion -Werror -pedantic")
endif(CMAKE_COMPILER_IS_GNUCXX)

ADD_LIBRARY(DemodulateMathLib STATIC 

	lib/DemodulateLibMath.h 
	lib/Tasks.h
	lib/DemodulateLibTypes.h 
	lib/fir_sr1M_cut_50k_x2=150k.h
	
	lib/DemodulateLibMath.cpp 
	lib/Tasks.cpp
	
	)

SET(APP_EXE DemodulationDemo)

include_directories(.)

ADD_EXECUTABLE(${APP_EXE}
				exe/main.cpp)
				
TARGET_LINK_LIBRARIES( ${APP_EXE}
                DemodulateMathLib )