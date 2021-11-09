# Automatically generated by scripts/boost/generate-ports.ps1

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO boostorg/xpressive
    REF boost-1.77.0
    SHA512 79fcb6050c770590b0756d6cc2980bf6c8a4824affb56e41e3cbbefadcf1b5bfb04476691ebda57c61c8511eb2a50ee9618fdd8f8f75a7617ddabbda551531b1
    HEAD_REF master
)

include(${CURRENT_INSTALLED_DIR}/share/boost-vcpkg-helpers/boost-modular-headers.cmake)
boost_modular_headers(SOURCE_PATH ${SOURCE_PATH})