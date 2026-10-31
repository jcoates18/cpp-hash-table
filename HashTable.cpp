/*
 * Project 9 - Hash Table with Conflict Resolution
 *
 * Name: Jourdyn Coates
 * Date: July 7, 2026
 */

#include <iostream>
#include <string>

using namespace std;

class Circle
{

private:
    double radius;

public:
    Circle()
    {
        radius = 0.0;
    }

    Circle(double r)
    {
        radius = r;
    }

    void setRadius(double r)
    {
        radius = r;
    }

    double getRadius() const
    {
        return radius;
    }

    double calculateArea() const
    {
        return 3.14159 * radius * radius;
    }
};

struct Node
{
    string* key;
    Circle* circle;

    Node()
    {
        key = nullptr;
        circle = nullptr;
    }
};

bool IsPrime(int num)
{
    if (num <= 1)
        return false;

    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
            return false;
    }

    return true;
}

int NextPrime(int num)
{
    while (!IsPrime(num))
    {
        num++;
    }

    return num;
}

int MyHasher(string key, int tableSize)
{
    int sum = 0;

    for (int i = 0; i < key.length(); i++)
    {
        sum += key[i];
    }

    return sum % tableSize;
}

void DestroyTable(Node*& table, int& tableSize)
{
    if (table != nullptr)
    {
        for (int i = 0; i < tableSize; i++)
        {
            delete table[i].key;
            delete table[i].circle;

            table[i].key = nullptr;
            table[i].circle = nullptr;
        }

        delete[] table;
        table = nullptr;
        tableSize = 0;

        cout << "Current hash table destroyed." << endl;
    }
}

void InsertElement(Node* table, int tableSize)
{
    if (table == nullptr)
    {
        cout << "You must create a hash table first." << endl;
        return;
    }

    string inputKey;
    double radius;

    cout << "Enter lowercase string key: ";
    cin >> inputKey;

    cout << "Enter circle radius: ";
    cin >> radius;

    int index = MyHasher(inputKey, tableSize);
    int originalIndex = index;
    int count = 0;

    while (table[index].key != nullptr && count < tableSize)
    {
        if (*(table[index].key) == inputKey)
        {
            table[index].circle->setRadius(radius);
            cout << "Key already existed. Circle radius updated." << endl;
            return;
        }

        index = (index + 1) % tableSize;
        count++;
    }

    if (count == tableSize)
    {
        cout << "Error: Hash table is full." << endl;
        return;
    }

    table[index].key = new string(inputKey);
    table[index].circle = new Circle(radius);

    cout << "Element inserted successfully." << endl;
    cout << "Original hash index: " << originalIndex << endl;
    cout << "Stored at index: " << index << endl;
}

void DisplayElement(Node* table, int tableSize)
{
    if (table == nullptr)
    {
        cout << "You must create a hash table first." << endl;
        return;
    }

    string inputKey;

    cout << "Enter key to display: ";
    cin >> inputKey;

    int index = MyHasher(inputKey, tableSize);
    int originalIndex = index;
    int count = 0;

    while (table[index].key != nullptr && count < tableSize)
    {
        if (*(table[index].key) == inputKey)
        {
            cout << "\nElement found!" << endl;
            cout << "Original hash index: " << originalIndex << endl;
            cout << "Found at index: " << index << endl;
            cout << "Key: " << *(table[index].key) << endl;
            cout << "Radius: " << table[index].circle->getRadius() << endl;
            cout << "Area: " << table[index].circle->calculateArea() << endl;
            return;
        }

        index = (index + 1) % tableSize;
        count++;
    }

    cout << "Element not found." << endl;
}

int main()
{
    Node* hashTable = nullptr;
    int tableSize = 0;
    int choice;

    do
    {
        cout << "\n===== Hash Table Menu =====" << endl;
        cout << "1. Size a new hash table" << endl;
        cout << "2. Destroy current table" << endl;
        cout << "3. Insert an element" << endl;
        cout << "4. Display an element" << endl;
        cout << "5. Terminate application" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int numberOfElements;

            cout << "How many elements do you plan to enter? ";
            cin >> numberOfElements;

            DestroyTable(hashTable, tableSize);

            tableSize = NextPrime(2 * numberOfElements + 1);
            hashTable = new Node[tableSize];

            cout << "New hash table created." << endl;
            cout << "Table size: " << tableSize << endl;
            cout << "This keeps the load factor <= 0.5." << endl;

            break;
        }

        case 2:
            DestroyTable(hashTable, tableSize);
            break;

        case 3:
            InsertElement(hashTable, tableSize);
            break;

        case 4:
            DisplayElement(hashTable, tableSize);
            break;

        case 5:
            DestroyTable(hashTable, tableSize);
            cout << "Program terminated." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 5);

    return 0;
}
