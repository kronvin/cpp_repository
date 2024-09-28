// CPPHW_Task5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

class Observer                                                           // Observer Interface
{
public:
	virtual ~Observer() = default;
	virtual void OnMoneyChanged(const int money) = 0;                    // Add event to react to
};


class MoneyInterface : public Observer 
{
public:
	virtual void OnMoneyChanged(const int money) override
	{
		cout << "Current Character's money: " << money << endl;          // React to the changes in Character's money
	};
};

class Character 
{
private:
	int money;
	vector<unique_ptr<Observer>> observers;                             // Create vector of objects which react to changes in money                   

public:
	Character(int initMoney) : money(initMoney) {}

	void Attach(unique_ptr<Observer> observer)                          // Create function to control the process of attaching new elements to the vector
	{
		observers.push_back(move(observer));
	}

	void AddMoney(int amount)                                           // Notify observers after adding money to the character
	{
		money += amount;
		Notify();
	}

	bool DeductMoney(int amount)                                         // Notify observers after deduct money from the character
	{
		if (money >= amount) 
		{
			money -= amount;
			Notify();
			return true;
		}
		cout << "Not enough money!" << endl;
		return false;
	}

	int GetMoney() const                                                
	{
		return money;
	}

	void Notify()                                                        // Notify functionality 
	{
		for (const auto& observer : observers)
		{
			observer->OnMoneyChanged(money);
		};
	};
};

class Weapon 
{
public:
	string name;
	int price;

	Weapon(string name, int price) : name(name), price(price) {}

	void ShowInfo() const 
	{
		cout << "Weapon: " << name << ", Price: " << price << endl;
	};
};

class Store                                      
{
private:
	vector<unique_ptr<Weapon>> weapons;

public:
	Store() 
	{
		weapons.push_back(make_unique<Weapon>("Sword", 100));
		weapons.push_back(make_unique<Weapon>("Axe", 150));
		weapons.push_back(make_unique<Weapon>("Bow", 200));
	}

	void ShowWeapons() const 
	{
		cout << "Available weapons in the store:" << endl;
		for (size_t i = 0; i < weapons.size(); i++) 
		{
			cout << i + 1 << ". ";
			weapons[i]->ShowInfo();
		};
	}

	unique_ptr<Weapon> BuyWeapon(int choice, Character& character)
	{
		if (choice < 1 || choice > weapons.size()) 
		{
			cout << "Invalid choice!" << endl;
			return nullptr;
		}

		unique_ptr<Weapon>& selectedWeapon = weapons[choice - 1];                    // Transfer weapon ownership from Store to Character
		if (character.DeductMoney(selectedWeapon->price))
		{
			cout << "You bought " << selectedWeapon->name << "!" << endl;
			return move(selectedWeapon);
		};

		return nullptr;
	};
};

int main() 
{
	Character character(50);

	auto moneyInterface = make_unique<MoneyInterface>();                             // Add money interface to the Character
	character.Attach(move(moneyInterface));

	cout << "Character's current money: " << character.GetMoney() << endl;

	Store store;

	int additionalMoney;
	cout << "Enter the amount of money to add to the character: ";
	cin >> additionalMoney;
	character.AddMoney(additionalMoney);

	store.ShowWeapons();
	int choice;
	cout << "Choose a weapon to buy (1-3): ";
	cin >> choice;

	unique_ptr<Weapon> purchasedWeapon = store.BuyWeapon(choice, character);

	if (purchasedWeapon) 
	{
		cout << "Weapon acquired: " << purchasedWeapon->name << endl;
	}
	else 
	{
		cout << "Weapon purchase failed!" << endl;
	}

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
