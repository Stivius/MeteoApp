TEMPLATE = subdirs

SUBDIRS += \
    BluetoothTests

CONFIG += c++17

QMAKE_CXXFLAGS += /std:c++17
#Uncomment for passing MSVC build
