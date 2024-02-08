# Chapter 1. Fundamentals

## 1.3. Bags, Queues, and Stacks

### Algorithm 1.1: Pushdown (LIFO) stack (resizing array implementation)
[implementation](algo_1p1/stack.c) | [header](algo_1p1/stack.h)
| [driver0](algo_1p1/driver.c) | [driver1](algo_1p1/drive1.c)

### Algorithm 1.2: Pushdown stack (linked-list implementation)
[implementation](algo_1p2/stack.c) | [header](algo_1p2/stack.h)
| [driver](algo_1p2/driver.c)

### Algorithm 1.3: FIFO queue
[implementation](algo_1p3/queue.c) | [header](algo_1p3/queue.h)
| [driver](algo_1p3/driver.c)

### Algorithm 1.4: Bag
> Please note that the both drivers below needs to be compiled with the 
  [implementation of Algorithm 1.2](algo_1p2/stack.c). And they also requires 
  another file in [the directory for algorithm 1.2](algo_1p2), which is named 
  [_stack_node.h](algo_1p2/_stack_node.h) that defines the `Bag_iter` structure.
[implementation](algo_1p4/bag.c) | [header](algo_1p4/bag.h)
| [driver0](algo_1p4/driver.c) | [driver1](algo_1p4/driver1.h)

### Exercise 3.1.
> Add a method `isFull()` to `FixedCapacityStackOfStrings`.

[implementation](ex3p1/fixCapStack.c) | [header](ex3p1/fixCapStack.h)
| [driver](ex3p1/driver.c)

### Exercise 3.2.
> Give the output printed by java Stack for the input:
> ```terminal
> it was - the best - of times - - - it  was - the - -
> ```
the output should be:
```terminal
was best times of the was the it
```

### Exercise 3.3.
> Suppose that a client performs an intermixed sequence of (stack) push and pop 
  operations. The push operations put the integers 0 through 9 in order onto the stack; 
  the pop operations print out the return values. Which of the following sequence(s) could 
  not occur?
>> a. `4 3 2 1 0 9 8 7 6 5`
>>
>> b. `4 6 8 7 5 3 2 9 0 1`
>>
>> c. `2 5 6 7 4 8 9 3 1 0`
>>
>> d. `4 3 2 1 0 5 6 7 8 9`
>>
>> e. `1 2 3 4 5 6 9 8 7 0`
>>
>> f. `0 4 6 5 3 8 1 7 2 9`
>>
>> g. `1 4 7 9 8 6 5 3 0 2`
>>
>> h. `2 1 4 3 6 5 8 7 9 0`

- a. Input: `0 1 2 3 4 - - - - - 5 6 7 8 9 - - - - -`
- b. Impossible
- c. Input: `0 1 2 - 3 4 5 - 6 - 7 - - 8 - 9 - - - -`
- d. Input: `0 1 2 3 4 - - - - - 5 - 6 - 7 - 8 - 9 -`
- e. Input: `0 1 - 2 - 3 - 4 - 5 - 6 - 7 8 9 - - - -`
- f. Impossible
- g. Impossible
- h. Input: `0 1 2 - - 3 4 - - 5 6 - - 7 8 - - 9 - -`

### Exercise 3.4.
> Write a stack client `Parentheses` that reads in a text stream from standard input and 
  uses a stack to determine whether its parentheses are properly balanced. For example, 
  your program should print true for `[()]{}{[()()]()}` and false for `[(])`.

[implementation](ex3p4/main.c)

### Exercise 3.5.
> What does the following code fragment print when `N` is 50? Give a high-level 
  description of what it does when presented with a positive integer `N`.
> ```java
> Stack<Integer> stack = new Stack<Integer>();
> while (N > 0)
> {
>     stack.push(N % 2);
>     N = N / 2;
> }
> for (int d : stack) StdOut.print(d);
> StdOut.println();
> ```

In short, it prints base 2 representation of the value 50.
In each iteration, the variable `N` is divided by `2` and the remainder is pushed to the 
stack. After the loop, the content (binary values, representing the remainders pushed) is 
printed in reverse order.

### Exercise 3.6.
> What does the following code fragment do to the queue `q`?
```java
Stack<String> stack = new Stack<String>();
while (!q.isEmpty())
    stack.push(q.dequeue());
while (!stack.isEmpty())
    q.enqueue(stack.pop());
```

At the end of the code fragment, `q` holds the same set of data, while having the order 
reversed.

### Exercise 3.7.
> Add a method `peek()` to Stack that returns the most recently inserted item on the stack 
  (without popping it).

[function implementation](ex3p7/peek.h)

### Exercise 3.8.
> Give the contents and size of the array for `DoublingStackOfStrings` with the input
> ```terminal
> it was - the best - of times - - - it was - the - -
> ```

With the above input, the `DoublingStackOfStrings` needs to hold 4 elements at peak.
At the end, the `DoublingStackOfStrings` holds merely one `it`.

### Exercise 3.9.
> Write a program that takes from standard input an expression without left parentheses 
  and prints the equivalent infix expression with the parentheses inserted. For example, 
  given the input:
> ```terminal
> 1 + 2 ) * 3 - 4 ) * 5- 6 ) ) )
> ```
> your program should print
> ```terminal
> ((1 + 2) * ((3 - 4) * (5 - 6)))
> ```

## 1.5. Case Study: Union Find
### Problem Statement: Dyamic Connectivity
Given a set of connection commands, which build equivalence relations that are:
- Reflexive: `p` is connected to `p`.
- Symmetric: If `p` is connected to `q`, then `q` is connected to `p`.
- Transitive: If `p` is connected to `q` and `q` is connected to `r`, then `p` is 
  connected to `r`.

Union Find (`UF`) programs are develop to recognize if two given points (or sites) 
are connected.

### Implementations
The General Interface for Union Find

[union_find.h](union_find/union_find.h)

#### Quick-Find
One of the most intuitive implementation would be to construct an array so that every 
site can be related to an index and then ensure that all the sites in a component (a set 
of sites connected together) holds the same index. This approach is called Quick-Find 
since the `find` function always take constant time.

[Quick Find Implementation](union_find/quick_find.c)
| [base structure for both quick-find and quick-union](union_find/base_structure.h)

***Analysis***: The `find` operation takes merely constant time, while the time complexity
of each `union` operation is proportional to data size (i.e., *O(n)*). Therefore, the 
quick find implementation is not considered practical.

#### Quick-Union
The next method is Quick Union, which is like a reciprocal to Quick-Find. This method, 
on the contrary, prioritizes the speed of `union` operation. This method uses the same 
data structure as Quick-Find; the interpretation of the `id` array is, however, 
different. The `id` array in Quick-Union is used to represent the "parent" of this site 
(instead of "root" as in Quick-Find). This fact indicates that the find process is not 
guaranteed to be constant time, but determined by the input and may take time 
proportional to data size in the worst case.

[Quick Union Implementation](union_find/quick_union.c)
| [base structure for both quick-find and quick-union](union_find/base_structure.h)

***Analysis***: On average, the quick-union algorithm should be faster than the quick-find 
algorithm, as it takes constant time to connect two components (not considering the time 
spent for `find`ing). The time spent for `find`ing depends on the depth of the "Tree"s, 
which is affected by the input content and order. Thus, it may, in the worst case, take 
time linear to data size to `find` and `union` (because union calls `find`).
