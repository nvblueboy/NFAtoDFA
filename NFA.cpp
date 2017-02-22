#include "NFA.h"


NFA::NFA()
{

}

NFA::~NFA()
{

}

NFA::NFA(vector<string> _states, vector<string> _alphabet,
  string _startState, vector<string> _acceptStates)
{
  states = _states;
  alphabet = _alphabet;
  currentState = _startState;
  startState = _startState;
  acceptStates = _acceptStates;
}

void NFA::addTransition(string from, string input, string to)
{
  transitions[from][input].push_back(to);
}

void NFA::setStates(vector<string> _states)
{
  states = _states;
}

void NFA::addState(string _state)
{
  if (!pointInVector(states, _state))
  {
    states.push_back(_state);
  }
}

void NFA::setAlphabet(vector<string> _alphabet)
{
  alphabet = _alphabet;
}

void NFA::setStartState(string _startState)
{
  startState = _startState;
}

void NFA::setAcceptStates(vector<string> _acceptStates)
{
  acceptStates = _acceptStates;
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
    string curr = v[i];
    if (curr == s)
    {
      return true;
    }
  }
  return false;
}


vector<string> vectorUnion(vector<string> v_1, vector<string> v_2)
{
  vector<string> output;
  for (int i = 0; i<v_1.size(); ++i)
  {
    //Copy v_1 into output.
    output.push_back(v_1[i]);
  }
  for (int i = 0; i<v_2.size(); ++i)
  {
    if (!pointInVector(output,v_2[i]))
    {
      output.push_back(v_2[i]);
    }
  }
  return output;
}

vector<string> NFA::epsClosures(vector<string> states)
{
  vector<string> output;
  for (int i = 0; i < states.size(); ++i)
  {
    output = vectorUnion(output, epsClosure(states[i]));
  }
  return output;
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
    //Get the front element of the queue and pop it.
    s = stateQueue.front();
    stateQueue.pop();
    //Mark the current state as visited.
    visited.push_back(s);
    vector<string> epsTransitions = transitions[s]["EPS"];
    for (int i = 0; i < epsTransitions.size(); ++i)
    {
      vector<string> q_vec = queueToVector(stateQueue);
      string poss = epsTransitions[i];
      if (!pointInVector(visited, poss) && !pointInVector(q_vec, poss))
      {
        //If poss hasn't already been visited, add it to the queue.
        //Unless it's already in the queue, then don't add it.
        stateQueue.push(poss);
      }
    }
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
    string state = states[i];
    for (int j = 0; j<alphabet.size()+1; ++j)
    {
      string letter;
      if (j == alphabet.size())
      {
        letter = "EPS";
      } else {
        letter = alphabet[j];
      }
      vector<string> states = transitions[state][letter];
      string out = join(transitions[state][letter],',');
      if (out.length() > 0)
      {
        cout << state << ", " << letter << " = "<< out << endl;
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
