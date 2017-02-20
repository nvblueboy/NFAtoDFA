#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#ifndef NFA_H
#define NFA_H

string join(vector<string> v, char d);
string pad(string in, char d, int num);
string joinQueue(queue<string> q, char d);

class NFA{
public:
  NFA();
  NFA(vector<string> _states, vector<string> _alphabet,
    string _startState, vector<string> _acceptStates,
    map<string, map<string,vector<string>>> _transitions);
  ~NFA();
  vector<string> epsClosure(string state);
  void deltaToString();
  void toString();

  vector<string> states;
  vector<string> alphabet;
  string startState;
  string currentState;
  vector<string> acceptStates;
  map<string, map<string,vector<string>>> transitions;

};

#endif
