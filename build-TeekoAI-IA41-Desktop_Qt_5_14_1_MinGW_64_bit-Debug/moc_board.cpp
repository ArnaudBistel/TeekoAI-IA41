/****************************************************************************
** Meta object code from reading C++ file 'board.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../TeekoAI-IA41/board.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'board.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Board_t {
    QByteArrayData data[18];
    char stringdata0[247];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Board_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Board_t qt_meta_stringdata_Board = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Board"
QT_MOC_LITERAL(1, 6, 15), // "changeInterface"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 4), // "name"
QT_MOC_LITERAL(4, 28, 12), // "playerPlayed"
QT_MOC_LITERAL(5, 41, 10), // "tileChosen"
QT_MOC_LITERAL(6, 52, 8), // "getBoard"
QT_MOC_LITERAL(7, 61, 17), // "pointer_to_arrays"
QT_MOC_LITERAL(8, 79, 10), // "printBoard"
QT_MOC_LITERAL(9, 90, 6), // "goBack"
QT_MOC_LITERAL(10, 97, 21), // "announceCurrentPlayer"
QT_MOC_LITERAL(11, 119, 28), // "prepareBoardForCurrentPlayer"
QT_MOC_LITERAL(12, 148, 9), // "placePion"
QT_MOC_LITERAL(13, 158, 16), // "initBoardVisible"
QT_MOC_LITERAL(14, 175, 18), // "initBoardInvisible"
QT_MOC_LITERAL(15, 194, 11), // "enableBoard"
QT_MOC_LITERAL(16, 206, 27), // "afficherDeplacementPossible"
QT_MOC_LITERAL(17, 234, 12) // "unselectPawn"

    },
    "Board\0changeInterface\0\0name\0playerPlayed\0"
    "tileChosen\0getBoard\0pointer_to_arrays\0"
    "printBoard\0goBack\0announceCurrentPlayer\0"
    "prepareBoardForCurrentPlayer\0placePion\0"
    "initBoardVisible\0initBoardInvisible\0"
    "enableBoard\0afficherDeplacementPossible\0"
    "unselectPawn"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Board[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    1,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   90,    2, 0x0a /* Public */,
       6,    0,   91,    2, 0x0a /* Public */,
       8,    0,   92,    2, 0x0a /* Public */,
       9,    0,   93,    2, 0x0a /* Public */,
      10,    1,   94,    2, 0x0a /* Public */,
      11,    2,   97,    2, 0x0a /* Public */,
      12,    5,  102,    2, 0x0a /* Public */,
      13,    0,  113,    2, 0x0a /* Public */,
      14,    0,  114,    2, 0x0a /* Public */,
      15,    0,  115,    2, 0x0a /* Public */,
      16,    2,  116,    2, 0x0a /* Public */,
      17,    1,  121,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    0x80000000 | 7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Bool, QMetaType::Bool,    2,    2,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void Board::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Board *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeInterface((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->playerPlayed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->tileChosen(); break;
        case 3: { pointer_to_arrays _r = _t->getBoard();
            if (_a[0]) *reinterpret_cast< pointer_to_arrays*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->printBoard(); break;
        case 5: _t->goBack(); break;
        case 6: _t->announceCurrentPlayer((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->prepareBoardForCurrentPlayer((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->placePion((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 9: _t->initBoardVisible(); break;
        case 10: _t->initBoardInvisible(); break;
        case 11: _t->enableBoard(); break;
        case 12: _t->afficherDeplacementPossible((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->unselectPawn((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Board::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Board::changeInterface)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Board::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Board::playerPlayed)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Board::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Board.data,
    qt_meta_data_Board,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Board::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Board::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Board.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Board::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void Board::changeInterface(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Board::playerPlayed(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
