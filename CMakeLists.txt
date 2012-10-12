# CMake build script for the git-fu project
#
# Building (out of source build):
# > mkdir _build && cd _build
# > cmake ..
# > cmake --build .

PROJECT(git-fu)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
FIND_PACKAGE(Qt4 REQUIRED)

SET(gitfu_SOURCES main.cpp gitfu.cpp)
SET(gitfu_HEADERS gitfu.h)
SET(gitfu_UI gitfu.ui)
SET(gitfu_RESOURCES gitfu.qrc)

QT4_WRAP_CPP(gitfu_HEADERS_MOC ${gitfu_HEADERS})
QT4_WRAP_UI(gitfu_UI_HEADERS ${gitfu_UI})
QT4_ADD_RESOURCES(gitfu_RESOURCES_RCC ${gitfu_RESOURCES})
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

# Get rid of the console for Win32/Mac
if(WIN32)
	set(GUI_TYPE WIN32)
endif(WIN32)
if(APPLE)
	set(GUI_TYPE MACOSX_BUNDLE)
endif(APPLE)

ADD_EXECUTABLE(git-fu
	${GUI_TYPE}
	${gitfu_SOURCES} 
	${gitfu_HEADERS_MOC}
	${gitfu_UI_HEADERS}
	${gitfu_RESOURCES_RCC}
	)
TARGET_LINK_LIBRARIES(git-fu ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})