# 2.1. Elementary Sorts

## Exercise 1.13: *Deck Sort*.
> Explain how you would put a deck of cards in order by suit (in the order spades, 
  hearts, clubs, diamonds) and by rank within each suit, with the restriction that the 
  cards must be laid out face down in a row, and the only allowed operations are:
> 1. to check the values of two cards, and 
> 2. to exchange two cards (keeping them face down).

To sort such a deck, using only the given operations, you can follow a process similar to 
a modified version of any of the elementary sorting algorithms. Demonstration in C is 
shown below:

[Deck sort demonstration](ex1p13to14/ex1p13.c) | [card object interface](ex1p13to14/card.h)
| [card obj. methods](ex1p13to14/card.c)

## Exercise 1.14: *Dequeue Sort*.
> Explain how you would sort a deck of cards, with the restriction that the only allowed 
  operations are:
> 1. to look at the values of the top two cards,
> 2. to exchange the top two cards, and
> 3. to move the top card to the bottom of the deck.

We can approach this problem by using a variant of bubble sort, where we repeatedly move 
the target unsorted card to the bottom of the deck through a series of comparisons and 
swaps. Steps to take:

1. **Identify the Largest Card and Move it to the Bottom:**
    - Repeat the following process for each pass through the deck:
        - Look at the top two cards.
        - If the top card is larger than the second card, exchange them.
        - Move the top card to the bottom of the deck.
        - Repeat until the largest card is found.
        - Move the largest card to the bottom.
2. **Reduce the Problem Size:**
    - After each pass, the largest card is correctly placed at the bottom of the deck.
    - Exclude the last card, which is now sorted, from the next pass.
    - Repeat the process for the remaining unsorted cards.
3. **Repeat until Fully Sorted:**
    - Continue the passes until all cards are sorted.

Demonstration in C:

[Deck sort demonstration](ex1p13to14/ex1p14/driver.c)
| [card object interface](ex1p13to14/card.h) | [card obj. methods](ex1p13to14/card.c)

Considering that it would be inefficient to implement the "move to bottom" operation for 
array data structure, a [variant version of queue](ex1p13to14/ex1p14/queue.h)
([Implementation](ex1p13to14/ex1p14/queue.c)) is applied.

## Exercise 1.15: *Expensive Exchange*.
> A clerk at a shipping company is charged with the task of rearranging a number of large 
  crates in order of the time they are to be shipped out. Thus, the cost of compares is 
  very low (just look at the labels) relative to the cost of exchanges (move the crates). 
  The warehouse is nearly full--there is extra space sufficient to hold any **ONE** of the 
  crates, but not two. What sorting method should the clerk use?

Given the constraints that the cost of compares is low and the cost of exchanges is high, 
along with the fact that there is only enough extra space to hold one crate, the most 
suitable sorting method for this scenario is the **[Selection Sort](README.md#selection-sort)** algorithm.


### Why Selection Sort?
1. **Minimizes Number of Exchanges**: Selection sort is particularly efficient in 
   scenarios where the cost of exchanges is high. This is because it reduces the number of 
   exchanges to a minimum. Specifically, it performs exactly $n - 1$ exchanges for an 
   array of $n$ elements.
2. **Space Efficiency**: Selection sort operates in-place and requires only a constant 
   amount of additional space (O(1) space complexity), which fits well with the limitation 
   of having extra space sufficient to hold only one crate.

### How It Works?
Here's a step-by-step outline of how selection sort would work in this context:
1. **Find the Minimum**: Iterate through the list of crates to the crate with the earlist 
   Shipping time.
2. **Swap**: Swap this minimum crate with the first crate in the list.
3. **Repeat**: Move to the next position in the list and repeat the process (finding the 
   crate having the earliest shipping date in the remaining unsorted part and swapping it 
   with the current position).

### C Implementation
Each crate has basically one property--Shipping [Date](ex1p15/date.h). For better memory 
management purpose, [helper functions](ex1p15/crate_list.h)
([definition](ex1p15/crate_list.c)) are written separately. The 
[main function](ex1p15/main.c) takes only one argument, the file storing input data. The 
format of input data is the shipping dates represented in order: "month,day,year" 
(one per line). For testing purpose, one set of [test input](ex1p15/test_input.csv) is 
given. Besides **all of the files with ".c" extension in the same directory**, 
[main function](ex1p15/main.c) should be compiled with [elem_sorts.c](elem_sorts.c).

## Exercise 1.21: *Comparable Transactions*.
> Write your implementation of `Transaction`, which should include at least date and 
  amount, and write a method that keeps `Transaction` in order by amount.

### C Implementation
[transaction definition & methods](ex1p21/transaction.h) | [driver](ex1p21/main.c)
| [test input file](ex1p21/test_input.csv)
