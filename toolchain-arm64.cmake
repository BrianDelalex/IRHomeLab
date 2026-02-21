# Target platform
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Cross compilers
set(CMAKE_C_COMPILER   /usr/bin/aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/aarch64-linux-gnu-g++)

# Sysroot
set(CMAKE_SYSROOT /opt/sysroots/debian-fs)

# Tell CMake to search inside the sysroot only
set(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})

set(CMAKE_C_FLAGS "--sysroot=${CMAKE_SYSROOT}" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_FLAGS "--sysroot=${CMAKE_SYSROOT}" CACHE INTERNAL "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "--sysroot=${CMAKE_SYSROOT}" CACHE INTERNAL "" FORCE)
set(CMAKE_C_LINK_FLAGS "--sysroot=${CMAKE_SYSROOT}" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_LINK_FLAGS "--sysroot=${CMAKE_SYSROOT}" CACHE INTERNAL "" FORCE)

set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} \
     -L${CMAKE_SYSROOT}/lib/aarch64-linux-gnu \
     -L${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu \
     -Wl,-rpath-link,${CMAKE_SYSROOT}/lib/aarch64-linux-gnu \
     -Wl,-rpath-link,${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu"
)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)  # use host tools
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)   # use target libs
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)   # use target headers
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)   # use target packages