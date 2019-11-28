#ifndef MYSQLPP_DEFS_H
#define MYSQLPP_DEFS_H

#include "platform.h"

#include <mysql.h>

namespace mysqlpp {

enum sql_cmp_type {sql_use_compare};

#if defined(NO_LONG_LONGS)
typedef unsigned long ulonglong;
typedef long longlong;
#elif !defined(__GNUC__) && (defined(__WIN32__) || defined(_WIN32))
typedef unsigned __int64 ulonglong;
typedef __int64 longlong;
#else
typedef unsigned long long ulonglong;
typedef long long longlong;
#endif

typedef MYSQL_FIELD Field;
typedef const char cchar;
typedef longlong longgint;
#ifndef uint
typedef unsigned int uint;
#endif

const bool use_exceptions = true;

} // end namespace mysqlpp

#endif

