TEMPLATE  = subdirs

SUBDIRS  += \
    src \
    src/dde-dock-plugins \
    src/pin_screenshots \
    src/cutout_screenshots


translations.path = /usr/share/deepin-screen-recorder/translations

isEmpty(TRANSLATIONS) {
     include(./translations.pri)
}
CONFIG += update_translations release_translations

CONFIG(update_translations) {
    isEmpty(lupdate):lupdate=lupdate
    system($$lupdate -no-obsolete -locations none $$_PRO_FILE_)
}
CONFIG(release_translations) {
    isEmpty(lrelease):lrelease=lrelease
    system($$lrelease $$_PRO_FILE_)
}


TRANSLATIONS_COMPILED = $$TRANSLATIONS
TRANSLATIONS_COMPILED ~= s/\.ts/.qm/g
translations.files = $$TRANSLATIONS_COMPILED


INSTALLS += translations
