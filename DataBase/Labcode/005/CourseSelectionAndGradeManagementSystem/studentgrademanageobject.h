#ifndef STUDENTGRADEMANAGEOBJECT_H
#define STUDENTGRADEMANAGEOBJECT_H

#include <QObject>

class StudentGradeManageObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString sno MEMBER m_cno READ sno WRITE setSno NOTIFY snoChanged)
    Q_PROPERTY(int grade MEMBER m_grade READ grade WRITE setGrade NOTIFY gradeChanged)
public:
    explicit StudentGradeManageObject(
            const QString & sno,
            const int grade) :
        m_sno(sno),
        m_grade(grade)
    {}

    inline QString
    sno() const
    { return m_sno; }

    inline void
    setSno(const QString & new_sno)
    { m_sno = new_sno; }

    inline int
    grade() const
    { return m_grade; }

    inline void
    setGrade(const int new_grade)
    { m_grade = new_grade; }

signals:
    void snoChanged(const QString &);
    void gradeChanged(int);
public slots:

private://members
    QString m_sno;
    int m_grade;
};

#endif // STUDENTGRADEMANAGEOBJECT_H
