#-------------------------------------------------
#
# Project created by QtCreator 2012-01-17T18:14:18
#
#-------------------------------------------------

QT       += core gui sql

TARGET = CDKiosk
TEMPLATE = app

#QMAKE_LFLAGS += -F/Library/Frameworks/ -m32
#QMAKE_CFLAGS += -m32
#QMAKE_CXXFLAGS += -m32

#LIBS += -framework as_storage
#LIBS += -framework JobManager
#LIBS += -framework JobProcessor
#LIBS += -framework PTRobot

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/speechmodel.cpp \
    src/speech.cpp \
    src/speechmanager.cpp \
    src/filter.cpp \
    src/datefilter.cpp \
    src/authorfilter.cpp \
    src/groupfilter.cpp \
    src/abstracttask.cpp \
    src/jobmanager.cpp \
    src/jobmanager/job.cpp \
    src/jobmanager/jobmanagermac.cpp \
    src/jobmanager/jobmanagersimulator.cpp \
    src/administrationwindow.cpp \
    speecheditdialog.cpp \
    cddisplaywidget.cpp

HEADERS  += src/mainwindow.h \
    src/speechmodel.h \
    src/speech.h \
    src/speechmanager.h \
    src/filter.h \
    src/datefilter.h \
    src/authorfilter.h \
    src/groupfilter.h \
    src/abstracttask.h \
    src/jobmanager.h \
    src/jobmanager/job.h \
    src/jobmanager/jobmanagermac.h \
    src/jobmanager/jobmanagersimulator.h \
    src/administrationwindow.h \
    speecheditdialog.h \
    cddisplaywidget.h

FORMS    += gui/mainwindow.ui \
    src/administrationwindow.ui \
    speecheditdialog.ui

RESOURCES += \
    res/res.qrc

OTHER_FILES += \
    README.md

TRANSLATIONS += \
	cdkiosk-de_DE.ts
