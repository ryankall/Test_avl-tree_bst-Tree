/* 
 * File:   BinarySearchTree.cpp
 * Author: Ryan Kallicharran
 * 
 * Created on October 1, 2015, 5:49 PM
 */


#include "BinarySearchTree.h"
#include <ostream>
using namespace std;

//default constructor
template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree( ) : root { nullptr }{}

//Copy constructor
template <typename Comparable>    
BinarySearchTree<Comparable>::BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr } 
{
    root = clone( rhs.root ); 
}
   
//Move constructor     
template <typename Comparable>    
BinarySearchTree <Comparable>::BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
{
    rhs.root = nullptr;
}

//Destructor
template <typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree( )
{
    makeEmpty();
}

template <typename Comparable>
BinarySearchTree<Comparable>& BinarySearchTree<Comparable>::  operator=( const BinarySearchTree & rhs )
{
    BinarySearchTree copy = rhs;//copy tree
    std::swap( *this, copy );//swap tree
    return *this;
}

template <typename Comparable>
BinarySearchTree<Comparable> & BinarySearchTree<Comparable>:: operator=( BinarySearchTree && rhs )
{
    std::swap( root, rhs.root );  //swap tree     
    return *this;
}    

template <typename Comparable>
const Comparable & BinarySearchTree<Comparable>::  findMin( ) const
{
    //looks for smallest key throw exception if empty tree
    if( isEmpty( ) )
        throw UnderflowException{ };
    return findMin( root )->element;
}

template <typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax( ) const
{   //looks for largest key throw exception if empty tree
    if( isEmpty( ) )
        throw UnderflowException{ };
    return findMax( root )->element;
}

template <typename Comparable>
bool BinarySearchTree<Comparable>:: contains(  Comparable & x ) 
{   //call private contains
    return contains( x, root );
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::isEmpty( ) const
{
    return root == nullptr;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty( )
{
    makeEmpty( root ); //call the private makeEmpty
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert( Comparable & x )
{
    insert( x, root );//call private insert
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert( Comparable && x )
{
    insert( std::move( x ), root );//call private insert
}
template <typename Comparable>
void BinarySearchTree<Comparable>::remove( Comparable & x )
{
    remove( x, root );//call private remove 
}

template <typename Comparable>
void BinarySearchTree<Comparable>::printTree( ostream & out )const
{
    if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );//call print in private
}
 
template <typename Comparable>
Comparable& BinarySearchTree<Comparable>::find(Comparable & x){
    //assign found node of x  from calling private find function
    BinaryNode* foundNode = find(root, x);
    return foundNode->element;//return found node object
}

//*Getters
template <typename Comparable>
int BinarySearchTree<Comparable>::getInsertCount(){
    
    return insert_count;
}
template <typename Comparable>
int BinarySearchTree<Comparable>::getRemoveCount(){
    
    return remove_count;    
}
template <typename Comparable>
int BinarySearchTree<Comparable>::getContainCount(){
    
    return contain_count; 
}

template<typename Comparable>
int BinarySearchTree<Comparable>::getNumberOfNodes(){
    return number_of_nodes;
}

template<typename Comparable>
int BinarySearchTree<Comparable>::internalPathLength(){
    //call private internal path function
    return internalPath(root, 0);
    
}

template<typename Comparable>
void BinarySearchTree<Comparable>::resetCounters(){
    
    //rest the counter for contain and remove
    contain_count = 0;
    remove_count = 0;
    
}


//Protected****************************************************************/

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(  Comparable & x, BinaryNode * & t )
{ 
    if( t == nullptr ){
        //create a new node
        t = new BinaryNode{ x, nullptr, nullptr };
        //add 1 to number of nodes
        number_of_nodes++;
    }else if( x < t-> element ){
        //add 1 to insert count
        insert_count++;      
        insert( x, t->left );
        //move to left node
    }else if( t->element < x ){
        //add 1 to insert count
         insert_count++; 
         //move to right node
        insert( x, t->right );      
    }else 
         t->element + x;  //match so  we combine the two object
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert( Comparable && x, BinaryNode * & t )
{
    if( t == nullptr ){
        //create a new node 
        t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        //add 1 to number of nodes
        number_of_nodes++;
    }else if( x < t->element ){
        //add 1 to insert count
        insert_count++;
        //move to left node
        insert( std::move( x ), t->left );
    }else if( t->element < x ){
        //add 1 to insert count
         insert_count++;
         //move to right node
        insert( std::move( x ), t->right );     
    }else
         t->element + x;;  //match so combine object
}

  
template <typename Comparable>
void BinarySearchTree<Comparable>::remove(  Comparable & x, BinarySearchTree<Comparable>::BinaryNode * & t )
{
    if( t == nullptr )
        return;   // Item not found; do nothing
    if( x < t->element ){
        //add 1 to remove count
        remove_count++;
        //move to left node
        remove( x, t->left );
    }else if( t->element < x ){
        //add 1 to remove count
        remove_count++;
        //move to right node
        remove( x, t->right );
    }else if( t->left != nullptr && t->right != nullptr ) // Two children
    {   //add 1 to remove count
        remove_count++;
        
        //both child is null
        //find the inorder predecessor
        t->element = findMin( t->right )->element;
        //move to right node
        remove( t->element, t->right );
    }
    else
    {  
        BinaryNode *oldNode = t;
        t = ( t->left != nullptr ) ? t->left : t->right;
        delete oldNode;
        //minus 1 from number of nodes on the tree
        number_of_nodes--;
    }
}

template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::findMin( BinaryNode *t ) const
{
    if( t == nullptr )
        return nullptr;//empty tree
    if( t->left == nullptr )
        return t;//found smallest
    return findMin( t->left );//keep moving left
}

template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::findMax( BinaryNode *t ) const
{   //keep going right of tree and returns t
    if( t != nullptr )
        while( t->right != nullptr )
            t = t->right;
    return t;
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(  Comparable & x, BinaryNode *t ) 
{
    if( t == nullptr )
        return false;
    else if( x < t->element ){
        //add 1 to contains count
        contain_count++;
        //move to left node
        return contains( x, t->left );
    }else if( t->element < x ){
        //add 1 to contains count
        contain_count++;
        //move to right node
        return contains( x, t->right );
    }else
        return true;    // Match
}

template <typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty( BinaryNode * & t )
{
    if( t != nullptr )
    {   //go everywhere on tree and delete node
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = nullptr;//set root to nullptr
}

template <typename Comparable>
void BinarySearchTree<Comparable>::printTree( BinarySearchTree<Comparable>::BinaryNode *t, ostream & out ) const
{
    if( t != nullptr )
    {   //print inorder  
        printTree( t->left, out );
        out << t->element << endl;
        printTree( t->right, out );
    }
}

template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::clone( BinaryNode *t ) const
{
    if( t == nullptr )
        return nullptr;
    else
        return new BinaryNode{ t->element, clone( t->left ), clone( t->right )};
        //create new node copy of t of the tree inorder traverse 
}

template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::find( BinaryNode *t,  Comparable & x) {
 
    if( t == nullptr )
        return nullptr;//not found
    else if( x < t->element )//search is less than key
        return find( t->left, x );//go left
    else if( t->element < x )//search item is greater than key
        return find( t->right, x );//go right
    else
        return t;    // Match
    
    
}

template<typename Comparable>
int BinarySearchTree<Comparable>::internalPath(BinaryNode* t, int value){
  if(t == nullptr) 
    {
        return 0;//return 0 when we hit pointer
    }
    return (value+internalPath(t->right,value+1)+internalPath(t->left,value+1));
    //add up  height on our way back up and recursive left traverse 
}