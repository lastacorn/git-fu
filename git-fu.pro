DESTDIR = _output
OBJECTS_DIR = _output/.obj
MOC_DIR = _output/.moc
RCC_DIR = _output/.rcc
UI_DIR = _output/.ui

TEMPLATE = app
TARGET = git-fu
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += gitfu.h
FORMS += gitfu.ui
SOURCES += gitfu.cpp main.cpp
RESOURCES += gitfu.qrc
