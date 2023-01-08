cmake_minimum_required(VERSION 3.1)
# -------------- Plugin Config ---------------
execute_process(COMMAND node -p "require('@nodegui/nodegui/plugin').CMAKE_HELPER_FILE"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE NODEGUI_PLUGIN_CMAKE_HELPER
)
string(REPLACE "\n" "" NODEGUI_PLUGIN_CMAKE_HELPER ${NODEGUI_PLUGIN_CMAKE_HELPER})
string(REPLACE "\"" "" NODEGUI_PLUGIN_CMAKE_HELPER ${NODEGUI_PLUGIN_CMAKE_HELPER})
include("${NODEGUI_PLUGIN_CMAKE_HELPER}")

# -------------- User Config ---------------
set(PLUGIN_ADDON_NAME "nodegui_plugin_qhotkey")

project(${PLUGIN_ADDON_NAME})

add_library(${PLUGIN_ADDON_NAME} SHARED
    "${CMAKE_JS_SRC}"
    "${PROJECT_SOURCE_DIR}/src/cpp/main.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/QHotkey_wrap.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/nhotkey.hpp"
    "${PROJECT_SOURCE_DIR}/QHotkey-1.5.0/QHotkey/qhotkey.cpp"
)

target_include_directories(${PLUGIN_ADDON_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/QHotkey-1.5.0/QHotkey")

AddPluginConfig(${PLUGIN_ADDON_NAME})

if (UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(${PLUGIN_ADDON_NAME} PRIVATE ${X11_LIBRARIES})
    target_sources(${PLUGIN_ADDON_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/QHotkey-1.5.0/QHotkey/qhotkey_x11.cpp")

    # Make the output shared library's RPATH relative so that it can
    # find the other Qt and NodeGui libs even if the dir is moved.

    # NodeGui and qode are assumed to be in the same node_modules directory as nodegui-plugin-qhotkey.
    set_target_properties(${PLUGIN_ADDON_NAME} PROPERTIES
        INSTALL_RPATH "\$ORIGIN/../../../@nodegui/nodegui/miniqt/6.4.1/gcc_64/lib:\$ORIGIN/../../../@nodegui/nodegui/build/Release")
    set_target_properties(${PLUGIN_ADDON_NAME} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
endif()

if (APPLE)
    find_library(CARBON_LIBRARY Carbon)
    mark_as_advanced(CARBON_LIBRARY)
    target_link_libraries(${PLUGIN_ADDON_NAME} PRIVATE ${CARBON_LIBRARY})
    target_sources(${PLUGIN_ADDON_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/QHotkey-1.5.0/QHotkey/qhotkey_mac.cpp")

    set_target_properties(${PLUGIN_ADDON_NAME} PROPERTIES
        INSTALL_RPATH "@loader_path/../../../@nodegui/nodegui/miniqt/6.4.1/macos/lib:@loader_path/../../../@nodegui/nodegui/build/Release")
    set_target_properties(${PLUGIN_ADDON_NAME} PROPERTIES SKIP_BUILD_RPATH FALSE)
    set_target_properties(${PLUGIN_ADDON_NAME} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
endif()

if(WIN32)
    target_sources(${PLUGIN_ADDON_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/QHotkey-1.5.0/QHotkey/qhotkey_win.cpp")
endif()

target_include_directories(${PLUGIN_ADDON_NAME} PRIVATE
    "${CMAKE_JS_INC}"
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/src/cpp"
)
target_link_libraries(${PLUGIN_ADDON_NAME} PRIVATE
    "${CMAKE_JS_LIB}"
     Qt6::Gui
     Qt6::Widgets
)
