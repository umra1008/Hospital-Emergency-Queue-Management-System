# Hospital-Emergency-Queue-Management-System
# Hospital-Emergency-Queue-Management-System
Hospital Emergency Queue Management System

Project Overview

The Hospital Emergency Queue Management System is a Data Structures and Algorithms (DSA) project developed using the C programming language. It manages patients waiting in a hospital emergency department by arranging them according to their emergency priority.

The system uses a priority-based queue to ensure that patients with higher urgency are placed ahead of patients with lower urgency. Patients with the same priority are served in their arrival order.

Objectives

- To manage patient registration efficiently.
- To arrange patients according to emergency priority.
- To display the list of waiting patients.
- To search for a patient using a unique patient ID.
- To serve the next patient according to queue priority.
- To demonstrate the practical application of data structures in healthcare.

Technologies Used
- Programming Language: C
- Data Structure: Priority Queue
- Concepts: Structures, Arrays, Functions, Searching and Queue Operations
- Compiler: GCC or any compatible C compiler

Key Features

1. Patient Registration
2. Emergency Priority Assignment
3. Display Waiting Patients
4. Serve Next Patient
5. Search Patient by ID
6. Queue Statistics
7. Menu-Driven Interface

Priority Classification

- Priority 1: Critical
- Priority 2: Serious
- Priority 3: Normal

A lower priority number indicates a higher level of urgency in this educational implementation.

How to Run the Project

Step 1: Compile the Program

gcc main.c -o hospital_queue

Step 2: Run the Program

On Windows:

hospital_queue.exe

On Linux:

./hospital_queue

Learning Outcomes

- Understanding priority-based queue management.
- Applying structures and arrays in C.
- Using functions to organize a program.
- Understanding searching and queue operations.
- Applying DSA concepts to a real-world-inspired problem.

Future Improvements

- Store patient records permanently using file handling.
- Add date and time of registration.
- Develop a graphical user interface.
- Add a database for patient records.

Disclaimer

This project is developed for academic and educational purposes only. It does not replace professional medical triage or clinical decision-making.
Algorithm

1. Start the program.
2. Display the main menu.
3. Ask the user to select an operation.
4. If Register Patient is selected, enter patient details and assign a priority.
5. Insert the patient into the queue according to priority.
6. If Display Patients is selected, show all waiting patients.
7. If Serve Next Patient is selected, remove and display the highest-priority patient.
8. If Search Patient is selected, find the patient using their ID.
9. If Queue Statistics is selected, display the number of patients in each priority category.
10. Repeat the menu until the user selects Exit.
11. Stop the program.

Flowchart

Start → Display Menu → Select Operation → Perform Selected Operation → Display Result → Repeat Menu → Exit → Stop
## Project Flowchart

![Hospital Emergency Queue Management System Flowchart](flowchart.png)
Project Team

This project was developed by the following team members:

1. Umra malik
2. Kafil vara 
3. Mahak malik
4. Palak thakur


Institution: Invertis University

Project: Hospital Emergency Queue Management System

Language: C Programming

Subject: Data Structures and Algorithms
