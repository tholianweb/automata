//------------------------------------------------------------------------
// File: CompiledDfa.h
// Programmer: Sarah Kazemian
//------------------------------------------------------------------------
//Pseudocode for part 2:
//
//CompiledDfa {
//public:
//   CompiledDfa(FiniteStateMachine fsm);
//   bool recognized(string s);
//
//private:
//   Dictionary<int,int> connections
//}
//
//CompiledDfa {  //constructor
//   for each entry in fsm.transitions
//      key = source plus transition char
//      value = destination
//      add entry to connections table
//}
//
//bool recognized(string s) {
//
//   currentState = fsm.startNode
//
//   for each character in s
//         look up next state in connections hash
//         replace currentState entry
//
//   if (currentState = one of the goal nodes)
//      return true
//   else
//      return false
//}
#ifndef COMPDFA_H
#define COMPDFA_H

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <list>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;
const int OFFSET = 1000;

struct Transition {
    int source;
    char transitionChar;
    int destination;

    Transition(int s, char t, int d) : source(s), transitionChar(t), destination(d) {}
};

struct FiniteStateMachine {
    set<int> nodes;
    int startNode;
    set<int> goalNodes;
    list<Transition> transitions;
};

//------------------------------------------------------------------------
// Compiled Deterministic Finite Automata (DFA) Class
//------------------------------------------------------------------------
class CompiledDfa {
public:
   CompiledDfa(FiniteStateMachine);
   bool recognized(string s);

private:
   void addToMap(Transition);
   FiniteStateMachine fsm;
   unordered_map<int,int> connections;
};


#endif
