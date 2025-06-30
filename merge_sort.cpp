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

void showSortingProcess( const vector<int> &nums ,
                         int left_bound , int right_bound ,
                         int _first_ptr , int _mid , int _second_ptr )
{
    cout << CLEAR_WINDOW ;
    for( size_t i = 0 ; i < nums.size() ; ++i ){
        const char *bg_color = BG_WHITE ;
        if( i == static_cast<size_t>(left_bound) || i == static_cast<size_t>(right_bound) )
            bg_color = BG_GREEN ;
        else if( i == static_cast<size_t>(_mid) )
            bg_color = BG_AQUA ;
        else if( i == static_cast<size_t>(_first_ptr) || i == static_cast<size_t>(_second_ptr) )
            bg_color = BG_RED ;

        cout << bg_color << std::setw(nums[i]) << ' ' << DEFAULT << '\n' ;
    }
    usleep(25000) ;

    return ;
}

template<typename Compare>
void merge2( vector<int> &nums , 
             const std::pair<int,int> &first_interval , const std::pair<int,int> &second_interval ,
             Compare _cmp ) ;
template<typename Compare>
void mergeSort( vector<int> &nums , int _first , int _last , Compare _cmp ) ;

template< typename Compare = std::less<int> >
void sorting_algorithm( vector<int> &nums , Compare _cmp = std::less<int>() ){
    return mergeSort( nums , 0 , nums.size()-1 , _cmp ) ;
}

int main(void){
    int numsSize ;
    cin >> numsSize ;
    vector<int> nums(numsSize) ;
    for( int i = 0 ; i < numsSize ; ++i )
        nums[i] = i+1 ;
    shuffle(nums) ;

    sorting_algorithm(nums) ;
    showSortingProcess( nums , -1 , -1 , -1 , -1 , -1 ) ;

    return EXIT_SUCCESS ;
}

template<typename Compare>
void merge2( vector<int> &nums ,
             const std::pair<int,int> &first_interval , const std::pair<int,int> &second_interval ,
             Compare _cmp )
{
    int interval1Size = first_interval.second - first_interval.first + 1 ;
    int interval2Size = second_interval.second - second_interval.first + 1 ;
    vector<int> result(interval1Size+interval2Size) ;
    int _first_ptr = first_interval.first ;
    int _second_ptr = second_interval.first ;

    int _modify_ptr = 0 ;
    while( _first_ptr <= first_interval.second && _second_ptr <= second_interval.second ){
        if(_cmp( nums[_first_ptr] , nums[_second_ptr] ))
            result[_modify_ptr++] = nums[_first_ptr++] ;
        else
            result[_modify_ptr++] = nums[_second_ptr++] ;

        showSortingProcess( nums ,
                            first_interval.first , second_interval.second ,
                            _first_ptr , second_interval.first , _second_ptr ) ;
    }

    while( _first_ptr <= first_interval.second ){
        result[_modify_ptr++] = nums[_first_ptr++] ;

        showSortingProcess( nums ,
                            first_interval.first , second_interval.second ,
                            _first_ptr , second_interval.first , _second_ptr ) ;
    }

    while( _second_ptr <= second_interval.second ){
        result[_modify_ptr++] = nums[_second_ptr++] ;

        showSortingProcess( nums ,
                            first_interval.first , second_interval.second ,
                            _first_ptr , second_interval.first , _second_ptr ) ;
    }

    for( size_t i = 0 ; i < result.size() ; ++i ){
        nums[first_interval.first+i] = result[i] ;
        showSortingProcess( nums ,
                            first_interval.first , second_interval.second ,
                            first_interval.first+i , second_interval.first , first_interval.first+i ) ;
    }
    return ;
}

template<typename Compare>
void mergeSort( vector<int> &nums , int _first , int _last , Compare _cmp ){
    if( _first >= _last )
        return ;

    int mid = (_first+_last) / 2 ;
    mergeSort( nums , _first , mid , _cmp ) ;
    mergeSort( nums , mid+1 , _last , _cmp ) ;

    merge2( nums , std::pair<int,int>{_first,mid} , std::pair<int,int>{mid+1,_last} , _cmp ) ;
}