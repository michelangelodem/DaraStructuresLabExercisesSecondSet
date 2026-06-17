#include <fstream>
#include <sstream>
#include "hashTable.h"
#include "BST.h"
#include "../Data/Mapper.h"

using namespace std;

void hashTableProcessing() 
{
    const string csvFilePath = "../../effects-of-covid-19-on-trade-at-15-december-2021-provisional.csv";
    HashTable HT;
    vector<Record> records = Mapper::fileToRecords(csvFilePath);
    
    for (const auto& rec : records) {
        HT.insert(rec);
    }
    
    int choice;
    Date searchDate;
    int day, month, year;
    long long cml;
    
    while (true) 
    {
        cout << "\nPress 1 for date search\n2 to edit a cumulative value\n3 to delete a record\n4 to exit\n";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "\nEnter date (day month year): ";
            cin >> day >> month >> year;
            searchDate = Date(day, month, year);
            HT.search(searchDate);
            break;
        case 2:
            cout << "\nEnter date (day month year): ";
            cin >> day >> month >> year;
            searchDate = Date(day, month, year);
            cout << "Enter new cumulative value for that date: ";
            cin >> cml;
            HT.update(searchDate, cml);
            break;
        case 3:
            cout << "\nEnter date (day month year) to delete: ";
            cin >> day >> month >> year;
            searchDate = Date(day, month, year);
            HT.deleteN(searchDate);
            break;
        case 4:
            return;
        default:
            cout << "Enter a valid choice.\n";
            break;
        }
    }
}

void bstProcessing() 
{
    BST tree;
    vector<Record> records = Mapper::fileToRecords("data.csv");
    
    for (const auto& rec : records) {
        tree.insert(rec);
    }
    
    int choice;
    Date searchDate;
    int day, month, year;
    long long newCml;
    
    while (true)
    {
        cout << "\nPress 1 for In-Order traversal\n2 to search cumulative values by date\n3 to update a record\n4 to delete a record\n5 to exit\n";
        cin >> choice;
        switch (choice) {
        case 1:
            tree.inOrder();
            break;
        case 2:
            cout << "\nEnter date (day month year): ";
            cin >> day >> month >> year;
            searchDate = Date(day, month, year);
            tree.search(searchDate);
            break;
        case 3:
            cout << "\nEnter date (day month year): ";
            cin >> day >> month >> year;
            searchDate = Date(day, month, year);
            cout << "\nEnter a new cumulative value:\n";
            cin >> newCml;
            tree.update(searchDate, newCml);
            break;
        case 4:
            cout << "\nEnter date (day month year) to delete: ";
            cin >> day >> month >> year;
            searchDate = Date(day, month, year);
            tree.deleteNode(searchDate);
            break;
        case 5:
            return;
        default:
            cout << "Enter a valid choice.\n";
            break;
        }
    }
}

void bstByCmlProcessing() 
{
    BST_cml tree;
    vector<Record> records = Mapper::fileToRecords("data.csv");
    
    for (const auto& rec : records) {
        tree.insert(rec);
    }
    
    int choice;
    while (true) 
    {
        cout << "\nPress 1 to find smallest cumulative date\n2 to find the greatest cumulative date\n3 to exit\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            tree.findMin();
            break;
        case 2:
            tree.findMax();
            break;
        case 3:
            return;
        default:
            cout << "\nEnter a valid option.\n";
        }
    }
}

int main()
{
    bool choice;    
    cout << "Process the file with BST (0) or HashTable(1)?";
    cin >> choice;
    if (choice==1)
    {
        hashTableProcessing();
    }
    else if (choice == 0)
    {
        cout << "Process tree by date(0) or by cumulative(1)?";
        int choice;
        cin >> choice;
        if (choice == 1)
            bstByCmlProcessing();
        else if (choice == 0)
            bstProcessing();
    }
}