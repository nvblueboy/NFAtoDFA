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
bool pointInVector(vector<string> v, string s);
template<class T>
vector<T> queueToVector(queue<T> q)
{
  int s = q.size();
  vector<T> out;
  for (int i = 0; i<s; ++i)
  {
    out.push_back(q.front());
    q.push(q.front());
    q.pop();
  }
  return out;
}
vector<string> queueToVector(queue<string> q);
vector<vector<string>> listQueueToVector(queue<vector<string>> q);
vector<string> vectorUnion(vector<string> v_1, vector<string> v_2);

class NFA{
public:
  NFA();
  NFA(vector<string> _states, vector<string> _alphabet,
    string _startState, vector<string> _acceptStates);
  ~NFA();
  void addTransition(string from, string input, string to);
  void setStates(vector<string> _states);
  void addState(string _state);
  void setAlphabet(vector<string> _alphabet);
  void setStartState(string _startState);
  void setAcceptStates(vector<string> _acceptStates);
  vector<string> epsClosures(vector<string> states);
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
