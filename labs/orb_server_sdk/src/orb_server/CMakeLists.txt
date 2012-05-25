PROJECT(orb_server)


ADD_EXECUTABLE(orb_server orb_server_SMManager.cpp
							orb_server_Core_Impl.cpp
							orb_server_MemManager.cpp
							orb_server_NetworkManager.cpp
							orb_server_utils.cpp
							orb_server_ServerApplication.cpp
							orb_server_SysConfig.cpp
							orb_server_DeviceManager.cpp)

SET_TARGET_PROPERTIES(orb_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../bin)

INCLUDE_DIRECTORIES(../../include /usr/local/include)


LINK_DIRECTORIES(/usr/local/lib ../../lib ../../bin)

find_package(boost)

TARGET_LINK_LIBRARIES(orb_server osal orb_bcl ede boost_filesystem)
