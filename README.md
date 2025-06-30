# Sorting_Visualizer

## Introduction
A project to visualize some famous sorting algorithms using terminal.
Below are sorting algorithms which are implemented in this project:
- [Bubble Sort](https://en.wikipedia.org/wiki/Bubble_sort)
- [Selection Sort](https://en.wikipedia.org/wiki/Selection_sort)
- [Insertion Sort](https://en.wikipedia.org/wiki/Insertion_sort)
- [Quick Sort](https://en.wikipedia.org/wiki/Quicksort)
- [Merge Sort](https://en.wikipedia.org/wiki/Merge_sort)
- [Heap Sort](https://en.wikipedia.org/wiki/Heapsort)
- [Radix Sort](https://en.wikipedia.org/wiki/Radix_sort)

Since "Selection Sort" involves the range query for extreme values, and coincidentally, there is a data structure "Segment Tree" which supports range query with high efficiency. I try using a Segment Tree implemented by myself to optimize the finding maximum/minimum process.  
You can see the details for Segment Tree here:  
https://github.com/MagicNotmac0820/Segment_Tree.git  

## Install
The source code requires a compiler with c++17 support. Please ensure you have GCC 7.1 or newer installed before building.
```
$ git clone https://github.com/MagicNotmac0820/Sorting_Visualizer.git
```

## Usage
- To build it, you need to
    ```
    $ make
    ```

- If you just want to build a specific file, you need to
    ```
    $ make bin/algo
    ```

- To execute it, you need to
    ```
    $ ./bin/algo
    ```

