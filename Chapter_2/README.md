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
sequence and compare smallest with each element. This process is affected by neither  
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
my implementation. That is a sequence of decreasing values $\frac{1}{2} \times (3^k - 1)$, 
starting at the largest increment less than $N/3$ and decreasing to $1$.

### Exercises

#### Exercise 1.13: *Deck Sort*.
> Explain how you would put a deck of cards in order by suit (in the order spades, 
  hearts, clubs, diamonds) and by rank within each suit, with the restriction that the 
  cards must be laid out face down in a row, and the only allowed operations are to check 
  the values of two cards and to exchange two cards (keeping them face down).

To sort such a deck, using only the given operations, you can follow a process similar to 
a modified version of any of the elementary sorting algorithms. A code demonstration is 
shown below:

[Deck sort demonstration](ex1p13/driver.c) | [card object interface](ex1p13/card.h)
| [card obj. method](ex1p13/card.c)

## 2.2. Mergesort
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

#### Usage
A version of bottom-up mergesort is the method of choice for sorting data organized in a 
*liked list*.

## 2.3. Quicksort
*Quicksort* is the sorting algorithm that is probably used more widely than any other. It 
is popular because:
- it is not difficult to implement,
- works well for a variety of different kinds of input data, and
- is substantially faster than any other sorting method in typical applications.

The quicksort algorithm's desirable features are that:
- it is *in-place* (uses only a small auxiliary stack), and that
- it requires time proportional to $N \cdot logN$ on the average.

None of the algorithms that we have so far considered combine these two properties.
Furthermore, it has a shorter inner loop than most other sorting algorithms, which means 
that it is fast in practice as well as in theory.

### The basic algorithm
Similar to mergesort, quicksort is a divide-and-conquer method for sorting. It works by 
*partitioning* an array into two subarrays, then sorting the subarrays independently. 
Quicksort is complementary to mergesort: for mergesort, we break the array into two 
subarrays to be sorted and then combine the ordered subarrays to make the whole ordered 
array; for quicksort, we rearrange the array such that, when the two subarrays are sorted, 
the whole array is ordered.

The crux of the method is the *partitioning* process, which rearranges the array to make 
the following three conditions hold:
- the entry `a[j]` is in its final place in the array, for some `j`.
- no entry in `a[lo]` through `a[j-1]` is greater than `a[j]`.
- no entry in `a[j+1]` through `a[hi]` is less than `a[j]`.

The complete sort is completed by partitioning, then recursively applying the method.

Because the partitioning process always fixes one item into its final position, it is 
simple to prove that this recursive method constitutes a proper sort:
- the items to the left are not greater than the partitioning item
- the items to the right are not smaller than the partitioning item
- the partitioning item is in its final place
- left subarray and right subarray are sorted through recursive call to this function

Quicksort is a *ramdomized* algorithm because it randomly shuffles the array before 
sorting it. The randomization is done so that its performance characteristics are more 
predictable.

### Knuth Shuffle
There is a simple shuffling algorithm that can be done in linear time and has even 
distribution. The process adopts the following set of instructions:
1. maintain a range of "shuffled elements", which start at a size of 0.
2. Add one "unshuffled element" into the "shuffled elements"
3. exchange it with an element randomly selected among the "shuffled elements" (including 
    the newly added element)
4. repeat step 2 & 3 until the entire array is added into "shuffled elements"

### Partition
The partitioning function is the kernel of quicksort. It involves the following general 
strategy:
1. Choose `a[lo]` (or any arbitrary item in the range) to be the *partitioning item*.
2. Scan from the left end until finding an entry greater than or equal to the partitioning 
    item. Then, scan from the right end until finding an entry less than or equal to the 
    partitioning item.
3. Exchange these two items, which are not in the right place.
4. Repeat step 2 & 3 until the two scan iterators cross.
5. Exchange the rightmost entry of the left subarray (`a[j]`) and return the index `j`.

*Staying in Bounds.* To stay within bounds, protective measures must be taken against the 
possibility that the partitioning item could be the smallest or largest item in the array. 
If this occurs, the iterators may inadvertently run off the left or right ends of the 
array, respectively. Testing at the left is redundant in this case because it is the first 
entry, which is not less than itself, to be chosen as the partitioning item.

*Preserving Randomness.* The random shuffle puts the array in random order. Since it 
treats all items in the subarrays uniformly, the partitioning has the property that its
two subarrays are also in random order. An alternate way to preserve randomness is to 
choose a random item for partitioning within partition.

*Handling Items with Keys Equal to the Partitioning Item's Key.* To maintain efficiency, 
halt the left scan when finding item greater than or **equal** to the partitioning item's 
key, and the right scan for items less than or **equal** to the partitioning item. Though 
it may prompt seemingly needless swaps for items with keys matching the partitioning item, 
this practice is vital for preventing quadratic runtimes in common cases. Subsequently, 
we will explore a more refined approach for arrays with numerous identical keys.

### Improvements
Quicksort is so well-balanced and elegant that only a few of the improvements among the 
proposed methods are considered generally successful. As noted, you need to run 
experiments to determine the effectiveness of these improvements and to determine the 
best choice of parameters for your implementation. Typically improvements of $20%$ to 
$30%$ are available.

#### Cutoff to insertion sort
As with most recursive algorithms, an easy way to improve the performance is based on the 
following two observations:
- Quicksort is slower than insertion sort for tiny subarrays.
- Being recursive, quicksort's `sort` is certain to call itself for tiny subarrays.

The optimum value of the cutoff is system-dependent, but any value between 5 and 15 is 
likely to work well in most situations.

#### Median-of-Three Partitioning
A second way to improve the performance of quicksort is to use the median of a small 
sample of items taken from the subarray as the partitioning item. Doing so will give a 
slightly better partition, but at the cost of computing the median. It turns out most of 
the available improvement comes from choosing a sample of size 3 and then partitioning on 
the middle item. As a bonus, we can use the sample item as sentinels at the ends of the 
array and remove both array bounds tests in `partition`.

#### Entropy-Optimal Sorting
Arrays with large numbers of duplicate keys arise frequently in applications. In such 
situations, the quicksort implementation that we considered has acceptable performance, 
but it can be substantially improved. For example, a subarray that consists solely of 
items that are equal (just one key value) does not need to be processed further, but our 
implementation keeps partitioning down to small subarrays.

One straitforward idea is to partition the array into *three* parts, one each for items 
with keys smaller than, equal to, and larger than the partitioning item's key. 

*Dijkstra's solution* to this problem leads to the remarkably simple partition code. It is 
based on a single left-to-right pass through the array that maintains a pointer `lt` such 
that `a[lo..lt-1]` is less than `v`, a pointer `gt` such that `a[gt+1..hi]` is greater 
than `v`, and a pointer `i` such that `a[lt..i-1]` are *equal to* `v` and `a[i..gt]` are 
not yet examined. Starting with `i` equal to `lo`, we process `a[i]` using the 3-way 
comparison to directly handle the three possible cases:
- `a[i]` less than `v`: exchange `a[lt]` with `a[i]` and increment both `lt` and `i`
- `a[i]` greater than `v`: exchange `a[i]` with `a[gt]` and decrement `gt`
- `a[i]` equal to `v`: increment `i`

Each of these operations both maintains the invariant and decreases the value of `gt - i` 
(so that the loop terminates).

Though this method is simple to implement, this method fell out of favor quickly because 
it uses many more exhcanges than the standard 2-way partitioning method when the number of 
duplicate keys in the array is not high.

There is a clever implementation that overcomes this problem (see *exercise 2.3.22*).

## 2.4. Priority Queues
Many applications require the processing of items with keys in order, but necessarily in 
full sorted order and not necessarily all at once. It is also often that items are 
collected so that the largest key at the time can be found and processed. This approach is 
usually how devices manage multiple applications by assigning priority to associated 
events and processing the highest-priority event next. For instance, incoming calls 
typically take priority over running a game application on most cellphones.

An appropriate data type in such an environment supports two operations: *remove the 
maximum* and *insert*. Such a data type is called *priority queue*.

### Possible Usage
To appreciate the value of the priority-queue abstraction, consider the following 
problem: You have a huge input stream of `N` strings and associated integer values, and 
your task is to find the largest or smallest `M` integers (and associated strings) in the 
input stream. In some applications, the size of the input stream is so huge that it is 
best to consider it to be unbounded. One way to address this problem would be to sort the 
input stream and take `M` largest keys from the result, but it is stipulated that the 
input stream is too large for that. Another approach would be to compare each new key 
against the `M` largest seen so far, but that is likely to be prohibitively expensive 
unless `M` is small. With priority queues, we can solve the problem with the `MinPQ` 
client *provided* that we can develop efficient implementations of both `insert` and 
`delMin`.

### Elementary Implementations
#### Array Representation (unordered)
- Append the item to the array when calling `insert`.
- Search and exhcange the maximum item with the item at the end and then delete it when 
    calling `remove the maximum`.

#### Array Representation (ordered)
- *insert* the new item to the right position (as in insertion sort) for `insert`.
- Simply remove the last item for `remove the maximum`.

#### Linked-List Representations
Similar to array representations above, linked-list 
representations can be implemented by keeping the items in a linked-list and either trying 
to "find and remove the maximum" when `remove the maximum` is called or by keeping the 
items in *reverse* order.

#### Analysis
| data structure | insert | remove maximum |
| -------------- | ------ | -------------- |
| ordered array  | N      | 1              |
| unordered array| 1      | N              |
| heap           | $log N$| $log N$        |
| impossible     | 1      | 1              |

Using unordered sequences is the prototypical *lazy* approach to this problem, where we 
defer doing work until necessary; using ordered sequence is the prototypical *eager* 
approach, where we do as much work as we can up front to make later operations efficient.

### Binary Heap
#### Definition
The *binary heap* is a data structure that can efficiently support the 
basic priority-queue operations. In a binary head, the keys are stored in an array such 
that each key is guaranteed to be larger than (or equal to) the keys at two other specific 
positions. The structure is analogous to a binary tree where each node is greater than 
(or equal to) it's subnodes.

#### Representation
If we use a linked representation for heap-ordered binary trees, we 
would need to have **three** links assciated with each key to allow traveling up and down 
the tree (i.e., one pointer to parent, and one to each child). It is particularly 
convenient, instead, to represent the binary tree in array representation. In a binary 
heap, the parent of the node in position $k$ is in position 
$\left\lfloor\frac{k}{2}\right\rfloor$ and, conversely, the two children of the node are 
in positions $2k$ and $2k + 1$. This not only uses less space but also allow users to 
travel up and down by doing simple arithmetic on array indicies: to move *up* the tree 
from `a[k]`, we set `k` to `k/2`; to move *down* the tree we set `k` to `2*k` or `2*k+1`.

> The height of a complete binary tree of size $N$ is $\left\lfloor lg N\right\rfloor$.

#### Implmentation
A heap of size `N` is represented in an array of size `N + 1`, with the zeroth entry 
unused. The heap operations work by first making a simple modification that could violate 
the heap condition, then traveling through the heap, modifying the heap as required to 
ensure that the heap condition is satisfied everywhere. We refer to this process as 
*reheapifying*, or *restoring heap order*.

***Bottom-up Reheapify (swim).*** If the heap order is violated because a node's key 
becoms *larger* than that node's parent's key, then we can make progrress toward fixing 
the violation by exchanging the node with it parent until it reach a parent that has 
higher key value, or the root.

***Top-down Reheapify (sink).*** If the heap order is violated because a node's key 
becomes *smaller* than one or both of that node's children's keys, then we can fix the 
violation by exchanging the node with the *larger* of its two children until both chilren 
are smaller or equal to the node, or reaching the bottom.

***Insert.*** Add the new key at the end of the array, increment the size of the heap, and 
then `swim` up through the heap with that key to restore the heap condition.

***Remove the maximum.*** We take the largest key off the top, put the item from the end 
of the heap at the top, decrement the size of the heap, and then sink down through the 
heap with that key to restore the heap condition.

#### Improvements
***Multiway Heaps.*** It is not difficult to modity our code to build heaps based on an 
array representation of complete heap-ordered *ternary* trees. However, there is a 
tradeoff between the lower cost from the reduced tree height ($log_{d}N$) and the higher 
cost of finding the largest of the *d* children at each node. This tradeoff is dependent 
on details of the implementation and the expected relative frequency of operations.

### Heapsort
We can use any priority queue to develop a sorting method. We insert all the items to be 
sorted into a minimum-origented priority queue, then repeatedly use *remove the minimum* 
to remove them all in order.

Using priority queue represented as an unordered array in this way corresponds to doing a 
selection sort; using an ordered array corresponds to doing an insertion sort. What 
sorting method do we get if we use a heap? It's a classic elegant sorting algorithm known 
as *heapsort.

Heapsort breaks into two phases:
1. **heap construction**
    - where we reorganize the original array into a heap
2. **sortdown**
    - where we pull the items out of the heap in decresing order to build the sorted 
        result

To sort the array in-place, we abandon the notion of hiding the representation of the 
priority queue and use `swim` and `sink` directly.

#### Heap construction
A simple method is to proceed from left to right through the array, using `swim` to 
ensure that the items to the left of the scanning pointer make up a heap-ordered complete 
tree, like successive priority-queue insertions.

A clever method that is much more efficient is to proceed from right to left, using `sink`
to make subheaps as we go. Every position in the array is the root of a small subheap; 
`sink` works for such subheaps, as well. If the children of a node are heaps, then calling 
`sink` on that node makes the subtree rooted at the parent a heap. This process 
establishes the heap order inductively.

> The scan starts halfway back through the array because we can skip the subheaps of size 
  \1. The scanf ends at position 1, when we finish building the heap with one call to 
  `sink`

#### Sortdown
Most the work during heapsort is done during the second phase, where we remove the 
largest remaining item from the heap and put it into the array position vacated as the 
heap shrinks. This process is a bit like selection sort (selecting the items in 
decreasing order instead of increasing order), but it uses many fewer compare because the 
heap provides a much more efficient way to find the largest item in the unsorted part.

*Sink to the bottom, then swim* is a simple method that can improve the efficiency of 
heapsort. Most items reinserted into the heap during sortdown go all the way to the 
bottom. Accodingly, we can save time by avoiding the check for whether the item has reach 
its position, simply promoting the larger of the two children until the bottom is reached, 
then moving back up the heap to the proper position. This idea cuts the number of compare 
a factor of 2 asymptotically--close to the number used by mergesort (for a 
randomly-ordered array).
> This method is useful in practice only when the cost of compare is relatively high (for 
  example, when we are sorting items with strings or other types of long keys.)
