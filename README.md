# Round Robin Scheduling Algorithm Simulation

## Summary

This project provides a simulation of a Round Robin scheduling algorithm using a time quantum of 10ms. The simulation reads a list of processes from the `job.txt` file, where each line represents one process with three comma-separated values: the job name, the time of the request, and the duration of the job.

The purpose of this program is to simulate the Round Robin scheduling algorithm, focusing on its functionality rather than serving as a full implementation for an operating system. The program handles the jobs in a similar manner to a Round Robin scheduler.

## How it Works

The program follows these steps to simulate the Round Robin scheduling algorithm:

1. Load all jobs into a master jobs list.
2. Initialize two variables: `current_time` and `time_allocated`.
3. Enter a while loop that iterates through the list of jobs.
   - If a job's scheduling time matches the current time, add it to the Round Robin queue.
   - Decrement the time left for the first process in the Round Robin queue.
   - If the first process in the queue completes, move it to the completed list and remove it from the queue.
   - If the first process in the queue has been allocated 10ms and is still incomplete, move it to the back of the queue.
   - If the number of completed processes equals the total number of jobs, terminate the while loop.
   - Otherwise, increment the current time by 1ms and repeat the process.
4. Once the while loop ends, the program concludes.

## Required Input

The program expects access to the `job.txt` file, which should be located in the same directory as the program's executable.

## Expected Output

The program's output will remain consistent for the same input jobs, as the Round Robin scheduling algorithm is deterministic. The output displays events chronologically, indicating the time each job was scheduled and its duration. It does not show the scheduling of all jobs in a batch and then the order in which they finish in a separate batch.

## How to Run

To run the simulation, follow these steps:

1. Clone the repository or download the project files.
2. Ensure that the `job.txt` file is present in the project directory.
3. Compile and build the source code using the appropriate compiler for your system.
4. Execute the compiled program.
5. The program will output the chronological order of events, indicating the time each job was scheduled and its duration.
