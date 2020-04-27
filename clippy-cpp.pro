QT       += network core gui

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
#    Clippy/clippygif.cpp \
    Clippy/abstractclippystate.cpp \
    Clippy/clippystate.cpp \
    DictionaryBox/dictdatabase.cpp \
    DictionaryBox/dictfrontend.cpp \
    DictionaryBox/dicthttp.cpp \
    DictionaryBox/dictmain.cpp \
    DictionaryBox/dictresultpage.cpp \
    DictionaryBox/dictsearchingpage.cpp \
    DictionaryBox/dictstartpage.cpp \
    Clippy/clippymain.cpp \
    Clippy/clippywidget.cpp \
    canvas.cpp \
#    clippywidget.cpp \
    main.cpp \
    messagebox.cpp \
    pokedexbox.cpp

HEADERS += \
    Clippy/abstractclippystate.h \
#    Clippy/clippygif.h \
    Clippy/clippystate.h \
    DictionaryBox/dictdatabase.h \
    DictionaryBox/dictfrontend.h \
    DictionaryBox/dicthttp.h \
    DictionaryBox/dictmain.h \
    DictionaryBox/dictresultpage.h \
    DictionaryBox/dictsearchingpage.h \
    DictionaryBox/dictstartpage.h \
    Clippy/clippymain.h \
    Clippy/clippywidget.h \
    canvas.h \
#    clippywidget.h \
    messagebox.h \
    pokedexbox.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Clippy/animations.qrc
