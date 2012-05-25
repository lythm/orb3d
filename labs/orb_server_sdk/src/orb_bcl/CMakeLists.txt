PROJECT(orb_bcl)


ADD_LIBRARY(orb_bcl SHARED orb_bcl_CircularQueue.cpp)

SET_TARGET_PROPERTIES(orb_bcl PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../bin)

INCLUDE_DIRECTORIES(../../include ../../include/orb_bcl ../../include/osal ../../include/types)

LINK_DIRECTORIES(../../lib)
