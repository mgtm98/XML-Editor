QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controllers/editorcontroller.cpp \
    Controllers/guiController.cpp \
    Controllers/xmlcontroller.cpp \
    GUI/settings.cpp \
    Highlighter/highlighter.cpp \
    Highlighter/htmlhighlighter.cpp \
    GUI/xml_Editor.cpp \
    Highlighter/xmlHighlighter.cpp \
    main.cpp \
    GUI/editor.cpp \
    GUI/directoryviewer.cpp \
    Highlighter/pythonhighlighter.cpp

HEADERS += \
    Controllers/editorcontroller.h \
    Controllers/guiController.h \
    Controllers/xmlcontroller.h \
    GUI/settings.h \
    Highlighter/highlighter.h \
    Highlighter/htmlHighlighter.h \
    GUI/editor.h \
    GUI/directoryviewer.h \
    Highlighter/pythonHighlighter.h \
    GUI/xml_Editor.h \
    Highlighter/xmlHighlighter.h

RESOURCES += \
    resources.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
