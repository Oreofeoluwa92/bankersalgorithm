Ademuyiwa Adebunmi

Overview
This program implements the Banker's Algorithm, a resource allocation and deadlock avoidance algorithm, in C++.
It reads process and resource data from an input file, handles dynamic resource requests, checks for safe states, 
and updates the system state accordingly.

Features:
Reads input data (processes, resource types, and resource matrices) from a file.
Displays the MAX, ALLOCATION, NEED, and AVAILABLE matrices/vectors.
Allows users to make resource requests for specific processes.
Checks if the system remains in a safe state after each request.
Rolls back requests if they lead to an unsafe state.

Compiler:It can be comply on any C++ supported Environment.

Input Commands:
Enter the process number (0 to N-1) to request resources for that process.
Provide the requested resource vector.
Enter -1 to exit the program.

Initialization:
Reads and initializes the MAX, AVAILABLE, and NEED matrices from the input file.
Displays the initial state of the system.

Resource Request:
The user selects a process and inputs a request vector.
The program checks if the request is valid:
Does not exceed the process's maximum need.
Does not exceed available resources.
If valid, the request is tentatively allocated, and the system checks for safety.

Safety Check:
The program simulates allocation and verifies if all processes can complete with the current resources.
If the system remains in a safe state, the allocation is finalized. Otherwise, it is rolled back.
