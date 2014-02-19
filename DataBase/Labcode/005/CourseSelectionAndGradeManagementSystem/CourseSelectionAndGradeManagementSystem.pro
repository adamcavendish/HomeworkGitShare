# Add more folders to ship with the application, here
folder_01.source = qml/CourseSelectionAndGradeManagementSystem
folder_01.target = qml
folder_02.source = qml/CourseSelectionAndGradeManagementSystem/contents
folder_02.target = qml
DEPLOYMENTFOLDERS = folder_01 folder_02

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    sqlmanager.cpp \
    studentinfoobject.cpp \
    availcoursesobject.cpp \
    coursegradeobject.cpp \
    selectedcoursesobject.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2controlsapplicationviewer/qtquick2controlsapplicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    sqlmanager.hpp \
    studentinfoobject.hpp \
    availcoursesobject.hpp \
    coursegradeobject.hpp \
    selectedcoursesobject.h


## Customize

QT += sql

CONFIG += c++11

RESOURCES += \
    resource.qrc

OTHER_FILES += \
    qml/CourseSelectionAndGradeManagementSystem/contents/StudentInfo.qml
