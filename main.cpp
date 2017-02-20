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
    vector<string> Q {"1","2","3","4","5","6"};

    vector<string> E {"a","b"};

    vector<string> F {"2"};

    map<string, map<string,vector<string>>> delta;
    delta["1"]["a"]={"5","2"};
    delta["1"]["b"]={"6"};
    delta["1"]["EPS"]={"2","3"};
    delta["5"]["EPS"]={"2"};
    delta["2"]["EPS"]={"3"};
    delta["3"]["EPS"]={"4"};
    delta["3"]["EPS"]={"1"};

    NFA myNFA(Q, E, "1", F, delta);
    myNFA.toString();
    vector<string> epsOne = myNFA.epsClosure("1");
    vector<string> epsFive = myNFA.epsClosure("5");

    for (int i = 0; i<epsOne.size(); ++i)
    {
      cout << "'"<< epsOne[i] <<"'"<< " ";
    }
    cout << endl;

    for (int i = 0; i<epsFive.size(); ++i)
    {
      cout << epsFive[i] << " ";
    }
    cout << endl;

  } else {
    NFA myNFA = readFile(argv[1]);
    myNFA.toString();
  }






  return 0;
}
