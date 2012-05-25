PROJECT(osal)


ADD_LIBRARY(osal SHARED os_api_freebsd.cpp)

SET_TARGET_PROPERTIES(osal PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../bin)

INCLUDE_DIRECTORIES(../../include ../../include/osal ../../include/types)


LINK_DIRECTORIES(../../lib)
