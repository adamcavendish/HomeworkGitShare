/****************************************************************************
** Meta object code from reading C++ file 'sqlmanager.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CourseSelectionAndGradeManagementSystem/sqlmanager.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sqlmanager.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SqlManager_t {
    QByteArrayData data[13];
    char stringdata[145];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SqlManager_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SqlManager_t qt_meta_stringdata_SqlManager = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 5),
QT_MOC_LITERAL(2, 17, 0),
QT_MOC_LITERAL(3, 18, 8),
QT_MOC_LITERAL(4, 27, 8),
QT_MOC_LITERAL(5, 36, 9),
QT_MOC_LITERAL(6, 46, 9),
QT_MOC_LITERAL(7, 56, 15),
QT_MOC_LITERAL(8, 72, 14),
QT_MOC_LITERAL(9, 87, 15),
QT_MOC_LITERAL(10, 103, 9),
QT_MOC_LITERAL(11, 113, 14),
QT_MOC_LITERAL(12, 128, 15)
    },
    "SqlManager\0login\0\0usr_name\0password\0"
    "lastError\0QSqlError\0lastErrorString\0"
    "getStudentInfo\0QList<QObject*>\0user_name\0"
    "getCourseGrade\0getAvailCourses\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SqlManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x02,
       5,    0,   49,    2, 0x02,
       7,    0,   50,    2, 0x02,
       8,    2,   51,    2, 0x02,
      11,    2,   56,    2, 0x02,
      12,    2,   61,    2, 0x02,

 // methods: parameters
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,    3,    4,
    0x80000000 | 6,
    QMetaType::QString,
    0x80000000 | 9, QMetaType::QString, QMetaType::QString,   10,    4,
    0x80000000 | 9, QMetaType::QString, QMetaType::QString,   10,    4,
    0x80000000 | 9, QMetaType::QString, QMetaType::QString,   10,    4,

       0        // eod
};

void SqlManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SqlManager *_t = static_cast<SqlManager *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->login((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { QSqlError _r = _t->lastError();
            if (_a[0]) *reinterpret_cast< QSqlError*>(_a[0]) = _r; }  break;
        case 2: { QString _r = _t->lastErrorString();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: { QList<QObject*> _r = _t->getStudentInfo((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QList<QObject*>*>(_a[0]) = _r; }  break;
        case 4: { QList<QObject*> _r = _t->getCourseGrade((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QList<QObject*>*>(_a[0]) = _r; }  break;
        case 5: { QList<QObject*> _r = _t->getAvailCourses((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QList<QObject*>*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject SqlManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SqlManager.data,
      qt_meta_data_SqlManager,  qt_static_metacall, 0, 0}
};


const QMetaObject *SqlManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SqlManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SqlManager.stringdata))
        return static_cast<void*>(const_cast< SqlManager*>(this));
    return QObject::qt_metacast(_clname);
}

int SqlManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
