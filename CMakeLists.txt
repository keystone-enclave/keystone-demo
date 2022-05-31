cmake_minimum_required(VERSION 3.10)
enable_language(C CXX ASM)

# check if SDK has been built and KEYSTONE_SDK_DIR environment variable exists
if (NOT DEFINED ENV{KEYSTONE_SDK_DIR})
  message(FATAL_ERROR "Please set KEYSTONE_SDK_DIR environment variable to an installed SDK path")
endif()
set(KEYSTONE_SDK_DIR $ENV{KEYSTONE_SDK_DIR})

if (NOT DEFINED ENV{LIBSODIUM_CLIENT_DIR})
  message(FATAL_ERROR "Please set LIBSODIUM_CLIENT_DIR")
endif()
set(LIBSODIUM_CLIENT_DIR $ENV{LIBSODIUM_CLIENT_DIR})

if (NOT DEFINED ENV{LIBSODIUM_DIR})
  message(FATAL_ERROR "Please set LIBSODIUM_DIR")
endif()
set(LIBSODIUM_DIR $ENV{LIBSODIUM_DIR})

include($ENV{KEYSTONE_SDK_DIR}/cmake/macros.cmake)

if(RISCV32)
  message(STATUS "riscv32")
  set(BITS 32)
else()
  message(STATUS "riscv64")
  set(BITS 64)
endif()

use_riscv_toolchain(${BITS})

# export include directory
include_directories(include
  ${LIBSODIUM_CLIENT_DIR}/include
  ${KEYSTONE_SDK_DIR}/include
  ${KEYSTONE_SDK_DIR}/include/host
  ${KEYSTONE_SDK_DIR}/include/edge
  ${KEYSTONE_SDK_DIR}/include/verifier)

# set paths to the libraries
set(KEYSTONE_LIB_HOST ${KEYSTONE_SDK_DIR}/lib/libkeystone-host.a)
set(KEYSTONE_LIB_EDGE ${KEYSTONE_SDK_DIR}/lib/libkeystone-edge.a)
set(KEYSTONE_LIB_VERIFIER ${KEYSTONE_SDK_DIR}/lib/libkeystone-verifier.a)
set(KEYSTONE_LIB_EAPP ${KEYSTONE_SDK_DIR}/lib/libkeystone-eapp.a)

# find program "makeself"
find_program(MAKESELF makeself)

# trusted client
add_executable(trusted_client.riscv
  trusted_client/client.cpp
  trusted_client/trusted_client.cpp
  include/enclave_expected_hash.h
  include/sm_expected_hash.h
)

target_link_libraries(trusted_client.riscv
  ${KEYSTONE_LIB_VERIFIER}
  ${LIBSODIUM_CLIENT_DIR}/.libs/libsodium.a)

# enclave
add_subdirectory(server_eapp)
set(host_bin demo-server.riscv)
set(host_src enclave-host.cpp edge_wrapper.cpp)
set(eyrie_plugins "freemem")
set(package_name "demo-server.ke")
set(package_script "./demo-server.riscv")

add_executable(${host_bin} ${host_src})
target_link_libraries(${host_bin} ${KEYSTONE_LIB_HOST} ${KEYSTONE_LIB_EDGE} ${KEYSTONE_LIB_VERIFIER})

set(eyrie_files_to_copy eyrie-rt)
add_eyrie_runtime(${eapp_bin}-eyrie
  "v1.0.0"
  ${eyrie_plugins}
  ${eyrie_files_to_copy})

add_keystone_package(packagedemo
  ${package_name}
  ${package_script}
  ${eyrie_files_to_copy} server_eapp/server_eapp.eapp_riscv ${host_bin})

add_dependencies(packagedemo ${eapp_bin}-eyrie)

