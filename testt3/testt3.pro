TEMPLATE = app
CONFIG += console
CONFIG += qt

INCLUDEPATH += /usr/local/include/opencv
INCLUDEPATH += /home/radek/Qt/5.0.2/Src/qtbase/src/widgets
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann
LIBS += -lopencv_nonfree

SOURCES += \
    ../mainwindow.cpp \
    ../main.cpp \
    ../robotvision.cpp

HEADERS += \
    ../mainwindow.h \
    ../robotvision.h

OTHER_FILES +=

FORMS += \
    ../mainwindow.ui

