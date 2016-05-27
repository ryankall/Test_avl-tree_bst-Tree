/* 
 * File:   BinarySearchTree.h
 * Author: Ryan Kallicharran
 *
 * Created on October 1, 2015, 5:49 PM
 */

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "dsexceptions.h"
#include <algorithm>
using namespace std;

template <typename Comparable>
class BinarySearchTree {
public:
    BinarySearchTree();
    //Copy constructor
    BinarySearchTree(const BinarySearchTree& rhs);
    //Move constructor
    BinarySearchTree( BinarySearchTree && rhs );
    // Destructor for the tree
    ~BinarySearchTree();
     
    //Copy assignment    
    BinarySearchTree & operator=( const BinarySearchTree & rhs );
    
    //Move assignment
    BinarySearchTree & operator=( BinarySearchTree && rhs );
    
    //Find the smallest item in the tree.
    //Throw UnderflowException if empty.
    const Comparable & findMin( ) const;
    
    
    //Find the largest item in the tree.
    //Throw UnderflowException if empty.    
    const Comparable & findMax( ) const;
    
    
    //Returns true if x is found in the tree.    
    bool contains(  Comparable & x ) ;
    
    
    //Test if the tree is logically empty.
    //Return true if empty, false otherwise.    
    bool isEmpty( ) const;
    
      
    //Print the tree contents in sorted order.    
    void printTree( ostream & out = cout )const;    
    
    
    //Make the tree logically empty.
    void makeEmpty( );
 
     
    //Insert x into the tree; duplicates are ignored.  
    void insert( Comparable & x );
    
    
    //Insert x into the tree; duplicates are ignored. 
    void insert( Comparable && x );
    
   
    //Remove x from the tree. Nothing is done if x is not found.   
    void remove( Comparable & x );
    
    //finds x in the tree if it exist.
    Comparable& find(Comparable & x);
    
     //find the sum of all the heights in tree
    //@return sum of height of all path
    int internalPathLength();
    
    //get the current insert count
    //@return the insert count
    int getInsertCount();
    
    //get the current remove count
    //@return remove count
    int getRemoveCount();
    
    //get the current contains count
    //@return contain count
    int getContainCount();
    
    //get the number of nodes in tree
    //@return the number of nodes in tree
    int getNumberOfNodes(); 
    
    //reset contains count and remove count
    void resetCounters();
    
private:
  struct BinaryNode{
  
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };
  
    int insert_count;
    int remove_count;
    int contain_count;
    int number_of_nodes;

    
    BinaryNode *root;
    
    BinaryNode * find( BinaryNode *t, Comparable & x) ;
    
    //Insert a item at a given node and set the new root of the subtree
    //@param Comparable variable
    //@param BinaryNode pointer of a give node
    //returns nothing
    void insert( Comparable & x, BinaryNode * & t );
  
    //Internal method to insert into a subtree and set the new root of the subtree.
    //@param x is the item to insert.
    //@param t is the node that roots the subtree.
    void insert( Comparable && x, BinaryNode * & t );
    
    // Internal method to remove from a subtree and set the new root of the subtree.
    //@param x is the item to remove.
    //@param t is the node that roots the subtree.
    //returns nothing 
    void remove( Comparable & x, BinaryNode * & t );
    
    //Internal method to find the smallest item in a subtree t.
    //@Return node containing the smallest item.
    BinaryNode * findMin( BinaryNode *t ) const;
    
    //Internal method to find the largest item in a subtree t.
    //@Return node containing the largest item.
    BinaryNode * findMax( BinaryNode *t ) const;
 
    // Internal method to test if an item is in a subtree.
    //@param x is item to search for.
    //@param t is the node that roots the subtree.
    bool contains(  Comparable & x, BinaryNode *t ) ;

    
    //Internal method to make subtree empty. 
    //@param a given subtree node
    void makeEmpty( BinaryNode * & t );

    //Internal method to print a subtree rooted at t in sorted order.
    //@param a give subtree node will be printed
    void printTree( BinaryNode *t, ostream & out ) const;
   
    //Internal method to clone subtree.
    //@param a given subtree to be copied
    //@return BinaryNode that was copied
    BinaryNode * clone( BinaryNode *t ) const;
    
    //finds the sum of all height in subtree
    //@param subtree t
    //@param value of height
    int internalPath(BinaryNode* t, int value);
};
#include "BinarySearchTree.cpp"
#endif	/* BINARYSEARCHTREE_H */

