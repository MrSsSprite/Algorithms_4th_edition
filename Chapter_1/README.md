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

### Exercises

#### Exercise 3.1.
> Add a method `isFull()` to `FixedCapacityStackOfStrings`.

[implementation](ex3p1/fixCapStack.c) | [header](ex3p1/fixCapStack.h)
| [driver](ex3p1/driver.c)

#### Exercise 3.2.
> Give the output printed by java Stack for the input:
> ```terminal
> it was - the best - of times - - - it  was - the - -
> ```
the output should be:
```terminal
was best times of the was the it
```

#### Exercise 3.3.
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

#### Exercise 3.4.
> Write a stack client `Parentheses` that reads in a text stream from standard input and 
  uses a stack to determine whether its parentheses are properly balanced. For example, 
  your program should print true for `[()]{}{[()()]()}` and false for `[(])`.

[implementation](ex3p4/main.c)

#### Exercise 3.5.
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

#### Exercise 3.6.
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

#### Exercise 3.7.
> Add a method `peek()` to Stack that returns the most recently inserted item on the stack 
  (without popping it).

[function implementation](ex3p7/peek.h)

#### Exercise 3.8.
> Give the contents and size of the array for `DoublingStackOfStrings` with the input
> ```terminal
> it was - the best - of times - - - it was - the - -
> ```

With the above input, the `DoublingStackOfStrings` needs to hold 4 elements at peak.
At the end, the `DoublingStackOfStrings` holds merely one `it`.

#### Exercise 3.9.
> Write a program that takes from standard input an expression without left parentheses 
  and prints the equivalent infix expression with the parentheses inserted. For example, 
  given the input:
> ```terminal
> 1 + 2 ) * 3 - 4 ) * 5 - 6 ) ) )
> ```
> your program should print
> ```terminal
> ((1 + 2) * ((3 - 4) * (5 - 6)))
> ```

[program implementation](ex3p9/main.c) | [stack implementation](ex3p9/stack.c)
| [stack interface](ex3p9/stack.h)

#### Exercise 3.10.
> Write a filter `InfixToPostfix` that converts an arithmetic expression from in-fix to 
  postfix.

[program implementation](ex3p10/main.c) | [parser kernel (directory)](expression_parser)

Please note that the implementation do not any incomplete set of parentheses. Instead, it 
follows normal precedence rule (e.g., parentheses first, and `*/` before `+-`)

#### Exercise 3.11.
> Write a program `EvaluatePostfix` that takes a postfix expression from standard input, 
  evaluates it, and prints the value. (Piping the output of your program from the previous 
  exercise to this program gives equivalent behavior to `Evaluate`.

[program implementation](ex3p11/main.c)

#### Exercise 3.12.
> Write an iterable `Stack` client that has a static method `copy()` that takes a stack of 
  strings as argument and returns a copy of the stack. Note: This ability is a prime 
  example of the value of having an iterator, because it allows development of such 
  functionality without changing the basic API.

[stack implementation](ex3p12/stack.c) | [stack header](ex3p12/stack.h)
| [driver](ex3p12/main.c)

**Note**: If you simply use the iterator and `stack_push` to "copy" the stack, the "copied 
to stack" would be in reverse order of the original stack. A simple solution would be to 
implement *enqueue*-like operation specifically for the copy function.

#### Exercise 3.13.
> Suppose that a client performs an intermixed sequence of (queue) `enqueue` and `dequeue` 
  operations. The enqueue operations put the integers 0 through 9 in order onto the queue; 
  the dequeue operations print out the return value. Which of the following sequence(s) 
  could *not* occur?
>> *a.* 0 1 2 3 4 5 6 7 8 9
>>
>> *b.* 4 6 8 7 5 3 2 9 0 1
>>
>> *c.* 2 5 6 7 4 8 9 3 1 0
>>
>> *d.* 4 3 2 1 0 5 6 7 8 9

Only *a.* is possible since *queue* follows FIFO order. The output always follows the 
input order regardless of the order of `enqueue` and `dequeue` operations.

#### Exercise 3.14.
> Develop a class `ResizingArrayQueueOfStrings` that implements the queue abstraction with i
  a fixed-size array, and then extend your implementation to use array resizing to remove 
  the size restriction.

[resizing array queue implementation](ex3p14/arrQueue.c) | [queue header](ex3p14/arrQueue.h)
| [driver function](ex3p14/driver.c)

#### Exercise 3.15.
> Write a `Queue` client that takes a command-line argument `k` and prints the `k`th from 
  the last string found on standard input (assuming that standard input has `k` or more 
  strings).

#### Exercise 3.16.
> Using `readInts()` on page 126 as a model, write a static method `readDates()` for 
  `Date` that reads dates from standard input in the format specified in the table on 
  page 119 and returns an array containing them.

#### Exercise 3.17.
> Do Exercise 1.3.16 for `Transaction`.

#### Exercise 3.18.
> Suppose `x` is a linked-list node and not the last node on the list. What is the effect 
  of the following code fragment?
> ```c
> x.next = x.next.next;
> ```

It makes `x` linked to the `next` node of `next` node of `x`, effectively discarding the 
immediate `next` node of `x`.

#### Exercise 3.19.
> Give a code fragment that removes the last node in a linked list whose first node is 
  `first`.

```c
list_node **p = &first;
while ((*p)->next)
    p = &(*p)->next;
free(*p);
*p = NULL;
```

#### Exercise 3.20.
> Write a method `delete()` that takes an `int` argument `k` and deletes the `k`th element 
  in a linked list, if it exists.

```c
int delete(list *l, int k)
{
    list_node **p = &l->first;
    list_node *node;

    for (int i = 0; i < k; i++)
    {
        if (*p == NULL)
            return 1;
        p = &(*p)->next;
    }

    if (*p == NULL)
        return 1;
    node = *p;
    *p = node->next;
    free(node);

    return 0;
}
```

#### Exercise 3.21.
> Write a method `find()` that takes a linked list and a string `key` as arguments and 
  returns `true` if some node in the list has `key` as its item field, `false` otherwise.

```c
int find(list *l, const char *key)
{
    node *p = l->first;
    while (p != NULL && strcmp(p->str, key))
        p = p->next;

    if (p == NULL)
        return 0;
    else
        return 1;
}
```

#### Exercise 3.22.
> Suppose that `x` is a linked list `Node`.What does the following code fragment do?
> ```c
> t.next = x.next;
> x.next = t;
> ```

The code fragment insert `Node` `t` immediately after `x`.

#### Exercise 3.23.
> Why does the following code fragment not do the same thing as in the previous question?
> ```c
> x.next = t;
> t.next = x.next;
> ```

This code fragment modify the value of `x.next` before assigning `x.next` to `t.next`. 
That means `t.next` would eventually be `t` itself.

#### Exercise 3.24.
> Write a method `removeAfter()` that takes a linked-list `Node` as argument and removes 
  the node following the given one (and does nothing if the argument or the next field in 
  the argument node is null).

```c
int removeAfter(list_node *node)
{
    list_node *temp = node->next;
    if (temp == NULL)
        return 1;
    node->next = temp->next;
    free(temp);
    return 0;
}
```

#### Exercise 3.25.
> Write a method `insertAfter()` that takes two linked-list `Node` arguments and inserts 
  the second after the first on its list (and does nothing if either argument is null).

```c
int insertAfter(list_node *dst, list_node *app)
{
    if (dst == NULL || app == NULL)
        return 1;

    list_node *temp = dst->next;
    dst->next = app;

    if (temp == NULL)
        return 0;
    while (app->next != NULL)
        app = app->next;
    app->next = temp;

    return 0;
```

#### Exercise 3.26.
> Write a method `remove()` that takes a linked list and a string `key` as arguments and 
  removes all of the nodes in the list that have `key` as its item field.

```c
unsigned int remove(list *l, const char *key)
{
    list_node **p = &l->first, *temp;
    unsigned int count = 0;
    while (*p != NULL)
    {
        if (strcmp((*p)->str, key) == 0)
        {
            temp = *p;
            *p = temp->next;
            free(temp);
            count++;
        }
        else
            p = &(*p)->next;
    }

    return count;
}
```

#### Exercise 3.27.
> Write a method `max()` that takes a reference to the first node in a linked list as 
  argument and returns the value of the maximum key in the list. Assume that all keys are 
  positive integers, and return `0` if the list is empty.

```c
unsigned int max(list_node *first)
{
    unsigned int highest = 0;
    while (first != NULL)
    {
        if (first->value > highest)
            highest = first->value;
        first = first->next;
    }

    return highest;
}
```

#### Exercise 3.28.
> Develop a recursive solution to the previous question.

```c
unsigned int max(list_node *first)
{
    if (first == NULL)
        return 0;
    unsigned int highest = max(first->next);
    if (first->value > highest)
        return first->value;
    else
        return highest;
}
```

#### Exercise 3.29.
> Write a `Queue` implementation that uses a *circular* linked list, which is the same as 
  a linked list except that no links are *null* and the value of `last.next` is `first` 
  whenever the list is not empty. Keep only one `Node` instance variable (`last`).

[circular linked list queue implementation](ex3p29/cirll_queue.c) | [queue header](ex3p29/cirll_queue.h)
| [driver function](ex3p29/driver.c)

#### Exercise 3.30.
> Write a function that takes the first `Node` in a linked list as argument and 
  (destructively) reverses the list, returning the first `Node` in the result.

[implementation & driver](ex3p30/main.c)

#### Exercise 3.31.
> Implement a nested class `DoubleNode` for building doubly-linked lists, where each node 
  contains a reference to the item preceding it and the item following it in the list 
  (`null` if there is no such item). Then implement static methods for the following 
  tasks: insert at the beginning, insert at the end, remove from the beginning, remove 
  from the end, insert before a given node, insert after a given node, and remove a given 
  node.

[doubly-linked list implentation](ex3p31/doublyll.c)
| [doubly-linked list interface](ex3p31/doublyll.h)
| [driver](ex3p31/driver.c)

### Creative Problems

#### Exercise 3.32: *Steque*.
> A *stack*-ended *queue* or ***steque*** is a data type that supports *push*, *pop*, and 
  *enqueue*. Articulate an API for this ADT. Develop a *link-list*-based implementation.

[Steque Interface](ex3p32/steque.h) | [Steque Implementation](ex3p32/steque.c)
| [driver](ex3p32/driver.c)

#### Exercise 3.33: *Deque*.
> A double-ended *queue* or *deque* (pronounced "deck") is like a stack or a queue but 
  supports adding and removing items at both ends. A deque stores a collection of items 
  and supports the following API:
> | return | name      | description |
> | ------ | --------- | ----------- |
> |   N/A  | Deque     | Create an Deque Object |
> |  bool  | isEmpty   | check if the deque is empty |
> |   int  | size      | the number of items in the deque |
> |  void  | pushLeft  | add an item to the left end |
> |  void  | pushRight | add an item to the right end |
> |  item  | popLeft   | remove an item from the left end |
> |  item  | popRight  | remove an item from the right end |
>
> Write a class **Deque** that uses doubly-linked list to implement this API and a class 
  **ResizingArrayDeque** that uses a resizing array.

The doubly-linked list implementation of [exercise 3.31](#exercise-331) includes 
basically all of the APIs above.

## 1.4. Analysis of Algorithms

### Exercises

#### Exercise 4.1.
> Show that the number of different triples that can be chosen from $N$ items is precisely 
  $N (N - 1)(N - 2)/6$. Hint : Use mathematical induction.

To prove that the number of different triples that can be chosen from $N$ items is 
precisely $\frac {N (N - 1)(N - 2)}{6}$, we can employ a mathematical induction.

***Base Case:***

For $N = 3$, the smallest case where a triple can be formed, there is exactly *one* triple 
that can be chosen. The formula yields:
$$\frac{3 (3 - 1) (3 - 2)}{6} = \frac{3\cdot 2\cdot 1}{6} = 1$$
This aligns with the actual number, thus confirming that the equation stands for the base 
case.

***Inductive Step:***

Assume that for some $k \geq 3$, the formula holds true, i.e., the number of different 
triples that can be chosen from $k$ items is $\frac {k (k - 1)(k - 2)}{6}$.

If we can prove that, based on the above assumption, the formula also holds for $k + 1$, 
which means the number of different triples that can be chosen from $k + 1$ items is 
$\frac {(k + 1) k (k - 1)}{6}$, we can prove that the formula holds for any integer 
greater than or equal to $3$ inductively from the base case.

When we add an ${(k + 1)}^{th}$ to the set of $k$ items, this item can form a triple with 
any *pair* from the original $k$ items. There are $\binom{k}{2}$ such pairs, which 
translates to
$$ \binom{k}{2} = \frac{k (k - 1)}{2} $$

Now, by adding this to our assumed number of triple for $k$, we get the total number of 
triples for a set of $k + 1$ items:
$$ \frac{k (k - 1)(k - 2)}{6} + \frac{k (k - 1)}{2} $$

Then, add these two fractions by finding a common denominator:
$$ \frac{k(k-1)(k-2) + 3k(k-1)}{6} $$

Distribute $k (k - 1)$ in the numerator:
$$ \frac{k (k - 1) (k - 2 + 3)}{6} $$

We get the exact formula that we want to prove:
$$ \frac{k(k - 1) (k + 1)}{6} \equiv \frac {(k + 1) k (k - 1)}{6} $$

Therefore, by the principle of mathematical induction, the formula holds true for all 
$N \geq 3$.

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
The General Interface for Union Find: [union_find.h](union_find/union_find.h)

The [Driver file](union_find/driver.c) should be compiled with either **ONE** of the 
implementations below (IMPORTANT: one but ONLY ONE, neither more nor less)

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

#### Weighted Quick-Union
There is a simple improvement that can be applied to effectively avoid bad cases. In the 
previous implementation, the algorithm always attach root of `p`, the first argument, to 
that of `q`, the second argument. By using if statement to guarantee that it is *always* 
the **smaller tree to be attached to the larger tree**, the algorithm can better contain 
the growth rate of the depth of the "tree"s.

This change requires the algorithm to keep track of the size of every tree. Accordingly, 
we introduce another array used to store the amount of element "below" that site. This 
method is named Weighted Quick-Union.

[Weighted Quick Union Implementation](union_find/weighted_quick_union.c)

#### Path Compression
There is still one more simple optimization that can be applied to further optimize 
Weighted Quick-Union: **Path Compression**.

The implementation of path compression is plain, add one more loop in `find` so that 
every site in the path (but not every site in the array) is linked directly to the root 
of the component (or "tree"). This action effectively flatten the "tree"s.

[Implementation](union_find/weighted_quick_union_with_pc.c)

