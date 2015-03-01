//------------------------------------------------------------------------
// File: CompiledNfaEpsilon.h
// Programmer: Sarah Kazemian
//------------------------------------------------------------------------
//Pseudocode for part 1:
//
//CompiledNfaEpsilon {
//public:
//   CompiledNfaEpsilon(FiniteStateMachine fsm);
//   bool recognized(string s);
//
//private:
//   Dictionary<int,int> states
//   List<int> currentStates;
//}
//
//CompiledNfaEpsilon {
//   for each entry in fsm.transitions
//      key = source plus transition char
//      value = destination
//      add entry to states table
//}
//
//bool recognized(string s) {
//
//   add all nodes which can be reached using only epsilon transitions
//   to currentNodes list
//
//   for each character in s
//      for each state in currentStates
//         look up transitions on current character
//            replace currentStates entries
//
//      for each state now in currentStates
//         add any possible epsilon transitions to currentStates
//
//
//   for all the nodes in currentStates
//      if (node's value = one of the goal nodes)
//         return true
//
//   return false if no states matched
//}
//----------------------------------------------------------------------
//Pseudocode for part 3:
//
////converter function is a member of compiledNFA class
//FiniteStateMachine converter() {
//   FiniteStateMachine dfa
//
//   set<char> transitionChars //build a list of all input characters
//
//   set<int> initial
//   Add all nodes accessible by epsilon transitions to the initial set
//   initial.insert(start node)
//
//   dfa.startNode = hashed(initial set)
//
//   for each (transitionChars)
//      findPaths(initial, transition character)
//
//   return fsm
//}
//
//findPaths(set<int> nodes, char c) {
//   set<int> results
//   int key
//
//   for each int in nodes
//      key = hash int with c
//      get all connections using key
//      for each connection
//         insert the destination node into results
//
//   int number = hash(results)
//   if (the results contained an accepting state)
//      add number to dfa's goal node list
//
//   Transition t(nodes, c, number)
//
//   if (the dfa's transition list does not already contain t)
//      add t to dfa's transition list
//      for each (transitionChars)
//         findPaths(results, transition character)
//}
#ifndef COMPNFAE_H
#define COMPNFAE_H

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <list>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "CompiledDfa.h"

using namespace std;

const int MAXNODES = 100; //maximum number of nodes(for unique hashing)
const char EPSILON = '0';
const int NOVAL = 0;
const int ASCII_MIN = 33; //which ascii character range to accept
const int ASCII_MAX = 126;

//struct Transition {
//    int source;
//    char transitionChar;
//    int destination;
//
//    Transition(int s, char t, int d) : source(s), transitionChar(t), destination(d) {}
//};
//
//struct FiniteStateMachine {
//    set<int> nodes;
//    int startNode;
//    set<int> goalNodes;
//    list<Transition> transitions;
//};

//------------------------------------------------------------------------
// Compiled NFA-Epsilon Class
//------------------------------------------------------------------------
class CompiledNfaEpsilon {
public:
   CompiledNfaEpsilon(FiniteStateMachine);
   bool recognized(string s);
   FiniteStateMachine convert(void);

private:
   FiniteStateMachine fsm;
   FiniteStateMachine dfa;
   unordered_multimap<int,int> connections;
   unordered_set<int> currentStates;
   set<char> transChars;
   unordered_set<int> newTrans;

   void epsilon(int, unordered_set<int> &);
   void findPaths(unordered_set<int> &, char);
   bool accepting(unordered_set<int> );
   int hasher(unordered_set<int>);
   int quickHash(int, char);
};


#endif
