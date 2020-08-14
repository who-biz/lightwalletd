//-----------------------------------------------------------------------------
// Hash is a simple wrapper around the VerusCoin verus_hash algorithms.
// It is intended for use in the go lightwalletd project.
// Written by David Dawes, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.

#ifndef _VERUSHASH_H_
#define _VERUSHASH_H_/* File : veruhash.h */

#include <stdio.h>
#include <string>
class Verushash {
public:
  bool initialized = false;
  void initialize();
  void * verushash(char const * bytes, size_t length);
  void * verushash_v2(const unsigned char * bytes, size_t length);
  void * verushash_v2b(const unsigned char * bytes, size_t length);
  void * verushash_v2b1(const unsigned char * bytes, size_t length);
  void * verushash_v2b2(const std::string bytes);
};
#endif