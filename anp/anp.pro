#-------------------------------------------------
#
# Project created by QtCreator 2018-06-08T08:36:47
#
#-------------------------------------------------

QT       -= core gui

TARGET = anp
TEMPLATE = lib
CONFIG += staticlib

SOURCES += anp.cpp \
    ip.cpp \
    crc.cpp \
    anppdu.cpp \
    anppdusequence.cpp

HEADERS += anp.h \
    anpglobals.h \
    ip.h \
    crc.h \
    file_formats.h \
    anppdu.h \
    anppdusequence.h
