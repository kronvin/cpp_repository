// CPPHW_Task3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Building                                                                                                                   // Create Building Class
{
private: 

	static int IDCounter;
	int ID;
	int MaxAge;
	int CurrentAge;
	int InitialCost;
	int CurrentCost;

	void Destroy(vector<Building>& Buildings)                                                                                  // Function to destroy a building and inform player about it
	{
		cout << "Building with ID " << ID << " has been destroyed.\n";

		Buildings.erase
		(remove_if(Buildings.begin(), Buildings.end(),
		[this](const Building& b) { return b.GetID() == this->ID; }),
		Buildings.end()
		);
	};


public:

	Building(int MaxAge, int InitialCost) : ID(++IDCounter), MaxAge(MaxAge), InitialCost(InitialCost), CurrentAge(0) {};       // Create Building constructor. Define Parametres
	

	int GetID() const                                                                                                          // Function to return Building ID
	{
		return ID;
	};

	void Aging(int Years, vector<Building>& Buildings)                                                                         // Function to age the building
	{
		CurrentAge += Years;

		if (CurrentAge >= MaxAge)
		{
			Destroy(Buildings);
		}
	};

	int GetCost() const                                                                                                        // Function to get current cost of the building                                                                  
	{
		return InitialCost * (MaxAge - CurrentAge) / MaxAge;
	};


	void PrintInfo() const                                                                                                     // Function to print info on the building
	{
		cout << "ID: " << ID << endl;
		cout << "Max Age: " << MaxAge << endl;
		cout << "Current Cost: " << GetCost() << endl;
		cout << "Current Age: " << CurrentAge << endl;
	};
};

int Building::IDCounter = 0;                                                                                                    // Set counter to save an existing ID and create the next unique one

Building* FindBuilding(vector<Building>& buildings, int ID)                                                                     // Find building in the vector by ID
{
	for (auto& building : buildings)
	{
		if (building.GetID() == ID)
		{
			return &building;
		}
	}
	return nullptr;
};

void BuildingsData(const vector<Building>& Buildings)                                                                          // Create function to get info on all existing buildings
{
	int TotalCost = 0;
	cout << "List of all buildings:" << endl;

	for (const auto& building : Buildings)
	{
		cout << "ID: " << building.GetID() << endl;
		cout << "Current Cost: " << building.GetCost() << endl;
		TotalCost += building.GetCost();                                                                                      // Sum all buildings cost to get total cost
	}

	cout << "Total Cost of all buildings: " << TotalCost << endl;                                         
};

int main()
{
	vector<Building> Buildings;                                                                                               // Create vector of buildings

	int MaxAge, InitialCost;
	int command;


	while (true)
	{
		cout << "Choose command to manage your City (1 to create buildings, 2 to get info about your buildings, 3 to modify existing buildings): " << endl;
		cin >> command;

		if (command == 1)
		{
			cout << "Create a new Building.\n" << "Enter Initial Cost of the Building" << endl;
			cin >> InitialCost;

			cout << "Enter Max Age of the Building" << endl;
			cin >> MaxAge;

			Building building(MaxAge, InitialCost);
			Buildings.push_back(building);

			cout << "Information on the Building added:" << endl;
			building.PrintInfo();
		}

		else if (command == 2)
		{
			BuildingsData(Buildings);
		}

		else if (command == 3)
		{
			int SearchID;

			cout << "Enter the ID of the building to age: " << endl;
			cin >> SearchID;

			Building* foundbuilding = FindBuilding(Buildings, SearchID);

			if (foundbuilding != nullptr)
			{
				int Years;
				cout << "Enter how many years to age the building: " << endl;
				cin >> Years;

				foundbuilding -> Aging(Years, Buildings);
			}
			else
			{
				cout << "Building with ID " << SearchID << " not found." << endl;
			};
		};
	};
	return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
