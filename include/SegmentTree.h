#ifndef __SEGMENTTREE_H__
#define __SEGMENTTREE_H__

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdexcept>

template<typename T>
class Node ;

template<typename T,typename Algo>
class SegmentTree ;

template<typename T>
class Node{
    private :
        std::pair<int,int> _interval ;
        T value ;
        Node<T> *left , *right ;
    public :
        // constructor
        Node( const std::pair<int,int> &interval , const T value , 
                Node<T> *left = nullptr , Node<T> *right = nullptr ) :
                _interval(interval) , value(value) , left(left) , right(right){}
        // copy constructor
        Node( const Node<T> &other_node ) : 
                _interval(other_node._interval) , value(other_node.value) , 
                left(other_node.left) , right(other_node.right){}
        // move constructor
        Node( Node<T> &&other_node ) : 
                _interval(std::move(other_node._interval)) , value(std::move(other_node.value)) ,
                left(std::move(other_node.left)) , right(std::move(other_node.right)){}

        // get the lower bound of its range
        size_t getLowerBound(void)const {
            return _interval.first ;
        }

        // get the upper bound of its range
        size_t getUpperBound(void)const {
            return _interval.second ;
        }
    template<typename U,typename Algo>
    friend class SegmentTree ;
} ;

template<typename T,typename Algo>
class SegmentTree{
    private :
        Node<T> *root ;
        // using custom algorithm for prefix operations
        Algo _prefixAlgo ;
        size_t __tree_size ;

        // generate tree recursively
        void generateTree( const std::vector<T> &nums , size_t left , size_t right , Node<T> *&root ) ;
        template<typename InputIterator>
        void generateTree( const InputIterator &__first ,
                           const std::pair<InputIterator,InputIterator> &interval , 
                           Node<T> *&root ) ;
        // update tree recursively
        void updateRecursive( Node<T> *&root , size_t index , T data ) ;
        // delete tree recursively
        void deleteTree( Node<T> *& ) ;
        // query recursively
        T getValue( const Node<T> *root , size_t begin , size_t end )const ;

        // check if the update index is within the bound
        bool isWithinBounds( size_t index )const {
            return index < __tree_size ;
        }

        // check if the query or update interval is within the bound
        bool isWithinBounds( size_t begin , size_t end )const {
            return begin < __tree_size && end < __tree_size ;
        }

        // check if the query or update interval is valid
        // that is, the lower bound should not greater than the upper bound
        bool isValidInterval( size_t begin , size_t end )const {
            return begin <= end ;
        }
    public :
        // default constructor
        SegmentTree(void) : root(nullptr) , _prefixAlgo() , __tree_size(0){}
        // copy constructor
        SegmentTree( const SegmentTree<T,Algo> &other_tree ) : 
                     root(other_tree.root) , _prefixAlgo(other_tree._prefixAlgo) , 
                     __tree_size(other_tree._tree_size){}
        // move constructor
        SegmentTree( SegmentTree<T,Algo> &&other_tree ) : 
                     root(std::move(other_tree.root)) , _prefixAlgo(std::move(other_tree._prefixAlgo)) ,
                     __tree_size(std::move(other_tree.__tree_size)){}
                     
        // constructor which supports random_access_iterator
        template<typename InputIterator>
        SegmentTree( InputIterator __first , InputIterator __last , 
                     const Algo &prefixAlgo = Algo() ) ;

        // destructor
        ~SegmentTree(void) ;

        // get size of tree
        size_t size(void)const { return __tree_size ; }

        // single-point update
        void update( size_t index , T data ) ;
        // interval query
        T query( size_t begin , size_t end )const ;
        T query( const std::pair<size_t,size_t> &queryInterval )const ;

        // Range update
        template<typename UpdatingAlgo>
        void updateRange( size_t begin , size_t end , const UpdatingAlgo &updating_algo ) ;

        template<typename UpdatingAlgo>
        void updateRange( const std::pair<size_t,size_t> &updateInterval , const UpdatingAlgo &updating_algo ) ;
} ;

template<typename T,typename Algo>
void SegmentTree<T,Algo>::generateTree( const std::vector<T> &nums , size_t left , size_t right , Node<T> *&root ){
    if( left == right ){
        root = new Node<T>( {left,right} , nums[left] ) ;
        return ;
    }

    root = new Node<T>( {left,right} , 0 ) ;
    size_t mid = (left+right) / 2 ;
    generateTree( nums , left , mid , root->left ) ;
    generateTree( nums , mid+1 , right , root->right ) ;
    root->value = _prefixAlgo( root->left->value , root->right->value ) ;
}

template<typename T,typename Algo>
template<typename InputIterator>
void SegmentTree<T,Algo>::generateTree( const InputIterator &__first , 
                                        const std::pair<InputIterator,InputIterator> &interval ,
                                        Node<T> *&root )
{
    InputIterator left = interval.first , right = interval.second ;
    if( left == right ){
        root = new Node<T>( {left-__first,right-__first} , *left ) ;
        return ;
    }

    root = new Node<T>( {left-__first,right-__first} , 0 ) ;
    InputIterator mid = left + (right-left) / 2 ;
    generateTree( __first , {left,mid} , root->left ) ;
    generateTree( __first , {mid+1,right} , root->right ) ;
    root->value = _prefixAlgo( root->left->value , root->right->value ) ;
}

template<typename T,typename Algo>
void SegmentTree<T,Algo>::deleteTree( Node<T> *&root ){
    if(!root)   return ;

    deleteTree(root->left) ;
    deleteTree(root->right) ;
    delete root ;
    root = nullptr ;
}

template<typename T,typename Algo>
template<typename InputIterator>
SegmentTree<T,Algo>::SegmentTree( InputIterator __first , InputIterator __last , const Algo &prefixAlgo ) : 
                                  root(nullptr) , _prefixAlgo(prefixAlgo) , __tree_size(0)
{
    static_assert(std::is_same_v<typename std::iterator_traits<InputIterator>::iterator_category,
                                  std::random_access_iterator_tag>) ;
    if( __first > __last )
        throw std::range_error("Invalid range from the input iterator!") ;
    if( __first == __last )
        return ;

    __tree_size = std::distance(__first,__last) ;
    generateTree( __first , {__first,__last-1} , root ) ;
}
                                         

template<typename T,typename Algo>
SegmentTree<T,Algo>::~SegmentTree(void){
    deleteTree(root) ;
}

template<typename T,typename Algo>
void SegmentTree<T,Algo>::updateRecursive( Node<T> *&root , size_t index , T data ){
    if( root->getLowerBound() == root->getUpperBound() ){
        root->value = data ;
        return ;
    }

    size_t mid = ( root->getLowerBound() + root->getUpperBound() ) / 2 ;
    if( index > mid )
        updateRecursive( root->right , index , data ) ;
    else
        updateRecursive( root->left , index , data ) ;
    root->value = _prefixAlgo( root->left->value , root->right->value ) ;
}

template<typename T,typename Algo>
void SegmentTree<T,Algo>::update( size_t index , T data ){
    if(!isWithinBounds(index))
        throw std::out_of_range("The update index is out of bounds!") ;

    updateRecursive( root , index , data ) ;
    return ;
}

template<typename T,typename Algo>
T SegmentTree<T,Algo>::getValue( const Node<T> *root , size_t begin , size_t end )const {
    if( begin == root->getLowerBound() && end == root->getUpperBound() )
        return root->value ;
    
    size_t mid = ( root->getLowerBound() + root->getUpperBound() ) / 2 ;
    if( begin > mid )
        return getValue( root->right , begin , end ) ;
    if( end <= mid )
        return getValue( root->left , begin , end ) ;

    return _prefixAlgo( getValue( root->left , begin , mid ) ,
                        getValue( root->right , mid+1 , end ) ) ;
}

template<typename T,typename Algo>
T SegmentTree<T,Algo>::query( size_t begin , size_t end )const {
    if(!isValidInterval( begin , end ))
        throw std::runtime_error("The lower bound of the interval should not be greater than the upper bound of the interval.") ;
    if(!isWithinBounds( begin , end ))
        throw std::out_of_range("Query range is out of bounds!") ;
        
    return getValue( root , begin , end ) ;
}

template<typename T,typename Algo>
T SegmentTree<T,Algo>::query( const std::pair<size_t,size_t> &queryInterval )const {
    if(!isValidInterval( queryInterval.first , queryInterval.second ))
        throw std::runtime_error("The lower bound of the interval shhould not be greater than the upper bound of the interval.") ;
    if(!isWithinBounds( queryInterval.first , queryInterval.second ))
        throw std::out_of_range("Query range is out of bounds!") ;

    return getValue( root , queryInterval.first , queryInterval.second ) ;
}

template<typename T,typename Algo>
template<typename UpdatingAlgo>
void SegmentTree<T,Algo>::updateRange( size_t begin ,  size_t end , const UpdatingAlgo &updating_algo ){
    if(!isValidInterval( begin , end ))
        throw std::runtime_error("The lower bound of the interval should not be greater than the upper bound of the interval.") ;
    if(!isWithinBounds( begin , end ))
        throw std::out_of_range("Update range is out of bounds!") ;

    // Not yet implemented
}

template<typename T,typename Algo>
template<typename UpdatingAlgo>
void SegmentTree<T,Algo>::updateRange( const std::pair<size_t,size_t> &updateInterval , const UpdatingAlgo &updating_algo ){
    if(!isValidInterval( updateInterval.first , updateInterval.second ))
        throw std::runtime_error("The lower bound of the interval should not be greater than the upper bound of the interval.") ;
    if(!isWithinBounds( updateInterval.first , updateInterval.second ))
        throw std::out_of_range("Update range is out of bounds!") ;

    // Not yet implemented
}

#endif	//__SEGMENTTREE_H__