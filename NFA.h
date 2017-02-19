#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

class NFA{
public:
  NFA();
  NFA(vector<vector<string>> _states, vector<string> _alphabet,
    vector<string> _startState, vector<vector<string>> _acceptStates,
    map<string, map<string,vector<string>>> _transitions);
  ~NFA();
  vector<string> epsClosure(vector<string> state);
  vector<vector<string>> states;
  vector<string> alphabet;
  vector<string> startStates;
  vector<vector<string>> acceptStates;
  map<string, map<string,vector<string>>> _transitions;

};
