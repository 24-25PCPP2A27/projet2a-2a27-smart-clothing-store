QT       += core gui sql network widgets serialport quick qml

QT +=  charts printsupport  location positioning quickwidgets






greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 openssl

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    arduinodialog.cpp \
    connection.cpp \
    fournisseurs.cpp \
    logviewer.cpp \
    mail.cpp \
    main.cpp \
    mainFournisseur.cpp \
    smtp.cpp

HEADERS += \
    arduino.h \
    arduinodialog.h \
    connection.h \
    fournisseurs.h \
    logviewer.h \
    mail.h \
    mainFournisseur.h \
    smtp.h

FORMS += \
    arduinodialog.ui \
    mail.ui \
    mainFournisseur.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    ressource.qrc
