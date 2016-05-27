/*
*       File Name: SequenceMap.cpp
 *
 *      Created on: Feb 18, 2015
 *      Author: Ryan Kallicharran
 *      Purpose: Defining what the functions will do
 */

#include <cstddef>
#include <iostream>
#include "SequenceMap.h"


using namespace std;

SequenceMap::SequenceMap() 
{
}  // end default constructor


void SequenceMap::Add_enzyme(const std::string new_entry)
{
    //check if string is contain in recognition_sequence
    bool redundant = Contains(new_entry);

    //if already exist in vector do not add to vector otherwise do
    if (!redundant)
    {
      //put item in vector
      enzyme_acronym.push_back(new_entry);
    }

//do nothing
}  // end add

//set the recognition_sequence
void SequenceMap::set_key( const string new_entry)
{
    recognition_sequence = new_entry;
}


bool SequenceMap::Contains(const std::string& an_entry) const
{
   
    bool found = false;
    //loop through the vector
    for(std::vector<string>::size_type i = 0; i != enzyme_acronym.size(); i++ ){ 
        //if enzyme is found in vector break loop and return true
        if(enzyme_acronym[i] == an_entry){
            found = true;
            break;
        }
    }
   
    return found;
        
}  // end contains


SequenceMap* SequenceMap::operator+( SequenceMap &set1){
         
    if(recognition_sequence == set1.recognition_sequence){
        //if the recognition sequence match the do this
        for(std::vector<string>::size_type i = 0; i != set1.enzyme_acronym.size(); i++){
                //add enzyme to this vector
                Add_enzyme(set1.enzyme_acronym[i]);           
        }       
    }   
    return this;// the point of this object
}



bool SequenceMap::operator<(  SequenceMap &set1){
    //check if set1 is greater than this and return true otherwise return false
    if(recognition_sequence < set1.recognition_sequence)
        return true;
    else 
        return false;
    
} 

//overloading the << operator so that template class can using it
 ostream &operator<<( ostream &output, SequenceMap &D )
{ 
   output << D.getRecognition_sequence()<<endl; 
   return output;            
}

//gets recognition_sequence
string SequenceMap::getRecognition_sequence()
{
   return recognition_sequence;  
}

//print the items in vector
void SequenceMap::print_enzyme(){
    
    cout<<"[ ";
            
    for( std::vector<string>::size_type x = 0; x < enzyme_acronym.size(); x++ ){
        //check x the last string, if not print item and ","
        if(x < enzyme_acronym.size()-1)
            cout<<enzyme_acronym[x]<<", ";
        else
            cout<<enzyme_acronym[x];
    }
    
    cout<<" ]"<<endl;
}







