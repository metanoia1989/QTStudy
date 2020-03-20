#include <QApplication>
#include <QScrollBar>
#include <QWidget>
#include <QAbstractSlider>
#include <QListView>
#include <QString>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextStream cout(stdout);
    QScrollBar s;
    QWidget *w = &s;

    cout << "We are testing a base class pointer that has "
         << "the address of a QScrollBar\n"
         << "First, we use qojbject_cast to inestigate." << endl;
    QScrollBar *ptr1 = qobject_cast<QScrollBar*>(w);
    if (ptr1) {
        cout << "Yes, it is ";
    } else {
        cout << "No is not ";
    }
    cout << "a QScrollBar!" << endl;

    QAbstractSlider *ptr2 = qobject_cast<QAbstractSlider*>(w);
    if (ptr2) {
        cout << "Yes, it is ";
    } else {
        cout << "No is not ";
    }
    cout << "a QAbstractSlider!" << endl;

    QListView *ptr3 = qobject_cast<QListView*>(w);
    if (ptr3) {
        cout << "Yes, it is ";
    } else {
        cout << "No is not ";
    }
    cout << "a QListView!" << endl;

    if (w->inherits("QAbstractSlider")) {
        cout << "Yes, it is ";
    } else {
        cout << "No, it is not";
    }
    cout << "a QAbstractSlider" << endl;

    if (w->inherits("QListView")) {
        cout << "Yes, it is ";
    } else {
        cout << "No, it is not";
    }
    cout << "a QListView" << endl;

    return a.exec();
}
