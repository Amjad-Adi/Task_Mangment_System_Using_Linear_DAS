# Task_Mangment_System_Using_Linear_DAS
A C-based console app for managing tasks using linked lists and stack data structures.
 The system enables users to manage tasks through a combination of singly linked lists (for unperformed tasks) and stack data structures (for performed tasks), enabling full control over task scheduling, execution, and undo operations.

The application is designed with a menu-driven interface that allows users to:

Load tasks from a file.

Add new tasks with unique IDs.

Delete existing tasks.

Search tasks by ID or name in both unperformed and performed lists.

Perform tasks (move from unperformed list to performed stack).

Undo tasks (move back from performed stack to unperformed list).

View current tasks and export reports to a file (Report.txt).

⚙️ Key Features:
✅ Linked List: Stores and manages unperformed tasks dynamically.

🔁 Stack (LIFO): Maintains a history of performed tasks to allow undoing operations.

🔍 Search Functionality: Allows search by task ID or name across both task states.

📄 File Input/Output: Supports reading tasks from a file (tasks.txt) and generating summary reports.

❌ Duplicate ID Prevention: Enforces task ID uniqueness across both unperformed and performed tasks.

🔒 Error Handling: Includes runtime checks for null pointers, memory allocation, and invalid input to prevent crashes.

📂 Data Structures Used:
struct TaskNode: Represents a task with fields for ID, name, date, duration, status, and pointer to the next task.

LinkedList: A singly linked list for tasks yet to be performed.

Stack: A stack implemented as a linked list for tasks that have been completed.

🧪 Sample Operations:
Add Task: Adds a new task to the end of the unperformed list.

Perform Task: Moves a task to the performed stack.

Undo Task: Pops a task from the stack and reinserts it into the unperformed list.

Report Generation: Writes a categorized summary of tasks to a file.
