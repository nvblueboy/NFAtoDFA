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
  cout << "PIV called" << v.size() <<endl;
  for (int i = 0; i<v.size(); ++i)
  {
    T curr = v[i];
    cout << "Entered loop "<<curr << " " << s << " " << (curr == s) << endl;
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
  cout << "VecEq Called" << endl;
  //Checks 2 vectors to see if their elements are the same (regardless of order).
  for (int i = 0; i<v_1.size(); ++i)
  {
    T p = v_1[i];
    cout << "P v_1: "<< p << " v_2:"<< join(v_2,',',false)<< endl;
    if (!pointInVector(v_2, p))
    {
      return false;
    }
  }
  for (int i = 0; i<v_2.size(); ++i)
  {
    T p = v_2[i];
    cout << "P v_2: " << p << endl;
    if (!pointInVector(v_1, p))
    {
      return false;
    }
  }
  cout << "True" << endl;
  return true;
}
template<class T>
bool vectorInVector(vector<vector<T>> v, vector<T> s)
{
  if (s.size() == 0)
  {
    cout << "S is the empty set." << endl;
  } else {
    cout << "The set size is " << s.size() << endl;
  }
  for (int i = 0; i<v.size(); ++i)
  {
    vector<T> curr = v[i];
    cout << "Vector to check: " << join(curr,',',false) << endl;
    if (vectorEquality(s, curr))
    {
      return true;
    }
  }
  cout << "Vector: " << join(s,',',false) << endl;
  cout << "VectorInVector turned out to be false I'm mr. meeseeks look at me" << endl;
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
