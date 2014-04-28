#ifndef COURSEGRADEOBJECT_HPP
#define COURSEGRADEOBJECT_HPP

#include <QObject>
#include <QString>

class CourseGradeObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString cno MEMBER m_cno READ cno WRITE setCno NOTIFY cnoChanged)
    Q_PROPERTY(QString course_name MEMBER m_course_name READ course_name WRITE setCourse_name NOTIFY course_nameChanged)
    Q_PROPERTY(int grade MEMBER m_grade READ grade WRITE setGrade NOTIFY gradeChanged)
public:
    explicit CourseGradeObject(
            const QString & cno,
            const QString & course_name,
            const int grade) :
        m_cno(cno),
        m_course_name(course_name),
        m_grade(grade)
    {}

    inline QString
    cno() const
    { return m_cno; }

    inline void
    setCno(const QString & new_cno)
    { m_cno = new_cno; }

    inline QString
    course_name() const
    { return m_course_name; }

    inline void
    setCourse_name(const QString & new_course_name)
    { m_course_name = new_course_name; }

    inline int
    grade() const
    { return m_grade; }

    inline void
    setGrade(const int new_grade)
    { m_grade = new_grade; }

signals:
    void cnoChanged(const QString &);
    void course_nameChanged(const QString &);
    void gradeChanged(int);
public slots:

private://members
    QString m_cno;
    QString m_course_name;
    int m_grade;
};

#endif // COURSEGRADEOBJECT_HPP
