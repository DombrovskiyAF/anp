TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt

HEADERS += \
    anpstatisticalcalc.h

SOURCES += main.cpp \
    anpstatisticalcalc.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../anp/release/ -lanp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../anp/debug/ -lanp

INCLUDEPATH += $$PWD/../../anp
DEPENDPATH += $$PWD/../../anp

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../anp/release/libanp.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../anp/debug/libanp.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../anp/release/anp.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../anp/debug/anp.lib
