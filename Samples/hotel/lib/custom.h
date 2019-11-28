
// This file is generated from the perl script custom.pl, please do 
// not modify this file directly.

#ifndef MYSQLPP_CUSTOM_H
#define MYSQLPP_CUSTOM_H

#include "defs.h"
#include "tiny_int.h"

#include <string>

namespace mysqlpp {

enum sql_dummy_type {sql_dummy};

inline int sql_cmp(const std::string &a, const std::string &b) {
  return a.compare(b);
}

inline int sql_cmp(char a,char b) {
  return a-b;
}

inline int sql_cmp(unsigned char a,unsigned char b) {
  return a-b;
}

inline int sql_cmp(tiny_int a,tiny_int b) {
  return a-b;
}

inline int sql_cmp(int a,int b) {
  return a-b;
}

inline int sql_cmp(unsigned int a,unsigned int b) {
  return a-b;
}

inline int sql_cmp(short int a,short int b) {
  return a-b;
}

inline int sql_cmp(unsigned short int a,unsigned short int b) {
  return a-b;
}

inline int sql_cmp(double a,double b) {
  if (a == b) return 0;
  if (a <  b) return -1;
  return 1;
}

inline int sql_cmp(float a,float b) {
  if (a == b) return 0;
  if (a <  b) return -1;
  return 1;
}

inline int sql_cmp(longlong a,longlong b) {
  if (a == b) return 0;
  if (a <  b) return -1;
  return 1;
}

inline int sql_cmp(ulonglong a,ulonglong b) {
  if (a == b) return 0;
  if (a <  b) return -1;
  return 1;
}

#include "custom-macros.h"

} // end namespace mysqlpp

#endif

