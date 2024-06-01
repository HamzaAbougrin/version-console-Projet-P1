
# CPU Scheduling Simulation

This project simulates CPU scheduling algorithms including First-Come, First-Served (FCFS), Shortest Job First (SJF), and Round Robin (RR). It reads a list of processes from a file, applies the selected scheduling algorithm, and prints a Gantt chart illustrating the scheduling.

## Features

- Supports three scheduling algorithms: FCFS, SJF, and RR.
- Reads process data from a file.
- Displays the scheduling results in a Gantt chart with different colors for each process.

## Requirements

- g++ compiler
- A POSIX-compliant environment (Linux, macOS, etc.)

## Installation

1. Clone this repository to your local machine:

    ```bash
    git clone https://your-repository-url.git
    cd your-project-directory
    ```

2. Build the project using the provided `Makefile`:

    ```bash
    make
    ```

## Usage

1. Prepare an input file containing process information. Each line in the file should have three integers: process ID, arrival time, and burst time. For example:

    ```
    1 0 5
    2 1 3
    3 2 8
    4 3 6
    ```

2. Run the program:

    ```bash
    ./scheduler
    ```

3. Enter the file path when prompted:

    ```
    Insert the address of your file: path/to/your/input_file.txt
    ```

4. Select the scheduling algorithm by entering the corresponding number:

    ```
    ==================== CPU Scheduling Algorithms ====================
    1. First-Come, First-Served (FCFS)
    2. Shortest Job First (SJF)
    3. Round Robin (RR)
    Enter your choice (1-3): 
    ```

5. For Round Robin scheduling, you will be prompted to enter the quantum time:

    ```
    Enter quantum time: 
    ```

6. The program will display the Gantt chart for the selected scheduling algorithm.

## Example

Given the following input file:

```
1 0 5
2 1 3
3 2 8
4 3 6
```

If you choose the FCFS algorithm, the output Gantt chart will show the scheduling of the processes as per the FCFS rules.

## Cleaning Up

To remove the compiled executable, run:

```bash
make clean
```
