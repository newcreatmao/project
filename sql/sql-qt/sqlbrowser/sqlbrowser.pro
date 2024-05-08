TEMPLATE        = app
TARGET          = sqlbrowser

QT              += sql widgets
requires(qtConfig(tableview))

HEADERS         = \
    include/browser.h \
    include/connectionwidget.h \
    include/qsqlconnectiondialog.h
SOURCES         = \
    src/browser.cpp \
    src/connectionwidget.cpp \
    src/main.cpp \
    src/qsqlconnectiondialog.cpp

FORMS           = \
    ui/browserwidget.ui \
    ui/qsqlconnectiondialog.ui
build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

# install
target.path = $$[QT_INSTALL_EXAMPLES]/sql/sqlbrowser
INSTALLS += target
