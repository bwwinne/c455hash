// Bryce Winnecke C455 Homework 3

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility> 
#include <stdexcept> 
#include <sstream> 
using namespace std;

long createKeyForDiv(string s1, string s2) {
    long i1 = 0;
    long i2 = 0;

    for (size_t i = 0; s1[i] != '\0'; i++)
    {
        i1 += s1[i];
    }

    for (size_t i = 0; s2[i] != '\0'; i++)
    {
        i2 += s2[i];
    }

    return i1 * i2; // using multiplication here gave me less collisions when using division hashing function
}

long createKeyForMult(string s1, string s2) {
    long i1 = 0;
    long i2 = 0;

    for (size_t i = 0; s1[i] != '\0'; i++)
    {
        i1 += s1[i];
    }

    for (size_t i = 0; s2[i] != '\0'; i++)
    {
        i2 += s2[i];
    }

    return (i1 + i2) * 31; // multiplying by a prime number here gave me less collisions when using multiplication hashing function
}

vector<vector<string> > read_csv(string inputFileName) {

    vector<vector<string> > data;
    vector<string> array;
    ifstream inputFile(inputFileName);
    
    string line, field;
    string temp;

    vector<string> row;

    getline(inputFile, line); // clear header row

    while (getline(inputFile, line))    // get next line in file
    {
        row.clear();
        stringstream ss(line);

        int i = 0;
        string temp1;
        string temp2;
        while (getline(ss, field, ','))  // break line into comma delimitted fields
        {
            // use second and third columns to create key (state and county)
            if (i == 0) {
                temp1 = field;
            }
            else if (i == 2) {
                temp2 = field;
            }
            i++;
            row.push_back(field);  // add each field to the 1D array
        }
        long keyDiv = createKeyForDiv(temp1, temp2);
        row.push_back(to_string(keyDiv)); // push division key to position 37 of each row
        long keyMult = createKeyForMult(temp1, temp2);
        row.push_back(to_string(keyMult)); // push multiplication key to position 38 of each row

        data.push_back(row);  // add the 1D array to the 2D array
    }

    return data;
}

float loadFactor(vector<vector<string> > hashTable) {
    int T = hashTable.size();
    int keysStored = 0;

    for (size_t i = 0; i < T; i++)
    {
        if (!hashTable[i].empty()) {
            keysStored++;
        }
    }
    cout << "Elements stored in hash table: " << keysStored << endl;
    return (float)keysStored / (float)T; // load factor = n / T
}

long hashByDivision(long key, long T) {
    return key % T;
}

long hashByMultiplication(long key, long T) {
    float k = (float)key;
    float t = (float)T;
    float A = 0.6180339887;

    long result = floor(t * (fmod((k * A), 1)));

    return result;
}

vector<vector<string> > createHashTableByDiv(vector<vector<string> > data) {
    vector<vector<string> > table;
    long tableSize = data.size() * 7; // T = n * 2
    table.resize(tableSize);
    long key;
    long rowToInsert;
    int j;
    int collisions = 0;

    for (size_t i = 0; i < data.size(); i++)
    {
        key = stol(data[i][37]); // key at position 37 in each row, convert to long
        rowToInsert = hashByDivision(key, tableSize);

        if (table[rowToInsert].empty()) {
            table[rowToInsert] = data[i];
        }
        else {
            while (!table[rowToInsert].empty()) {
                if (rowToInsert >= tableSize) { // if we're at last element in table, roll over to 0
                    rowToInsert = 0;
                }
                else {
                    rowToInsert++; // else increment row until we find empty slot
                }
            }
            table[rowToInsert] = data[i]; // collision resolution by linear probing
            collisions++;
        }
    }

    cout << "Collisions while hashing by division: " << collisions << endl;
    cout << "Table size: " << table.size() << endl;
    cout << "Load factor while hashing by division: " << loadFactor(table) << endl;

    return table;
}

vector<vector<string> > createHashTableByMult(vector<vector<string> > data) {
    vector<vector<string> > table;
    long tableSize = data.size() * 3; // T = n * 2
    table.resize(tableSize);
    long key;
    long rowToInsert;
    int j;
    int collisions = 0;

    for (size_t i = 0; i < data.size(); i++)
    {
        key = stol(data[i][38]); // key at position 38 in each row, convert to long
        rowToInsert = hashByMultiplication(key, tableSize);

        if (table[rowToInsert].empty()) {
            table[rowToInsert] = data[i];
        }
        else {
            while (!table[rowToInsert].empty()) {
                if (rowToInsert >= tableSize) { // if we're at last element in table, roll over to 0
                    rowToInsert = 0;
                }
                else {
                    rowToInsert++; // else increment row until we find empty slot
                }
            }
            table[rowToInsert] = data[i]; // collision resolution by linear probing
            collisions++;
        }
    }

    cout << "Collisions while hashing by multiplication: " << collisions << endl;
    cout << "Table size: " << table.size() << endl;
    cout << "Load factor while hashing by multiplication: " << loadFactor(table) << endl;

    return table;
}



int main() {

    vector<vector<string> > data = read_csv("acs2015_county_data.csv");

    vector<vector<string> > hashTableD = createHashTableByDiv(data);
    cout << endl;
    vector<vector<string> > hashTableM = createHashTableByMult(data);

    return 0;
}

/*

Outputs:

///////////////////////////////////////////////////////

Collisions while hashing by division: 885
Table size: 22540
Elements stored in hash table: 3220
Load factor while hashing by division: 0.142857

Collisions while hashing by multiplication: 2647
Table size: 9660
Elements stored in hash table: 3220
Load factor while hashing by multiplication: 0.333333

///////////////////////////////////////////////////////

Using the collision resolution strategy of linear probing gave me mixed results on the hashing functions of division and multiplication. 
Creating the key using the 'state' and 'county' columns and multiplying them together gave me less collisions with the division method,
and adding them together then multiplying by a prime number gave me less collisions with multiplication hashing. Increasing the table 
size (thereby reducing the load factor) helped reduce collisions in both methods, but in multiplication I found diminishing returns after
increasing table size T above 3, and in division I found diminishing returns after increasing it above 7. In all the multiplication method
produced significantly more collisions with this input.

*/