#ifndef SQLMANAGER_HPP
#define SQLMANAGER_HPP

// STL
#include <memory>
// Qt5
#include <QObject>
#include <QMessageBox>
#include <QtCore>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
// CourseSelectionAndGradeManagementSystem
#include "studentinfoobject.hpp"
#include "availcoursesobject.hpp"
#include "coursegradeobject.hpp"

class SqlManager : public QObject
{
    Q_OBJECT
public:
    explicit
    SqlManager(QObject *parent = 0);

    Q_INVOKABLE bool
    login(const QString & usr_name, const QString & password);

    Q_INVOKABLE QSqlError
    lastError() const;

    Q_INVOKABLE QString
    lastErrorString() const;

    Q_INVOKABLE QList<QObject *>
    getStudentInfo(const QString & user_name, const QString & password);

    Q_INVOKABLE QList<QObject *>
    getCourseGrade(const QString & user_name, const QString & password);
signals:

public slots:

private://members
    std::shared_ptr<QSqlDatabase> m_pdb;
    QSqlQuery m_query;
};

#endif // SQLMANAGER_HPP
