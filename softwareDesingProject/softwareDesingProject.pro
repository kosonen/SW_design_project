QT += quick charts widgets core xml

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        controller.cpp \
        datacontainer.cpp \
        datafetcher.cpp \
        fingriddatasource.cpp \
        fmidatasource.cpp \
        main.cpp \
        model.cpp \
        savemanager.cpp \
        settings.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    controller.h \
    datacontainer.h \
    datafetcher.h \
    defines.h \
    fingriddatasource.h \
    fmidatasource.h \
    idatasource.h \
    isaveobject.h \
    model.h \
    savemanager.h \
    settings.h
