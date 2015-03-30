# -------------------------------------------------
# Project created by QtCreator 2010-04-21T11:25:14
# -------------------------------------------------
TARGET = BomberMan
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
RC_FILE -= ressource.rc
SOURCES += main.cpp \
    case.cpp \
    partie.cpp \
    partiegui.cpp \
    bombermanslots.cpp \
    bomberman.cpp \
    joueur.cpp \
    bombe.cpp \
    menuprincipalgui.cpp \
    flamme.cpp \
    bombeexplosionthread.cpp \
    casedestructionthread.cpp \
    bombermanmortthread.cpp \
    bonus.cpp
HEADERS += case.h \
    partie.h \
    partiegui.h \
    bombermanslots.h \
    bomberman.h \
    joueur.h \
    bombe.h \
    menuprincipalgui.h \
    flamme.h \
    bombeexplosionthread.h \
    casedestructionthread.h \
    bombermanmortthread.h \
    bonus.h
OTHER_FILES += ressource.rc
