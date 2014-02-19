#include "sqlmanager.hpp"
#include "selectedcoursesobject.h"

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
SqlManager::getStudentInfo()
{
    m_query.prepare("SELECT SNO, SNAME, GENDER, AGE, SDEPT "
                  "FROM Students WHERE LOGN = :logn AND PSWD = :pswd");
    m_query.bindValue(":logn", m_username);
    m_query.bindValue(":pswd", m_password);

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
SqlManager::getCourseGrade()
{
    m_query.prepare(
        "SELECT "
            "CourseGrades.CNO, Courses.CNAME, CourseGrades.GRADE "
        "FROM "
            "Courses, Students, CourseGrades "
        "WHERE "
            "CourseGrades.sno = Students.sno AND "
            "Courses.cno = CourseGrades.cno AND "
            "CourseGrades.GRADE IS NOT NULL AND "
            "Students.LOGN = :logn AND "
            "Students.PSWD = :pswd;");
    m_query.bindValue(":logn", m_username);
    m_query.bindValue(":pswd", m_password);
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
SqlManager::getAvailCourses()
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
    m_query.bindValue(":logn", m_username);
    m_query.bindValue(":pswd", m_password);
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

QList<QObject *>
SqlManager::getSelectedCourses()
{
    m_query.prepare(
        "SELECT "
            "Courses.CNO, Courses.CNAME, Courses.CREDIT, Courses.CDEPT, Courses.TNAME "
        "FROM Courses, CourseGrades, Students WHERE "
            "Courses.CNO = CourseGrades.CNO AND "
            "Students.SNO = CourseGrades.SNO AND "
            "Students.LOGN = :logn AND "
            "Students.PSWD = :pswd AND "
            "CourseGrades.GRADE IS NULL;");
    m_query.bindValue(":logn", m_username);
    m_query.bindValue(":pswd", m_password);
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
        ret.append(new SelectedCoursesObject(cno, cname, credit, cdept, tname));
    }//while

    return ret;
}

QString SqlManager::getCourseName(const QString &cno)
{
    m_query.prepare(
        "SELECT CNAME FROM Courses WHERE "
            "CNO = :cno;");
    m_query.bindValue(":cno", cno);
    if(!m_query.exec()) {
        qDebug() << "SQL QUERY EXEC() FAILED: "
                 << m_pdb->lastError().text();
        return QString();
    }//if
    if(m_query.size() > 0) {
        m_query.next();
        return m_query.value(0).toString();
    }//if
    return QString();
}

QString SqlManager::getTeacherName(const QString &cno)
{
    m_query.prepare(
        "SELECT TNAME FROM Courses WHERE "
            "CNO = :cno;");
    m_query.bindValue(":cno", cno);
    if(!m_query.exec()) {
        qDebug() << "SQL QUERY EXEC() FAILED: "
                 << m_pdb->lastError().text();
        return QString();
    }//if
    if(m_query.size() > 0) {
        m_query.next();
        return m_query.value(0).toString();
    }//if
    return QString();
}

bool
SqlManager::selectCourse(const QString & cno)
{
    m_query.prepare(
        "INSERT INTO CourseGrades(SNO, CNO) VALUES "
        "(:sno, :cno);");
    m_query.bindValue(":sno", m_username);
    m_query.bindValue(":cno", cno);
    if(!m_query.exec()) {
        qDebug() << "SQL QUERY EXEC() FAILED: "
                 << " Select Course Failed. You've already selected the course.";
        return false;
    }//if
    return true;
}

bool SqlManager::dropCourse(const QString &cno)
{
    m_query.prepare(
        "DELETE FROM CourseGrades WHERE "
            "SNO = :sno AND "
            "CNO = :cno AND "
            "GRADE IS NULL;");
    m_query.bindValue(":sno", m_username);
    m_query.bindValue(":cno", cno);
    if(!m_query.exec()) {
        qDebug() << "SQL QUERY EXEC() FAILED: "
                 << " Drop Course Failed. You haven't selected the course!";
        return false;
    }//if
    return true;
}


