# Chapter 2. Sorting

Sorting is the process of rearranging data items in a sequence of objects in a certain 
order, which represent concrete logical meanings, by comparing data elements with each
other.

To implement sensible sorting bahavior, the comparisons between the data types must 
have a *total order*. That means it must be:
- *Reflexive*: for all `v`, `v` = `v`)
- *Antisymmetric*: for all `v` and `w`, if `v < w`, `w > v`, and if `v = w`, `w = v`
- *Transitive*: for all `v`, `w`, and `x`, if `v <= w` and `w <= x`, `v <= x`

***Utilities:***
[sort_driver](sort_driver.c): Given an input file that holds a given number of 
`unsigned long`s, sort the sequence and output the result (either to `stdout` or a given 
file.)

[check_sorted](sorted_check.c): Given an output file of "*sort_driver*", check if the 
result is sorted, and output the result (judgement) to `stdout`.

[num_set_generator](num_set_generator.c): Generate a sequence of `unsigned long`.

## 2.1. Elementary Sorts
The major reasons for studying these relatively simple algorithms are:
- They provide context in which we can learn terminology and basic mechanisms.
- They are more effective in some applications than the sophisticated ones.
- They are useful in improving the efficiency of more sophisticated algorithms.

The implementation of elementary sorts are provided:
[implementation](elem_sorts.c) | [interface](elem_sorts.h)

### Selection Sort
One of the simplest and most instinctual sorting algorithm that you might have written 
before learning any sorting algorithms works as follows:

1. find the smallest item in the array and exchange it with the first entry
2. find the smallest item and exchange it with the second entry
3. and so on...

This method is called *selection sort* because it works by repeatedly selecting the 
smallest remaining item.

#### Analysis
**Running Time is Insensitive to Content**: Each iteration traverse to the end of the 
sequence and compare smallest with each element. This process is not affected by neither  
content of the array nor order of it.

**Data movement is Linear to Array Size**: Exchange only happen in the outer iteration. 
When exchange is implemented, the smallest item in the remaining is always sent to the 
correct destination.

### Insertion Sort
Similar to selection sort, insertion sort also maintain a pointer (or index) to mark a 
fraction that is guaranteed to be sorted. Nonetheless, the "sorted" fraction in insertion 
sort only guaranteed to be sorted among the sorted fraction (as opposed to final position 
that is guranteed in selection sort), meaning that these elements may be moved to provide 
extra room for smaller items inserted later from the "unsorted" fraction.

#### Analysis
**Running Time is Content Dependent**: Unlike selection sort, the performance of 
insertion sort is highly dependent on the input content. For instance, if the array is 
sorted (or nearly sorted) before the function call, it takes merely time linear to data 
size.

**Partially Sorted Array**: An *inversion* is a pair of entries that are out of order in 
the array. For instance, `E X A M P L E` has 11 inversions: `E-A`, `X-A`, `X-M`, `X-P`, 
`X-L`, `X-E`, `M-L`, `M-E`, `P-L`, `P-E`, and `L-E`. If the number if *inversions* in the 
array is less than a constant multiple of the array size, the array is partially sorted.

#### Practice

Insertion sort is efficient for sorting **partially sorted arrays** (while selection is 
not). Indeed, when the number of *inversions* is low enough, insertion sort is likely to 
be faster than ***any*** sorting method involved in this chapter (even the elegant ones).
Typical examples of *partially* sorted arrays are:
- An array where each entry is not far from its final position
- A small array appended to a large sorted array
- An array with only a few entries that are not in place

### Shellsort
Insertion sort is slow for large unordered array because items can move through the array 
only one place at a time. For example, if the item with the smallest key happens to be at 
the end of the array, $N - 1$ exchanges are executed to "walk through" the whole array.

There is, accordingly, a simple extension to move items to roughly the right place, thus 
producing a partially sorted array. That is to sort the sequence to give it the property 
that taking every $h$th entry (starting anywhere) yields a sorted subsequence. Such an 
array is termed $h$-sorted. In other words, an $h$-sorted array is $h$ independent sorted 
subsequences that are interleaved together. By $h$-sorting for same large values of $h$, 
items that are far from it's final position can be moved efficiently to a position that 
is close to it's final position.

#### $h$ Sequence
Shellsort typically $h$-sort for a sequence of $h$ values, which must end in 1.
There is a relatively simple but rather effective sequence, which is actually adopted in 
the my implementation. That is a sequence of decreasing values $\frac{1}{2} \times (3^k - 1)$, 
starting at the largest increment less than $N/3$ and decreasing to $1$.

## 2.2. Merge Sort
As the name suggests, merge sorts are based on a simple operation kown as *merging*: 
combining two ordered arrays to make one larger ordered array. To sort an array, *merge 
sort* simply divide it into two halves, sort those halves (recursively), and then *merge* 
the results.

### Merge
A simple approach to implementing merging is to seperate the output array from input 
arrays, and choose successively the smallest remaining item from the two input arrays to 
be appended to the output array.

However, when the data size is large, the amount of merge call is large; the total 
cost of creating a new array in every merge call is expensive. Hence, it would be much 
more efficient to have an appropriate in-place method, avoiding using a significant amount 
of extra space. Though this might sound plain, the solutions that are known are quit 
complicated, especially by comparison to alternatives that use extra space.

Still, the *abstraction* of an in-place merge is handy for mergesort implementation. 
Accordingly, our first merge implementation uses the signature 
`merge(first, mid, last)`, where `first` is a pointer to the array, `mid` is the past-end 
pointer to first half, or equivalently start of second half, last is the past-end pointer 
to the second half.

### Sort
The sort part of mergesort appears to be simple: use recursive call to sort the left half, 
sort the righ half, and lastly use a designated merge method to combine those two halves.
This is one of the best-known examples of the utility of the *divide-and-conquer* paradigm 
for efficient algorithm design. This recursive code is the basis for an inductive proof 
that the algorithm sorts the array: if it sorts the two subarrays, it sorts the whole 
array, by merging the subarrays.

### Top-down Mergesort
The [top-down mergesort implementation](merge_sort.c) ([interface](merge_sort.h)), 
explained above, require time proportional to $N \cdot log N$. That fact brings us to a 
different level from the elementary method in section 1 because it can sort huge arrays 
using just a logarithmic factor more time than it takes to examine every entry. With 
modern computer, you can sort millions of items (or even more) with mergesort, but it 
would not be possible (in reasonable amount of time) with insertion sort or selection 
sort.

### Improvements

***Use insertion sort for small subarrays.*** We can improve most recursive algorithms by 
handling small cases differently. The logic is that the *divide-and-conquer* paradigm 
guarantees that the array is always cut into small subarrays when it approaches the base 
case (i.e., array size = 1). In such cases, insertion sort (or selection sort) is faster 
than mergesort because their structure is simple, while mergesort has unnecessary costs 
during the function calls. Consequently, switching to insertion sort for small subarrays 
(length 15 or less, say) will improve the running time of a typical merge sort 
implementation by 10 to 15 percent.

***Test whether the array is already in order.*** The running time for sorted subarrays 
can be reduced by adding a test to skip the call to `merge` if `arr[mid - 1] <= arr[mid]`.
With this change, the running time for any sorted subarray is linear.

***Eliminate the copy to the auxiliary array.*** It is possible to eliminate the time 
(but not space) taken to copy the auxiliaray array used for merging. In brief, we allocate 
space for two arrays, and the two arrays switch their roles of input array and auxiliary 
array sequentially at each level.

### Bottom-up Mergesort
Another way to implement mergesort is to organize the merges so that we do all the merges 
of tiny subarrays on one pass, then, do a second pass to merge those subarrays in pairs, 
and so forth, continuing until we do a merge that encompasses the entire array. This 
method requires even less code than the standard recursive implementation. We start by 
doing a pass of 1-by-1 merges (considering individual items as subarrays of size 1), then 
a pass of 2-by-2 merges (merge subarrays of size 2 to make subarrays of 4), then 4-by-4 
merges, and so forth. The second subarray may be smaller than the first in the last merge 
on each pass (which is no problem for `merge`), but otherwise all merges involve subarrays 
of equal size, doubling the sorted subarray size for the next pass.
> The [Implementation](merge_sort.c) and [interface](merge_sort.h) is in the same file as 
  the Top-down ones.
