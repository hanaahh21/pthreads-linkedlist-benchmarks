# pthreads-linkedlist-benchmarks

This project implements a linked list in three different ways:  

1. **Serial implementation**  
2. **Parallel implementation using a single mutex** for the entire list  
3. **Parallel implementation using a read-write lock**  

The program supports the following operations on the linked list:  
- `Member`  
- `Insert`  
- `Delete`  

It benchmarks the performance of these implementations under different workloads and thread counts.  

---

## Getting Started

### 1. Compile the Program

Use `gcc` to compile all source files:

```bash
gcc -g -o prog main.c serial.c mutex.c rw_lock.c linked_list.c -pthread
```
### 2. Run the Benchmark

Execute the compiled program:

```bash
./prog
```

This will generate CSV files in the output directory for different test cases:

- `Case_1.csv`
- `Case_2.csv`
- `Case_3.csv`

### 3. Install Python Dependencies

To visualize the benchmark results, install the required Python packages:

```bash
pip install matplotlib pandas numpy
```

### 4. Generate Plots

Run the plotting script to generate line and bar plots for each test case:
```bash
python plot.py
```
This wil also give the average execution time and standard deviation for each type of linked list implementation per run

The plots will be saved in a plots directory:

- Line plots: `Case_1_lineplot.png`, `Case_2_lineplot.png`, `Case_3_lineplot.png`

- Bar plots: `Case_1_barplot.png`, `Case_2_barplot.png`, `Case_3_barplot.png`
