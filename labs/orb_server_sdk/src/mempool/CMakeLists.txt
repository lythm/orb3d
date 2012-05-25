PROJECT(mempool)


ADD_LIBRARY(mempool SHARED mem_MemPool.cpp)

SET_TARGET_PROPERTIES(mempool PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../bin)

INCLUDE_DIRECTORIES(../../include ../../include/mem ../../include/types)


LINK_DIRECTORIES(../../lib)
