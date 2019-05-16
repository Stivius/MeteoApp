QT += testlib
QT -= gui
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

CONFIG += c++17

#QMAKE_CXXFLAGS += /std:c++17

TEMPLATE = app

SOURCES +=  tst_dataparsertest.cpp \
    ../../../WeatherPrototype/bluetooth/model/ChunkedDataParser.cpp
