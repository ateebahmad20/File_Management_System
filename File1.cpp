#include<iostream>
#include<string>
using namespace std;

//A function for going back
void clear();

//Amount of directories that can be created in our File Management System
#define SIZE 100 

class file
{
public:

	file* next; //Pointer to the next file
	string name; //Variable to store the name
	string text; //Variable to store file's content
	int size = 0; //Variable to store file's size
};

class FileSystem
{
public:

	int MEMORY = 1000000; //Total Memory of OS => Approximately 100MB
	file* head[SIZE]; //Pointer to head node
	int Dir = 0; //A counter to maintain directories

	//Initializing all directories as NULL:

	FileSystem()
	{
		for (int i = 0; i < SIZE; i++)
		{
			head[i] = NULL;
		}
	}

	//To check whether any more directories can be created or not:

	bool Any_isEmpty()
	{
		int flag = 0;

		for (int i = 0; i < SIZE; i++)
		{
			if (head[i] == NULL)
				flag = 1; //if any directory is empty, flag returns 1
		}

		return flag;
	}

	//Function to check if any directory exist in the system or not:

	bool All_isEmpty()
	{
		int flag = 1;

		for (int i = 0; i < SIZE; i++)
		{
			if (head[i] != NULL)
				flag = 0; //if atleast one directory exist, flag becomes 0
		}

		return flag;
	}

	//Function to Create Folders:

	void Mkdir(string dirName)
	{
		if (Any_isEmpty() && !Dir_Exist(dirName)) //if folder not already exists
		{
			//Creating new directory:
			file* dir_name = new file();
			dir_name->name = dirName;

			//Pointing head to the new directory
			head[Dir] = dir_name;

			cout << "\n**Folder " << head[Dir]->name << " Created Successfully!**" << endl;
			Dir++;
		}

		else
			cout << "Directories Are Full OR Directory Already Exist!" << endl;
	}

	//Function to Search for a particular directory

	bool Dir_Exist(string dname)
	{
		int flag = 0;

		for (int i = 0;i < SIZE;i++)
		{
			file* temp = head[i];

			if (temp != NULL && temp->name == dname)
				flag = 1; //if directory exists, flag becomes 1 
		}

		return flag;
	}

	//To check whether a given file exist in the folder or not:

	bool File_Exist(string fname, string dname)
	{
		int flag = 0;

		for (int i = 0;i < SIZE;i++)
		{
			if (head[i] != NULL && head[i]->name == dname) //Searching folder
			{
				file* temp = head[i]->next;

				while (temp != NULL && temp->name != fname) //Searching File
				{
					temp = temp->next;
				}

				if (temp != NULL && temp->name == fname) //If file exist
					flag = 1;
			}

		}

		return flag;
	}

	//Function to Create Files in a Specific Folder

	void Create(string Fname, string d_name)
	{
		file* new_file = new file();
		new_file->name = Fname;

		if (All_isEmpty()) //if no directory exists
		{
			cout << "\nCreate a Folder First" << endl;
		}

		else if (!File_Exist(Fname, d_name)) //If file not already exist in folder
		{
			//If such a folder already exist in the System:

			if (Dir_Exist(d_name))
			{
				for (int i = 0;i < SIZE;i++)
				{
					//If directory is found and head is not NULL

					if (head[i] != NULL && head[i]->name == d_name)
					{
						file* temp = head[i]; //Creating a temporary node to point head

						while (temp->next != NULL) //Till end of list is reached
						{
							temp = temp->next;
						}

						temp->next = new_file; //Storing new file
						cout << "\n**File " << temp->next->name << " was created in Folder " << d_name << "**" << endl;
					}
				}
			}

			else
				cout << "\nFolder \"" << d_name << "\" Does not Exist!" << endl;
		}

		else
			cout << "\nFile " << Fname << " Already Exist!" << endl;

	}

	//A function for deleting directory:

	void Delete_Dir(string dname)
	{
		if (Dir_Exist(dname))
		{
			for (int i = 0;i < SIZE;i++)
			{
				if (head[i] != NULL && head[i]->name == dname)
				{
					file* temp = head[i];

					while (temp->next != NULL) //traversing all files and freeing memory
					{
						temp = temp->next;
						MEMORY += temp->size;
					}

					head[i] = NULL; // making folder equal to NULL if it exists
				}
			}

			cout << "\n**Folder \"" << dname << "\" Deleted!**" << endl;
		}

		else
			cout << dname << " Doesnot Exist" << endl;
	}

	void Delete_file(string fname)
	{
		string dname;

		cout << "From Folder: "; //Which folder to delete File from?
		cin >> dname;

		if (File_Exist(fname, dname))
		{
			for (int i = 0;i < SIZE;i++)
			{
				if (head[i] != NULL && head[i]->name == dname)
				{
					file* temp = head[i];

					while (temp->next->name != fname) //Until the file is found
					{
						temp = temp->next; //Increment Temp
					}

					//Freeing Space Occupied by the file 
					MEMORY += temp->next->size;

					//Deleting the file by pointing it to NULL
					temp->next = temp->next->next;
				}
			}
			cout << "\n**File \"" << fname << "\" Deleted!**" << endl;
		}

		else
			cout << fname << " Doesnot Exist" << endl;

	}

	//A function for moving a file from one folder to another:

	void Move(string fname, string dname)
	{
		string cur_dir, cur_text;
		int length, new_size;

		//Finding current directory of the file:

		for (int i = 0;i < SIZE;i++)
		{
			file* temp = head[i];

			while (temp != NULL && temp->name != fname)
			{
				temp = temp->next;
			}

			if (temp != NULL && temp->name == fname)
			{
				cur_dir = head[i]->name;
				cur_text = temp->text;
			}
		}

		if (File_Exist(fname, cur_dir) && Dir_Exist(dname)) //if both the file and folder exists
		{
			cout << "\n\nMoving File " << fname << " From " << cur_dir << "..." << endl;

			Delete_file(fname); //Deleting Previous file

			//Creating the Same file in another folder, hence MOVING:

			file* new_file = new file();
			new_file->name = fname;

			if (!File_Exist(fname, dname)) //If file not already exist in folder
			{
				//If such a folder already exist in the System:
				if (Dir_Exist(dname))
				{
					for (int i = 0;i < SIZE;i++)
					{
						//If directory is found and head is not NULL

						if (head[i] != NULL && head[i]->name == dname)
						{
							file* temp = head[i]; //Creating a temporary node to point head

							while (temp->next != NULL) //Till end of list is reached
							{
								temp = temp->next;
							}

							temp->next = new_file; //Storing new file
							cout << "\nFile " << fname << " Successfully Moved!" << endl;

							//Moving File Content:
							temp->next->text = cur_text;
							length = cur_text.length();
							new_size = length * 2; //Assuming each alphabet takes 2 byte to store

							temp->next->size = new_size; //Writing new file size
							MEMORY -= new_size; //Decreasing OS memory
						}
					}
				}

				else
					cout << "\nFolder \"" << dname << "\" Does not Exist!" << endl;
			}

			else
				cout << "\nFile " << fname << " Already Exist!" << endl;
		}

		else
			cout << "File or Folder Doesnot Exist" << endl;
	}

	//Function to Read From a File:

	void ReadFile(string Fname)
	{
		for (int i = 0;i < SIZE;i++)
		{
			//Searching for the file:

			file* temp = head[i];

			while (temp != NULL && temp->name != Fname)
			{
				temp = temp->next;
			}

			if (temp != NULL && temp->name == Fname) //When file is found
			{
				if (temp != NULL && temp->text.empty()) //if file doesnot contain text
					cout << "\nFile is Empty. Enter some text..." << endl;

				else
					cout << endl << "\"" << temp->text << "\"" << endl;
			}
		}
	}

	//Function for writing text in a file:

	void WriteFile(string Fname, string str)
	{
		int length, new_size;

		for (int i = 0;i < SIZE;i++)
		{
			//Searching for the file:

			file* temp = head[i];

			while (temp != NULL && temp->name != Fname)
			{
				temp = temp->next;
			}

			if (temp != NULL && temp->name == Fname) //When file is found
			{
				temp->text = str; //Inserting text into File

				//Calculating File Size:
				length = temp->text.length();
				new_size = length * 2; //Assuming each alphabet takes 2 byte to store

				temp->size = new_size; //Writing new file size
				MEMORY -= new_size; //Decreasing OS memory
			}
		}
	}

	//Opening a file to perform various operations:

	void OpenFile(string fname, char mode)
	{
		string text;

		if (All_isEmpty()) //if no file exists
		{
			cout << "\nNo Such File Exist!" << endl;
		}

		else
		{
			switch (mode)
			{

			case 'r': ReadFile(fname); break;

			case 'w':
				cout << "\nEnter Text: ";
				cin.ignore(); //to ignore the newline that cin generates
				getline(cin, text);
				WriteFile(fname, text);
				break;
			}
		}
	}

	//Closing the File

	void Close(string fname)
	{
		cout << "\nFile " << fname << " Closed Successfully!" << endl;
	}

	//Checking Memory of the OS:

	void OS_Memory()
	{
		cout << "\nMemory: " << MEMORY << " Bytes" << endl;
	}

	//Showing Distribution of files and folders:

	void Memory_Map()
	{
		if (!All_isEmpty()) //If atleast one directory exist to show
		{

			for (int i = 0;i < SIZE;i++)
			{
				if (head[i] != NULL)
				{
					file* temp = head[i]->next;

					cout << "-------------------------" << endl;
					cout << "|\t**" << head[i]->name << "**\t|" << endl;
					cout << "|\t\t\t|" << endl;

					while (temp != NULL)
					{
						cout << "|$" << temp->name << "\t" << temp->size << " Bytes" << endl;
						temp = temp->next;
					}

					cout << "|\t\t\t|" << endl;
					cout << "-------------------------";
					cout << endl << endl;
				}
			}
		}

		else
			cout << "\nNo Folder Or Files to Show" << endl;
	}
};

int main()
{
	FileSystem obj;
	string name, name2;
	char mode;

	for (int prompt = 0;prompt != 11;)
	{
		cout << "\t\tx---------------------------------------------------------------x" << endl;
		cout << "\t\t\t\t\tFILE MANAGEMENT SYSTEM\t\t" << endl << endl;
		cout << "\t\t1-Create Folder       2-Create File\t    3-Show Memory Map" << endl;
		cout << "\t\t4-Delete Folder\t      5-Delete File         6-Move File" << endl;
		cout << "\t\t7-Open File\t      8-Close File          9-Show OS Memory" << endl;
		cout << "\t\t10-Truncate File      11-Exit" << endl << endl;
		cout << "\t\tx----------------------------------------------------------------x" << endl;

		cout << "Function: ";
		cin >> prompt;

		switch (prompt)
		{
		case 1:
			cout << "\nEnter the Name of Directory: "; cin >> name;
			obj.Mkdir(name);
			clear();
			continue;

		case 2:
			cout << "\nEnter the Name of File: "; cin >> name;
			cout << "In Folder: "; cin >> name2;
			obj.Create(name, name2);
			clear();
			continue;

		case 3:
			obj.Memory_Map();
			clear();
			continue;

		case 4:
			cout << "\nEnter the Name of Directory: "; cin >> name;
			obj.Delete_Dir(name);
			clear();
			continue;

		case 5:
			cout << "\nEnter the Name of File: "; cin >> name;
			obj.Delete_file(name);
			clear();
			continue;

		case 6:
			cout << "\nEnter the Name of File: "; cin >> name;
			cout << "Move To Folder: "; cin >> name2;
			obj.Move(name, name2);
			clear();
			continue;

		case 7:
			cout << "\nEnter Name of the File: "; cin >> name;
			cout << "Select Mode (r-read, w-write): "; cin >> mode;
			obj.OpenFile(name, mode);
			clear();
			continue;

		case 8:
			cout << "\nEnter Name of the File: "; cin >> name;
			obj.Close(name);
			clear();
			continue;

		case 9:
			obj.OS_Memory();
			clear();
			continue;

		case 11:
			cout << "\nThanks For Using\n\nExiting......" << endl;
			system("exit");
		}
	}
}

void clear()
{
	cout << "\n\nPress E to go back..." << endl;
	getchar();
	getchar();
	system("CLS");
}
