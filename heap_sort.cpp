#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <output_style.hpp>
using std::cin ;
using std::cout ;
using std::endl ;
using std::vector ;

void shuffle( vector<int> &nums ){
    std::mt19937 rng(std::random_device{}()) ;
    std::shuffle( nums.begin() , nums.end() , rng ) ;
    return ;
}

void showSortingProcess( const vector<int> &nums , int target_index ){
    cout << CLEAR_WINDOW ;
    for( size_t i = 0 ; i < nums.size() ; ++i ){
        const char *bg_color = BG_WHITE ;
        if( i == static_cast<size_t>(target_index) )
            bg_color = BG_RED ;
            
        cout << bg_color << std::setw(nums[i]) << ' ' << DEFAULT << '\n' ;
    }
    usleep(25000) ;

    return ;
}

int indexOfParentNode( const vector<int> &nums , int target_index ) ;
int indexOfLeftNode( const vector<int> &nums , int target_index ) ;
int indexOfRightNode( const vector<int> &nums , int target_index ) ;
template<typename Compare>
void heapifyDown( vector<int> &nums , int target_index , Compare _cmp ) ;
template< typename Compare = std::greater<int> >
int heap_pop( vector<int> &nums , Compare _cmp = std::greater<int>() ) ;
template< typename Compare = std::greater<int> >
void make_heap( vector<int> &nums , Compare _cmp = std::greater<int>() ) ;

template< typename Compare = std::greater<int> >
void sorting_algorithm( vector<int> &nums , Compare _cmp = std::greater<int>() ){
    make_heap( nums , _cmp ) ;

    int index = nums.size()-1 ;
    while(index)
        nums[index--] = heap_pop( nums , _cmp ) ;

    return ;
}

int main(void){
    cout << WHITE << "Please enter the number of data items to be sorted: " << DEFAULT ;
    
    int numsSize ;
    cin >> numsSize ;
    vector<int> nums(numsSize) ;
    for( int i = 0 ; i < numsSize ; ++i )
        nums[i] = i+1 ;
    shuffle(nums) ;
    
    sorting_algorithm(nums) ;
    showSortingProcess( nums , -1 ) ;
    
    return EXIT_SUCCESS ;
}

int indexOfParentNode( const vector<int> &nums , int target_index ){
    if( target_index <= 0 || static_cast<size_t>(target_index) >= nums.size() )
        return -1 ;

    return (target_index-1) / 2 ;
}

int indexOfLeftNode( const vector<int> &nums , int target_index ){
    if( target_index < 0 || static_cast<size_t>( 2*target_index + 1 ) >= nums.size() )
        return -1 ;

    return 2*target_index + 1 ;
}

int indexOfRightNode( const vector<int> &nums , int target_index ){
    if( target_index < 0 || static_cast<size_t>( 2*target_index + 2 ) >= nums.size() )
        return -1 ;

    return 2*target_index + 2 ;
}

template< typename Compare >
void heapifyDown( vector<int> &nums , int effective_elements_num , int target_index , Compare _cmp ){
    while(1){
        int left_node_index = indexOfLeftNode( nums , target_index ) ;
        int right_node_index = indexOfRightNode( nums , target_index ) ;
        int most_priority_node_index = target_index ;

        if( left_node_index != -1 && left_node_index < effective_elements_num &&
            _cmp( nums[left_node_index] , nums[most_priority_node_index] ) )
            most_priority_node_index = left_node_index ;
        if( right_node_index != -1 && right_node_index < effective_elements_num && 
            _cmp( nums[right_node_index] , nums[most_priority_node_index] ) )
            most_priority_node_index = right_node_index ;

        if( most_priority_node_index == target_index ){
            showSortingProcess( nums , target_index ) ;
            break ;
        }


        showSortingProcess( nums , target_index ) ;
        std::swap( nums[target_index] , nums[most_priority_node_index] ) ;
        target_index = most_priority_node_index ;
        showSortingProcess( nums , target_index ) ;
    }

    return ;
}

template<typename Compare>
int heap_pop( vector<int> &nums , Compare _cmp ){
    static int back_index = nums.size()-1 ;

    int result = nums[0] ;
    nums[0] = nums[back_index] ;
    heapifyDown( nums , back_index-- , 0 , _cmp ) ;

    return result ;
}

template<typename Compare>
void make_heap( vector<int> &nums , Compare _cmp ){
    int first_non_leaf_node_index = (nums.size()-1) / 2 ;

    for( int i = first_non_leaf_node_index ; i >= 0 ; --i )
        heapifyDown( nums , nums.size() , i , _cmp ) ;

    return ;
}