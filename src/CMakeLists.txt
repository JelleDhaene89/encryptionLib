set(SOURCES
    cipher.cpp
)

set(PUBLIC_HEADERS
    cipher.h
)

set(PRIVATE_HEADERS

)

createlib(
    NAME Encryption SHARED
    NAMESPACE ENC
    VERSION 1.0.0
    SOURCES ${SOURCES}
    PRIVATE_HEADERS ${PRIVATE_HEADERS}
    PUBLIC_HEADERS ${PUBLIC_HEADERS}
    PUBLIC_DEPS Qt6::Core
    PRIVATE_DEPS
    GENERATE_PACKAGE)

