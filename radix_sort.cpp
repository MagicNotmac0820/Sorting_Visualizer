#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>
#include <queue>
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

void showSortingProcess( const vector<int> &nums , int start_index , int curr_index )
{
    cout << CLEAR_WINDOW ;
    for( size_t i = 0 ; i < nums.size() ; ++i ){
        const char *bg_color = BG_WHITE ;
        if( i == static_cast<size_t>(start_index) )
            bg_color = BG_AQUA ;
        else if( i == static_cast<size_t>(curr_index) )
            bg_color = BG_RED ;

        cout << bg_color << std::setw(nums[i]) << ' ' << DEFAULT << '\n' ;
    }
    usleep(25000) ;

    return ;
}

int getKthDigit( const int num , const int k ){
    return ( num / static_cast<int>(pow(10,k-1)) ) % 10 ;
}

void sorting_algorithm( vector<int> &nums , bool descending ){
    std::queue<int> buckets[10] ;
    int maxDigit = 1 ;
    for( const int &element : nums )
        if(element)
            maxDigit = std::max( maxDigit , static_cast<int>(log(element)/log(10))+1 ) ;

    for( int i = 1 ; i <= maxDigit ; ++i ){
        for( int j = 0 ; static_cast<size_t>(j) < nums.size() ; ++j ){
            buckets[getKthDigit(nums[j],i)].push(nums[j]) ;
            showSortingProcess( nums , -1 , j ) ;
        }

        int index = 0 ;
        for( std::queue<int> &q : buckets ){
            int head = index ;

            while(!q.empty()){
                showSortingProcess( nums , head , index ) ;
                nums[index++] = q.front() ;
                showSortingProcess( nums , head , index ) ;
                q.pop() ;
            }
        }
    }

    if(descending)
        std::reverse( nums.begin() , nums.end() ) ;
    return ;
}

int main(void){
    int numsSize ;
    cin >> numsSize ;
    vector<int> nums(numsSize) ;
    for( int i = 0 ; i < numsSize ; ++i )
        nums[i] = i+1 ;
    shuffle(nums) ;

    sorting_algorithm( nums , 0 ) ;
    showSortingProcess( nums , -1 , -1 ) ;

    return EXIT_SUCCESS ;
}