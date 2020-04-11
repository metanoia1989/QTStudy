#pragma once
#include <QCoreApplication>
#include "QtAwesome.h"

QtAwesome *qtAwesome()
{
    static QtAwesome* qtAwesome = nullptr;
    if( !qtAwesome ) {
        qtAwesome  = new QtAwesome(qApp);
        qtAwesome->initFontAwesome();
    }
    return qtAwesome;
}
