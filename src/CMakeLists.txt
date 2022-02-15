set(SRC main.cpp
    welcome.cpp
    welcome.h)

qtquick_compiler_add_resources(RESOURCES qml/glacier-welcome.qrc)

add_executable(glacier-welcome ${SRC} ${RESOURCES})

target_link_libraries(glacier-welcome
	Qt5::Gui
	Qt5::Qml
	Qt5::Quick
        Qt5::DBus
	Glacier::App)

install(TARGETS glacier-welcome RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})
