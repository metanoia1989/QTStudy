#include "textbook.h"
#include "textbookmap.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    Textbook* t1 = new Textbook("The C++ Programming Language",
                                "Stroustrup", "0201700735", 1997);
    Textbook* t2 = new Textbook("XML in a Nutshell",
                                "Harold", "0596002920", 2002);
    Textbook* t3 = new Textbook("UML Distilled",
                                "Fowler", "0321193687", 2004);
    Textbook* t4 = new Textbook("Design Patterns",
                                "Gamma", "0201633612", 1995);
    {
        TextbookMap m;
        m.add(t1);
        m.add(t2);
        m.add(t3);
        m.add(t4);
        qDebug() << m.toString();
        m.remove(t3->getIsbn());
    }
    qDebug() << "After m has been destroy we still have:\n"
             << t3->toString();
    return 0;
}
