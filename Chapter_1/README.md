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
