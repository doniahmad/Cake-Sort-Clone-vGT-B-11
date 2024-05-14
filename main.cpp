#include <iostream>
#include <vector>
using namespace std;

struct Plate
{

    vector<int> cakes = {0, 0, 0, 0, 0, 0};
};

vector<Plate> table[5][4];

bool HasCake(const Plate &plate, int cakeType)
{
    for (int cake : plate.cakes)
    {
        if (cake == cakeType)
        {
            return true; // Found the specified cake type
        }
    }
    return false;
}

bool HasSimilarCake(const Plate &plate1, const Plate &plate2)
{
    for (int cakeType : plate1.cakes)
    {
        if (cakeType != 0 && HasCake(plate2, cakeType))
        {
            return true; // Found a similar cake (non-zero and present in other plate)
        }
    }
    return false;
}

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

bool IsComplete(Plate &plate)
{
    if (plate.cakes[0] != 0)
    {

        int cakeToCheck = plate.cakes[0];
        for (int cake : plate.cakes)
        {
            if (cake != cakeToCheck)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool TableIsEmpty(int row, int col)
{
    Plate currentPlate = table[row][col][0];

    for (int cake : currentPlate.cakes)
    {
        if (cake != 0)
        {
            return false;
        }
    }

    return true;
}

void PrintCakes(const Plate &plate)
{
    cout << "[ ";
    for (int cake : plate.cakes)
    {
        cout << cake << " ";
    }
    cout << "]";
}

void PrintTable()
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
                    PrintCakes(table[i][j][k]);
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
    for (int i = 0; i < rand() % plate.cakes.size() + 1; ++i)
    {
        plate.cakes[i] = rand() % 4 + 1; // Assign random value to each element
    }
    return plate;
}

void SwapCake(vector<Plate> &plate1, vector<Plate> &plate2)
{
    Plate &currentPlate = plate1[0];
    Plate &neighborPlate = plate2[0];
    for (int &cake : currentPlate.cakes)
    {
        if (cake != 0)
        {
            for (int &neighborCake : neighborPlate.cakes)
            {
                if (neighborCake == cake)
                {
                    for (int &cake : currentPlate.cakes)
                    {
                        if (cake == 0)
                        {
                            cake = neighborCake;
                            neighborCake = 0;
                            break;
                        }
                    }
                }
            }
        }
    }
    plate1[0] = currentPlate;
    plate2[0] = neighborPlate;
}

// Function to check if there's a possible switch with nearby plates
void CheckCake()
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            Plate currentPlate = table[i][j][0]; // Get the current plate

            // Check neighboring plates: top, bottom, left, right
            if (i < 4 && HasSimilarCake(currentPlate, table[i + 1][j][0]))
            {

                SwapCake(table[i][j], table[i + 1][j]);
            }
            if (i > 0 && HasSimilarCake(currentPlate, table[i - 1][j][0]))
            {

                SwapCake(table[i][j], table[i - 1][j]);
            }
            if (j > 0 && HasSimilarCake(currentPlate, table[i][j - 1][0]))
            {

                SwapCake(table[i][j], table[i][j - 1]);
            }
            if (j < 3 && HasSimilarCake(currentPlate, table[i][j + 1][0]))
            {
                SwapCake(table[i][j], table[i][j + 1]);
            }

            if (IsComplete(table[i][j][0]))
            {
                table[i][j].clear();
                Plate newPlate;
                table[i][j].push_back(newPlate);
                CheckCake();
            }
        }
    }
}

int main()
{
    srand(time(0));
    initTable();
    while (true)
    {
        system("cls");
        int row, col;
        PrintTable();
        Plate currentPlate = GeneratePlate();

        while (true)
        {
            cout << "Current Cake : ";
            PrintCakes(currentPlate);
            cout << endl;

            cout << "Insert to Table";
            cout << "\n\n";
            cout << "Row : ";
            cin >> row;
            cout << "Col : ";
            cin >> col;

            if (row < 0 || row >= 5 || col < 0 || col >= 4)
            {
                cout << "Invalid position. Try again.\n"
                     << endl;
                continue;
            }

            if (!table[row][col].empty())
            {
                table[row][col][0] = currentPlate; // Replace the existing plate with the new one
            }
            else
            {
                cout << "Invalid position. Try again.\n"
                     << endl;
                continue;
            }

            CheckCake();  // Check for possible switches
            PrintTable(); // Check for possible switches
            break;
        }
    }
}