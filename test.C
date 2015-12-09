/*
 * Copyright (c) 2002 Mayukh Bose
 * See the file LICENSE for details.
 */

#include <iostream>
#include <string>

#include "parser.h"

using namespace std;

int main(int argc, char **argv) {

  if (argc < 2) {
    cout << "MOO interpreter, Copyright (c) 2002 Mayukh Bose." << endl;
    cout << "Released under the BSD license. See the file LICENSE for details." << endl;
    cout << "Usage: " << argv[0] << " filename" << endl;
    cout << "Where filename is the name of a MOO source file." << endl;
    return 1;
  }

  try {
    Parser foo(argv[1]);
    foo.Run();
    //cout << "Dumping all variables now\n";
    //foo.DumpVariables();
  } catch (char *err) {
    cerr << err << "\n";
  }

  return 0;
}
