/****************************************************************************
** Meta object code from reading C++ file 'scanresults.h'
**
** Created: Sat Apr 14 17:17:37 2018
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "scanresults.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scanresults.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScanResults[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   13,   12,   12, 0x0a,
      40,   12,   12,   12, 0x0a,
      56,   12,   12,   12, 0x0a,
      70,   12,   12,   12, 0x0a,
      87,   83,   12,   12, 0x0a,
     117,   12,   12,   12, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ScanResults[] = {
    "ScanResults\0\0_wpagui\0setWpaGui(WpaGui*)\0"
    "updateResults()\0scanRequest()\0"
    "getResults()\0sel\0bssSelected(QTreeWidgetItem*)\0"
    "languageChange()\0"
};

const QMetaObject ScanResults::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ScanResults,
      qt_meta_data_ScanResults, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScanResults::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScanResults::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScanResults::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScanResults))
        return static_cast<void*>(const_cast< ScanResults*>(this));
    if (!strcmp(_clname, "Ui::ScanResults"))
        return static_cast< Ui::ScanResults*>(const_cast< ScanResults*>(this));
    return QDialog::qt_metacast(_clname);
}

int ScanResults::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setWpaGui((*reinterpret_cast< WpaGui*(*)>(_a[1]))); break;
        case 1: updateResults(); break;
        case 2: scanRequest(); break;
        case 3: getResults(); break;
        case 4: bssSelected((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 5: languageChange(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
