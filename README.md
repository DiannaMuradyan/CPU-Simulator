# CPU-Simulator

Description
The CPU Simulator is a terminal-based tool that simulates a simple CPU, capable of executing an extended subset of assembly-like instructions. This project helps to visualize the CPU's inner workings, including the operation of the Arithmetic Logic Unit (ALU), registers, memory, and control unit (CU). The tool supports various CPU operations, such as arithmetic, data movement, memory management, and execution control, and allows users to input custom assembly instructions to observe the changes to the CPU state.

Features
1. CPU Components:
Registers: 7 general-purpose registers (R0 to R6) and a Working Status Register (WSR).
Memory (RAM): Simulated RAM with 256 locations.
Instruction Pointer (IP): Tracks the execution progress of instructions.
ALU: Performs arithmetic operations like ADD, SUB, and MOV.
2. Supported Instructions:
ADD: Adds two registers or a register and a constant value.
SUB: Subtracts one register from another or subtracts a constant from a register.
MOV: Moves data between registers or loads a constant into a register.
LOAD: Loads data from memory into a register.
STORE: Stores data from a register into memory.
START: Initializes the CPU and sets WSR to 1.
EXIT: Terminates the simulation by setting WSR to 0.
DISC: Discards the last N instructions and reverts the CPU to the previous state.
LAYO: Displays the current state of all registers, memory, and the instruction pointer.
3. Instruction Cycles:
Fetch: Fetches the instruction from the input.
Decode: Decodes the instruction and determines the operation.
Execute: Executes the instruction and updates the CPU state.
4. State Logging:
After each instruction, the CPU state (register values and memory contents) is logged to a file for tracking and debugging purposes.

Example Assembly Program

START
MOV R0, 90        // Load 90 into register R0
MOV R1, 10        // Load 10 into register R1
ADD R0, R1        // Add the values of R0 and R1, storing the result in R0 (90 + 10 = 100)
SUB R0, 10        // Subtract 10 from R0, storing the result in R0 (100 - 10 = 90)
LOAD R2, 10       // Load the value at memory location 10 into R2
STORE R0, 10      // Store the value of R0 into memory location 10
LAYO              // Display register and memory contents
EXIT              // Reset CPU and memory, end simulation
