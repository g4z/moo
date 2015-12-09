/*
 * Copyright (c) 2002 Mayukh Bose
 * See the file LICENSE for details.
 */

#ifndef __FILEREADER_H__
#define __FILEREADER_H__

#include <string>
using namespace std;

class FileReader {
 private:
  long filesize;
  long filepos;
  string sBuf;
  long nLine, nColumn;
 public:
  FileReader(char *filename);
  char GetChar();
  void UngetChar();
  string DumpBuf();
  long GetLineNum();
  long GetColumnNum();
  long GetFilePosition();
  void SetFilePosition(long nPos);
};

#endif
