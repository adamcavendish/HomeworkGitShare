#include "sqlmanager.hpp"
// CourseSelectionAndGradeManagementSystem
#include "studentinfoobject.hpp"
#include "availcoursesobject.hpp"
#include "coursegradeobject.hpp"
#include "selectedcoursesobject.h"
#include "courseinfoobject.h"
#include "studentgrademanageobject.h"
#include "userinfoobject.h"

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
            << lastErrorString();
        return false;
    }//if
    return true;
}

QString SqlManager::lastErrorString() const
{
    return m_pdb->lastError().text() + "|" + m_query.lastError().text();
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
                 << lastErrorString();
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
                 << lastErrorString();
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
                 << lastErrorString();
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
                 << lastErrorString();
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

QString
SqlManager::getCourseName(const QString &cno)
{
    m_query.prepare(
        "SELECT CNAME FROM Courses WHERE "
            "CNO = :cno;");
    m_query.bindValue(":cno", cno);
    if(!m_query.exec()) {
        qDebug() << "SQL QUERY EXEC() FAILED: "
                 << lastErrorString();
        return QString();
    }//if
    if(m_query.size() > 0) {
        m_query.next();
        return m_query.value(0).toString();
    }//if
    return QString();
}

QString
SqlManager::getTeacherName(const QString &cno)
{
    m_query.prepare(
        "SELECT TNAME FROM Courses WHERE "
            "CNO = :cno;");
    m_query.bindValue(":cno", cno);
    if(!m_query.exec()) {
        qDebug() << "SQL QUERY EXEC() FAILED: "
                 << lastErrorString();
        return QString();
    }//if
    if(m_query.size() > 0) {
        m_query.next();
        return m_query.value(0).toString();
    }//if
    return QString();
}

QList<QObject *>
SqlManager::getAllCourseInfo()
{
    m_query.prepare("SELECT * FROM Courses;");
    if(!m_query.exec()) {
        qDebug() << "SQL QUERY EXEC() FAILED: "
                 << lastErrorString();
        return QList<QObject *>();
    }//if

    QList<QObject *> ret;
    while(m_query.next()) {
        auto cno = m_query.value(0).toString();
        auto cname = m_query.value(1).toString();
        auto credit = m_query.value(2).toInt();
        auto cdept = m_query.value(3).toString();
        auto tname = m_query.value(4).toString();
        ret.append(new CourseInfoObject(cno, cname, credit, cdept, tname, cname));
    }//while

    return ret;
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

bool
SqlManager::dropCourse(const QString &cno)
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

QList<QObject *>
SqlManager::getCourseStudentsGrade(const QString &cno)
{
    m_query.prepare("SELECT * FROM CourseGrades WHERE CNO = :cno;");
    m_query.bindValue(":cno", cno);
    if(!m_query.exec()) {
        qDebug() << "SQL QUERY EXEC() FAILED: "
                 << m_pdb->lastError().text();
        return QList<QObject *>();
    }//if

    QList<QObject *> ret;
    while(m_query.next()) {
        auto sno = m_query.value(0).toString();
        auto grade = m_query.value(2).toInt();
        ret.append(new StudentGradeManageObject(sno, grade));
    }//while

    return ret;
}

void
SqlManager::updateGrade(const QString &sno, const QString &cno, int grade)
{
    m_query.prepare("UPDATE CourseGrades SET GRADE=:grade WHERE "
                    "SNO = :sno AND CNO = :cno;");
    m_query.bindValue(":sno", sno);
    m_query.bindValue(":cno", cno);
    m_query.bindValue(":grade", grade);
    if(!m_query.exec()) {
        qDebug() << "SQL QUERY EXEC() FAILED: "
                 << lastErrorString();
        return;
    }//if
}

QList<QObject *> SqlManager::getAllUsers()
{
    m_query.prepare(
        "SELECT SNO, SNAME, GENDER, AGE, SDEPT, USER, PSWD FROM "
            "mysql.db, CourseSelectionAndGradeManagement.Students AS S "
        "WHERE "
            "db = 'CourseSelectionAndGradeManagement' AND S.SNO = user;");
    if(!m_query.exec()) {
        qDebug() << "SQL QUERY EXEC() FAILED: "
                 << lastErrorString();
        return QList<QObject *>();
    }//if

    QList<QObject *> ret;
    while(m_query.next()) {
        auto sno = m_query.value(0).toString();
        auto sname = m_query.value(1).toString();
        auto sgender = m_query.value(2).toString();
        auto sage = m_query.value(3).toInt();
        auto sdept = m_query.value(4).toString();
        ret.append(new UserInfoObject(sno, sname, sgender, sage, sdept));
    }//while

    return ret;
}

void
SqlManager::addUser(const QString &sno, const QString &sname, const QString & gender, int age, const QString &sdept)
{
    if(sno.isEmpty() || sname.isEmpty() || gender.isEmpty() ||
            age > 100 || age < 0 || sdept.isEmpty()) {
        qDebug() << "Invalid data, please check!";
        return;
    }//if

    QString str = "GRANT ALL PRIVILEGES ON CourseSelectionAndGradeManagement.* TO '";
    str += sno;
    str += "'@'localhost' IDENTIFIED BY '";
    str += sno;
    str += "' WITH GRANT OPTION;";
    m_query.prepare(str);
    if(!m_query.exec()) {
        qDebug() << "SQL QUERY EXEC() FAILED: "
                 << lastErrorString();
        return;
    }//if

    m_query.prepare("INSERT INTO Students VALUES "
                    "(:sno, :sname, :gender, :age, :sdept, :sno, :sno);");
    m_query.bindValue(":sno", sno);
    m_query.bindValue(":sname", sname);
    m_query.bindValue(":gender", gender);
    m_query.bindValue(":age", age);
    m_query.bindValue(":sdept", sdept);
    if(!m_query.exec()) {
        qDebug() << "SQL QUERY EXEC() FAILED: "
                 << lastErrorString();
        return;
    }//if
}

void
SqlManager::dropUser(const QString &sno)
{
    QString str = "DROP USER '";
    str += sno;
    str += "'@'localhost';";
    m_query.prepare(str);
    if(!m_query.exec()) {
        qDebug() << "SQL QUERY EXEC() FAILED: "
                 << lastErrorString();
        return;
    }//if

    m_query.prepare("DELETE FROM Students WHERE "
                    "SNO = :sno;");
    m_query.bindValue(":sno", sno);
    if(!m_query.exec()) {
        qDebug() << "SQL QUERY EXEC() FAILED: "
                 << lastErrorString();
        return;
    }//if
}
