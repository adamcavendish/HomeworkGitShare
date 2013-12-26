#include "qtquick2controlsapplicationviewer.h"
#include "sqlmanager.hpp"
// Qt5
#include <QtQml>
#include <QQmlEngine>

int main(int argc, char *argv[])
{
    Application app(argc, argv);
    qmlRegisterType<SqlManager>("Logics", 1, 0, "SqlManager");

    QtQuick2ControlsApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/CourseSelectionAndGradeManagementSystem/main.qml"));
    viewer.show();

    return app.exec();
}
