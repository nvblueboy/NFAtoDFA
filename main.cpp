#include <iostream>
#include <map>
#include <vector>
#include "DFA.h"
#include "NFA.h"
#include "FileIO.h"

using namespace std;

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    //return 0; #TODO: Uncomment this line.
    cout << "Using a pre-made FSA\n" << endl;
    vector<string> Q;
    Q.push_back("1");
    Q.push_back("2");
    Q.push_back("3");
    Q.push_back("4");

    vector<string> E;
    E.push_back("a");
    E.push_back("b");

    vector<string> F;
    F.push_back("2");

    map<string, map<string,vector<string>>> delta;
    delta["1"]["EPS"] = {"2"};
    delta["1"]["a"] = {"2"};
    delta["1"]["b"] = {"3","2","4"};
    delta["2"]["EPS"] = {"1","4"};
    delta["2"]["a"] = {"4"};
    delta["2"]["b"] = {"1"};
    delta["4"]["EPS"] = {"3"};
    delta["4"]["a"] = {"2"};
    delta["4"]["b"] = {"3"};
    delta["3"]["a"] = {"2"};
    delta["3"]["b"] = {"4"};

    NFA myNFA(Q, E, "1", F, delta);
    cout << myNFA.toString() << endl;
  } else {
    NFA myNFA = readFile(argv[1]);
    cout << myNFA.toString() << endl;
  }






  return 0;
}
