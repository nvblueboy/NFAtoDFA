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
    vector<string> epsTransitions = transitions[s]["EPS"];
    for (int i = 0; i < epsTransitions.size(); ++i)
    {
      string poss = epsTransitions[i];
      if (find(visited.begin(), visited.end(), poss) == visited.end())
      {
        //If poss hasn't already been visited, add it to the queue.
        stateQueue.push(poss);
      }
    }
    //Mark the current state as visited.
    visited.push_back(s);
  }
  return visited;
}
