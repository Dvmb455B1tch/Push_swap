# Push_Swap

## Overview
Push_swap is a sorting algorithm project that sorts data on a stack using a limited set of instructions. The goal is to sort the stack with the minimum number of operations.

## Compilation
To compile the program, simply run:
```bash
make
```
This will generate the `push_swap` executable.

## Usage
```bash
./push_swap [integers]
```

Example:
```bash
./push_swap 3 1 2 5 4
```

The program will display the sequence of operations needed to sort the stack:
```
pb
ra
pb
sa
pa
pa
```

## Instructions
The push_swap program uses the following operations:

- `sa`: Swap the first two elements at the top of stack A.
- `sb`: Swap the first two elements at the top of stack B.
- `ss`: `sa` and `sb` at the same time.
- `pa`: Take the first element at the top of stack B and put it at the top of stack A.
- `pb`: Take the first element at the top of stack A and put it at the top of stack B.
- `ra`: Rotate stack A - shift up all elements by 1. The first element becomes the last one.
- `rb`: Rotate stack B - shift up all elements by 1. The first element becomes the last one.
- `rr`: `ra` and `rb` at the same time.
- `rra`: Reverse rotate stack A - shift down all elements by 1. The last element becomes the first.
- `rrb`: Reverse rotate stack B - shift down all elements by 1. The last element becomes the first.
- `rrr`: `rra` and `rrb` at the same time.

## Implementation Details
The implementation follows these key principles:

1. **Input Validation**: Checks that all inputs are valid integers with no duplicates.
2. **Algorithm Selection**: Different algorithms are used based on stack size:
   - For 2-3 elements: Direct pattern-based sorting
   - For 4-5 elements: Basic insertion sort strategy
   - For larger stacks: Radix sort implementation

3. **Performance**: The algorithm is optimized to minimize the number of operations:
   - 3 numbers: Maximum 2-3 operations
   - 5 numbers: Maximum ~12 operations
   - 100 numbers: ~700 operations
   - 500 numbers: ~5500 operations

## Error Handling
The program displays "Error" in the following cases:
- Non-integer arguments
- Integers out of range (not fitting in an int)
- Duplicate integers

## Algorithmic Approach
For large stacks, the program implements a radix sort algorithm working with a binary representation of the numbers. This approach is particularly efficient as it has a complexity of O(n log n), where n is the number of elements to sort.
