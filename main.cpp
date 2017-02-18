#include <iostream>
#include <map>
#include <vector>
#include "DFA.h"

using namespace std;

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    //return 0; #TODO: Uncomment this line.
    cout << "Using a pre-made FSA" << endl;
    vector<string> Q;
    Q.push_back("1");
    Q.push_back("2");
    Q.push_back("3");

    vector<string> E;
    E.push_back("a");
    E.push_back("b");

    vector<string> F;
    F.push_back("2");

    map<string, map<string,string>> delta;
    delta["1"]["a"] = string("1");
    delta["1"]["b"] = "2";
    delta["2"]["a"] = "3";
    delta["2"]["b"] = "2";
    delta["3"]["a"] = "2";
    delta["3"]["b"] = "2";

    DFA myDFA(Q, E, "1", F, delta);
    cout << myDFA.toString() << endl;
  }






  return 0;
}
