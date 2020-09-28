add_executable(server_eapp
  server_eapp.c
  edge_wrapper.c
  calculator.c
  channel.c)

include_directories(include
  ${KEYSTONE_SDK_DIR}/include/app)

target_link_libraries(server_eapp
  ${KEYSTONE_LIB_EDGE}
  ${KEYSTONE_LIB_EAPP}
  ${LIBSODIUM_DIR}/.libs/libsodium.a)

set_target_properties(server_eapp
  PROPERTIES LINK_FLAGS "-nostdlib -static -T ${CMAKE_CURRENT_SOURCE_DIR}/app.lds")
