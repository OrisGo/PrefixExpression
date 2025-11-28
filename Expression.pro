QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ExprStruct.cpp \
    calculatedialog.cpp \
    calculatewidget.cpp \
    compoundwidget.cpp \
    inputwidget.cpp \
    main.cpp \
    expression.cpp \
    showdialog.cpp \
    showwidget.cpp

HEADERS += \
    ExprStruct.h \
    calculatedialog.h \
    calculatewidget.h \
    compoundwidget.h \
    expression.h \
    inputwidget.h \
    showdialog.h \
    showwidget.h

FORMS += \
    calculatewidget.ui \
    compoundwidget.ui \
    evaluatedialog.ui \
    expression.ui \
    inputwidget.ui \
    showdialog.ui \
    showwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
