/****************************************************************************
** Meta object code from reading C++ file 'mainwindowarticles.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GestionArticles/mainwindowarticles.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindowarticles.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindowArticles_t {
    QByteArrayData data[16];
    char stringdata0[344];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindowArticles_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindowArticles_t qt_meta_stringdata_MainWindowArticles = {
    {
QT_MOC_LITERAL(0, 0, 18), // "MainWindowArticles"
QT_MOC_LITERAL(1, 19, 30), // "on_pushButton_Afficher_clicked"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 30), // "on_pushButton_Modifier_clicked"
QT_MOC_LITERAL(4, 82, 29), // "on_pushButton_Ajouter_clicked"
QT_MOC_LITERAL(5, 112, 30), // "on_pushButton_Exporter_clicked"
QT_MOC_LITERAL(6, 143, 31), // "on_pushButton_Supprimer_clicked"
QT_MOC_LITERAL(7, 175, 28), // "on_pushButton_Vendre_clicked"
QT_MOC_LITERAL(8, 204, 15), // "on_stat_clicked"
QT_MOC_LITERAL(9, 220, 14), // "searchArticles"
QT_MOC_LITERAL(10, 235, 5), // "query"
QT_MOC_LITERAL(11, 241, 27), // "on_pushButton_Trier_clicked"
QT_MOC_LITERAL(12, 269, 27), // "on_pushButton_Image_clicked"
QT_MOC_LITERAL(13, 297, 13), // "showNextImage"
QT_MOC_LITERAL(14, 311, 17), // "showPreviousImage"
QT_MOC_LITERAL(15, 329, 14) // "refreshCatalog"

    },
    "MainWindowArticles\0on_pushButton_Afficher_clicked\0"
    "\0on_pushButton_Modifier_clicked\0"
    "on_pushButton_Ajouter_clicked\0"
    "on_pushButton_Exporter_clicked\0"
    "on_pushButton_Supprimer_clicked\0"
    "on_pushButton_Vendre_clicked\0"
    "on_stat_clicked\0searchArticles\0query\0"
    "on_pushButton_Trier_clicked\0"
    "on_pushButton_Image_clicked\0showNextImage\0"
    "showPreviousImage\0refreshCatalog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindowArticles[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    1,   86,    2, 0x08 /* Private */,
      11,    0,   89,    2, 0x08 /* Private */,
      12,    0,   90,    2, 0x08 /* Private */,
      13,    0,   91,    2, 0x08 /* Private */,
      14,    0,   92,    2, 0x08 /* Private */,
      15,    0,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindowArticles::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindowArticles *_t = static_cast<MainWindowArticles *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_Afficher_clicked(); break;
        case 1: _t->on_pushButton_Modifier_clicked(); break;
        case 2: _t->on_pushButton_Ajouter_clicked(); break;
        case 3: _t->on_pushButton_Exporter_clicked(); break;
        case 4: _t->on_pushButton_Supprimer_clicked(); break;
        case 5: _t->on_pushButton_Vendre_clicked(); break;
        case 6: _t->on_stat_clicked(); break;
        case 7: _t->searchArticles((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->on_pushButton_Trier_clicked(); break;
        case 9: _t->on_pushButton_Image_clicked(); break;
        case 10: _t->showNextImage(); break;
        case 11: _t->showPreviousImage(); break;
        case 12: _t->refreshCatalog(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindowArticles::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindowArticles.data,
      qt_meta_data_MainWindowArticles,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindowArticles::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindowArticles::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindowArticles.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindowArticles::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
