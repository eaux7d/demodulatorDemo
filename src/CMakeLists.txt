ADD_LIBRARY(DemodulateMathLib STATIC lib/DemodulateLibMath.h lib/DemodulateLibMath.cpp lib/DemodulateLibTypes.h)

SET(APP_EXE DemodulationDemo)

ADD_EXECUTABLE(${APP_EXE}
				exe/main.cpp)
				
TARGET_LINK_LIBRARIES( ${APP_EXE}
                DemodulateMathLib )