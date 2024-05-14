#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits>
using namespace std;

struct Plate
{
    vector<int> cakes = {0, 0, 0, 0, 0, 0};
};

vector<Plate> table[5][4];

void printPlate(const Plate &plate)
{
    cout << "[ ";
    for (int cake : plate.cakes)
    {
        cout << cake << " ";
    }
    cout << "]";
}

void printTable()
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            cout << "{(" << i << "," << j << ") ";
            if (table[i][j].empty())
            {
                cout << "[]";
            }
            else
            {
                for (int k = 0; k < table[i][j].size(); ++k)
                {
                    printPlate(table[i][j][k]);
                }
            }
            cout << "} ";
        }
        cout << endl; // Newline at the end of each row
    }
}

Plate GeneratePlate()
{
    Plate plate;
    for (int &cake : plate.cakes)
    {
        cake = rand() % 6;
    }
    return plate;
}

// Function to initialize all plates with 0, 0, 0, 0, 0, 0
void initTable()
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            table[i][j].clear(); // Clear existing plates
            Plate newPlate;
            table[i][j].push_back(newPlate);
        }
    }
}

// Function to check if there's a possible switch with nearby plates
void checkSwitch()
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            Plate currentPlate = table[i][j][0]; // Get the current plate
            // Check neighboring plates: top, bottom, left, right
            if (i > 0 && table[i - 1][j][0].cakes != currentPlate.cakes && currentPlate.cakes != vector<int>{0, 0, 0, 0, 0, 0})
            {
                cout << "Possible switch exists for plate (" << i << "," << j << ") with plate (" << i - 1 << "," << j << ")" << endl;
            }
            if (i < 4 && table[i + 1][j][0].cakes != currentPlate.cakes && currentPlate.cakes != vector<int>{0, 0, 0, 0, 0, 0})
            {
                cout << "Possible switch exists for plate (" << i << "," << j << ") with plate (" << i + 1 << "," << j << ")" << endl;
            }
            if (j > 0 && table[i][j - 1][0].cakes != currentPlate.cakes && currentPlate.cakes != vector<int>{0, 0, 0, 0, 0, 0})
            {
                cout << "Possible switch exists for plate (" << i << "," << j << ") with plate (" << i << "," << j - 1 << ")" << endl;
            }
            if (j < 3 && table[i][j + 1][0].cakes != currentPlate.cakes && currentPlate.cakes != vector<int>{0, 0, 0, 0, 0, 0})
            {
                cout << "Possible switch exists for plate (" << i << "," << j << ") with plate (" << i << "," << j + 1 << ")" << endl;
            }
        }
    }
}


int main()
{
    srand(time(0));
    initTable(); // Initialize the table with all plates having 0, 0, 0, 0, 0, 0
    while (true)
    {
        system("cls");
        int row, col;
        printTable();
        Plate currentPlate = GeneratePlate();
        cout << "Current Cake : ";
        printPlate(currentPlate);
        cout << endl;

        cout << "Insert to Table";
        cout << "\n\n";
        cout << "Row : ";
        cin >> row;
        cout << "\nCol : ";
        cin >> col;
        if (!table[row][col].empty())
        {
            table[row][col][0] = currentPlate; // Replace the existing plate with the new one
        }
        else
        {
            table[row][col].push_back(currentPlate);
        }
        printTable();
        checkSwitch(); // Check for possible switches
        
        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    // Create a Plate object and modify its cakes vector before pushing
    // Plate customPlate;
    // customPlate.cakes = {7, 8, 9, 10, 11, 12};
    // table[4][0].push_back(customPlate);
    // printTable();
}
