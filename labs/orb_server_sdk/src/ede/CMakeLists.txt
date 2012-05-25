PROJECT(ede)


ADD_LIBRARY(ede SHARED ede_EDObject.cpp 
						ede_EventDispatchEngine.cpp 
						ede_eventfilter.cpp 
						ede_EventQueue.cpp)

SET_TARGET_PROPERTIES(ede PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../bin)

INCLUDE_DIRECTORIES(../../include/ede ../../include ../../include/osal ../../include/types)


LINK_DIRECTORIES(../../lib)
