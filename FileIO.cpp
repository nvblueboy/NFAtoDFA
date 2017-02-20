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

string cleanString(string input)
{
  //Removes newlines from the string.
  string outStr = "";
  for (int i = 0; i<input.length(); ++i)
  {
    if (input[i] != '\n' && input[i] != '\r')
    {
      outStr += input[i];
    }
  }
  return outStr;
}

NFA readFile(char* filename)
{
  ifstream infile(filename);
  vector<string> states;
  vector<string> alphabet;
  string startState;
  vector<string> acceptStates;
  map<string, map<string,vector<string>>> _transitions;
  NFA output;
  if (infile.is_open())
  {
    string line;
    int linecount = 0;
    while (getline(infile, line))
    {
      line = cleanString(line);
      linecount++;
      if (linecount == 1)
      {
        states = splitString(line, '\t');
        output.setStates(states);
      } else if (linecount == 2)
      {
        alphabet = splitString(line, '\t');
        output.setAlphabet(alphabet);
      } else if (linecount == 3)
      {
        startState = line;
        output.setStartState(startState);
      } else if (linecount == 4)
      {
        acceptStates = splitString(line, '\t');
        output.setAcceptStates(acceptStates);
      } else {
        //Read in the transition function.
        vector<string> str1 = splitString(line,',');
        vector<string> str2 = splitString(str1[1],'=');
        vector<string> str {str1[0],str2[0],str2[1]};
        output.addTransition(str[0],str[1],str[2]);
      }
    }
  }
  return output;
}
