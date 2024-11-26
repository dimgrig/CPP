QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -Wno-deprecated #-std=c++2a

DISTFILES += \
    qmake-destination-path.pri \
    qmake-nc3-elmo-mbc-version.pri \
    qmake-target-platform.pri

include(qmake-target-platform.pri)
include(qmake-destination-path.pri)

DEFINES += NOCRYPT #fix DOMDocument ambigious with qcustomplot
DEFINES += NOUSER

SOURCES += \
    Adapter.cpp \
    Config.cpp \
    DebugDecorator.cpp \
    Decorator.cpp \
    Logger.cpp \
    Profiler.cpp \
    Sleeper.cpp \
    SmartPtr.cpp \
    Switches.cpp \
    Value.cpp \
    VariantVisitor.cpp \
    Visitor.cpp \
    VisitorSerializer.cpp \
    aqp.cpp \
    enum_macro.cpp \
    enums.cpp \
    functions.cpp \
    macroses.cpp \
    main.cpp \
    mainwindow.cpp \
    mixins.cpp \
    qcustomplot.cpp \
    templates.cpp \
    templates_cout.cpp

HEADERS += \
    Adapter.h \
    Config.h \
    DebugDecorator.h \
    Decorator.h \
    Logger.h \
    Profiler.h \
    Sleeper.h \
    SmartPtr.h \
    Switches.h \
    TestRunner.h \
    Value.h \
    VariantVisitor.h \
    Visitor.h \
    VisitorSerializer.h \
    aqp.h \
    enum_macro.h \
    enums.h \
    functions.h \
    icons.h \
    interfaces.h \
    macroses.h \
    mainwindow.h \
    mixins.h \
    qcustomplot.h \
    templates.h \
    templates_cout.h

FORMS += \
    uis/Auth.ui \
    uis/User.ui \
    uis/Users.ui \
    uis/about.ui \
    uis/mainwindow.ui \
    uis/settings.ui

RESOURCES += \
    resources/resources.qrc

TRANSLATIONS += widgets.ts

TRANSLATIONS += QtLanguage_ru.ts
CODECFORSRC     = UTF-8

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

DESTDIR = $$PWD/../$${TARGET}-binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/../$${TARGET}-build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/../$${TARGET}-build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/../$${TARGET}-build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/../$${TARGET}-build/$$DESTINATION_PATH/.ui




