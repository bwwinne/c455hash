// c455hash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
//#include <math.h>
using namespace std;

string** read_csv(string inputFileName) {

    //vector<vector<string> > data;
    vector<string> array;
    ifstream inputFile(inputFileName);

    int rows = 3221;
    int cols = 36;
    
    string line, field;
    string** data = 0;
    data = new string*[rows];

    for (size_t i = 0; i < rows; i++)
    {
        data[i] = new string[cols];
        getline(inputFile, line);
        stringstream ss(line);
        for (size_t j = 0; j < cols; j++)
        {
            getline(ss, field, ',');
            data[i][j] = field;
        }
    }

    //while (getline(inputFile, line, '\n'))    // get next line in file
    //{
    //    row.clear();
    //    stringstream ss(line);

    //    while (getline(ss, field, ','))  // break line into comma delimitted fields
    //    {
    //        row.push_back(field);  // add each field to the 1D array
    //    }

    //    data.push_back(row);  // add the 1D array to the 2D array
    //}

    return data;
}

void printLine(int line, vector<vector<string> > data) {
    for (int i = 0; i < data[line].size(); i++)
    {
        cout << data[line][i] << " ";
    }
    cout << "\n";
}

int createKey(string s1, string s2) {
    int i1 = stoi(s1);
    int i2 = stoi(s2);

    return i1 * i2;
}

int hashByDivision(int key, int T) {
    return key % T;
}

int hashByMultiplication(int key, int T) {
    float k = (float)key;
    float t = (float)T;
    float A = 0.6180339887;

    int result = floor(t * (fmod(k * A, 1)));

    return result;
}

vector<vector<string> > createHashTable(vector<vector<string> > data) {
    data.erase(data.begin()); // delete header row

    return data;
}

int main() {

    string** data = read_csv("acs2015_county_data.csv");

    //cout << data.size() << "\n";
    //cout << data[0].size() << "\n";
    cout << data[0][0].size() << "\n";
    cout << data[0][0] << endl;
    cout << data[1][0] << endl;
    for (size_t i = 0; i < 36; i++)
    {
        for (size_t j = 0; j < 36; j++)
        {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
    //cout << data[1][0]; // index out of bounds error

    //printLine(0, data);
    //printLine(1, data);

    //data = createHashTable(data);
    //cout << data.at(0).size() << "\n";
    //printLine(0, data);
    //printLine(1, data);

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