//------------------------------------------------------------------------
// File: CompiledDfa.cpp
// Programmer: Sarah Kazemian
//------------------------------------------------------------------------
#include "CompiledDfa.h"

//-----------------------------------------------------------------------------
//	Method:			CompiledNfaEpsilon(FiniteStateMachine newFsm)
//
//	Description:	constructor, builds list of connections between nodes
//
// Calls:         none
//
// Called By:		n/a
//
// Parameters:		FiniteStateMachine newFsm -- finite state machine to
//                                             construct
//
// Returns:		   n/a
// ----------------------------------------------------------------------------
CompiledDfa::CompiledDfa(FiniteStateMachine newFsm) { //constructor
   fsm = newFsm;
   list<Transition>::const_iterator it;
   for (it = fsm.transitions.begin(); it != fsm.transitions.end(); it++) {
      int key = (it->source * OFFSET) + it->transitionChar;
      connections.emplace(key, it->destination);
   }
}
//-----------------------------------------------------------------------------
//	Method:			bool recognized(string s)
//
//	Description:	determines if a given string s is recognized by the finite
//                   state machine
//
// Calls:         none
//
// Called By:		n/a
//
// Parameters:		string s -- string of characters to analyze
//
// Returns:		   true if string s is recognized, false otherwise
// ----------------------------------------------------------------------------
bool CompiledDfa::recognized(string s) {

   int currentState = fsm.startNode;
   int key;
   for (int i = 0; i < s.size(); i++) {
      key = currentState * OFFSET + s[i];
      auto nextState = connections.find(key);
      if (nextState != connections.end()) {
         currentState = nextState->second;
      }
      else {return false;}
   }
   if (fsm.goalNodes.count(currentState) != 0) {
      return true;
   }
   else {return false;}
}
