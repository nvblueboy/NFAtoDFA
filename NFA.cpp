#include "NFA.h"


NFA::NFA()
{

}

NFA::~NFA()
{

}

NFA::NFA(vector<string> _states, vector<string> _alphabet,
  string _startState, vector<string> _acceptStates,
  map<string, map<string,vector<string>>> _transitions)
{
  states = _states;
  alphabet = _alphabet;
  currentState = _startState;
  startState = _startState;
  acceptStates = _acceptStates;
  transitions = _transitions;
}

string joinQueue(queue<string> q, char d)
{
  int s = q.size();
  vector<string> out;
  for (int i = 0; i<s; ++i)
  {
    out.push_back(q.front());
    q.push(q.front());
    q.pop();
  }
  return join(out,d);
}

bool pointInVector(vector<string> v, string s)
{
  for (int i = 0; i<v.size(); ++i)
  {
    if (v[i] == s)
    {
      return true;
    }
  }
  return false;
}

vector<string> NFA::epsClosure(string state)
{
  //Put the first state in the queue then search until the queue is empty.
  queue<string> stateQueue;
  vector<string> visited;
  stateQueue.push(state);
  string s = "";
  while (!stateQueue.empty())
  {
    cout << joinQueue(stateQueue,',') << endl;
    //Get the front element of the queue and pop it.
    s = stateQueue.front();
    stateQueue.pop();
    vector<string> epsTransitions = transitions[s]["EPS"];
    for (int i = 0; i < epsTransitions.size(); ++i)
    {
      string poss = epsTransitions[i];
      if (!pointInVector(visited, poss))
      {
        //If poss hasn't already been visited, add it to the queue.
        cout << "Pushing " << poss << endl;
        stateQueue.push(poss);
      } else {
        cout << "Already visited " << poss << endl;
      }
    }
    //Mark the current state as visited.
    visited.push_back(s);
  }
  return visited;
}

//To use in the "toString" function in class NFA.
string join(vector<string> v, char d)
{
  if (v.size() == 0)
  {
    return "";
  }
  string outStr = "";
  for (int i = 0; i<v.size(); ++i)
  {
    outStr += v[i];
    if (i+1<v.size())
    {
      //If it's not the last element, add the delimeter and a space.
      outStr += string(1,d) + " ";
    }
  }
  return outStr;
}

string pad(string in, char d, int num)
{
  //Pads string in with char d to be num chars long.
  int len = in.length();
  if (len >= num)
  {
    return in;
  }
  string p = string(num-len,d);
  return p+in;
}

void NFA::deltaToString()
{
  for (int i = 0; i<states.size(); ++i)
  {
    //cout <<"i " << i << endl;
    string state = states[i];
    //cout << "State: " << state << endl;
    for (int j = 0; j<alphabet.size()+1; ++j)
    {
      //cout << "j "<< j << endl;
      string letter;
      if (j == alphabet.size())
      {
        letter = "EPS";
      } else {
        letter = alphabet[j];
      }
      //cout << "Letter: "<<letter << endl;
      string out = join(transitions[state][letter],',');
      if (out.length() > 0)
      {
        cout << "Function: "<< state << ", "<<letter<<" = "<<out << endl;
      }
    }
  }
}
void NFA::toString()
{
  cout << "States: " << join(states, ',') << endl;
  cout << "Alphabet: " << join(alphabet, ',')<< endl;
  cout << "Start state: " << startState << endl;
  cout << "Accept states: " << join(acceptStates, ',') << endl;
  cout << "Transition table: " << endl;
  deltaToString();
}
