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
vector<string> queueToVector(queue<string> q);

class NFA{
public:
  NFA();
  NFA(vector<string> _states, vector<string> _alphabet,
    string _startState, vector<string> _acceptStates);
  ~NFA();
  void addTransition(string from, string input, string to);
  void setStates(vector<string> _states);
  void setAlphabet(vector<string> _alphabet);
  void setStartState(string _startState);
  void setAcceptStates(vector<string> _acceptStates);
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
