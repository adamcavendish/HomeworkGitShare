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

class SqlManager : public QObject
{
    Q_OBJECT
public:
    explicit
    SqlManager(QObject *parent = 0);

    Q_INVOKABLE bool
    login(const QString & usr_name, const QString & password);

    Q_INVOKABLE QString
    lastErrorString() const;

    Q_INVOKABLE void
    setUsername(const QString & usrname)
    { m_username = usrname; }

    Q_INVOKABLE void
    setPassword(const QString & pswd)
    { m_password = pswd; }

    Q_INVOKABLE QList<QObject *>
    getStudentInfo();

    Q_INVOKABLE QList<QObject *>
    getCourseGrade();

    Q_INVOKABLE QList<QObject *>
    getAvailCourses();

    Q_INVOKABLE QList<QObject *>
    getSelectedCourses();

    Q_INVOKABLE QString
    getCourseName(const QString & cno);

    Q_INVOKABLE QString
    getTeacherName(const QString & cno);

    Q_INVOKABLE QList<QObject *>
    getAllCourseInfo();

    Q_INVOKABLE bool
    selectCourse(const QString & cno);

    Q_INVOKABLE bool
    dropCourse(const QString & cno);

    Q_INVOKABLE QList<QObject *>
    getCourseStudentsGrade(const QString & cno);

    Q_INVOKABLE void
    updateGrade(const QString & sno, const QString & cno, int grade);

    Q_INVOKABLE QList<QObject *>
    getAllUsers();

    Q_INVOKABLE void
    addUser(const QString & sno, const QString & sname, const QString & gender,
            int age, const QString & sdept);

    Q_INVOKABLE void
    dropUser(const QString & sno);
signals:

public slots:

private://members
    std::shared_ptr<QSqlDatabase> m_pdb;
    QSqlQuery m_query;
    QString m_username;
    QString m_password;
};

#endif // SQLMANAGER_HPP
