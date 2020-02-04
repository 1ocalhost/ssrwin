CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(ssrwin)

find_program(CUSTOM_CC "i686-w64-mingw32-gcc")
set(CMAKE_C_COMPILER "${CUSTOM_CC}")
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O1" )

set(LIBSODIUM "third_party/libsodium-1.0.18")
set(LIBEV "third_party/libev-4.24-mingw")
set(MBEDTLS "third_party/mbedtls-2.16.4")
set(LIBCORK "third_party/libcork-0.15.0")

# sodium
file(GLOB_RECURSE SODIUM_SRC
  "${LIBSODIUM}/*.c"
)
add_library(sodium STATIC ${SODIUM_SRC})
target_include_directories(sodium
  PRIVATE "${LIBSODIUM}/include"
  PRIVATE "${LIBSODIUM}/include/sodium"
)
target_compile_definitions(sodium PRIVATE
  CONFIGURED=1
)

# libev
file(GLOB_RECURSE EV_SRC
  "${LIBEV}/ev.c"
  "${LIBEV}/wepoll.c"
  "${LIBEV}/clock_gettime.c"
)
add_library(libev STATIC ${EV_SRC})
target_compile_definitions(libev PRIVATE
  EV_STANDALONE
  EV_HAVE_EV_TIME
  EV_USE_EPOLL=1
)

# mbedtls
file(GLOB_RECURSE MBEDTLS_SRC
  "${MBEDTLS}/*.c"
)
add_library(mbedtls STATIC ${MBEDTLS_SRC})
target_include_directories(mbedtls
  PRIVATE "${MBEDTLS}/include"
)

# libcork
file(GLOB_RECURSE LIBCORK_SRC
  "${LIBCORK}/*.c"
)
add_library(libcork STATIC ${LIBCORK_SRC})
target_include_directories(libcork
  PRIVATE "${LIBCORK}/include"
)

# ssrwin
file(GLOB_RECURSE APP_SRC
  "src/*.c"
)
add_executable(ssrwin ${APP_SRC})
target_link_libraries(ssrwin
  sodium libev mbedtls libcork
  -lws2_32 -mthreads
)
target_include_directories(ssrwin
  PRIVATE "src"
  PRIVATE "${LIBEV}"
  PRIVATE "${LIBSODIUM}/include"
  PRIVATE "${MBEDTLS}/include"
  PRIVATE "${LIBCORK}/include"
)
target_compile_definitions(ssrwin PRIVATE
  USE_CRYPTO_MBEDTLS
  HAVE_CONFIG_H
  MODULE_LOCAL
)

