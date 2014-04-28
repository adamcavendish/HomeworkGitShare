#ifndef STUDENTINFOOBJECT_HPP
#define STUDENTINFOOBJECT_HPP

#include <QObject>

class StudentInfoObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString sno MEMBER m_sno READ sno WRITE setSno NOTIFY snoChanged)
    Q_PROPERTY(QString name MEMBER m_name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString gender MEMBER m_gender READ gender WRITE setGender NOTIFY genderChanged)
    Q_PROPERTY(int age MEMBER m_age READ age WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(QString department MEMBER m_department READ department WRITE setDepartment NOTIFY departmentChanged)
public:
    explicit StudentInfoObject(
            const QString & sno,
            const QString & name,
            const QString & gender,
            const int & age,
            const QString & department)
        : m_sno(sno),
          m_name(name),
          m_gender(gender),
          m_age(age),
          m_department(department)
    {}

    inline QString
    sno() const
    { return m_sno; }

    inline void
    setSno(const QString & new_sno)
    { m_sno = new_sno; }

    inline QString
    name() const
    { return m_name; }

    inline void
    setName(const QString & new_name)
    { m_name = new_name; }

    inline QString
    gender() const
    { return m_gender; }

    inline void
    setGender(const QString & new_gender)
    { m_gender = new_gender; }

    inline int
    age() const
    { return m_age; }

    inline void
    setAge(int new_age)
    { m_age = new_age; }

    inline QString
    department() const
    { return m_department; }

    inline void
    setDepartment(const QString & new_department)
    { m_department = new_department; }

signals:
    void snoChanged(const QString &);
    void nameChanged(const QString &);
    void genderChanged(const QString &);
    void ageChanged(const QString &);
    void departmentChanged(const QString &);
public slots:

private: //members
    QString m_sno;
    QString m_name;
    QString m_gender;
    int m_age;
    QString m_department;
};

#endif // STUDENTINFOOBJECT_HPP
