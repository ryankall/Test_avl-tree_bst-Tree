/*
 *       FileName: SequenceMap.h

 *
 *      Created on: Feb 18, 2015
 *      Author: Ryan Kallicharran
 *      Purpose: Defining the function
 */

#ifndef SEQUENCEMAP_H_
#define SEQUENCEMAP_H_

#include <vector>
#include <string>
using namespace std;
class SequenceMap 
{
 
public:
  SequenceMap();//default constructor
  
  //set recognition_sequence
  //@param a string
  void set_key( const string new_entry);

  //adds an enzyme to the vector
  //@param a string
  void Add_enzyme( const string new_entry);

  //check if enzyme is contained in the vector
  //@param a string
  //@return true if string is found otherwise false
   bool Contains(const string& an_entry) const;
  
   //add two sequence object together no repeats in vector
  //@param on rhs a Sequence object
  //@return a combined SequenceMap
   SequenceMap* operator+( SequenceMap &set1);
  
  //Checks the rhs is greater than the left
  //@param a Sequence object
  //@return true if left less than right
  bool operator<( SequenceMap &set1);

  //gets the private variable
  //@return recognition_sequence
  string getRecognition_sequence();
  
  //Prints enzyme in vector
  void print_enzyme();
  

  
 private:
  string recognition_sequence;
  vector<string> enzyme_acronym ;  //collection of enzyme_acronym

};  // end SequenceMap
#include "SequenceMap.cpp"
#endif
