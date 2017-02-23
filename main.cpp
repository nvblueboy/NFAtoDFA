#include <iostream>
#include <map>
#include <vector>
#include "DFA.h"
#include "NFA.h"
#include "FileIO.h"
#include "Boldness.h"

using namespace std;

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
  } else {
    NFA myNFA = readFile(argv[1]);
    NFA newDFA = convert(myNFA);
    newDFA.toString();
    string output = newDFA.toOutputString();
    ofstream outFile("output.DFA");
    outFile << output;
    outFile.close();
  }
  return 0;
}
