# specify the manifest file, this file is required for click
# packaging and for the IDE to create runconfigurations
UBUNTU_MANIFEST_FILE = manifest.json.in

# specify translation domain, this must be equal with the
# app name in the manifest file
UBUNTU_TRANSLATION_DOMAIN="guh-ubuntu.stuerz-simon"

# specify the source files that should be included into
# the translation file, from those files a translation
# template is created in po/template.pot, to create a
# translation copy the template to e.g. de.po and edit the sources
UBUNTU_TRANSLATION_SOURCES+= \
    $$files(*.qml,true) \
    $$files(*.js,true)  \
    $$files(*.cpp,true) \
    $$files(*.h,true)

# specifies all translations files and makes sure they are
# compiled and installed into the right place in the click package
UBUNTU_PO_FILES+=$$files(po/*.po)

TEMPLATE = app
TARGET = guh-ubutnu

load(ubuntu-click)

QT += qml quick websockets

QMAKE_CXXFLAGS += -Werror
CONFIG += c++11

HEADERS += backend/core.h \
           backend/upnpdiscovery.h \
           backend/upnpdiscoverymodel.h \
           backend/upnpdevice.h \
           backend/guhinterface.h \
    backend/vendor.h \
    backend/vendormodel.h \
    backend/jsontypes.h \
    backend/devicemanager.h

SOURCES += backend/main.cpp \
           backend/core.cpp \
           backend/upnpdiscovery.cpp \
           backend/upnpdiscoverymodel.cpp \
           backend/upnpdevice.cpp \
           backend/guhinterface.cpp \
    backend/vendor.cpp \
    backend/vendormodel.cpp \
    backend/jsontypes.cpp \
    backend/devicemanager.cpp

RESOURCES += app.qrc

# config files for click package
OTHER_FILES += guh-ubuntu.apparmor \
               guh-ubuntu.desktop \
               guh-ubuntu.png

# specify where the config files are installed to
config_files.path = /guh-ubuntu
config_files.files += $${OTHER_FILES}

target.path = $${UBUNTU_CLICK_BINARY_PATH}

INSTALLS += target config_files





