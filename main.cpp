
#include "CompiledDfa.h"
#include "CompiledNfaEpsilon.h"

using namespace std;

int main()
{
////DFA, recognizes binary numbers that are multiples of 3
//   Transition t1(1, '0', 1);
//   Transition t2(1, '1', 2);
//   Transition t3(2, '1', 1);
//   Transition t4(2, '0', 3);
//   Transition t5(3, '0', 2);
//   Transition t6(3, '1', 3);
//   FiniteStateMachine f;
//   f.nodes.insert(1);
//   f.nodes.insert(2);
//   f.nodes.insert(3);
//   f.startNode = 1;
//   f.goalNodes.insert(1);
//   f.transitions.push_front(t1);
//   f.transitions.push_front(t2);
//   f.transitions.push_front(t3);
//   f.transitions.push_front(t4);
//   f.transitions.push_front(t5);
//   f.transitions.push_front(t6);
//
////DFA equivalent to regular expression a+
//   Transition t1(1, 'a', 2);
//   Transition t2(2, 'a', 2);
//   FiniteStateMachine f;
//   f.nodes.insert(1);
//   f.nodes.insert(2);
//   f.startNode = 1;
//   f.goalNodes.insert(2);
//   f.transitions.push_front(t1);
//   f.transitions.push_front(t2);

////NFA, recognizes strings containing only a's and b's and ending in a
//   Transition t1(1, 'a', 1);
//   Transition t2(1, 'b', 1);
//   Transition t3(1, 'a', 2);
//   FiniteStateMachine f;
//   f.nodes.insert(1);
//   f.nodes.insert(2);
//   f.startNode = 1;
//   f.goalNodes.insert(2);
//   f.transitions.push_front(t1);
//   f.transitions.push_front(t2);
//   f.transitions.push_front(t3);

////NFA-E, equivalent to a*b*c*
//   Transition t1(1, 'a', 1);
//   Transition t2(1, '0', 2);
//   Transition t3(2, 'b', 2);
//   Transition t4(2, '0', 3);
//   Transition t5(3, 'c', 3);
//   FiniteStateMachine f;
//   f.nodes.insert(1);
//   f.nodes.insert(2);
//   f.nodes.insert(3);
//   f.startNode = 1;
//   f.goalNodes.insert(1);
//   f.goalNodes.insert(2);
//   f.goalNodes.insert(3);
//   f.transitions.push_front(t1);
//   f.transitions.push_front(t2);
//   f.transitions.push_front(t3);
//   f.transitions.push_front(t4);
//   f.transitions.push_front(t5);

//NFA-E, determines if even number of o's or l's
   Transition t1(1, '0', 2);
   Transition t2(1, '0', 4);
   Transition t3(2, 'l', 2);
   Transition t4(2, 'o', 3);
   Transition t5(3, 'l', 3);
   Transition t6(3, 'o', 2);
   Transition t7(4, 'o', 4);
   Transition t8(4, 'l', 5);
   Transition t9(5, 'l', 4);
   Transition t10(5, 'o', 5);
   FiniteStateMachine f;
   f.nodes.insert(1);
   f.nodes.insert(2);
   f.nodes.insert(3);
   f.nodes.insert(4);
   f.nodes.insert(5);
   f.startNode = 1;
   f.goalNodes.insert(2);
   f.goalNodes.insert(4);
   f.transitions.push_front(t1);
   f.transitions.push_front(t2);
   f.transitions.push_front(t3);
   f.transitions.push_front(t4);
   f.transitions.push_front(t5);
   f.transitions.push_front(t6);
   f.transitions.push_front(t7);
   f.transitions.push_front(t8);
   f.transitions.push_front(t9);
   f.transitions.push_front(t10);

   CompiledNfaEpsilon nfa(f);
   string s = "oooll";
   cout << "String entered: " << s << endl;
   cout << endl << "NFA: ";
   if (nfa.recognized(s))
   cout << "valid";
   else {cout << "invalid";}

   FiniteStateMachine test = nfa.convert();
   CompiledDfa c(test);

   cout << endl << "DFA: ";
   if (c.recognized(s))
   cout << "valid";
   else {cout << "invalid";}
   cout << endl;

   cout << endl << "NEW MACHINE:" << endl;
   cout << "Nodes: ";
   for (auto it = test.nodes.begin(); it != test.nodes.end(); ++it)
      cout << (*it) << " ";
   cout << endl << "Start at " << test.startNode << endl;
   cout << "Goal states: ";
   for (auto git = test.goalNodes.begin(); git != test.goalNodes.end(); ++git)
      cout << (*git) << " ";
   cout << endl << "All transitions:" << endl;
   for (auto tranit = test.transitions.begin(); tranit != test.transitions.end(); ++tranit)
      cout << (*tranit).source << " to " << (*tranit).destination << " on "
         << (*tranit).transitionChar << endl;


   return EXIT_SUCCESS;
}




