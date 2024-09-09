// CPPHW_Task2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Player                                                                              // Create Player's Structure. Need to be added befor battle to use in the battle structure
{
	string name;
	int clan;
	int health;
	int damage;

	Player(const string n, int c, int h, int d): name(n), clan(c), health(h), damage(d) {} // Create Player constructor. Define Parametres
};

struct Battle                     // Create Battle Conditions
{
	vector<Player> FirstClan;     // Create First Clan Vector
	vector<Player> SecondClan;    // Create Second Clan Vector

public:

	void AddPlayer(const string name, int clan, int health, int damage)    // Create Add Player Function
	{
		Player player(name, clan, health, damage);

		if (clan == 0)
		{
			FirstClan.push_back(player);     // Add Created Player to the First Clan Vector
		}
		else if (clan == 1)
		{
			SecondClan.push_back(player);    // Add Created Player to the Second Clan Vector
		}
	};

	bool RemovePlayer(const string name, int clan)     // Create Remove Player Function
	{
		auto& SelectedClan = (clan == 0) ? FirstClan : SecondClan;    // Find Clan to Remove Player from, ?: - to compare variables, use auto& to find target vector

		size_t originalSize = SelectedClan.size();     // Define Clan size

		SelectedClan.erase(remove_if(SelectedClan.begin(), SelectedClan.end(),   // remove_if - move elements which need to be kept to the end, move it to the element which needs to be removed, erase - delete moved elements
			[&](const Player& p) {return p.name == name;}),    // returns true if Player's name matches input name
			SelectedClan.end());

		return SelectedClan.size() != originalSize;            // Check if Clan size has been changed, returns true if changed, returns false if not
	};

	void SimulateBattle() 
	{
		int turn = 0;                                          // Define Clan's Turn

		while (!FirstClan.empty() && !SecondClan.empty())      // Continue Battle While Both Clans have Players (!clan.empty - not empty)
		{                                                          
			if (turn == 0 && !FirstClan.empty())               // If Fist Clan's Turn and First Clan is not empty
			{                  
				attack(FirstClan, SecondClan);
			}
			else if (turn == 1 && !SecondClan.empty()) {        // If Second Clan's Turn and Second Clan is not empty
				attack(SecondClan, FirstClan);
			}

			turn = 1 - turn;                                    // change turn
		}

		if (SecondClan.empty()) 
		{
			cout << "First Clan has Won!" << endl;
		}
		else if (FirstClan.empty()) 
		{
			cout << "Second Clan has Won!" << endl;
		}
		else {
			cout << "Both Clans Have Died!" << endl;
		}
	}

private:
	void attack(vector<Player>& attackers, vector<Player>& defenders)    // Define range of attackers and defenders 
	{
		if (attackers.empty() && defenders.empty()) return;              // Stop attack once both clans are empty. Return true to the SimulateBattle function

		Player& attacker = attackers.front();
		Player& defender = defenders.front();

		defender.health -= attacker.damage;                              // Attack
		
		cout << attacker.name << " from " << attacker.clan << " attacks " << defender.name << " from " << defender.clan << endl;   // Attack result
		cout << "Damage caused by " << attacker.name << ": " << attacker.damage << endl;
		cout << defender.name << "'s Current Health: " << defender.health << endl;

		if (defender.health <= 0)                                        // Remove dead player from the Clan. Use erase since we know the position of the element
		{
			cout << defender.name << " has died!" << endl;
			defenders.erase(defenders.begin());
		}
	}
};



int main()
{
	Battle battle;    // Add Battle structure to main

	int command;     // Create command variable

	while (true)    // Repeat itself
	{
		cout << "Enter Your Command (0 - to add player to the team, 1 - to remove player from the team, 2 - to start the battle):" << endl;
		cin >> command;

		if (command == 0)
		{
			string name;
			int clan, health, damage;

			cout << "Enter Player's Name:" << endl;
			cin >> name;
			cout << "Choose Player's Clan:" << endl;
			cin >> clan;
			cout << "Enter Player's Health:" << endl;
			cin >> health;
			cout << "Enter Player's Damage:" << endl;
			cin >> damage;

			if (clan == 0)                             // Define stats increase depending on the clan
			{
				health == health + 10;
			}
			else if (clan == 1)
			{
				damage == damage + 5;
			};

			battle.AddPlayer(name, clan, health, damage);    // Call AddPlayer function using the stats given

			if (clan == 0)
			{
				cout << "Player has been added to the First Clan. Player's health has been increased." << endl;
			}
			else if (clan == 1)
			{
				cout << "Player has been added to the Second Clan. Player's damage has been increased." << endl;
			};
		}

		else if (command == 1)
		{
			string name;
			int clan;

			cout << "Enter name of a Player you want to remove: ";
			cin >> name;

			cout << "Enter clan (0 for the First Clan or 1 for the Second Clan): " << endl;
			cin >> clan;

			if (battle.RemovePlayer(name, clan))
			{
				cout << "Player has been removed succesfully." << endl;
			}
			else
			{
				cout << "Player has not been found in the Clan" << endl;
			};
		}

		else if (command == 2)
		{
			battle.SimulateBattle();
		}
	}
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
