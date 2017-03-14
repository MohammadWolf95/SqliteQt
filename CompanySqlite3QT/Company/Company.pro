#-------------------------------------------------
#
# Project created by QtCreator 2017-02-09T14:27:22
#
#-------------------------------------------------

QT       += core gui\
            widgets uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Company
TEMPLATE = app

#Specify the path to the header files here
INCLUDEPATH += C:\\sqlite3\\include

win32: QMAKE_CXXFLAGS_RELEASE -= -Zc:strictStrings
win32: QMAKE_CFLAGS_RELEASE -= -Zc:strictStrings
win32: QMAKE_CFLAGS -= -Zc:strictStrings
win32: QMAKE_CXXFLAGS -= -Zc:strictStrings

#Here it is indicated that the project is created for 32, 64-bit
contains(QMAKE_HOST.arch, x86_64){
    CONFIG( debug, debug|release ) {
        #Specify here the paths to the libraries, 64 bit
        LIBS += -LC:\\sqlite3\\lib\\x64\
        -lsqlite3libd
    }
    else {
        LIBS += -LC:\\sqlite3\\lib\\x64\
        -lsqlite3lib
    }
}
else{
    CONFIG( debug, debug|release ) {
        #Specify here the paths to the libraries, 32 bit
        LIBS += -LC:\\sqlite3\\lib\\x86\
        -lsqlite3libd
    }
    else {
        LIBS += -LC:\\sqlite3\\lib\\x86\
        -lsqlite3lib
    }
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    company.cpp \
    editdb.cpp \
    addemployee.cpp \
    sqlcompany.cpp \
    singletonpath.cpp

HEADERS  += \
    company.h \
    editdb.h \
    addemployee.h \
    sqlcompany.h \
    str_switch.h \
    singletonpath.h

FORMS    += \
    editdb.ui \
    addemployee.ui

RESOURCES += \
    company.qrc

DISTFILES +=
