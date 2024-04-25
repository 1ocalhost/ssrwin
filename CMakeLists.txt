CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(ssrwin)

find_program(CUSTOM_CC "i686-w64-mingw32-gcc")
set(CMAKE_C_COMPILER "${CUSTOM_CC}")
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O1" )

set(STRIP "i686-w64-mingw32-strip")

set(LIBSODIUM "third_party/libsodium-1.0.18")
set(LIBEV "third_party/libev-4.24-mingw")
set(MBEDTLS "third_party/mbedtls-2.16.4")
set(LIBCORK "third_party/libcork-0.15.0")
set(LIBBLOOM "third_party/libbloom")

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
  TLS=__thread
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
target_compile_options(libev PRIVATE
  "-Wno-incompatible-pointer-types"
  "-Wno-int-conversion"
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

# libbloom
file(GLOB_RECURSE LIBBLOOM_SRC
  "${LIBBLOOM}/*.c"
)
add_library(libbloom STATIC ${LIBBLOOM_SRC})
target_include_directories(libbloom
  PRIVATE "${LIBBLOOM}/murmur2"
)

# sswin
file(GLOB_RECURSE SS_SRC
  "ss/*.c"
)
add_executable(sswin ${SS_SRC})
target_link_libraries(sswin
  sodium libev mbedtls libcork libbloom
  -lws2_32 -mthreads
)
target_include_directories(sswin
  PRIVATE "ss"
  PRIVATE "${LIBEV}"
  PRIVATE "${LIBSODIUM}/include"
  PRIVATE "${MBEDTLS}/include"
  PRIVATE "${LIBCORK}/include"
  PRIVATE "${LIBBLOOM}"
)
target_compile_definitions(sswin PRIVATE
  USE_CRYPTO_MBEDTLS
  MODULE_LOCAL
)
add_custom_command(TARGET sswin POST_BUILD
    COMMAND ${STRIP} sswin.exe
)

# ssrwin
file(GLOB_RECURSE SSR_SRC
  "ssr/*.c"
)
add_executable(ssrwin ${SSR_SRC})
target_link_libraries(ssrwin
  sodium libev mbedtls libcork
  -lws2_32 -mthreads
)
target_include_directories(ssrwin
  PRIVATE "ssr"
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
add_custom_command(TARGET ssrwin POST_BUILD
    COMMAND ${STRIP} ssrwin.exe
)

