#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <output_style.hpp>
using std::cin ;
using std::cout ;
using std::vector ;

void shuffle( vector<int> &nums ){
    std::mt19937 rng(std::random_device{}()) ;
    std::shuffle( nums.begin() , nums.end() , rng ) ;
    return ;
}

void showSortingProcess( const vector<int> &nums , int base_index , int _first , int _last )
{
    cout << CLEAR_WINDOW ;
    for( size_t i = 0 ; i < nums.size() ; ++i ){
        const char *bg_color = BG_WHITE ;
        if( i == static_cast<size_t>(base_index) )
            bg_color = BG_AQUA ;
        else if( i == static_cast<size_t>(_first) || i == static_cast<size_t>(_last) )
            bg_color = BG_RED ;

        cout << bg_color << std::setw(nums[i]) << ' ' << DEFAULT << '\n' ;
    }
    usleep(25000) ;

    return ;
}

template<typename Compare>
int find_median_index( vector<int> &nums , int _first , int _second , int _third , Compare _cmp ) ;
template<typename Compare>
int partition( vector<int> &nums , int _first , int _last , Compare _cmp ) ;
template<typename Compare>
void quick_sort( vector<int> &nums , int _first , int _last , Compare _cmp ) ;

template< typename Compare = std::less<int> >
void sorting_algorithm( vector<int> &nums , Compare _cmp = std::less<int>() ){
    return quick_sort( nums , 0 , nums.size()-1 , _cmp ) ;
}

int main(void){
    int numsSize ;
    cin >> numsSize ;
    vector<int> nums(numsSize) ;
    for( int i = 0 ; i < numsSize ; ++i )
        nums[i] = i+1 ;
    shuffle(nums) ;

    sorting_algorithm(nums) ;
    showSortingProcess( nums , -1 , -1 , -1 ) ;

    return EXIT_SUCCESS ;
}

template<typename Compare>
int find_median_index( vector<int> &nums , int _first , int _second , int _third , Compare _cmp ){
    if( !_cmp( nums[_second] , nums[_first] ) && !_cmp( nums[_third] , nums[_second] ) )
        return _second ;

    if( !_cmp( nums[_first] , nums[_second] ) && !_cmp( nums[_third] , nums[_first] ) )
        return _first ;

    return _third ;
}

template<typename Compare>
int partition( vector<int> &nums , int _first , int _last , Compare _cmp ){
    int base_index = find_median_index( nums , _first , (_first+_last) / 2 , _last , _cmp ) ;
    std::swap( nums[base_index] , nums[_first] ) ;
    base_index = _first ;

    while( _first < _last ){
        while( _first < _last && !_cmp( nums[_last] , nums[base_index] ) ){
            --_last ;
            showSortingProcess( nums , base_index , _first , _last ) ;
        }
            
        while( _first < _last && !_cmp( nums[base_index] , nums[_first] ) ){
            ++_first ;
            showSortingProcess( nums , base_index , _first , _last ) ;
        }

        std::swap( nums[_first] , nums[_last] ) ;
        showSortingProcess( nums , base_index , _first , _last ) ;
    }

    std::swap( nums[base_index] , nums[_first] ) ;
    showSortingProcess( nums , base_index , _first , _last ) ;

    return _first ;
}

template<typename Compare>
void quick_sort( vector<int> &nums , int _first , int _last , Compare _cmp ){
    if( _first >= _last )
        return ;

    int pivot = partition( nums , _first , _last , _cmp ) ;
    quick_sort( nums , _first , pivot-1 , _cmp ) ;
    quick_sort( nums , pivot+1 , _last , _cmp ) ;
}