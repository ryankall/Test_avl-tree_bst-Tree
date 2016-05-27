/*
 * File: LazyAvlTree.cpp
 *
 * Created on: Oct 5, 2015
 * Author: Ryan Kallicharran
 */

#include "LazyAvlTree.h"

//default constructor
template <typename Comparable>
LazyAvlTree<Comparable>::LazyAvlTree( ) : root{ nullptr }{ }

//Copy constructor
template <typename Comparable>
LazyAvlTree<Comparable>::LazyAvlTree( const LazyAvlTree & rhs ) : root{ nullptr }
{
    root = clone( rhs.root );
}

//Move constructor
template <typename Comparable>
LazyAvlTree<Comparable>::LazyAvlTree( LazyAvlTree && rhs ) : root{ rhs.root }
{
    rhs.root = nullptr;
}

//Destructor
template <typename Comparable>
LazyAvlTree<Comparable>::~LazyAvlTree( )
{
    makeEmpty( );
}

template <typename Comparable>
LazyAvlTree<Comparable> & LazyAvlTree<Comparable>::operator=( const LazyAvlTree & rhs )
{
    LazyAvlTree copy = rhs; //copy tree
    std::swap( *this, copy );//swap tree
    return *this;
}

template <typename Comparable>
LazyAvlTree<Comparable> & LazyAvlTree<Comparable>::operator=( LazyAvlTree && rhs )
{
    std::swap( root, rhs.root );//swap tree

    return *this;
}

template <typename Comparable>
Comparable & LazyAvlTree<Comparable>::findMin( ) const
{
    //looks for smallest key throw exception if empty tree
    if( isEmpty( ) )
        throw UnderflowException{ };
    return findMin( root )->element;
}

template <typename Comparable>
Comparable & LazyAvlTree<Comparable>::findMax( ) const
{   //looks for largest key throw exception if empty tree
    if( isEmpty( ) )
        throw UnderflowException{ };
    return findMax( root )->element;
}

template <typename Comparable>
bool LazyAvlTree<Comparable>::contains(  Comparable & x )
{   //call private contains
    return contains( x, root );
}

template <typename Comparable>
bool LazyAvlTree<Comparable>::isEmpty( ) const
{
    return root == nullptr;
}

template <typename Comparable>
void LazyAvlTree<Comparable>::printTree( ) const
{
    if( isEmpty( ) )
        std::cout << "Empty tree" << std::endl;
    else
        printTree( root );//call print in private
}

template <typename Comparable>
void LazyAvlTree<Comparable>::makeEmpty( )
{
    makeEmpty( root );//call the private makeEmpty
}

template <typename Comparable>
void LazyAvlTree<Comparable>::insert( Comparable & x )
{
    insert( x, root );//call private insert
}

template <typename Comparable>
void LazyAvlTree<Comparable>::insert( Comparable && x )
{
    insert( std::move( x ), root );//call private insert
}

template <typename Comparable>
void LazyAvlTree<Comparable>::remove( Comparable & x )
{
    remove( x, root );//call private remove 
}

template <typename Comparable>
Comparable& LazyAvlTree<Comparable>::find(Comparable& x){
    //assign found node of x  from calling private find function
    LazyAvlNode* foundNode = find_en(x, root);
    return foundNode->element;//return found node object
}

//*Getters
template <typename Comparable>
int LazyAvlTree<Comparable>::getInsertCount(){
    
    return insert_count;
}
template <typename Comparable>
int LazyAvlTree<Comparable>::getRemoveCount(){
    
    return remove_count;    
}
template <typename Comparable>
int LazyAvlTree<Comparable>::getContainCount(){
    
    return contain_count; 
}

template<typename Comparable>
int LazyAvlTree<Comparable>::getNumberOfNodes(){
    return number_of_nodes;
}

template<typename Comparable>
int LazyAvlTree<Comparable>::internalPathLength(){
    //call private internal path function
    return internalPath(root, 0);
    
}

template<typename Comparable>
void LazyAvlTree<Comparable>::resetCounters(){
    
    //rest the counter for contain and remove
    contain_count = 0;
    remove_count = 0;
    
}
//protected****************************************************************


template <typename Comparable>
void LazyAvlTree<Comparable>::insert(  Comparable & x, LazyAvlNode * & t )
{
    if( t == nullptr ){
        //create a new node
        t = new LazyAvlNode{ x, nullptr, nullptr };
        //activate node
        t->active = true;
        //add 1 to number of nodes
        number_of_nodes++;
    }else if( x < t->element ){
        //add 1 to insert count
        insert_count++;
        //move to left node
        insert( x, t->left );
    }else if( t->element < x ){
        //add 1 to insert count
        insert_count++;
        //move to right node
        insert( x, t->right );
    }else{
         t->element + x;//match so  we combine the two object
         t->active = true;//activate node
    }
    balance( t );
}

    
template <typename Comparable>
void LazyAvlTree<Comparable>::insert( Comparable && x, LazyAvlNode * & t )
{
    if( t == nullptr ){
        //create a new node 
        t = new LazyAvlNode{ std::move( x ), nullptr, nullptr };
        //add 1 to number of nodes
        number_of_nodes++;
        //activate node
        t->active = true;
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
    }else{
        t->element + x;//match so combine object
        t->active = true;//activate node
    }
    balance( t );//balance the tree after insert
}


template <typename Comparable>
void LazyAvlTree<Comparable>::remove(  Comparable & x, LazyAvlNode * & t )
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
    {
        //both child is null
        
        //add 1 to remove count
        remove_count++;
        //move to right node
        remove( t->element, t->right );
    }
    else
    {   //deactivate node
        t->active = false; 
    }

   
}



template <typename Comparable>
void LazyAvlTree<Comparable>::balance( LazyAvlNode * & t )
{
    if( t == nullptr )
        return;//do nothing
    
    //left side is heavy
    if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
    {
        if( height( t->left->left ) >= height( t->left->right ) )
            rotateWithLeftChild( t );//rotate left child
        else
            doubleWithLeftChild( t );//double rotate
    }
    else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
    {   //right side is heavy
        if( height( t->right->right ) >= height( t->right->left ) )
            rotateWithRightChild( t );//rotate right child
        else
            doubleWithRightChild( t );//double rotate
    }
    //take the greater of the left or right height
    t->height = max( height( t->left ), height( t->right ) ) + 1;
}


template <typename Comparable>  
typename LazyAvlTree<Comparable>::LazyAvlNode * LazyAvlTree<Comparable>::findMin( LazyAvlNode *t ) const
{
    if( t == nullptr )
        return nullptr;//empty tree
    if( t->left == nullptr )
        return t;//found smallest
    return findMin( t->left );//keep moving left
}


template <typename Comparable>
typename LazyAvlTree<Comparable>::LazyAvlNode * LazyAvlTree<Comparable>::findMax( LazyAvlNode *t ) const
{   //keep going right of tree and returns t
    if( t != nullptr )
        while( t->right != nullptr )
            t = t->right;
    return t;
}



template <typename Comparable>
bool LazyAvlTree<Comparable>::contains(  Comparable & x, LazyAvlNode *t )
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
    }else{
       
        return true;    // Match
    }
}


template <typename Comparable>
void LazyAvlTree<Comparable>::makeEmpty( LazyAvlNode * & t )
{
    if( t != nullptr )
    {   //go everywhere on tree and deactivate all nodes
        makeEmpty( t->left );
        makeEmpty( t->right );
        t->active = false;
    }
    
}


template <typename Comparable>
void LazyAvlTree<Comparable>::printTree( LazyAvlNode *t ) const
{
    if( t != nullptr )
    {   //print inorder
        printTree( t->left );
        std::cout << t->element << std::endl;
        printTree( t->right );
    }
}


template <typename Comparable>   
typename LazyAvlTree<Comparable>::LazyAvlNode * LazyAvlTree<Comparable>:: clone( LazyAvlNode *t ) const
{
    if( t == nullptr )
        return nullptr;
    else
        return new LazyAvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
         //create new node copy of t of the tree inorder traverse
}

template <typename Comparable>    
int LazyAvlTree<Comparable>::height( LazyAvlNode *t ) const
{
    //-1 if t is null otherwise return height value of node
    return t == nullptr ? -1 : t->height;
}

template <typename Comparable>
int LazyAvlTree<Comparable>::max( int lhs, int rhs ) const
{
    //return left side height if left side is greater otherwise return right side height
    return lhs > rhs ? lhs : rhs;
}


template <typename Comparable>
void LazyAvlTree<Comparable>::rotateWithLeftChild( LazyAvlNode * & k2 )
{
    LazyAvlNode *k1 = k2->left;//copy left child node
    k2->left = k1->right;//right child node is now on the left
    k1->right = k2;//left goes to the right
    ////add 1+ max height of right child
    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    //add 1+ max height of our node
    k1->height = max( height( k1->left ), k2->height ) + 1;
    k2 = k1;
}

template <typename Comparable>
void LazyAvlTree<Comparable>::rotateWithRightChild( LazyAvlNode * & k1 )
{
    LazyAvlNode *k2 = k1->right;//copy right child node
    k1->right = k2->left;//left child node is now on the right
    k2->left = k1;//right goes left
    //add 1 + max height of left child 
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    //add 1 + max height of our node
    k2->height = max( height( k2->right ), k1->height ) + 1;
    k1 = k2;
}

template <typename Comparable>  
void LazyAvlTree<Comparable>::doubleWithLeftChild( LazyAvlNode * & k3 )
{
    rotateWithRightChild( k3->left );
    rotateWithLeftChild( k3 );
}

template <typename Comparable>
void LazyAvlTree<Comparable>::doubleWithRightChild( LazyAvlNode * & k1 )
{
    rotateWithLeftChild( k1->right );
    rotateWithRightChild( k1 );
}   

template <typename Comparable>
typename LazyAvlTree<Comparable>::LazyAvlNode* LazyAvlTree<Comparable>::find_en( Comparable & x, LazyAvlNode *t ) 
{
    if( t == nullptr )
        return nullptr;//not found
    else if( x < t->element )//search is less than key
        return find_en( x, t->left );//go left
    else if( t->element < x )//search item is greater than key
        return find_en( x, t->right );//go right
    else
        return t;    // Match
}

template<typename Comparable>
int LazyAvlTree<Comparable>::internalPath(LazyAvlNode* t, int value){
     if(t == nullptr) 
    {
        return 0;//return 0 when we hit pointer
    }
    return (value+internalPath(t->right,value+1)+internalPath(t->left,value+1));
    //add up  height on our way back up and recursive left traverse 
}    