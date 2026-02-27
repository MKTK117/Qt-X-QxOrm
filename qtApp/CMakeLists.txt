cmake_minimum_required(VERSION 3.16)

project(qtApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Core Gui Widgets Sql)
qt_standard_project_setup(REQUIRES 6.8)

include_directories(
    "../cpp_model/include"
    "../cpp_view_model/include"
    "${QXORM_ROOT}/include"
)

qt_add_executable(appqtApp
    main.cpp
    appController.cpp
    projectListModel.cpp
    userListModel.cpp
)



qt_add_qml_module(appqtApp
    URI qtApp
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES QSingleton.h
        SOURCES AppController.h AppController.cpp
)

set_target_properties(appqtApp PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appqtApp
    PRIVATE
        Qt6::Quick
        Qt6::Core
        Qt6::Gui
        Qt6::Sql
        TestQxOrm
        TestQxOrmModel
        QxOrm
)

target_include_directories(appqtApp
    PRIVATE
        ${CMAKE_SOURCE_DIR}/cpp_view_model/include
        ${CMAKE_SOURCE_DIR}/cpp_view_model/custom/include
)

qt_finalize_executable(appqtApp)

add_custom_command(TARGET appqtApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:TestQxOrm>
        $<TARGET_FILE:TestQxOrmModel>
        $<TARGET_FILE:QxOrm>
        $<TARGET_FILE_DIR:appqtApp>
)