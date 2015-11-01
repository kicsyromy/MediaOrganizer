find_package(PkgConfig)
pkg_search_module(GOBJECT REQUIRED gobject-2.0>=2.32.4)
pkg_search_module(GLIB2   REQUIRED glib-2.0>=2.32.4)

set(PKG_CONFIG_REQUIRES "${PKG_CONFIG_REQUIRES} gobject-2.0")
set(PKG_CONFIG_REQUIRES "${PKG_CONFIG_REQUIRES} glib-2.0")

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    pkg_search_module(LIBVLC  REQUIRED libvlc>=2.0.8)

    set(LIBMO "${MediaOrganizer_BINARY_DIR}/libmo.so")
    set(PKG_CONFIG_REQUIRES "${PKG_CONFIG_REQUIRES} libvlc")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(LIBVLC_INCLUDE_DIRS "${MediaOrganizer_SOURCE_DIR}/osx/include")
    set(LIBVLC_LIBRARIES "${MediaOrganizer_SOURCE_DIR}/osx/lib/libvlc.dylib")

    set(LIBMO "${MediaOrganizer_BINARY_DIR}/libmo.dylib")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(ProductVersion_DIR  "${MediaOrganizer_SOURCE_DIR}/cmake")
    set(TargetArch_DIR  "${MediaOrganizer_SOURCE_DIR}/cmake")

    find_package(TargetArch)
    target_architecture(ARCH)
    if(${ARCH} MATCHES "x86_64")
        set(LIB_PATH "${MediaOrganizer_SOURCE_DIR}/windows/lib/x64")
    else(${ARCH} MATCHES "x86_64")
        set(LIB_PATH "${MediaOrganizer_SOURCE_DIR}/windows/lib/win32")
    endif(${ARCH} MATCHES "x86_64")

    find_package(ProductVersion)
    generate_product_version(
        PROJECT_INFORMATION
        NAME "Media Organizer"
        ICON "${MediaOrganizer_SOURCE_DIR}/windows/project.ico"
        VERSION_MAJOR ${MediaOrganizer_VERSION_MAJOR}
        VERSION_MINOR ${MediaOrganizer_VERSION_MINOR}
        VERSION_PATCH ${MediaOrganizer_VERSION_PATCH}
        VERSION_REVISION 0
        COMPANY_NAME "Romeo Calota"
    )

    set(LIBVLC_INCLUDE_DIRS "${MediaOrganizer_SOURCE_DIR}/windows/include")
    set(LIBVLC_LIBRARIES "${LIB_PATH}/libvlc.dll")

    set(LIBMO "${MediaOrganizer_BINARY_DIR}/libmo.dll")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
