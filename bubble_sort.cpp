#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>
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

void showSortingProcess( const vector<int> &nums , int target ){
    cout << CLEAR_WINDOW ;
    for( size_t i = 0 ; i < nums.size() ; ++i ){
        const char *bg_color = BG_WHITE ;
        if( i == static_cast<size_t>(target) )
            bg_color = BG_RED ;

        cout << bg_color << std::setw(nums[i]) << ' ' << DEFAULT << '\n' ;
    }
    usleep(25000) ;

    return ;
}

template< typename Compare = std::less<int> >
void sorting_algorithm( vector<int> &nums , Compare _cmp = std::less<int>() ){
    int numsSize = nums.size() ;

    for( int i = numsSize-1 ; i > 0 ; --i ){
        for( int j = 1 ; j <= i ; ++j ){
            if(_cmp( nums[j] , nums[j-1] ))
                std::swap( nums[j] , nums[j-1] ) ;

            showSortingProcess( nums , j-1 ) ;
        }
    }

    return ;
}

int main(void){
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