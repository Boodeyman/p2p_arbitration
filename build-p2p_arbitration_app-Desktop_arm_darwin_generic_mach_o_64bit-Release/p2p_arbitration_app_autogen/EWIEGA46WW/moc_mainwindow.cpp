/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../p2p_arbitration_app/mainwindow.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.2. It"
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
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "updateCryptoData",
    "",
    "symbol",
    "data",
    "requestData",
    "searchCrypto",
    "onRowSelected",
    "sortByChangeColumn",
    "column",
    "logout",
    "hideLineEdit",
    "openBuyCrypto",
    "on_themeChange_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[28];
    char stringdata0[11];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[7];
    char stringdata4[5];
    char stringdata5[12];
    char stringdata6[13];
    char stringdata7[14];
    char stringdata8[19];
    char stringdata9[7];
    char stringdata10[7];
    char stringdata11[13];
    char stringdata12[14];
    char stringdata13[23];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 16),  // "updateCryptoData"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 6),  // "symbol"
        QT_MOC_LITERAL(36, 4),  // "data"
        QT_MOC_LITERAL(41, 11),  // "requestData"
        QT_MOC_LITERAL(53, 12),  // "searchCrypto"
        QT_MOC_LITERAL(66, 13),  // "onRowSelected"
        QT_MOC_LITERAL(80, 18),  // "sortByChangeColumn"
        QT_MOC_LITERAL(99, 6),  // "column"
        QT_MOC_LITERAL(106, 6),  // "logout"
        QT_MOC_LITERAL(113, 12),  // "hideLineEdit"
        QT_MOC_LITERAL(126, 13),  // "openBuyCrypto"
        QT_MOC_LITERAL(140, 22)   // "on_themeChange_clicked"
    },
    "MainWindow",
    "updateCryptoData",
    "",
    "symbol",
    "data",
    "requestData",
    "searchCrypto",
    "onRowSelected",
    "sortByChangeColumn",
    "column",
    "logout",
    "hideLineEdit",
    "openBuyCrypto",
    "on_themeChange_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   68,    2, 0x08,    1 /* Private */,
       5,    0,   73,    2, 0x08,    4 /* Private */,
       6,    0,   74,    2, 0x08,    5 /* Private */,
       7,    0,   75,    2, 0x08,    6 /* Private */,
       8,    1,   76,    2, 0x08,    7 /* Private */,
      10,    0,   79,    2, 0x08,    9 /* Private */,
      11,    0,   80,    2, 0x08,   10 /* Private */,
      12,    0,   81,    2, 0x08,   11 /* Private */,
      13,    0,   82,    2, 0x08,   12 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'updateCryptoData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QJsonObject &, std::false_type>,
        // method 'requestData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'searchCrypto'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRowSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sortByChangeColumn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'logout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'hideLineEdit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openBuyCrypto'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_themeChange_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateCryptoData((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[2]))); break;
        case 1: _t->requestData(); break;
        case 2: _t->searchCrypto(); break;
        case 3: _t->onRowSelected(); break;
        case 4: _t->sortByChangeColumn((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->logout(); break;
        case 6: _t->hideLineEdit(); break;
        case 7: _t->openBuyCrypto(); break;
        case 8: _t->on_themeChange_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
