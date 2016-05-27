/*
 *  queryTrees.cpp
 *  
 *  Purpose: to test AVl, LazyAvl and Binarysearch Tree
 *   and how analysis on
 * 
 *  Created on: Oct 5, 2015
 *  Author: Ryan Kallicharran
 */
#include <iostream>
#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"
#include <fstream>
#include "LazyAvlTree.h"
using namespace std;

/*
 *read the filename and paser the string before adding to the tree 
 * and the prompt user to search database.
 * @param filename as command
 * @param Tree  
 */
template < class Tree>
void readFile(char *argument_one, Tree OurTree ){
    //opens file we are reading
    std::ifstream myFile;
    myFile.open(argument_one, std::ios_base::in);


    //check if file exists
    if(!myFile.good()){
        std::cout<<"Error: file does not exist"<<std::endl;
        exit(1);
    }

    cout<<"Building database..."<<endl;

    string curr_line;

    while(getline(myFile, curr_line)){

        //skip unnecessary data
        if(curr_line.back() != '/' )
            continue;
        
        SequenceMap curr_map;
        int size_of_acronym =  curr_line.find_first_of('/');//finds size of acronym
        string acronym = curr_line.substr(0, size_of_acronym);//get the acronym from string

        //delete acronym from string
        curr_line.erase(0,size_of_acronym); 
        //erase '/' in front in front of string
        curr_line.erase(0,1);
        //erase the 1 of the last '//' to get just '/' at end
        curr_line.erase(curr_line.end()-1,curr_line.end());

        //Deletes what we add to the tree as empty the string
        while(!curr_line.empty()){

            //find the size of the sequence
            int size_of_seq = curr_line.find_first_of('/');
            //create a sub string to be adding into tree
            string sequence = curr_line.substr(0,size_of_seq );

            curr_map.set_key(sequence);//put key in sequence map
            curr_map.Add_enzyme(acronym);//adds the enzyme
            OurTree->insert(curr_map);//add to tree

            //delete this sequence from string and '/' after sequence
            curr_line.erase(0,size_of_seq+1); 

        }//end while

    }//end while
    
    //asking user for recognition sequence
    cout<<"database is ready for use.."<<endl;
    cout<<endl;
    cout<<"//////////////////////////////////////////////////////////////"<<endl;
    cout<<"/                     DataBase                               /"<<endl;
    cout<<"//////////////////////////////////////////////////////////////"<<endl;
    
    
    while(1){
        cout<<"Please enter a Recognition Sequence to be search or press enter : ";
        //get users input
        string input;
        cin>>input;


        SequenceMap seq_tofind;
        seq_tofind.set_key(input);
        if( OurTree->contains(seq_tofind)){
           //finds the node of the recognition sequence
            SequenceMap foundSeq = OurTree->find(seq_tofind);
            //prints the enzyme of users request 
            foundSeq.print_enzyme();   

        }else{
            cout<< "Recognition sequence is not found in database."<<endl;
        }

            //prompts user to end program
            cout<< "Do you wish to exit program? Enter 1 for yes and 2 for no."<<endl;
            //only allow integer inputs
            int run = 0;
	    while(!(cin >> run)){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input.  Try again: ";
	    }
            
            
            if(run == 1){

                exit(1);
        }

    }//end while
    
    
}//end function


    // Test program
int main(int argc, char** argv )
{
    /*tell user if right amount of argument have not been given*/
    if (argc != 3)  {
            cout << "You have not provided the required amount of arguments"<<endl;
            exit(1);
    }
    
    string param(argv[2]);
  
    
    //creates tree base of parameter passed by user
   if( param == "LazyAVL"){
       
        //create LazyAvlTree on the heap
        LazyAvlTree<SequenceMap> *Tree = new LazyAvlTree<SequenceMap>();
        readFile(argv[1], Tree);
         
   }else if( param == "BST"){
       
       //create a BinarySearchTree on the heap 
       BinarySearchTree<SequenceMap> *Tree = new BinarySearchTree<SequenceMap>();
       readFile(argv[1], Tree);
       
   }else if ( param == "AVL"){
       
       //create AvlTree on the heap
       AvlTree<SequenceMap> *Tree = new AvlTree<SequenceMap>();
       readFile(argv[1], Tree);
       
   }else{
       //exit program if the parameter is not called that is listed
       cout<< "You have provided invalid Parameter!"<<endl;
       exit(1);
   }
   
    return 0;
}
