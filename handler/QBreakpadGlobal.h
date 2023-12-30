#ifndef QBREAKPADGLOBAL_H
#define QBREAKPADGLOBAL_H

#include <QtGlobal>

#ifndef QBREAKPAD_EXPORT
#  ifdef QBREAKPAD_STATIC
#    define QBREAKPAD_EXPORT
#  else
#    ifdef QBREAKPAD_LIBRARY
#      define QBREAKPAD_EXPORT Q_DECL_EXPORT
#    else
#      define QBREAKPAD_EXPORT Q_DECL_IMPORT
#    endif
#  endif
#endif

#endif // QBREAKPADGLOBAL_H
