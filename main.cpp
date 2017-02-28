#include <iostream>
#include <map>
#include <vector>
#include "NFA.h"
#include "FileIO.h"
#include "Boldness.h"

using namespace std;

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
  } else {
    NFA myNFA = readFile(argv[1]);
    NFA newDFA = convert(myNFA);
    string output = newDFA.toOutputString();
    const char* filename;
    if (argc > 2)
    {
      filename = argv[2];
    } else {
      filename = "output.DFA";
    }
    ofstream outFile(filename);
    outFile << output;
    outFile.close();
  }
  return 0;
}
