/*
 * LazyAvlTree.h
 *
 *  Created on: Oct 5, 2015
 *  Author: Ryan Kallicharran
 */

#ifndef LAZYAVLTREE_H_
#define LAZYAVLTREE_H_

#include "dsexceptions.h"
#include <algorithm>
#include <iostream> 
using namespace std; 

template <typename Comparable>
class LazyAvlTree {
    
  public:
    //default constructor
    LazyAvlTree( );
    
    //copy constructor
    LazyAvlTree( const LazyAvlTree & rhs );

    //move constructor
    LazyAvlTree( LazyAvlTree && rhs );
    
    //Destructor
    ~LazyAvlTree( );

    
    //Deep copy assignment operator
    //@param LazyAvlTree  
    LazyAvlTree & operator=( const LazyAvlTree & rhs );    
    
    //Move assignment
    //@param LazyAvlTree 
    LazyAvlTree & operator=( LazyAvlTree && rhs );
    
    //Find the smallest item in the tree.
    //Throw UnderflowException if empty.
    //@return smallest item in the tree. 
    Comparable & findMin( ) const;
    
    //Find the largest item in the tree.
    //Throw UnderflowException if empty.
    //@return largest item in tree
    Comparable & findMax( ) const;

    //Checks if x exist in the tree
    //@param Comaprable x
    //@Returns true if x is found in the tree.
    bool contains( Comparable & x );
    
    //Test if the tree is logically empty.
    //@Return true if empty, false otherwise.  
    bool isEmpty( ) const;
    
    //Print the tree contents in sorted order.
    void printTree( ) const;
 
    //Make the tree logically empty.
    void makeEmpty( );
    
    //Insert x into the tree; duplicates are ignored.
    //@param Comparable  x
    void insert( Comparable & x );
    
    //Insert x into the tree; duplicates are ignored.
    //@param Comparable x
    void insert( Comparable && x );
     
    //Remove x from the tree. Nothing is done if x is not found.
    //@param Comparable x    
    void remove( Comparable & x );
    
    //finds a given item in avltree if there exist
    //@param the x to be searched for in tree
    //@return the x that was found in tree
    Comparable& find(Comparable& x);
    
    //find the sum of all the heights in tree
    //@return sum of heigcht of all path
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
    struct LazyAvlNode
    {
        Comparable element;
        LazyAvlNode   *left;
        LazyAvlNode   *right;
        int       height;
        bool      active;

        LazyAvlNode( const Comparable & ele, LazyAvlNode *lt, LazyAvlNode *rt, int h = 0 )
          : element{ ele }, left{ lt }, right{ rt }, height{ h } { }
        
        LazyAvlNode( Comparable && ele, LazyAvlNode *lt, LazyAvlNode *rt, int h = 0 )
          : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
    };

    LazyAvlNode *root;

    int insert_count;
    int remove_count;
    int contain_count;
    int number_of_nodes;
    
    //Internal method to insert into a subtree and set the new root of the subtree.
    //@param x is the item to insert.
    //@param t is the node that roots the subtree.
    void insert(  Comparable & x, LazyAvlNode * & t );
    

    
    //Internal method to insert into a subtree and set the new root of the subtree.
    //@param x is the item to insert.
    //@param t is the node that roots the subtree.
    void insert( Comparable && x, LazyAvlNode * & t );
     
    
    //Internal method to remove from a subtree and set the new root of the subtree.
    //@param x is the item to remove.
    //@param t is the node that roots the subtree.
     void remove( Comparable & x, LazyAvlNode * & t );
    
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( LazyAvlNode * & t );
    
    
    //Internal method to find the smallest item in a subtree t.
    //@param subtree t
    //@Return node containing the smallest item.   
    LazyAvlNode * findMin( LazyAvlNode *t ) const;

    
    //Internal method to find the largest item in a subtree t.
    //@param subtree t
    //@return node containing the largest item.  
    LazyAvlNode * findMax( LazyAvlNode *t ) const;

    
    //Internal method to test if an item is in a subtree.
    //@param x is item to search for.
    //@param t is the node that roots the tree.
    //@return true if x exist in tree other wise return false
    bool contains( Comparable & x, LazyAvlNode *t ) ;
    
    //Internal method to make subtree empty.
    //@param subtree to be empty
    void makeEmpty( LazyAvlNode * & t );
    
    //Internal method to print a subtree rooted at t in sorted order.
    //@param subtree root t
    void printTree( LazyAvlNode *t ) const;
    
    //Internal method to clone subtree. 
    //@param subtree t
    //@returns subtree 
    LazyAvlNode * clone( LazyAvlNode *t ) const;
        
    // Avl manipulations
   
    //Return the height of node t or -1 if nullptr. 
    //@param the avlnode t
    //@return the value of height 
    int height( LazyAvlNode *t ) const;
    
    //returns the max height between two height
    //@param left height
    //@param right height
    //@return height that greater of the two
    int max( int lhs, int rhs ) const;
    
    //Rotate binary tree node with left child.
    //For AVL trees, this is a single rotation for case 1.
    //Update heights, then set new root.
    //@param AvllNode
    void rotateWithLeftChild( LazyAvlNode * & k2 );

    
    //Rotate binary tree node with right child.
    //For AVL trees, this is a single rotation for case 4.
    //Update heights, then set new root.
    //@param AvllNode
    void rotateWithRightChild( LazyAvlNode * & k1 );

    
    //Double rotate binary tree node: first left child.
    //with its right child; then node k3 with new left child.
    //For AVL trees, this is a double rotation for case 2.
    //Update heights, then set new root.
    //@param AvllNode    
    void doubleWithLeftChild( LazyAvlNode * & k3 );

    
    //Double rotate binary tree node: first right child.
    //with its left child; then node k1 with new right child.
    //For AVL trees, this is a double rotation for case 3.
    //Update heights, then set new root.     
    void doubleWithRightChild( LazyAvlNode * & k1 );   
    
    //find the x in the subtree
    //@param x to be found in subtree
    //@param subtree to search
    //@return the node of found x
    LazyAvlNode* find_en( Comparable & x, LazyAvlNode *t ) ;  
    
    //finds the sum of all height in subtree
    //@param subtree t
    //@param value of height
    int internalPath(LazyAvlNode* t, int value);
    
    
};
#include "LazyAvlTree.cpp"
#endif /* LAZYAVLTREE_H_ */
