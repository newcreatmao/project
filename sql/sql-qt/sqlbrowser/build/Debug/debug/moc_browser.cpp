/****************************************************************************
** Meta object code from reading C++ file 'browser.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/browser.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'browser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSBrowserENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSBrowserENDCLASS = QtMocHelpers::stringData(
    "Browser",
    "statusMessage",
    "",
    "message",
    "openNewConnectionDialog",
    "about",
    "exec",
    "showTable",
    "table",
    "showMetaData",
    "onFieldStrategyAction",
    "onRowStrategyAction",
    "onManualStrategyAction",
    "onSubmitButton",
    "onClearButton"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSBrowserENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   80,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,   83,    2, 0x0a,    3 /* Public */,
       5,    0,   84,    2, 0x0a,    4 /* Public */,
       6,    0,   85,    2, 0x09,    5 /* Protected */,
       7,    1,   86,    2, 0x09,    6 /* Protected */,
       9,    1,   89,    2, 0x09,    8 /* Protected */,
      10,    0,   92,    2, 0x09,   10 /* Protected */,
      11,    0,   93,    2, 0x09,   11 /* Protected */,
      12,    0,   94,    2, 0x09,   12 /* Protected */,
      13,    0,   95,    2, 0x09,   13 /* Protected */,
      14,    0,   96,    2, 0x09,   14 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Browser::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSBrowserENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSBrowserENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSBrowserENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Browser, std::true_type>,
        // method 'statusMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'openNewConnectionDialog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'about'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exec'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'showMetaData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onFieldStrategyAction'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRowStrategyAction'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onManualStrategyAction'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSubmitButton'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onClearButton'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Browser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Browser *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->statusMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->openNewConnectionDialog(); break;
        case 2: _t->about(); break;
        case 3: _t->exec(); break;
        case 4: _t->showTable((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->showMetaData((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->onFieldStrategyAction(); break;
        case 7: _t->onRowStrategyAction(); break;
        case 8: _t->onManualStrategyAction(); break;
        case 9: _t->onSubmitButton(); break;
        case 10: _t->onClearButton(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Browser::*)(const QString & );
            if (_t _q_method = &Browser::statusMessage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *Browser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Browser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSBrowserENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Browser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Browser::statusMessage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSCustomModelENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSCustomModelENDCLASS = QtMocHelpers::stringData(
    "CustomModel"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSCustomModelENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject CustomModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QSqlTableModel::staticMetaObject>(),
    qt_meta_stringdata_CLASSCustomModelENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSCustomModelENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSCustomModelENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CustomModel, std::true_type>
    >,
    nullptr
} };

void CustomModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *CustomModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSCustomModelENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QSqlTableModel::qt_metacast(_clname);
}

int CustomModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSqlTableModel::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
