#include "sqlmanager.hpp"

SqlManager::SqlManager(QObject *parent) :
    QObject(parent),
    m_pdb(new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL")),
          [](QSqlDatabase * p) {
                p->close();
                delete p;
          }
    )
{
    m_pdb->setHostName("localhost");
    m_pdb->setDatabaseName("CourseSelectionAndGradeManagement");
}

bool SqlManager::login(const QString & usr_name, const QString & password)
{
    m_pdb->setUserName(usr_name);
    m_pdb->setPassword(password);
    if(!m_pdb->open()) {
        qDebug() << "Error opening database: "
            << m_pdb->lastError();
        return false;
    }//if
    return true;
}

QSqlError SqlManager::lastError() const
{
    return m_pdb->lastError();
}

QString SqlManager::lastErrorString() const
{
    return m_pdb->lastError().text();
}

QList<QObject *>
SqlManager::getStudentInfo(const QString & user_name, const QString & password)
{
    m_query.prepare("SELECT SNO, SNAME, GENDER, AGE, SDEPT "
                  "FROM Students WHERE LOGN = :logn AND PSWD = :pswd");
    m_query.bindValue(":logn", user_name);
    m_query.bindValue(":pswd", password);

    if(!m_query.exec()) {
        qDebug() << "SQL QUERY EXEC() FAILED: "
                 << m_pdb->lastError().text();
    }//if

    QList<QObject *> ret;
    while(m_query.next()) {
        auto sno = m_query.value(0).toString();
        auto sname = m_query.value(1).toString();
        auto gender = m_query.value(2).toString();
        auto age = m_query.value(3).toInt();
        auto sdept = m_query.value(4).toString();
        ret.append(new StudentInfoObject(sno, sname, gender, age, sdept));
    }//while

    return ret;
}

QList<QObject *>
SqlManager::getCourseGrade(const QString & user_name, const QString & password)
{
    m_query.prepare(
        "SELECT "
            "CourseGrades.CNO, Courses.CNAME, CourseGrades.GRADE "
        "FROM "
        "Courses, Students, CourseGrades "
        "WHERE "
        "CourseGrades.sno = Students.sno AND "
        "Courses.cno = CourseGrades.cno AND "
        "Students.LOGN = :logn AND "
        "Students.PSWD = :pswd;");
    m_query.bindValue(":logn", user_name);
    m_query.bindValue(":pswd", password);
    if(!m_query.exec()) {
        qDebug() << "SQL QUERY EXEC() FAILED: "
                 << m_pdb->lastError().text();
    }//if

    QList<QObject *> ret;
    while(m_query.next()) {
        auto cno = m_query.value(0).toString();
        auto sno = m_query.value(1).toString();
        auto grade = m_query.value(2).toInt();
        ret.append(new CourseGradeObject(cno, sno, grade));
    }//while

    return ret;
}

QList<QObject *>
SqlManager::getAvailCourses(const QString &user_name, const QString &password)
{
    m_query.prepare(
        "SELECT "
            "Courses.CNO, Courses.CNAME, Courses.CREDIT, Courses.CDEPT, Courses.TNAME "
        "FROM Courses WHERE Courses.cno NOT IN ("
            "SELECT "
                "CourseGrades.cno "
            "FROM CourseGrades, Students WHERE "
                "CourseGrades.sno = Students.SNO AND "
                "Students.LOGN = :logn AND "
                "Students.PSWD = :pswd);");
    m_query.bindValue(":logn", user_name);
    m_query.bindValue(":pswd", password);
    if(!m_query.exec()) {
        qDebug() << "SQL QUERY EXEC() FAILED: "
                 << m_pdb->lastError().text();
    }//if

    QList<QObject *> ret;
    while(m_query.next()) {
        auto cno = m_query.value(0).toString();
        auto cname = m_query.value(1).toString();
        auto credit = m_query.value(2).toInt();
        auto cdept = m_query.value(3).toString();
        auto tname = m_query.value(4).toString();
        ret.append(new AvailCoursesObject(cno, cname, credit, cdept, tname));
    }//while

    return ret;
}
