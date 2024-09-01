// CPPHW_Task1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;


int main()
{
    cout << "Enter Initial Health: \n";

    float health;
    cin >> health;

    while (health > 0)
    {
        cout << "Enter Item Impact: \n";
        float item_impact;
        cin >> item_impact;

        cout << "Enter Distance to the Item: \n";
        float item_distance;
        cin >> item_distance;

        if ((item_impact > 0) && (item_distance < 100))
        {
            health = health + item_impact * (1 - item_distance / 100);
            cout << "Hero was Healed!\n";
        }
        else if ((item_impact < 0) && (item_distance < 100))
        {
            health = health + item_impact * (1 - item_distance / 100);
            cout << "Hero was Damaged!\n";
        }
        else if (item_distance >= 100)
        {
            health = health;
            cout << "Missed!\n";
        }

        if ((health > 0) && (health < 1))
            health = 1;

        if (health > 0)
        cout << "Current Health: " << health << endl;
    }

    cout << "The Hero is Dead!";

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
