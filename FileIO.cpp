#include "FileIO.h"

int countChars(string in, char delimeter)
{
  //Counts the occurances of delimeter in the input.
  int count = 0;
  for (int i = 0; i<in.length(); ++i)
  {
    if (in[i] == delimeter)
    {
      count ++;
    }
  }
  return count;
}

vector<string> splitString(string in, char delimeter)
{
  vector<string> output;
  string current = "";
  for (int i = 0; i<in.length(); ++i)
  {
    if (in[i] != delimeter)
    {
      current += in[i];
    } else {
      if (current.length()>0)
      {
        output.push_back(current);
      }
      current = "";
    }
  }
  if (current.length()>0)
  {
    output.push_back(current);
  }
  return output;
}

NFA readFile(char* filename)
{
  ifstream infile(filename);
  vector<string> states;
  vector<string> alphabet;
  string startState;
  vector<string> acceptStates;
  map<string, map<string,vector<string>>> _transitions;

  if (infile.is_open())
  {
    string line;
    int linecount = 0;
    while (getline(infile, line))
    {
      linecount++;
      if (linecount == 1)
      {
        states = splitString(line, '\t');
      } else if (linecount == 2)
      {
        alphabet = splitString(line, '\t');
        cout << "Alphabet: "<< join(alphabet,'X') << endl;
      } else if (linecount == 3)
      {
        startState = line;
      } else if (linecount == 4)
      {
        acceptStates = splitString(line, '\t');
      } else {
        //Read in the transition function.
        vector<string> str1 = splitString(line,',');
        vector<string> str2 = splitString(str1[1],'=');
        vector<string> str {str1[0],str2[0],str2[1]};
        _transitions[str[0]][str[1]].push_back(str[2]);
      }
    }
  }
  return NFA(states,alphabet,startState,acceptStates,_transitions);
}
