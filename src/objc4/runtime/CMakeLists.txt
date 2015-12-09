project(libobjc)

cmake_minimum_required(VERSION 2.4.0)
enable_language(C CXX ASM)

if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
	cmake_policy(SET CMP0005 NEW)
endif(COMMAND cmake_policy)

add_definitions(-D__APPLE__ -D__MACH__)
add_definitions(-DTARGET_OS_MAC=1)
add_definitions(-D__APPLE__ -D__DYNAMIC__)
add_definitions(-D__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__=1080)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostdinc -D__DARWIN_UNIX03 -fPIC -fblocks")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdinc -nostdinc++ -std=c++11 -D__DARWIN_UNIX03 -fPIC -fblocks")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -nostdlib -Wl,--version-script=${DARLING_TOP_DIRECTORY}/darwin.map")
set(CMAKE_CXX_IMPLICIT_LINK_LIBRARIES "")

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib${SUFFIX}/darling")
SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE) 
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_definitions(-DOBJC_NO_GC) # For now (TODO)
add_definitions(-DTARGET_OS_IPHONE=0)

if(BITS EQUAL 64)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fobjc-runtime=macosx")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fobjc-runtime=macosx -ggdb -O0")
	add_definitions(-D__OBJC2__=1)
else(BITS EQUAL 64)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fobjc-fragile-abi -fobjc-runtime=macosx-fragile-10.6")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fobjc-fragile-abi -fobjc-runtime=macosx-fragile-10.6")
	add_definitions(-D__OBJC2__=0)
endif(BITS EQUAL 64)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${DARLING_TOP_DIRECTORY}/src/external/libcxx/include)
include_directories(${DARLING_TOP_DIRECTORY}/src/external/libdispatch)
include_directories(${DARLING_TOP_DIRECTORY}/src/external/foundation/Headers)
include_directories(${DARLING_TOP_DIRECTORY}/src/libclosure)
include_directories(${DARLING_TOP_DIRECTORY}/src/libunwind/include)
include_directories(${DARLING_TOP_DIRECTORY}/src/libc/gen)
include_directories(${DARLING_TOP_DIRECTORY}/src/launchd/liblaunch)
include_directories(${CMAKE_BINARY_DIR}/src/external/foundation/Headers)

set(objc_SRCS
	hashtable2.mm
	maptable.mm
	NSObject.mm
	objc-block-trampolines.mm
	objc-cache.mm
	objc-class.mm
	objc-errors.mm
	objc-exception.mm
	objc-externalref.mm
	objc-file.mm
	objc-initialize.mm
	objc-layout.mm
	objc-loadmethod.mm
	objc-load.mm
	objc-lockdebug.mm
	objc-opt.mm
	objc-os.mm
	objc-references.mm
	objc-runtime.mm
	objc-runtime-new.mm
	objc-sel.mm
	objc-sel-set.mm
	objc-sync.mm
	objc-typeencoding.mm
	objc-weak.mm
	Protocol.mm

	a1a2-blocktramps-x86_64.S
	a2a3-blocktramps-x86_64.S
	Messengers.subproj/objc-msg-i386.S
	Messengers.subproj/objc-msg-x86_64.S
	objc-sel-table.S
	extra/encoding2.c
)

add_library(objc SHARED ${objc_SRCS})
target_link_libraries(objc PRIVATE system_c system_malloc cxx dyld)

install(TARGETS objc DESTINATION lib${SUFFIX}/darling)
