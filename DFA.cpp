#include "DFA.h"

DFA::DFA()
{

}

DFA::~DFA()
{

}

DFA::DFA(vector<string> _states, vector<string> _alphabet,
  string _startState, vector<string> _acceptStates,
  map<string, map<string,string>> _transitions)
{
    states = _states;
    alphabet = _alphabet;
    currentState = _startState;
    startState = _startState;
    acceptStates = _acceptStates;
    transitions = _transitions;
}

string DFA::deltaToString()
{
  string outString = "   ";
  for (int i = 0; i<alphabet.size(); ++i)
  {
    outString = outString + alphabet[i] + "   ";
  }
  outString = outString+"\n";
  for (int i = 0; i<states.size(); ++i)
  {
    string s = states[i];
    string substring = s+"  ";
    for (int j = 0; j<alphabet.size(); ++j)
    {
      string a = alphabet[j];
      substring = substring + transitions[s][a] + "   ";
    }
    outString = outString + substring + "\n";
  }

  return outString;
}

string DFA::toString()
{
  string outStr = "";
  if (isAccepted())
  {
    outStr = "Accepted\n";
  } else {
    outStr = "Not Accepted\n";
  }
  outStr = outStr + "States: ";
  for (int i = 0; i<states.size(); ++i)
  {
    outStr = outStr + states[i];
    if (i+1 < states.size())
    {
      outStr = outStr + ", ";
    }
  }
  outStr = outStr + "\nAlphabet:";
  for (int i = 0; i<alphabet.size(); ++i)
  {
    outStr = outStr + alphabet[i];
    if (i+1<alphabet.size())
    {
      outStr = outStr + ", ";
    }
  }
  outStr = outStr + "\nCurrent state: "+currentState+"\nAccept states: ";
  for (int i = 0; i<acceptStates.size(); ++i)
  {
    outStr = outStr + acceptStates[i];
    if (i+1<acceptStates.size())
    {
      outStr = outStr + ", ";
    }
  }
  outStr = outStr + "\nTransition function: \n" + deltaToString();
  return outStr;
}

void DFA::input(string in)
{
  if (find(alphabet.begin(), alphabet.end(), in) == alphabet.end())
  {
    throw invalid_argument("That value is not in the valid alphabet.");
    return;
  }
  currentState = transitions[currentState][in];
  return;
}

bool DFA::isAccepted()
{
  return (find(acceptStates.begin(), acceptStates.end(), currentState) != acceptStates.end());
}
