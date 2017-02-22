#include "Boldness.h"


NFA convert(NFA input)
{
  vector<vector<string>> stateSetVisited;
  queue<vector<string>> stateSetQueue;
  //Start at the eps closure of the start state, q'_0.
  vector<string> startstate = input.epsClosure(input.startState);
  NFA output;
  //Push q'_0 to the queue to be processed.
  stateSetQueue.push(startstate);
  vector<string> currentStates;
  vector<string> nextSet;
  while(!stateSetQueue.empty())
  {
    //Set currentstates to the front of the queue, mark it as visited and pop.
    currentStates = stateSetQueue.front();
    stateSetVisited.push_back(stateSetQueue.front());
    stateSetQueue.pop();
    //Iterate through every letter.
    for (int j = 0; j < input.alphabet.size(); ++j)
    {
      nextSet.clear();
      string letter = input.alphabet[j];
      //Iterate through every state in currentStates.
      for (int i = 0; i < currentStates.size(); ++i)
      {
        string state = currentStates[i];
        //At this point, state is the current state and letter is the current letter.
        //Add the states reached by inputting letter into state into nextset.
        nextSet = vectorUnion(nextSet, input.transitions[state][letter]);
      }
      //Finally, get the epsilon closure of nextSet and add that to the queue
      //    if it hasn't already been visited.
      nextSet = input.epsClosures(nextSet);
      vector<vector<string>> queue = queueToVector(stateSetQueue);
      cout << "Checking: "<<join(nextSet,',',false) << endl;
      bool inQueue = vectorInVector(queue, nextSet);
      cout <<"I'm calling it I'm mr meeseeks look at me" << endl;
      bool visited = vectorInVector(stateSetVisited,nextSet);
      if (!inQueue && !visited)
      {
        cout << "True, pushing to queue." << endl;
        stateSetQueue.push(nextSet);
      }
      output.addState(join(nextSet,',',false));
    }
  }
  return output;
}
