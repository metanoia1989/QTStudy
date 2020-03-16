#pragma once

#ifndef OBJECTBROWSER_EXPORT
#include <QtGlobal>
#define OBJECTBROWSER_EXPORT Q_DECL_EXPORT
#else
#include <QtGlobal>
#define OBJECTBROWSER_EXPORT Q_DECL_IMPORT
#endif
