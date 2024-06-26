QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/page_login.cpp \
    src/stu_sql.cpp \

HEADERS += \
    head/mainwindow.h \
    head/page_login.h \
    head/stu_sql.h \

FORMS += \
    ui/mainwindow.ui \
    ui/page_login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image/res.qrc \

DISTFILES += \
    image/login.jpg \
    image/user.jpg \
    ohter/stuqss.css
