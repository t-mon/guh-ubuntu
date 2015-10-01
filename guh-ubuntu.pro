# specify the manifest file, this file is required for click
# packaging and for the IDE to create runconfigurations
UBUNTU_MANIFEST_FILE=manifest.json.in

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
TARGET = guh-ubuntu

load(ubuntu-click)

QT += qml quick websockets

QMAKE_CXXFLAGS += -Werror
CONFIG += c++11

HEADERS += backend/core.h \
           backend/guhinterface.h \
           backend/devicemanager.h \
           backend/discovery/upnpdiscovery.h \
           backend/discovery/upnpdiscoverymodel.h \
           backend/discovery/upnpdevice.h \
           backend/types/vendor.h \
           backend/types/vendormodel.h \
           backend/jsonrpc/jsontypes.h \
           backend/jsonrpc/jsonrpcclient.h \
           backend/types/deviceclass.h \
           backend/jsonrpc/devicehandler.h \
           backend/jsonrpc/jsonhandler.h

SOURCES += backend/main.cpp \
           backend/core.cpp \
           backend/guhinterface.cpp \
           backend/devicemanager.cpp \
           backend/discovery/upnpdiscovery.cpp \
           backend/discovery/upnpdiscoverymodel.cpp \
           backend/discovery/upnpdevice.cpp \
           backend/types/vendor.cpp \
           backend/types/vendormodel.cpp \
           backend/jsonrpc/jsontypes.cpp \
           backend/jsonrpc/jsonrpcclient.cpp \
           backend/types/deviceclass.cpp \
           backend/jsonrpc/devicehandler.cpp \
           backend/jsonrpc/jsonhandler.cpp

RESOURCES += app.qrc

# config files for click package
OTHER_FILES += guh-ubuntu.apparmor \
               guh-ubuntu.desktop \
               guh-ubuntu.png

# specify where the config files are installed to
configs.path = /guh-ubuntu
configs.files += $${OTHER_FILES}

target.path = $${UBUNTU_CLICK_BINARY_PATH}

INSTALLS += target configs





