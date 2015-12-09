/*
 * Copyright (c) 2002 Mayukh Bose
 * See the file LICENSE for details.
 */

#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <cctype>
#include <iostream>
#include "parser.h"
#include "common.h"

using namespace std;

/* Case insensitive compare operator */
bool ltstr::operator() (const string& s1, const string& s2) const {
  int i1 = 0, i2 = 0;
  short int df;
  char c1, c2; 

  do {
    c1 = i1 == s1.length() ? (char)0 : s1[i1];
    c2 = i2 == s2.length() ? (char)0 : s2[i2];
    df = tolower(c1) - tolower(c2);
    i1++; i2++;
  } while (c1 && c2 && df == 0);

  return df < 0;
}

Parser::Parser(char *filename) {
  lexer = new Lexer(filename);  
}

Parser::~Parser() {
  delete lexer;
}

void Parser::Run(void) {
  DoParse();
  cerr << "\n\nDone\n";
}

void Parser::DoParse(void) {
  string s, sRet;
  TagTypes tagtype;
  s = lexer->GetNextTag();
  while (!lexer->end_of_file()) {
    // This tag has to be a keyword or comment to start with.
    tagtype = lexer->GetTagType();
    if (tagtype == ttKeyword) {
      // FIXME: process the keyword as needed
      if (s == Keywords[PRINT_CMD]) 
	DoPrintCmd(); // This is a print command.
      else if (s == Keywords[IF_CMD]) 
	DoIfCmd(); // This is an if statement
      else if (s == Keywords[END_CMD])
	return;
      else if (s == Keywords[WHILE_CMD])
	DoWhileCmd();
      else if (s == Keywords[INPUT_CMD])
	DoInputCmd();
    }
    else if (tagtype == ttIdentifier) {
      string tagname = s;
      s = lexer->GetNextTag();
      if (s != "=")
	lexer->report_error(tagname + " :Invalid identifier after it.");
      tagtype = EvalExp(sRet);

      if (tagtype == ttNumber)
	ivIntList[tagname] = (atol(sRet.c_str()));
      else
	svStringList[tagname] = sRet;
    }
    s = lexer->GetNextTag();
  }
}

TagTypes Parser::EvalExp(string& sRet, string extratags) {
  string tagname;
  string sTemp;
  string sOper;
  TagTypes tagtype, oper, vartype = ttNone;
  long n1, n2, n3;
  ostringstream longval;
  

  tagname = lexer->GetNextTag();
  tagtype = lexer->GetTagType();

  if (tagtype == ttIdentifier) {
    vartype = GetVarType(tagname, sRet);
  }
  else if (tagtype == ttNumber) {
    vartype = ttNumber;
    sRet = tagname;
  }
  else if (tagtype == ttString) {
    vartype = ttString;
    sRet = tagname;
  }

  sOper = lexer->GetNextTag();
  oper = lexer->GetTagType();
  if (oper != ttSymbol) {
    if (oper == ttKeyword && (sOper == Keywords[THEN_CMD] || sOper == Keywords[DO_CMD]))
	return vartype;
    else
      lexer->report_error(string("Invalid symbol: ") + sOper + " " + tagname); 
  }
  if (sOper == ";")
    return vartype; // Default ret value

  // If we hit a , and commas are allowed for this exp,
  // then return here
  if (sOper == "," && extratags.find(",") >= 0) 
    return vartype;

  // Recursive call to evaluate the expression further
  EvalExp(sTemp);

  if (vartype == ttNumber) {
    // Do string specific operations
    n1 = atol(sRet.c_str());
    n2 = atol(sTemp.c_str());
    if (sOper == "+")
      n3 = n1 + n2;
    else if (sOper == "-")
      n3 = n1 - n2;
    else if (sOper == "*") 
      n3 = n1 * n2;
    else if (sOper == "/")
      n3 = n1 / n2;
    else if (sOper == "%")
      n3 = n1 % n2;
    else if (sOper == "=")
      n3 = (n1 == n2);
    else if (sOper == "<")
      n3 = (n1 < n2);
    else if (sOper == ">")
      n3 = (n1 > n2);
    else if (sOper == "<=")
      n3 = (n1 <= n2);
    else if (sOper == ">=")
      n3 = (n1 >= n2);
    else if (sOper == "<>")
      n3 = (n1 != n2);
    else if (sOper == "!=")
      n3 = (n1 != n2);
    else
      lexer->report_error(string("Illegal operator: ") + sOper);    
    longval << n3;
    sRet = longval.str();
  } else if (vartype == ttString) {
    if (sOper == "+")
      sRet += sTemp;
    else if (sOper == "=")
      sRet = (sRet == sTemp) ? "1" : "0";
    else if (sOper == "<")
      sRet = (sRet < sTemp) ? "1" : "0";
    else if (sOper == ">")
      sRet = (sRet > sTemp) ? "1" : "0";
    else if (sOper == "<>")
      sRet = (sRet != sTemp) ? "1" : "0";
    else if (sOper == "!=")
      sRet = (sRet != sTemp) ? "1" : "0";
    else if (sOper == "<=")
      sRet = (sRet <= sTemp) ? "1" : "0";
    else if (sOper == ">=")
      sRet = (sRet >= sTemp) ? "1" : "0";
    else
      lexer->report_error(string("Illegal operator: ") + sOper);
  }
  
  return vartype;
}

TagTypes Parser::GetVarType(const string varname, string &retval) {
  ostringstream longval;
  // If we're an identifier, check to make sure that it's in the var lists.
  if (ivIntList.find(varname) != ivIntList.end()) {
    longval << ivIntList[varname];
    retval = longval.str();
    return ttNumber;
  }
  else if (svStringList.find(varname) != svStringList.end()) {
    retval = svStringList[varname];
    return ttString;
  }
  
  // if not in the var list, assume it's an int by default and
  ivIntList[varname] = 0;
  return ttNumber;
}


/******************************************************************************
 * Function: DumpVariables
 * Purpose:  For debugging only. Dumps the states of all variables.
 *****************************************************************************/
void Parser::DumpVariables() {
  /* Now dump all the variables */
  IntVars::iterator iit;
  StringVars::iterator sit;

  cout << "\nInteger values\n";
  for (iit = ivIntList.begin(); iit != ivIntList.end(); iit++) {
    string name = (*iit).first;
    long value = (*iit).second;
    cout << name << " = " << value << "\n";
  }

  cout << "\nString values\n";
  for (sit = svStringList.begin(); sit != svStringList.end(); sit++) {
    string name = (*sit).first;
    string value = (*sit).second;
    cout << name << " = " << value << "\n";
  }
}

/******************************************************************************
 * Function: DoPrintCmd
 * Purpose:  To handle the "print" statement
 *****************************************************************************/
void Parser::DoPrintCmd(void) {
  string s, lastsym;
  
  do {
    EvalExp(s, ",");
    cout << s;
    lastsym = lexer->GetTagName();
  } while (lastsym != ";");
  cout << "\n";
}

/******************************************************************************
 * Function: DoIfCmd
 * Purpose: To handle the "if" statement
 *****************************************************************************/
void Parser::DoIfCmd(void) {
  string s, lastsym;
  do {
    EvalExp(s, "then");
    // FIXME - add logic for AND, OR etc
    lastsym = lexer->GetTagName();
  } while (lastsym != "then");

  // Now evaluate the return value of IF
  if (s == "0") {
    // ignore everything till you get an "end" statement
    int depth = 1;
    do {
      lastsym = lexer->GetNextTag();
      if (lastsym == "if" || lastsym == "while")
	depth++;
      else if ((lastsym == "end" || lastsym == "else") && depth > 0)
	depth--;
    } while (lastsym != "end" && lastsym != "else" && depth > 0);
  } else 
    // "if" statement was true. Recurse into DoParse
    DoParse();
}

/******************************************************************************
 * Function: DoWhileCmd
 * Purpose: To handle the "while" statement
 *****************************************************************************/
void Parser::DoWhileCmd(void) {
  string s, lastsym;
  int nPos = lexer->GetFilePosition();
  while (1) {
    do {
      EvalExp(s, "do");
      lastsym = lexer->GetTagName();
    } while (lastsym != "do");

    // Now evaluate the return value of while.
    if (s == "0") {
      // ignore everything till an "end" statement
      int depth = 1;
      do {
	lastsym = lexer->GetNextTag();
	if (lastsym == "if" || lastsym == "while")
	  depth++;
	else if ((lastsym == "end" || lastsym == "else") && depth > 0)
	  depth--;
      } while (lastsym != "end" && depth > 0);
      break;
    } else {
      DoParse();
      lexer->SetFilePosition(nPos);
    }
  }
}

/******************************************************************************
 * Function: IsInteger
 * Purpose:  To determine if the string is an integer or not
 *****************************************************************************/
bool Parser::IsInteger(const string &s) {
  for (string::size_type i = 0; i < s.length(); i++) 
    if (!isdigit(s[i])) 
      return false;
  return true;
}


/******************************************************************************
 * Function: DoInputCmd
 * Purpose:  To handle the "input" statement
 *****************************************************************************/
void Parser::DoInputCmd(void) {
  string s, symname;
 
  getline(cin, s);
  symname = lexer->GetNextTag();
  if (symname != ";") {
    if (IsInteger(s))
      ivIntList[symname] = atol(s.c_str());
    else
      svStringList[symname] = s;
  }
}
