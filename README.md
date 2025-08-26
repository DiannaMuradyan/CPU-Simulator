# ⚙️ CPU Simulator

The **CPU Simulator** is a terminal-based tool that simulates a simple CPU capable of executing an extended subset of assembly-like instructions.  

It provides a way to visualize the **inner workings of a CPU**, including the **Arithmetic Logic Unit (ALU)**, **registers**, **memory**, and **control unit (CU)**.  

This project is designed for learning and debugging purposes, allowing users to input custom assembly instructions and observe how the CPU state changes after each instruction.

---

## 🚀 Features

### 🖥️ CPU Components
- **Registers**:  
  - 7 general-purpose registers (`R0` → `R6`)  
  - 1 Working Status Register (`WSR`)  
- **Memory (RAM)**:  
  - 256 memory locations (0–255).  
- **Instruction Pointer (IP)**:  
  - Tracks execution progress of instructions.  
- **ALU**:  
  - Performs arithmetic operations (`ADD`, `SUB`, etc.).  

---

### 📜 Supported Instructions

- **ADD** → Adds two registers or a register and a constant.  
- **SUB** → Subtracts one register from another or subtracts a constant.  
- **MOV** → Moves data between registers or loads a constant into a register.  
- **LOAD** → Loads data from memory into a register.  
- **STORE** → Stores data from a register into memory.  
- **START** → Initializes the CPU and sets `WSR = 1`.  
- **EXIT** → Terminates the simulation by setting `WSR = 0`.  
- **DISC** → Discards the last `N` instructions and reverts the CPU to the previous state.  
- **LAYO** → Displays the current state of registers, memory, and the instruction pointer.  

---

### 🔄 Instruction Cycle
The simulator follows the classic **Fetch–Decode–Execute** cycle:
1. **Fetch** → Retrieve instruction from program input.  
2. **Decode** → Interpret instruction type and operands.  
3. **Execute** → Perform operation and update CPU state.  

---

### 📝 State Logging
- After **every instruction**, the CPU state is logged to a file.  
- Log includes:
  - Register values  
  - Memory snapshot  
  - Instruction pointer  

This makes debugging and analysis easy.  

---

## 📊 Example Assembly Program

```asm
START

MOV R0, 90       // Load 90 into register R0
MOV R1, 10       // Load 10 into register R1
ADD R0, R1       // R0 = R0 + R1  (90 + 10 = 100)
SUB R0, 10       // R0 = R0 - 10  (100 - 10 = 90)

LOAD R2, 10      // Load memory[10] into R2
STORE R0, 10     // Store R0 into memory[10]

LAYO             // Display CPU state

EXIT             // Reset CPU and stop simulation
```

---

```
🏗️ Compilation & Running
gcc -o cpu_simulator cpu_simulator.c
./cpu_simulator
```
