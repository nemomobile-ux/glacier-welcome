cmake_minimum_required(VERSION 3.6.0)

project(glacier-welcome
	VERSION 0.1
	DESCRIPTION "The welcome app for glacier ui")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INSTALL_PREFIX /usr)

include(FeatureSummary)
include(GNUInstallDirs)

set(QT_MIN_VERSION "5.11.0")

find_package(Qt5 COMPONENTS Gui Qml Quick DBus LinguistTools REQUIRED)
find_package(Glacier 0.8 COMPONENTS App REQUIRED)
find_package(Qt5QuickCompiler)

add_subdirectory(src)

# Translations
#file(GLOB TS_FILES translations/*.ts)
#qt5_add_translation(QM_FILES ${TS_FILES})
#add_custom_target(translations DEPENDS ${QM_FILES})
#add_dependencies(glacier-welcome translations)

install(FILES ${QM_FILES}
	DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/glacier-welcome/translations)
