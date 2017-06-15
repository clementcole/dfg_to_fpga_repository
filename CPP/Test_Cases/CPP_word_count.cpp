//C++ program to count number of words in text file

#include<fstream>
#include<iostream>
#include<string>
using namespace std;

int main()
{
    ifstream inFile; //Declares a file stream object
    string fileName;
    string word;
    int count = 0;

    cout << "Please enter the file name ";
    getline(cin,fileName);

    inFile.open(fileName.c_str());

    while(!inFile.eof())
    {               
        inFile >> word; 
        count++;
    }

    cout << "Number of words in file is " << count;
    inFile.close();

    cin.get();  
    return 0;
}