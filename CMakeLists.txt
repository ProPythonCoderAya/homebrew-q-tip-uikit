cmake_minimum_required(VERSION 4.0)

project(QTipUIKit
    VERSION 0.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(QTip REQUIRED)
find_package(SDL3 REQUIRED)

include(GNUInstallDirs)

add_library(QTipUIKit STATIC
    include/UIObject.h
    include/Textbox.h
    src/Textbox.cpp
        include/UIKit.h
        src/UIKit.cpp
)

add_library(QTipUIKit::QTipUIKit ALIAS QTipUIKit)

target_include_directories(QTipUIKit
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(QTipUIKit
    PUBLIC
        QTip::QTip
    PRIVATE
        SDL3::SDL3
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/QTipUIKitConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/QTipUIKitConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QTipUIKit
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/QTipUIKitConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/QTipUIKitConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/QTipUIKitConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QTipUIKit
)

add_executable(QTipUIKitTest
    test.cpp
)

target_link_libraries(QTipUIKitTest PUBLIC
    QTipUIKit::QTipUIKit
)

install(
    TARGETS QTipUIKit
    EXPORT QTipUIKitTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT QTipUIKitTargets
    FILE QTipUIKitTargets.cmake
    NAMESPACE QTipUIKit::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QTipUIKit
)