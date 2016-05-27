/* 
 * File:   testTree.cpp
 * 
 * Purpose: to build a data base with any of the three tree 
 * AVL, Lazy AVL, Binary tree and be able to have user search the 
 * database.
 * 
 * Author: Ryan Kallicharran
 *
 * Created on October 1, 2015, 5:46 PM
 */


#include <iostream>
#include "BinarySearchTree.h"
#include "AvlTree.h"
#include "SequenceMap.h"
#include <fstream>
#include "LazyAvlTree.h"
#include <math.h>
using namespace std;



/*
 * Deletes items form the tree in second file but choosing every other sequence
 * @param second file name
 * @param tree
 */
template<class Tree>
void seqDelete(char* argument_two, Tree* OurTree){
    //deleting from tree 
     
    //opens file we are reading
    std::ifstream queriesFile;
    queriesFile.open(argument_two, std::ios_base::in);
     
    
    int num = 0;
    int successful_removal = 0;
    while(!queriesFile.eof()){
        
        string curr_word;
        //take only odd words
        if(num % 2 == 0){
            //skip a even word
            queriesFile >>curr_word;
            
        }else{
            
            //create an object to search
            queriesFile >>curr_word;
            SequenceMap toDelete;
            toDelete.set_key(curr_word);
            
            //if it exist in the our removal pattern
            if(OurTree->contains(toDelete))
                successful_removal++;           
           
            //delete
            OurTree->remove(toDelete);
        }
         
        num++;
    }
    queriesFile.close();//close file
    //display finding
    cout<<endl;
    cout<<"********************Deleting from Tree********************"<<endl;
    cout<<"Total number of successful removal: "<< successful_removal<<endl;
    cout<<"The number of recursive calls to the remove method: "<< OurTree->getRemoveCount()<<endl;
    
    //resets the counters
    OurTree->resetCounters();
}

/*
 * Search the tree for items in second file and displaying the recursive method count
 * @param second filename
 * @param Tree
 */
template<class Tree>
void searchTree(char* argument_two, Tree* OurTree){
    //searches tree for items in text file
     
    //opens file we are reading
    std::ifstream queriesFile;
    queriesFile.open(argument_two, std::ios_base::in);
   

    //check if file exists
    if(!queriesFile.good() ){
        std::cout<<"Error: a file does not exist"<<std::endl;
        exit(1);
    }  
        
    int successful_queries = 0;
    while(!queriesFile.eof()){
        
        string curr_word;

        //create an object to search
        queriesFile >>curr_word;
        SequenceMap toSearch;
        toSearch.set_key(curr_word);

        //if it exist in in tree
        if(OurTree->contains(toSearch))
            successful_queries++;
    
    }
    queriesFile.close();//close text file
    //display findings
    cout<<endl;
    cout<<"**********************Searching Tree**********************"<<endl;
    cout<<"Total number of successful queries: "<< successful_queries<<endl;
    cout<<"The number of recursive calls to the contains method: "<<OurTree->getContainCount()<<endl;
    
    //resets the counters
    OurTree->resetCounters();
}




/*
 * Open rebase210.txt and build database base on which tree user passed as command
 * and tell information about the tree's depth and nodes and method calls
 * 
 * @param argument one passed in command line for first filename
 * @param argument two passed in command line for second filname
 * @param tree that will be build
 * 
 */
template <class Tree>
void readFile(char *argument_one, char* argument_two, Tree* OurTree ){
    //opens file we are reading
    std::ifstream myFile;
    myFile.open(argument_one, std::ios_base::in);
   

    //check if file exists
    if(!myFile.good() ){
        std::cout<<"Error: a file does not exist"<<std::endl;
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
    
    //close myFile after reading from it
    myFile.close();
    
    //asking user for recognition sequence
    cout<<"database is ready for use.."<<endl;
    cout<<endl;
    cout<<"//////////////////////////////////////////////////////////////"<<endl;
    cout<<"/                     DataBase Analysis                      /"<<endl;
    cout<<"//////////////////////////////////////////////////////////////"<<endl;
    
    //set precision on output of numbers of  double.
    cout.precision(2);
    
    //Display findings before deletion
    cout<<"Total number of recursive calls to Insert:  "<<OurTree->getInsertCount()<<endl;
    cout<<"Total number of nodes: "<<OurTree->getNumberOfNodes()<<endl;
    cout<<endl;
    cout<<"***********************Computation***********************"<<endl;
    cout<<"Average depth of Tree is: ";
    double average = (double)OurTree->internalPathLength() / (double)OurTree->getNumberOfNodes();
    cout<<average<<endl;
       
    cout<<"The ratio of the average depth to log:  "<<average<<"/"<< log2 (OurTree->getNumberOfNodes())
            <<" = "<< average/ log2 (OurTree->getNumberOfNodes())<<fixed;
    cout<<endl; 
    
     
    //searches tree
    searchTree(argument_two,OurTree);
           
    //deletes from tree
    seqDelete(argument_two, OurTree);
    
    cout<<endl;//space out output
    
    //set position again
    
    //Display findings after deletion
    cout<<"///////////////////* After Deletion *//////////////////////"<<endl;
    cout<<endl;//space out output
    cout<<"Total number of nodes: "<<OurTree->getNumberOfNodes()<<endl;
    cout<<endl;
    cout<<"***********************Computation***********************"<<endl;
    cout<<"Average depth of Tree is: ";
    average = (double)OurTree->internalPathLength() / (double)OurTree->getNumberOfNodes();
    cout<<average<<endl;
       
    cout<<"The ratio of the average depth to log:  "<<average<<"/"<< log2 (OurTree->getNumberOfNodes())
            <<" = "<< average/ log2 (OurTree->getNumberOfNodes())<<fixed;
    cout<<endl;
    
    //searches tree again
    searchTree(argument_two,OurTree);
    
}//end function


    // Test program
int main(int argc, char** argv )
{
    /*tell user if right amount of argument have not been given*/
    if (argc != 4)  {
            cout << "You have not provided the required amount of arguments"<<endl;
            exit(1);
    }
    

    string param(argv[3]);
    
       
    //creates tree base of parameter passed by user
   if( param == "LazyAVL"){
       
        //create LazyAvlTree on the heap
        LazyAvlTree<SequenceMap> *Tree = new LazyAvlTree<SequenceMap>();
        readFile(argv[1], argv[2], Tree);
         
   }else if( param == "BST"){
       
       //create a BinarySearchTree on the heap
       BinarySearchTree<SequenceMap> *Tree = new BinarySearchTree<SequenceMap>();
       readFile(argv[1], argv[2], Tree);
       
   }else if ( param == "AVL"){
       
       //create AvlTree on the heap
       AvlTree<SequenceMap> *Tree = new AvlTree<SequenceMap>();
       readFile(argv[1], argv[2], Tree);
       
   }else{
       //exit program if the parameter is not called that is listed
       cout<< "You have provided invalid Parameter!"<<endl;
       exit(1);
   }
 
    
    
   
    return 0;
}
