# Specify Qt modules
QT       += core gui

# Add widgets module for Qt 5 and higher
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Use C++17 standard
CONFIG += c++17

# Uncomment to disable deprecated APIs before Qt 6.0 (optional)
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Source files
SOURCES += \
    adddialog.cpp \
    main.cpp \
    mainwindow.cpp \
    searchdialog.cpp

# Header files
HEADERS += \
    adddialog.h \
    mainwindow.h \
    searchdialog.h

# UI form files
FORMS += \
    adddialog.ui \
    mainwindow.ui \
    searchdialog.ui

# Intermediate directories for generated files
UI_DIR = ./ui
MOC_DIR = ./moc
OBJECTS_DIR = ./obj
RCC_DIR = ./rcc

# Default rules for deployment (platform-specific)
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
