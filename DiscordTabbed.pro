QT       += core gui webenginewidgets webenginecore

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
RC_ICONS = resources/icon.ico

SOURCES += \
    src/PreferencesForm.cpp \
    src/ViewForm.cpp \
    src/main.cpp \
    src/DiscordTabbed.cpp \
    src/DiscordTabbedPage.cpp

HEADERS += \
    src/PreferencesForm.h \
    src/DiscordTabbed.h \
    src/DiscordTabbedPage.h \
    src/ViewForm.h

FORMS += \
    src/PreferencesForm.ui \
    src/DiscordTabbed.ui \
    src/ViewForm.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
