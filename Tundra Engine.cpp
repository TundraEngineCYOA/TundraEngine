#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>

int readInputChoice();
void printOutInventory();
void addOrRemoveFromInventory(int binary, int position);
bool compareWithInventory(int binary, int position);

//your inventory
int inventory[16];

int main()
{
	using namespace std;

	//common finite-state-machine, keep track of "state" of the game
	//-1 = exit game, 0 = main menu, 1 = play game with basic dialogue/traversal,
	//2 = play game with fight monster, 9 = help menu within gameplay
	int gameState = 0;
	//current input choice by player
	int currentChoice = 0;
	//current "location" based on file
	int currentLocation = 1;

	//crude way to clear the console screen:
	cout << string(100, '\n');
	//game loop: play until "exit game"
	while(gameState != -1)
	{
		//if in "main menu"...
		if (gameState == 0)
		{
			cout << "\n";
			cout << "|   Welcome and thank you for using the - Tundra Engine Verison 1.0\n";
            cout << "\n";
			cout << "|   MAIN MENU: What do you want to do? \n";
            cout << "\n";
			cout << "|   1. Play New Game \n" << "|   2. Quit Game \n" ;
			cin.sync();
			currentChoice = readInputChoice();
			currentLocation = 1;
			if (currentChoice == 1)
				gameState = 1;
			else if (currentChoice == 3)
				gameState = -1;
			else
				cout << "That's not a valid choice, try again. \n";
			for (int i = 0; i < sizeof(inventory)/sizeof(inventory[0]); i++)
			{
				inventory[i] = 0;
			}
		}
		//if in "play game with basic dialogue/traversal"...
		else if (gameState == 1)
		{
			//cout << "(this is the main game with basic dialogue/traversal)\n";

			std::vector<std::pair <int,int> > options(1,std::make_pair(-1,-1));
			string line;
			std::stringstream ss;
			ss << currentLocation << ".txt";
			string fileName;
			ss >> fileName;
			ifstream currentFile(fileName.c_str());
			if (currentFile.is_open())
			{
				//find format of file by reading first integer
				int fileFormat = 0;
				currentFile >> fileFormat;
				//cout << "my file format is " << fileFormat << "\n";
				if (fileFormat == 1)
				{
					getline(currentFile,line,'@');
					//while (getline(currentFile,line) && line != "@")
					//{
						cout << line << "\n";
					//}
					int choice, path;
					while (currentFile.eof() == false)
					{
						currentFile >> choice >> path;
						options.push_back(std::make_pair(choice,path));
					}
					currentFile.close();

					printOutInventory();

					currentChoice = readInputChoice();
					for(std::vector< std::pair<int,int> >::size_type i = 0; i != options.size(); i++) {
						if (options[i].first == currentChoice)
						{
							currentLocation = options[i].second;
							break;
						}
					}
				}
				else if (fileFormat == 2)
				{
					for(int i=0; i < sizeof(inventory)/sizeof(inventory[0]); i++)
					{
						int bin = 0;
						currentFile >> bin;
						addOrRemoveFromInventory(bin, i);
					}

					getline(currentFile,line,'@');
					//while (getline(currentFile,line) && line != "@")
					//{
						cout << line << "\n";
					//}
					int choice, path;
					while (currentFile.eof() == false)
					{
						currentFile >> choice >> path;
						options.push_back(std::make_pair(choice,path));
					}
					currentFile.close();

					printOutInventory();

					currentChoice = readInputChoice();
					for(std::vector< std::pair<int,int> >::size_type i = 0; i != options.size(); i++) {
						if (options[i].first == currentChoice)
						{
							currentLocation = options[i].second;
							break;
						}
					}
				}
				else if (fileFormat == 3)
				{
					bool correctPath = true;
					int nextLocation = 0;
					do{
						correctPath = true;
						for(int i=0; i < sizeof(inventory)/sizeof(inventory[0]); i++)
						{
							int bin = 0;
							currentFile >> bin;
							correctPath = correctPath && compareWithInventory(bin, i);
						}
						currentFile >> nextLocation;
					}while(correctPath==false);
					currentLocation = nextLocation;
				}
				else
				{
					currentFile.close();
				}
			}
			else
			{
				//cout << "file " << fileName << " doesn't exist...\n";
				cout << string(100, '\n');
				gameState = 0;
			}
		}
		//if in "play game with fight monster"...
		else if (gameState == 2)
		{
			if (cin.get() << '\n')
			{
			}
		}
		//if in "help menu within gameplay"...
		else if (gameState == 9)
		{
			if (cin.get() << '\n')
			{
			}
		}
	}

	cout << string(100, '\n');
	cout << "Thank you for playing... \n";
	return 0;
}

int readInputChoice()
{
	using namespace std;

	int currentChoice = 0;
	cin >> currentChoice;

	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cout << string(100, '\n');

	if (currentChoice < 1 || currentChoice > 9)
	{
		cout << "Enter a proper number! \n";
		currentChoice = 0;
	}

	return currentChoice;
}

void printOutInventory()
{
	using namespace std;
	bool empty = true;
	cout << "Make your move: ";
	for (int i=0; i < sizeof(inventory); i++)
	{
		if (inventory[i] == 1)
		{
			//print out what's in your inventory
			if (i == 0)
				cout << "A Bible" << "\t";
			else if (i == 1)
				cout << "A coin" << "\t";
			else if (i == 2)
				cout << "Rabbits Foot" << "\t";
			else if (i == 3)
				cout << "A Napkin" << "\t";
			//...

			empty = false;
		}
	}
	if (empty == true)
	{
		cout << "(nothing)";
	}
	cout << "\n";
}

void addOrRemoveFromInventory(int binary, int position)
{
	//if binary is 1 and inventory is 0, add
	//if binary is 1 and inventory is 1, remove
	if (binary == 0)
	{
		//do nothing
	}
	else
	{
		if (inventory[position] == 1)
		{
			inventory[position] = 0;
		}
		else
		{
			inventory[position] = 1;
		}
	}
}

bool compareWithInventory(int binary, int position)
{
	if (binary == 0)
	{
		return true;
	}
	else if (binary == 1 && inventory[position] == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
