
QT       += 

INCLUDEPATH+= \
            $$PWD \
            $$PWD/include/ \


HEADERS += \
    $$PWD/ListenTick.h \
    $$PWD/../utils.h \
    $$PWD/TestTick.h

SOURCES += \
    $$PWD/../ListenTick.cpp \
    $$PWD/../utils.c \
    $$PWD/../TestTick.cpp

INCLUDEPATH += $$PWD/../../../rabbitmq-c/include

win32: LIBS += -L$$PWD/../../../rabbitmq-c/lib/win32 -lrabbitmq.4
unix:!macx: LIBS += -L$$PWD/../../../rabbitmq-c/lib -lrabbitmq

#linux       sudo apt-get install librabbitmq-dev

