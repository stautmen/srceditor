TEMPLATE = app

QT += qml quick declarative

SOURCES += main.cpp \
    chessman.cpp \
    chessgame.cpp

RESOURCES += qml.qrc

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    chessman.h \
    chessgame.h
