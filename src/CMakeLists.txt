set(SOURCES
    cipher.cpp
)

set(PUBLIC_HEADERS
    cipher.h
)

set(PRIVATE_HEADERS

)

#include_directories(${OPENSSL_LIBS_DIR})

message(STATUS "OpenSSL Libraries: ${OPENSSL_LIBRARIES}")
message(STATUS "OpenSSL LIBS: ${ZLIB_LIBRARIES}")

createlib(
    NAME Encryption SHARED
    NAMESPACE ENC
    VERSION 1.0.0
    SOURCES ${SOURCES}
    PRIVATE_HEADERS ${PRIVATE_HEADERS}
    PUBLIC_HEADERS ${PUBLIC_HEADERS}
    PUBLIC_DEPS Qt6::Core #Qt6::Network #OpenSSL::SSL OpenSSL::Crypto #remove network ???
    PRIVATE_DEPS OpenSSL::SSL OpenSSL::Crypto #${ZLIB_LIBRARIES}
    GENERATE_PACKAGE)

target_include_directories(Encryption PRIVATE ${ZLIB_INCLUDE_DIRS})
target_link_libraries(Encryption PRIVATE ${ZLIB_LIBRARIES})

#target_link_libraries(Core ${ZLIB_LIBRARIES})
