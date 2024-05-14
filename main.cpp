#include <iostream>
#include <vector>
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

int main()
{
    srand(time(0));
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
        table[row][col].push_back(currentPlate);
    }

    // Create a Plate object and modify its cakes vector before pushing
    // Plate customPlate;
    // customPlate.cakes = {7, 8, 9, 10, 11, 12};
    // table[4][0].push_back(customPlate);
    // printTable();
}