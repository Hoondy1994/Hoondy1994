QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# OpenCV 包含目录
INCLUDEPATH += I:/openlib/include

# OpenCV 的库目录
LIBS += -LI:/openlib/x64/mingw/bin \
        -lopencv_core452 \
        -lopencv_imgproc452 \
        -lopencv_highgui452 \
        -lopencv_ml452 \  # 使用 OpenCV 的 ml 模块
        -lopencv_imgcodecs452



SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui
