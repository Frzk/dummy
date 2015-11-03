# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = QSqlTableModel_Remorses

CONFIG += sailfishapp

QT += sql

SOURCES += src/QSqlTableModel_Remorses.cpp \
    src/MModel.cpp

OTHER_FILES += qml/QSqlTableModel_Remorses.qml \
    qml/cover/CoverPage.qml \
    rpm/QSqlTableModel_Remorses.changes.in \
    rpm/QSqlTableModel_Remorses.spec \
    rpm/QSqlTableModel_Remorses.yaml \
    translations/*.ts \
    QSqlTableModel_Remorses.desktop

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/QSqlTableModel_Remorses-de.ts

HEADERS += \
    src/MModel.h

