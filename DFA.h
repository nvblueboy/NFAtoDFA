#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

#ifndef DFA_H
#define DFA_H

class DFA {
public:
  DFA();
  DFA(vector<string> _states, vector<string> _alphabet,
    string _startState, vector<string> _acceptStates,
    map<string, map<string,string>> _transitions);
  ~DFA();
  string toString();
  string deltaToString();
  void input(string in);
  bool isAccepted();
private:
  vector<string> states;
  vector<string> alphabet;
  string startState;
  string currentState;
  vector<string> acceptStates;
  map<string, map<string, string>> transitions;
};

#endif
