/*
 * Copyright (c) 2002 Mayukh Bose
 * See the file LICENSE for details.
 */

#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include "lexer.h"

using namespace std;

struct lower {
  unsigned char operator() (unsigned char c) { return tolower(c); }
};


Lexer::Lexer(char *filename) : FileReader(filename) {
  sLastTag = "";
  ttTagType = ttNone;
  bEOF = false;
}

bool Lexer::IsKeyword(string sTag) {
  string sTemp = sTag;

  transform(sTemp.begin(), sTemp.end(), sTemp.begin(), lower());
  for (register int i = 0; Keywords[i] != LASTKEYWORD; i++) {
    if (Keywords[i] == sTemp)
      return true;
  }
  return false;
}

bool Lexer::IsSymbol(char ch) {
  if (Symbols.find(ch, 0) != string::npos)
    return true;
  else
    return false;
}

string Lexer::GetNextTag(void) {
  char ch;

  sLastTag = "";
  ch = GetChar();
  if (ch == '\0') {
    ttTagType = ttEOF;
    bEOF = true;
    return "";
  }
  
  // First skip past any white space
  while ((ch != '\0') && (isspace(ch)))
    ch = GetChar();

  if (ch == '\0') {
    ttTagType = ttEOF;
    bEOF = true;
    return "";
  }

  // Now check what type of char we have here
  if (isdigit(ch)) 
    ttTagType = ttNumber;
  else if (isalpha(ch))
    ttTagType = ttIdentifier;
  else if (ch == '\"')
    ttTagType = ttString;
  else
    ttTagType = ttSymbol;

  // Now read the rest of the word in
  if (ttTagType != ttString) {
    while ((ch != '\0') && (!isspace(ch))) {
      if ((ttTagType == ttNumber) && (isalpha(ch))) 
	report_error("Parse error: Number contains letters!");
      else if ((ttTagType == ttNumber) && (!isdigit(ch)) && (ch != '.'))
	break; // End of number
      else if ((ttTagType == ttSymbol) && (isalnum(ch)))
	break; // End of symbol
      else if ((ttTagType == ttIdentifier) && (IsSymbol(ch)))
	break; // End of identifier
      sLastTag += ch;
      ch = GetChar();
    }
  } else {
    ch = GetChar();
    while (ch != '\0') {
      if (ch == '\n')
	report_error("Parse error: unterminated string constant");
      else if (ch == '\"')
	break;
      else
	sLastTag += ch;
      ch = GetChar();
    }
  }

  // Check if this is a keyword (if ttTagType = identifier))
  if ((ttTagType == ttIdentifier) && (IsKeyword(sLastTag))) {
    transform(sLastTag.begin(), sLastTag.end(), sLastTag.begin(), lower());
    ttTagType = ttKeyword;
  }

  // Push the last character back up the stack for the next pass
  if (ch != '\0' && ttTagType != ttString)
    UngetChar();

  return sLastTag;
}

string Lexer::GetTagName(void) {
  return sLastTag;
}

TagTypes Lexer::GetTagType(void) {
  return ttTagType;
}

bool Lexer::end_of_file(void) {
  return bEOF;
}

void Lexer::report_error(string err) {
  ostringstream oerr;
  oerr << err << " Line: " << GetLineNum() << " Column: " << GetColumnNum();
  throw oerr.str();
}
