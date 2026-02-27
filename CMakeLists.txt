cmake_minimum_required(VERSION 3.21)

project(TestQxOrmSuper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Sql Gui Widgets)

# QxOrm (from environment)
set(QXORM_ROOT $ENV{QXORM_ROOT} CACHE PATH "Path to QxOrm")
if (NOT QXORM_ROOT)
    message(FATAL_ERROR "QXORM_ROOT environment variable is not set")
endif()

include("${QXORM_ROOT}/QxOrm.cmake")

# Subprojects
add_subdirectory(cpp_model)
add_subdirectory(cpp_view_model)
add_subdirectory(qtApp)