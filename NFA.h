#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#ifndef NFA_H
#define NFA_H

string join(vector<string> v, char d, bool space);
string pad(string in, char d, int num);
string joinQueue(queue<string> q, char d);
template<class T>
bool pointInVector(vector<T> v, T s)
{

  for (int i = 0; i<v.size(); ++i)
  {
    T curr = v[i];
    if (curr == s)
    {
      return true;
    }
  }
  return false;
}


template<class T>
bool vectorEquality(vector<T> v_1, vector<T> v_2)
{
  //cout << "VecEq Called" << endl;
  //Checks 2 vectors to see if their elements are the same (regardless of order).
  for (int i = 0; i<v_1.size(); ++i)
  {
    T p = v_1[i];
    if (!pointInVector(v_2, p))
    {
      return false;
    }
  }
  for (int i = 0; i<v_2.size(); ++i)
  {
    T p = v_2[i];
    if (!pointInVector(v_1, p))
    {
      return false;
    }
  }
  return true;
}
template<class T>
bool vectorInVector(vector<vector<T>> v, vector<T> s)
{
  for (int i = 0; i<v.size(); ++i)
  {
    vector<T> curr = v[i];
    if (vectorEquality(s, curr))
    {
      return true;
    }
  }
  return false;
}
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
  void addAcceptState(string s);
  vector<string> epsClosures(vector<string> states);
  vector<string> epsClosure(string state);
  void deltaToString();
  void toString();
  string toOutputString();
  string deltaToOutString();

  vector<string> states;
  vector<string> alphabet;
  string startState;
  string currentState;
  vector<string> acceptStates;
  map<string, map<string,vector<string>>> transitions;

};

#endif
