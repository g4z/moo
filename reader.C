/*
 * Copyright (c) 2002 Mayukh Bose
 * See the file LICENSE for details.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "reader.h"

using namespace std;

// Method to open a file
FileReader::FileReader(char *filename) {
  long start, end, size;
  string sTemp;
  
  // Set up the private variables
  filepos = 0;
  sBuf = "";

  // Next figure out the filesize
  ifstream file(filename, ios::in | ios::binary);
  if (!file.is_open()) 
    throw "FileReader: file could not be opened for input";

  start = file.tellg();
  file.seekg(0, ios::end);
  end = file.tellg();
  filesize = end - start;
  file.seekg(0, ios::beg);
  while (std::getline(file, sTemp)) {
    sBuf += sTemp + "\n";
  }
  file.close();

  nLine = nColumn = 1;
}

char FileReader::GetChar() {
  if (filepos < filesize) {
    if (sBuf[++filepos] == '\n') {
      nLine++;
      nColumn = 1;
    }
    else
      nColumn++;
    return (char) sBuf[filepos];
  }
  else
    return '\0';
}

void FileReader::UngetChar() {
  if (filepos > 0) {
    filepos--;
    nColumn--;
  }
}

string FileReader::DumpBuf() {
  return sBuf;
}

long FileReader::GetLineNum() {
  return nLine;
}

long FileReader::GetColumnNum() {
  return nColumn;
}

long FileReader::GetFilePosition() {
  return filepos;
}

void FileReader::SetFilePosition(long nPos) {
  if (nPos < filesize)
    filepos = nPos;
}
