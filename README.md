# Task_Mangment_System_Using_Linear_DAS
A C-based console app for managing tasks using linked lists and stack data structures.
This system helps you manage and keep track of tasks you need to do, mark tasks as done, undo done tasks, and generate reports.

Features
Uses a linked list to store tasks you haven't done yet.

Uses a stack to keep track of tasks you've completed (so you can undo if needed).

Search for tasks by ID or name in both lists.

Load tasks from a file and save reports back to a file.

Makes sure task IDs are unique to avoid confusion.

Includes error checks to prevent crashes and invalid inputs.

How It Works
Tasks are stored as nodes in a linked list if not done.

When you perform a task, it moves to the stack of done tasks.

You can undo a task, which moves it back to the linked list.

Search lets you find tasks quickly by ID or name.

Reports summarize all your tasks into a text file.
