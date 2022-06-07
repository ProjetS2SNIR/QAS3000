#-------------------------------------------------
#
# Project created by QtCreator 2022-04-20T14:13:08
#
#-------------------------------------------------

QT       += core gui sql # Insctructions nécessaire au fonctionnement de l'appli QT, on ajoute ici sql pour faire fonctionner les bibliothèques SQL de QT

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QAS3 # Nom du projet
TEMPLATE = app # Type de projet

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 # On travail en C++ version 11

SOURCES += \
        main.cpp \
        ihm.cpp # Fichiers .cpp avec les définitions et les appels des méthodes /attributs de l'interface

HEADERS += \
        ihm.h\ # Fichier .h avec les déclarations de la classe IHM

FORMS += \ 
    ihm.ui # Fichier .ui qui servent au visuel de l'application

LIBS += -Wall # Bibliothèques

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
