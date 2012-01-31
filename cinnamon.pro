QT += declarative opengl network

# Add more folders to ship with the application, here
folder_01.source = qml/cinnamon
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
CONFIG += qdeclarative-boostable

# Additional import path used to resolve Qml modules in Creator's code model
QML_IMPORT_PATH =


# Needs to be defined for Symbian
#DEFINES += NETWORKACCESS

symbian:TARGET.UID3 = 0xE1E0F350

# Define QMLJSDEBUGGER to enable basic debugging (setting breakpoints etc)
# Define QMLOBSERVER for advanced features (requires experimental QmlInspector plugin!)
#DEFINES += QMLJSDEBUGGER
#DEFINES += QMLOBSERVER

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += src/main.cpp \
    src/collectionminer.cpp \
    src/collection.cpp \
    src/item.cpp \
    src/itemmodel.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog

HEADERS += \
    src/collectionminer.h \
    src/collection.h \
    src/item.h \
    src/itemmodel.h

































contains(MEEGO_EDITION,harmattan) {
    desktopfile.files = $${TARGET}.desktop
    desktopfile.path = /usr/share/applications
    INSTALLS += desktopfile
}

contains(MEEGO_EDITION,harmattan) {
    icon.files = cinnamon.png
    icon.path = /usr/share/icons/hicolor/80x80/apps
    INSTALLS += icon
}
