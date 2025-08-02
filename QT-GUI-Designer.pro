# http://doc.qt.io/qt-5/qmake-variable-reference.html
CONFIG += console
QT += core widgets gui
DEFINES += QT_WIDGETS_LIB
#LIBS += 
INCLUDEPATH += .

HEADERS += paint.h \
           button.h \
           canvas.h \
           component.h \
           container.h \
           csvloader.h \
           csvwriter.h \
           jsonloader.h \
           jsonwriter.h \
           node.h \
           writer.h \
           loader.h \
           xmlwriter.h \
           xmlloader.h \
           stack.h \
           InvalidOperationException.h

SOURCES += paint.cpp \
           button.cpp \
           canvas.cpp \
           container.cpp \
           csvloader.cpp \
           csvwriter.cpp \
           jsonloader.cpp \
           jsonwriter.cpp \
           main.cpp \
           node.cpp \
           xmlwriter.cpp \
           xmlloader.cpp \
           stack.cpp
