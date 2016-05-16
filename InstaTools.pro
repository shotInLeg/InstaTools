#-------------------------------------------------
#
# Project created by QtCreator 2016-05-02T02:46:58
#
#-------------------------------------------------

QT       += core gui network webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InstaTools
TEMPLATE = app


SOURCES += main.cpp\
        instatools.cpp \
    instaauth.cpp \
    http_request/http_request.cpp \
    insta_api/insta_api.cpp \
    json/json.cpp \
    instatags.cpp \
    instarelat.cpp \
    instagenname.cpp \
    instamassauth.cpp

HEADERS  += instatools.h \
    http_request/http_request.h \
    insta_api/insta_api.h \
    json/json.h

FORMS    += instatools.ui
