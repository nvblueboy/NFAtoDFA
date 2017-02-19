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
  string s = state;
  vector<string> outStates;
  //Keep going along epsilon transitions until you can't make one anymore.
  while (transitions[s].find("EPS") != transitions[s].end())
  {
    outStates.push_back(transitions[s]["EPS"]);
    s = transitions[s]["EPS"];
  }
  return outStates;
}
