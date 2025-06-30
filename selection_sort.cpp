#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <algorithm>
#include <unistd.h>
// using segment tree to optimize the time complexity of finding interval extremum
#include <SegmentTree.h>
#include <output_style.hpp>
using std::cin ;
using std::cout ;
using std::vector ;

void shuffle( vector<int> &nums ){
    std::mt19937 rng(std::random_device{}()) ;
    std::shuffle( nums.begin() , nums.end() , rng ) ;
    return ;
}

void showSortingProcess( const vector<int> &nums , int base_index , int min_index )
{
    cout << CLEAR_WINDOW ;
    for( size_t i = 0 ; i < nums.size() ; ++i ){
        const char *bg_color = BG_WHITE ;
        if( i == static_cast<size_t>(base_index) )
            bg_color = BG_AQUA ;
        else if( i == static_cast<size_t>(min_index) )
            bg_color = BG_RED ;

        cout << bg_color << std::setw(nums[i]) << ' ' << DEFAULT << '\n' ;
    }
    usleep(25000) ;

    return ;
}

template< typename Compare = std::less<int> >
void sorting_algorithm( vector<int> &nums , Compare _cmp = std::less<int>() ){
    int numsSize = nums.size() ;
    vector<int> indexArray(numsSize) ;
    for( int i = 0 ; i < numsSize ; ++i )
        indexArray[i] = i ;
        
    struct prefixAlgo{
        vector<int> &data ;
        Compare cmp_obj ;
        prefixAlgo( vector<int> &input_data , const Compare &obj ) : 
            data(input_data) , cmp_obj(obj){}

        int operator()( const int &index1 , const int &index2 )const {
            if(cmp_obj( data[index1] , data[index2] ))
                return index1 ;
            return index2 ;
        }
    } ;

    SegmentTree<int,prefixAlgo> tree( indexArray.begin() , indexArray.end() , prefixAlgo(nums,_cmp) ) ;
    for( int i = 0 ; i < numsSize-1 ; ++i ){
        int minIndex = tree.query(i,numsSize-1) ;
        showSortingProcess( nums , i , minIndex ) ;
        
        if( i != minIndex ){
            std::swap( nums[i] , nums[minIndex] ) ;
            tree.update(i,i) ;
            tree.update(minIndex,minIndex) ;
        }

        showSortingProcess( nums , i , minIndex ) ;
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
    showSortingProcess( nums , -1 , -1 ) ;

    return EXIT_SUCCESS ;
}