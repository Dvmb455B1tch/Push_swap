# Push_Swap Project Compilation Guide

## Initial Setup

1. Clone your repository or set up your project folder with all source files:
   ```
   main.c
   stack_operations.c
   stack_utils.c
   operations_swap.c
   operations_push.c
   operations_rotate.c
   operations_reverse_rotate.c
   parse_arguments.c
   utils.c
   sort_three.c
   sort_small.c
   sort_large.c
   sort.c
   push_swap.h
   Makefile
   ```

2. Ensure your Makefile is properly configured (as shown in this repository).

## Compilation

### Standard Compilation

Simply run make in your project directory:
```bash
make
```

This will:
1. Compile all source files into object files
2. Link them together to create the `push_swap` executable

### Clean and Rebuild

To clean the project and remove all object files:
```bash
make clean
```

To completely clean the project and remove the executable:
```bash
make fclean
```

To rebuild the entire project from scratch:
```bash
make re
```

## Testing

### Basic Testing

Test with a small set of numbers:
```bash
./push_swap 3 1 5 2 4
```

### Test Random Numbers

You can create a script to generate random numbers for testing:
```bash
ARG=$(seq -10 10 | sort -R | head -n 5 | tr '\n' ' '); echo $ARG; ./push_swap $ARG | wc -l
```

This will:
1. Generate 5 random numbers between -10 and 10
2. Display the numbers
3. Run push_swap with these numbers
4. Count the number of operations

### Efficiency Testing

For testing with larger sets:
```bash
# Generate 100 random numbers
ARG=$(seq -1000 1000 | sort -R | head -n 100 | tr '\n' ' '); ./push_swap $ARG | wc -l

# Generate 500 random numbers
ARG=$(seq -2500 2500 | sort -R | head -n 500 | tr '\n' ' '); ./push_swap $ARG | wc -l
```

### Validating Correctness

You can validate that your sorting is correct using a checker program:
```bash
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker_OS $ARG
```

Note: You'll need to download the checker program appropriate for your operating system.

## Common Issues and Solutions

1. **Compilation Errors**:
   - Ensure all function prototypes are correctly defined in push_swap.h
   - Check for missing includes in your source files
   - Verify parameter types match between declarations and definitions

2. **Memory Leaks**:
   - Remember to free all allocated memory before program exit
   - Use valgrind to check for memory leaks: `valgrind --leak-check=full ./push_swap 3 1 5 2 4`

3. **Algorithm Efficiency**:
   - If your operation count is too high, review your sorting algorithm
   - Different strategies are needed for different stack sizes
   - The radix sort implementation is particularly efficient for large stacks

4. **Input Validation Issues**:
   - Make sure your program handles all edge cases (duplicates, non-integers, etc.)
   - Test with negative numbers, very large numbers, and empty input

## Performance Benchmarks

For reference, here are typical operation counts for efficient implementations:
- 3 numbers: ≤ 3 operations
- 5 numbers: ≤ 12 operations
- 100 numbers: ≤ 700 operations
- 500 numbers: ≤ 5500 operations

Good luck with your Push_Swap project!
