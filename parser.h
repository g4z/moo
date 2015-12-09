/*
 * Copyright (c) 2002 Mayukh Bose
 * See the file LICENSE for details.
 */

#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <map>
#include "lexer.h"
#include "common.h"

struct ltstr {
  bool operator()(const string& s1, const string& s2) const;
};

typedef map<const string, long, ltstr> IntVars;
typedef map<const string, string, ltstr> StringVars;

class Parser {
 private:
  Lexer *lexer;
  StringVars svStringList;
  IntVars ivIntList;
  void DoParse(void);
  TagTypes EvalExp(string &ret, string extratags="");
  TagTypes GetVarType(const string varname, string &retval);
  bool IsInteger(const string &s);

  // Various keyword commands
  void DoPrintCmd(void);
  void DoIfCmd(void);
  void DoWhileCmd(void);
  void DoInputCmd(void);

 public: 
  Parser(char *filename);
  ~Parser();  
  void Run(void);
  void DumpVariables(void); // For debugging
};

#endif
