#ifndef AVAILCOURSESOBJECT_HPP
#define AVAILCOURSESOBJECT_HPP

// Qt5
#include <QObject>
#include <QList>
#include <QString>

class AvailCoursesObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString cno MEMBER m_cno READ cno WRITE setCno NOTIFY cnoChanged)
    Q_PROPERTY(QString cname MEMBER m_cname READ cname WRITE setCname NOTIFY cnameChanged)
    Q_PROPERTY(int credit MEMBER m_credit READ credit WRITE setCredit NOTIFY creditChanged)
    Q_PROPERTY(QString cdept MEMBER m_cdept READ cdept WRITE setCdept NOTIFY cdeptChanged)
    Q_PROPERTY(QString tname MEMBER m_tname READ tname WRITE setTname NOTIFY tnameChanged)
public:
    AvailCoursesObject(
            const QString & cno,
            const QString & cname,
            const int credit,
            const QString & cdept,
            const QString & tname) :
        m_cno(cno),
        m_cname(cname),
        m_credit(credit),
        m_cdept(cdept),
        m_tname(tname)
      {}

    inline QString
    cno() const
    { return m_cno; }

    inline void
    setCno(const QString & new_cno)
    { m_cno = new_cno; }

    inline QString
    cname() const
    { return m_cname; }

    inline void
    setCname(const QString & new_cname)
    { m_cname = new_cname; }

    inline int
    credit() const
    { return m_credit; }

    inline void
    setCredit(const int new_credit)
    { m_credit = new_credit; }

    inline QString
    cdept() const
    { return m_cdept; }

    inline void
    setCdept(const QString & new_cdept)
    { m_cdept = new_cdept; }

    inline QString
    tname() const
    { return m_tname; }

    inline void
    setTname(const QString & new_tname)
    { m_tname = new_tname; }

signals:
    void cnoChanged(const QString &);
    void cnameChanged(const QString &);
    void creditChanged(int);
    void cdeptChanged(const QString &);
    void tnameChanged(const QString &);
public slots:

private://members
    QString m_cno;
    QString m_cname;
    int m_credit;
    QString m_cdept;
    QString m_tname;
};

#endif // AVAILCOURSESOBJECT_HPP
