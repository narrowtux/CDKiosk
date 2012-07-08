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

SOURCES += src/filter/authorfilter.cpp \
			src/filter/datefilter.cpp \
			src/filter/filter.cpp \
			src/filter/groupfilter.cpp \
			src/gui/administrationwindow.cpp \
			src/gui/mainwindow.cpp \
			src/gui/speecheditdialog.cpp \
			src/gui/cddisplaywidget.cpp \
			src/jobmanager/abstracttask.cpp \
			src/jobmanager/job.cpp \
			src/jobmanager/jobmanager.cpp \
			src/jobmanager/jobmanagermac.cpp \
			src/jobmanager/jobmanagersimulator.cpp \
			src/main.cpp \
			src/speech/speech.cpp \
			src/speech/speechmanager.cpp \
			src/speech/speechmodel.cpp \
    src/gui/paintutils.cpp \
    src/gui/databaseentrydialog.cpp

HEADERS  += src/filter/authorfilter.h \
			src/filter/datefilter.h \
			src/filter/filter.h \
			src/filter/groupfilter.h \
			src/gui/administrationwindow.h \
			src/gui/mainwindow.h \
			src/gui/speecheditdialog.h \
			src/gui/cddisplaywidget.h \
			src/jobmanager/abstracttask.h \
			src/jobmanager/job.h \
			src/jobmanager/jobmanager.h \
			src/jobmanager/jobmanagermac.h \
			src/jobmanager/jobmanagersimulator.h \
			src/speech/speech.h \
			src/speech/speechmanager.h \
			src/speech/speechmodel.h \
    src/gui/paintutils.h \
    src/gui/databaseentrydialog.h \
    src/utils/utils.h

FORMS    += src/gui/administrationwindow.ui \
			src/gui/mainwindow.ui \
			src/gui/speecheditdialog.ui \ 
    src/gui/databaseentrydialog.ui

RESOURCES += \
    res/res.qrc

OTHER_FILES += \
    README.md

TRANSLATIONS += \
	cdkiosk-de_DE.ts
