// CPPHW_Task4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

using namespace std;

class IDamagable 
{
public:

	virtual void ApplyDamage(float Damage)                                 // Create method for further realisation of applying damage
	{
	};
};

class IHealthNotifier                                          // Notification about health change (interface)
{
public:

	virtual ~IHealthNotifier() = default;
	virtual void Subscribe(class IHealthUpdate* observer) = 0;
	virtual void Unsubscribe(class IHealthUpdate* observer) = 0;
	virtual void NotifyHealthChange() = 0;
};

class IHealthUpdate                                           // Interface for observers/subscribers to health changes
{
public:

	virtual ~IHealthUpdate() = default;
	virtual void ReceiveHealthUpdate(float newHealth) = 0;
};

class Enemy : public IHealthNotifier, public IDamagable                   // Enemy Class, has default health, notifies Character about changes in health
{
private:

	float health;
	vector<IHealthUpdate*> observers;                                     // Vector for health changes observers

public:

	Enemy(float initialHealth) : health(initialHealth) {}    

	void Subscribe(IHealthUpdate* observer) override 
	{
		observers.push_back(observer);
	}

	void Unsubscribe(IHealthUpdate* observer) override 
	{
		observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
	}

	void NotifyHealthChange() override                                         // Notification for all subscribers
	{
		for (IHealthUpdate* observer : observers)
		{
			observer->ReceiveHealthUpdate(health);
		}
	};

	void ApplyDamage(float damage) override                                // Receive damage and update subscribers about health changes
	{
		health -= damage;
		NotifyHealthChange(); 
	};
	
	float GetHealth() const                          
	{
		return health;
	}
};

class Weapon : public IDamagable                                                                       // Weapon parent class
{
private:

	float damage;
	string name;

public:

	Weapon(float dmg, string nm) : damage(dmg), name(nm) {}

	string GetName() const 
	{
		return name;
	}

	float GetDamage() const
	{
		return damage;
	};

	void DamageActor(IDamagable& target)                                                  
	{
		target.ApplyDamage(damage);
	};
};



class Character : public IHealthUpdate, public IDamagable                       // Character subscribes to enemy's health changes
{
private:

	vector<unique_ptr<Weapon>> weapons;   // All weapons
	Weapon* activeWeapon = nullptr;      // Active weapon
	unique_ptr<Weapon> fists;

public:

	Character() 
	{
		fists = make_unique<Weapon>(5.0f, "Fists");                                  // Create fists as base damage weapon
	}

	void AddWeapon(unique_ptr<Weapon> weapon) 
	{
		weapons.push_back(move(weapon));
	}

	void EquipWeapon(int index)                                                   // Move weapon from vector to character - equip
	{
		if (index >= 0 && index < weapons.size()) 
		{
			activeWeapon = weapons[index].get();
			cout << "Equipped " << activeWeapon->GetName() << endl;
		}
		else 
		{
			cout << "No weapon equipped!" << endl;
			activeWeapon = fists.get();
			cout << "Character will be fighting with " << activeWeapon->GetName() << endl;

		};
	};

	void ReceiveHealthUpdate(float newHealth) override                            // receive health update info (method)
	{
		cout << "Enemy's health is now " << newHealth << ".\n";
	}

	Weapon* GetActiveWeapon() const                                               // Get info about active weapon
	{
		return activeWeapon;
	}

	void AttackWithEquippedWeapon(IDamagable& target)                              // As an owner, character is responsible for weapon's damage applying
	{
		activeWeapon->DamageActor(target);
	};
};


// Create Weapon child classes

class Sword : public Weapon 
{
public:

	Sword() : Weapon(80.0f, "Sword") {}
};

class Axe : public Weapon 
{
public:

	Axe() : Weapon(50.0f, "Axe") {}
};

class Bow : public Weapon 
{
public:

	Bow() : Weapon(40.0f, "Bow") {}
};

int main() 
{
	Character character;       

	Enemy enemy(100.0f);

	cout << "Enemy's health is now " << enemy.GetHealth() << endl;

	unique_ptr<Weapon> sword = make_unique<Sword>();
	unique_ptr<Weapon> axe = make_unique<Axe>();
	unique_ptr<Weapon> bow = make_unique<Bow>();

	character.AddWeapon(move(sword));                            // Character becomes an owner of all weapons
	character.AddWeapon(move(axe));
	character.AddWeapon(move(bow));

	enemy.Subscribe(&character);                                 // Character subscribes to enemy health update

	int weaponChoice;
	cout << "Choose your weapon (1 = Sword, 2 = Axe, 3 = Bow): ";
	cin >> weaponChoice;

	character.EquipWeapon(weaponChoice);                          // Equip weapon of choice

	cout << "Character attacks enemy with " << character.GetActiveWeapon()->GetName() << " and deals " << character.GetActiveWeapon()->GetDamage() << " damage!" << endl;      // Use character to get information (use methods of active weapon)

	character.AttackWithEquippedWeapon(enemy);       

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



