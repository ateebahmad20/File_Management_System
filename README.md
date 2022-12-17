# File_Management_System
The system can perform the following functions:

•	It can create a new folder
•	It can create a new file inside a folder of the user’s choice
•	It shows the distribution of folders and files inside.
•	It can delete a particular folder along with all files in it.
•	It can delete a single file from a folder.
•	It can move files from one directory to another while retaining the file’s content
•	It can search for a directory in the system.
•	It can search for a file in the system.
•	It can open a file for reading and writing.
•	It can truncate a file to desired words.
•	It calculates file size and updates at the run-time.
•	It shows the total memory of the OS available.

To Perform the desire function, enter the corresponding number to it. For instance, to "Create Folder,"
Press 1 on the menu. Similarly, press "E" to go back to the menu and "11" to Exit the System.

Data Structure:
We used an array of linked lists as our main data structure to store various files and folders in the system. 
The head of the linked list stores the information about the folder. Whereas the file’s information (name, text, size) is stored in nodes, which are 
connected to the respective head/folder.

Memory Map:
The memory map shows the complete distribution of files and folders in the System. 
It also tells us the size (number of bytes) occupied by each file. 
The names in the middle represent the folders whereas inside are the files:

Files & Directories:
Files and directories were cautiously implemented in my File Management System. 
Almost 100 directories can be simultaneously created in the system. 
Each directory may contain as many files as the memory allows. The user has the option to create folders and files inside the folder of their choice.

Memory Allocation:
Linked allocation technique is followed for the memory allocation. 
A fixed size of 100MB is used for the total OS memory, which can be increased depending on the use. 
The memory taken by a file is determined by its size. If the file has no content in it, it occupies 0 bytes. 

Similarly, 2 bytes are allocated for each alphabet in the file. 
For instance, if a file contains 5 letters, a total of 10 Bytes would be occupied by that file. 
The change in size can be observed both in the memory map as well as in the total OS memory.
