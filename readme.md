# Process Scheduling

A C++ desktop application built with QtCreator to schedule processes using 3 different algorithms
FIFO, SJF, Round Robin

### 1) FIFO (First In First Out)

![FIFO Screenshot](https://imgur.com/IVVSjOC)
It is an algorithm without requisition. The execution of the processes is done in their chronological order of arrival

### 2) SJF (Shortest Job First)

![SJF Screenshot](https://imgur.com/5E1C667)
The scheduler chooses the ready process having the smaller run time. Once a process is elected, it is never suspended until the end of his execution.

### 3) Round Robin

![Round Robin Screenshot](https://imgur.com/1iU9miY)
Each process is assigned a fixed time slot in a cyclic way. It's a starvation-free as all processes get fair share of CPU time.