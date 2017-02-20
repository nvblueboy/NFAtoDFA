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

//To use in the "toString" function in class NFA.
string join(vector<string> v, char d)
{
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

string NFA::deltaToString()
{
  //Find out how long the longest state is.
  int stateSize=0;
  for (int i = 0; i<states.size(); ++i)
  {
    if (states[i].length() > stateSize)
    {
      stateSize = states[i].length();
    }
  }
  //Iterate through each letter in the alpbabet.
  //Get the longest string to pretty-print the table.
  map<string, int> alphabetSize;
  for (int i = 0; i<alphabet.size()+1; ++i)
  {
    //Don't forget about eps transitions, so start at -1.
    int currentSize = 0;
    string currentLetter;
    if (i == alphabet.size())
    {
      //Before iterating through the letters, check for EPS.
      currentLetter = "EPS";
      currentSize = 3;
    } else {
      //Get the size of the letter.
      currentLetter = alphabet[i];
      currentSize = currentLetter.length();
    }
    for (int j = 0; j<states.size(); ++j)
    {
      //Get the output of the delta function for the state and letter.
      vector<string> output = transitions[states[j]][currentLetter];
      //Get it's size when joined.
      string str = join(output, ',');
      int s = str.length();
      //If it's the biggest string, mark that.
      if (s>currentSize)
      {
        currentSize = s;
      }
    }
    //Map it for use later on.
    alphabetSize[currentLetter] = currentSize;
  }
  //Now start to constuct the string.
  string outStr = "";
  //Construct the top row, showing the alphabet (and epsilon)
  outStr += string(stateSize, ' ')+ " |"; //Offset for the states.
  for (int i = 0; i<alphabet.size()+1; ++i)
  {
    string letter;
    if (i == alphabet.size())
    {
      letter = "EPS";
    } else {
      letter = alphabet[i];
    }
    outStr += pad(letter, ' ', alphabetSize[letter]) + " |";
  }
  outStr += "\n";
  for (int i = 0; i<states.size(); ++i)
  {
    string state = states[i];
    outStr += pad(state, ' ',stateSize)+" |";
    for (int j = 0; j<alphabet.size()+1; ++j)
    {
      string letter;
      if (j == alphabet.size())
      {
        letter = "EPS";
      } else {
        letter = alphabet[j];
      }

      //cout << "'" <<state <<"'" << letter <<"'" << endl;
      vector<string> output = transitions[state][letter];
      string out = pad(join(output,','), ' ',alphabetSize[letter]);
      //cout << "Out: "<<out << endl;
      outStr += out+" |";
    }
    outStr += "\n";
  }


  return outStr;
}

string NFA::toString()
{
  string outStr = "";
  outStr += "States: " + join(states, ',') + "\n";
  outStr += "Alphabet: " + join(alphabet, ',')+"\n";
  outStr += "Start state: " + startState + "\n";
  outStr += "Accept states: " + join(acceptStates, ',') + "\n";
  outStr += "Transition table: \n";
  outStr += deltaToString() + "\n";
  return outStr;
}
