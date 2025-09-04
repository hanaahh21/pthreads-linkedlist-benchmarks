import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# Create 'plots' directory if it doesn't exist
os.makedirs('plots', exist_ok=True)

# Number of threads for concurrent tests
threads = [1, 2, 4, 8]

def read_and_average(csv_file, case_num):
    """
    Read a CSV and compute the average and standard deviation of execution times
    for Serial, Mutex, and RW Lock.

    Args:
        csv_file (str): Path to CSV file
        case_num (int): Case number for display purposes

    Returns:
        serial_avg, serial_std (float)
        mut_avg, mut_std (list of float)
        rw_avg, rw_std (list of float)
    """
    df = pd.read_csv(csv_file)
    df.columns = [c.strip() for c in df.columns]  # Remove leading/trailing spaces

    # Serial
    serial_avg = df['Serial'].mean()
    serial_std = df['Serial'].std()

    # Mutex
    mut_avg = [df[f'mut_t{t}'].mean() for t in threads]
    mut_std = [df[f'mut_t{t}'].std() for t in threads]

    # RW Lock
    rw_avg  = [df[f'rw_t{t}'].mean() for t in threads]
    rw_std  = [df[f'rw_t{t}'].std() for t in threads]

    # Print results
    print(f"\nCase {case_num} execution time statistics:")
    print(f"Serial      -> Avg: {serial_avg:.2f} μs, Std: {serial_std:.2f} μs")
    print(f"Mutex       -> Avg: {mut_avg}, Std: {mut_std}")
    print(f"RW Lock     -> Avg: {rw_avg}, Std: {rw_std}")

    return (serial_avg, serial_std, mut_avg, mut_std, rw_avg, rw_std)

def plot_line(serial_avg, mut_avg, rw_avg, case_num):
    """
    Plot a line graph showing execution time vs number of threads.
    """
    plt.figure(figsize=(8,6))
    plt.axhline(y=serial_avg, color='black', linestyle='--', label=f'Serial ({serial_avg:.0f} μs)')
    plt.plot(threads, mut_avg, marker='o', label='Mutex')
    plt.plot(threads, rw_avg, marker='s', label='RW Lock')
    
    plt.title(f'Case {case_num}: Avg Execution Time vs Threads')
    plt.xlabel('Number of Threads')
    plt.ylabel('Execution Time (μs)')
    plt.xticks(threads)
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f'plots/Case_{case_num}_lineplot.png')
    plt.close()

def plot_bar(serial_avg, mut_avg, rw_avg, case_num):
    """
    Plot a collective bar graph comparing Serial, Mutex, and RW Lock.
    """
    x = np.arange(len(threads))
    width = 0.25

    plt.figure(figsize=(10,6))
    plt.bar(x - width, mut_avg, width, label='Mutex')
    plt.bar(x, rw_avg, width, label='RW Lock')
    plt.bar(x + width, [serial_avg]*len(threads), width, label='Serial')
    
    plt.xlabel('Number of Threads')
    plt.ylabel('Execution Time (μs)')
    plt.title(f'Case {case_num}: Execution Time Comparison')
    plt.xticks(x, threads)
    plt.grid(axis='y', linestyle='--', alpha=0.7)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f'plots/Case_{case_num}_barplot.png')
    plt.close()

# CSV files corresponding to each case
csv_files = ['output/Case_1.csv', 'output/Case_2.csv', 'output/Case_3.csv']

# Generate all plots
for case_num, csv_file in enumerate(csv_files, start=1):
    serial_avg, serial_std, mut_avg, mut_std, rw_avg, rw_std = read_and_average(csv_file, case_num)
    plot_line(serial_avg, mut_avg, rw_avg, case_num)
    plot_bar(serial_avg, mut_avg, rw_avg, case_num)

print("All plots saved in the 'plots' directory.")
