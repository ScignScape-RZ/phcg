#pragma once

#include <QtGlobal>

#if defined(PGVM_PLUGIN_LIBRARY)
#  define PGVM_PLUGIN_SHARED_EXPORT Q_DECL_EXPORT
#else
#  define PGVM_PLUGIN_SHARED_EXPORT Q_DECL_IMPORT
#endif
