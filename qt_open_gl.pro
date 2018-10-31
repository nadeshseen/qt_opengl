#-------------------------------------------------
#
# Project created by QtCreator 2018-08-25T11:12:07
#
#-------------------------------------------------

QT       += core gui widgets opengl

TARGET = qt_open_gl
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

#LIBS += -lglut -lGLU -lGL

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    gl_widget.cpp \
    object.cpp \
    line.cpp \
    circle.cpp \
    thickness_dialog.cpp \
    pattern_dialog.cpp \
    scale_dialog.cpp \
    rotate_dialog.cpp \
    translate_dialog.cpp \
    ellipse.cpp \
    polygon.cpp \
    region.cpp \
    special_polygon.cpp

HEADERS += \
        mainwindow.h \
    gl_widget.h \
    object.h \
    line.h \
    circle.h \
    thickness_dialog.h \
    pattern_dialog.h \
    scale_dialog.h \
    rotate_dialog.h \
    classes_header.h \
    translate_dialog.h \
    ellipse.h \
    polygon.h \
    region.h \
    special_polygon.h

FORMS += \
        mainwindow.ui \
    thickness_dialog.ui \
    pattern_dialog.ui \
    scale_dialog.ui \
    rotate_dialog.ui \
    translate_dialog.ui \
    special_polygon.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    opengl_resource.qrc
