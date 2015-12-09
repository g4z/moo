/*
 * Copyright (c) 2002 Mayukh Bose
 * See the file LICENSE for details.
 */
#ifndef __LEXER_H__
#define __LEXER_H__

#include <string>
#include "reader.h"
#include "common.h"

class Lexer : public FileReader {
 private:
  bool bEOF;
  string sLastTag;
  TagTypes ttTagType;
  
  bool IsKeyword(string sTag);
  bool IsSymbol(char c);
 public:
  Lexer(char *filename);
  string GetNextTag(void);
  string GetTagName(void);
  TagTypes GetTagType(void);
  bool end_of_file(void);
  void report_error(string err);
};

#endif
