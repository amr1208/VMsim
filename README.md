This repository contains a C-based mini-project focused on simulating the organization of virtual memory in a running process. The project is structured into four key steps, each implemented in separate C files:

### Features:
1. **Doubly Linked List Representation**: 
   - Simulates the virtual address space, using a dynamic doubly linked list.
   - Stores odd integers in one stack (growing from the head) and even integers in another stack (growing from the tail).
   - Free space is dynamically allocated between the two stacks, simulating the heap and stack memory separation.

2. **Memory Management**:
   - Allocates and frees memory dynamically using custom allocator and deallocator functions.
   - Ensures memory leaks are tracked and reported with Valgrind compatibility.

3. **Push and Pull Operations**:
   - Implements operations to push digits (odd or even) onto the respective stacks and pull them off while managing the dynamic allocation of free memory nodes.

4. **User Interaction**:
   - Provides a command-line interface for users to input sequences of digits, managing them between the two stacks.
   - Pushes and pulls operations are user-controlled with a limit to avoid overflow.

### Files:
- `step1.c`: Initializes the list structure and basic memory allocation functions.
- `step2.c`: Implements memory block allocation to manage free space.
- `step3.c`: Adds functionality for pushing and pulling integers to and from the list.
- `step4.c`: Handles user input and interaction, including parsing and managing stack operations based on input.

### Compilation:
- The code is designed to be compiled with `gcc -Wall -Werror -Wpedantic` and runs on a Linux environment.
- Includes a Valgrind test to ensure memory is properly managed without leaks.

### Usage:
- Compile the individual steps and run them sequentially to simulate virtual memory management.
- User input allows pushing and pulling integers between the two stacks, with results dynamically updated in real-time.
