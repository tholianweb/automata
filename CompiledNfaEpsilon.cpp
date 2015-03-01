//------------------------------------------------------------------------
// File: CompiledNfaEpsilon.cpp
// Programmer: Sarah Kazemian
//------------------------------------------------------------------------
#include "CompiledNfaEpsilon.h"

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
CompiledNfaEpsilon::CompiledNfaEpsilon(FiniteStateMachine newFsm) {
   fsm = newFsm;
   list<Transition>::const_iterator it;
   for (it = fsm.transitions.begin(); it != fsm.transitions.end(); it++) {
      int key = quickHash(it->source, it->transitionChar);
      connections.emplace(key, it->destination);
   }
}
//-----------------------------------------------------------------------------
//	Method:			bool recognized(string s)
//
//	Description:	determines if a given string s is recognized by the finite
//                   state machine
//
// Calls:         epsilon();
//
// Called By:		n/a
//
// Parameters:		string s -- string of characters to analyze
//
// Returns:		   true if string s is recognized, false otherwise
// ----------------------------------------------------------------------------
bool CompiledNfaEpsilon::recognized(string s) {

   currentStates.insert(fsm.startNode);
   int key;
   unordered_set<int>::const_iterator stateIt;
   unordered_set<int> newStates;

   epsilon(fsm.startNode, currentStates);

   for (int i = 0; i < s.size(); i++) {
      for (stateIt = currentStates.begin(); stateIt != currentStates.end(); stateIt++) {
         key = quickHash(*stateIt, s[i]);
         auto states = connections.equal_range(key);
         for (auto it = states.first; it != states.second; ++it) {
            newStates.insert(it->second);
         }
      }
      currentStates.clear();
      currentStates = newStates;
      newStates.clear();

      stateIt = currentStates.begin();
      while (stateIt != currentStates.end()) {
         epsilon(*stateIt, currentStates);
         stateIt++;
      }
   }
   return (accepting(currentStates));
}
//-----------------------------------------------------------------------------
//	Method:			void epsilon(int start)
//
//	Description:	puts all nodes that can be reached using epsilon transitions,
//                   starting at the start node, in the current states list
//
// Calls:         epsilon(); -- recursively
//
// Called By:		recognized();
//
// Parameters:		int start -- node to start at
//
// Returns:		   void
// ----------------------------------------------------------------------------
void CompiledNfaEpsilon::epsilon(int start, unordered_set<int> &nodes)
{
   int key = quickHash(start, EPSILON);
   auto initial = connections.equal_range(key);
   for (auto it = initial.first; it != initial.second; ++it) {
      epsilon(it->second, nodes);
      nodes.insert(it->second);
   }
}
//-----------------------------------------------------------------------------
//	Method:			FiniteStateMachine convert()
//
//	Description:	converts the NFA into an equivalent DFA
//
// Calls:         epsilon();
//                findPaths();
//
// Parameters:		void
//
// Returns:		   FiniteStateMachine - the equivalent DFA
// ----------------------------------------------------------------------------
FiniteStateMachine CompiledNfaEpsilon::convert(void)
{
   for (auto it = fsm.transitions.begin(); it != fsm.transitions.end(); it++) {
      transChars.insert(it->transitionChar);
   }
   transChars.erase(EPSILON);

   unordered_set<int> initial;
   initial.insert(fsm.startNode);
   epsilon(fsm.startNode, initial);

   int start = hasher(initial);
   if (accepting(initial)) {dfa.goalNodes.insert(start);}
   dfa.startNode = start;
   dfa.nodes.insert(start);

   for (auto cit = transChars.begin(); cit != transChars.end(); cit++) {
      findPaths(initial, *cit);
   }

   return dfa;
}
//-----------------------------------------------------------------------------
//	Method:			void findPaths(unordered_set<int> nodes, char transChar)
//
//	Description:	finds all DFA nodes and transitions
//
// Calls:         findPaths(); -- recursively
//
// Called By:		convert();
//
// Parameters:		unordered_set<int> nodes -- current nodes
//                char transChar -- character to check for transitions on
//
// Returns:		   void
// ----------------------------------------------------------------------------
void CompiledNfaEpsilon::findPaths(unordered_set<int> &nodes, char transChar)
{
   unordered_set<int> results;
   unordered_set<int> temp;
   int key = 0;
   int checkTrans = 0;

   for (auto it = nodes.begin(); it != nodes.end(); ++it) {
      key = quickHash(*it, transChar);
      auto states = connections.equal_range(key);
         for (auto sit = states.first; sit != states.second; ++sit) {
            results.insert(sit->second);
         }
   }

   for (auto rit = results.begin(); rit != results.end(); ++rit) {
      epsilon(*rit, temp);
   }
   for (auto tempit = temp.begin(); tempit != temp.end(); ++tempit) {
      results.insert(*tempit);
   }

   int number = hasher(results);
   if (accepting(results)) { dfa.goalNodes.insert(number);}

   checkTrans = quickHash(hasher(nodes), transChar);
   if (newTrans.count(checkTrans) == 0) {
      newTrans.insert(checkTrans);
      if (dfa.nodes.count(number) == 0) {dfa.nodes.insert(number);}

      Transition t(hasher(nodes), transChar, number);
      dfa.transitions.push_front(t);
      for (auto cit = transChars.begin(); cit != transChars.end(); cit++) {
         findPaths(results,*cit);
      }
   }
}
//-----------------------------------------------------------------------------
//	Method:			bool accepting(unordered_set<int> checkSet)
//
//	Description:	determines if a given set of states contains a goal state
//
// Called By:		recognized();
//                findPaths();
//
// Parameters:		unordered_set<int> checkSet -- states to check
//
// Returns:		   true if set contains a goal state, false otherwise
// ----------------------------------------------------------------------------
bool CompiledNfaEpsilon::accepting(unordered_set<int> checkSet)
{
   unordered_set<int>::const_iterator it;
   for (it = checkSet.begin(); it != checkSet.end(); it++) {
      if (fsm.goalNodes.count(*it) != 0) {
         return true;
      }
   }
   return false; //not in goal nodes set
}
//-----------------------------------------------------------------------------
//	Method:			int hasher(unordered_set<int> s)
//
//	Description:	converts any set into a unique identifier
//
// Called By:		convert();
//
// Parameters:		unordered_set<int> s -- set to convert
//
// Returns:		   int -- a number identifying the set, 0 if empty set
//                (NOTE - GIVES SAME RETURN VALUE REGARDLESS OF SET ORDER)
// ----------------------------------------------------------------------------
int CompiledNfaEpsilon::hasher(unordered_set<int> s)
{
   int hashed = 0;
   int count = 1;
   set<int> c;
   //first, sort the set to ensure duplicate sets hash to the same thing:
   copy(s.begin(), s.end(), inserter(c, c.end()));

   for (set<int>::reverse_iterator rit = c.rbegin(); rit != c.rend(); ++rit) {
      hashed += (*rit * count);
      count *= MAXNODES;
   }
   return hashed;
}
//-----------------------------------------------------------------------------
//	Method:			int quickHash(int i, char c)
//
//	Description:	hashes together a node int and a transition character
//
// Called By:		convert();
//                recognized();
//                CompiledNfaEpsilon();
//
// Parameters:		int i -- node identifier
//                char c -- transition character
//
// Returns:		   int -- the hashed number
// ----------------------------------------------------------------------------
int CompiledNfaEpsilon::quickHash(int i, char c)
{
   int offset = 1000;
   int hashed = (c >= ASCII_MIN && c <= ASCII_MAX)? ((i * offset) + c) : NOVAL;
   return hashed;
}

