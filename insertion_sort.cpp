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

void showSortingProcess( const vector<int> &nums , int curr_index , int insert_index ){
    cout << CLEAR_WINDOW ;
    for( size_t i = 0 ; i < nums.size() ; ++i ){
        const char *bg_color = BG_WHITE ;

        if( i == static_cast<size_t>(curr_index) )
            bg_color = BG_AQUA ;
        else if( i == static_cast<size_t>(insert_index) || i == static_cast<size_t>(insert_index)-1 )
            bg_color = BG_RED ;

        cout << bg_color << std::setw(nums[i]) << ' ' << DEFAULT << '\n' ;
    }
    usleep(25000) ;

    return ;
}

template< typename Compare = std::less<int> >
void sorting_algorithm( vector<int> &nums , Compare _cmp = std::less<int>() ){
    int numsSize = nums.size() ;
    for( int i = 1 ; i < numsSize ; ++i ){
        int insert_index = i ;

        while( insert_index > 0 && _cmp( nums[insert_index] , nums[insert_index-1] ) ){
            showSortingProcess( nums , i , insert_index ) ;
            std::swap( nums[insert_index] , nums[insert_index-1] ) ;
            showSortingProcess( nums , i , insert_index ) ;
            --insert_index ;
        }
    }

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
    showSortingProcess( nums , -1 , -1 ) ;

    return EXIT_SUCCESS ;
}