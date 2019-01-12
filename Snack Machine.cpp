//
//  Dalton_Serena_Asst11.cpp
//  
//
//  Created by Serena Dalton on 8/11/18.
//
//

#include <iostream>
#include <cctype>
#include <fstream>
#include <iomanip>

using  namespace std;

struct snackType
{
    string name;
    string code;
    double price;
    int remaining;
};


int readItems(ifstream&, snackType[]);
void outputItem(string, string, double);
string format(string);


const int MAX_ITEMS = 20;

int  main()
{
    char continueChar1;
    
    
    string fileName;
    cout << "Enter filename: "; //prompts user for file
    cin >> fileName;
    
    cout << endl;
    cout << "Welcome to the vending machine app!" << endl;
    cout << " " << endl;
    
    do //beginning of do/while loop
    {
        
        snackType snacks[MAX_ITEMS];
        
        ifstream userFile; //
        userFile.open(fileName.c_str());//opens user input file
        
        cout << endl;
        cout << "Item Name" << setw(20) << right << "Item Code" << setw(16) << right << "Price" << setw(20) << left << endl;
        
        int linecount = readItems(userFile, snacks); //variable for holding line count value
        
        cout << endl;
        cout << fixed << setprecision(2);
        readItems(userFile, snacks); //reads file into struct array
        
        
        for(int i = 0; i < linecount; i++) //checks if machine is empty, and exits program if so
        {
            if(snacks[i].remaining != 0)
                break;
            
            if(i == linecount - 1 && snacks[i].remaining == 0)
            {
                cout << "Vending machine is empty" << endl;
                return 0;
            }
        }
        
        for(int i = 0; i < linecount; i++)
        {
            if(snacks[i].remaining > 0) //prints only items with a snacks[i].remaining value greater than 0
            {
                outputItem(format(snacks[i].name), format(snacks[i].code), snacks[i].price);
            }
        }
        
        string userInput;
        cout << "Enter item code: ";//prompts user for item code
        cin >> userInput;
        
        for(int i = 0; i < linecount; i++)
        {
            if((format(snacks[i].code) == format(userInput)) && snacks[i].remaining > 0) //this runs if input is successful and there are items of that kind left
            {
                cout << "Good choice!" << endl;
                snacks[i].remaining = snacks[i].remaining - 1; //decrements amount of items left
                
                userFile.close();
                ofstream userFile; //ofstream variable
                userFile.open(fileName.c_str()); //opens file again to be read into
                
                for(int i = 0; i < linecount; i++) //reads back into file with same formatting
                {
                    userFile << snacks[i].name << " " << snacks[i].code << " " << snacks[i].remaining << " " << snacks[i].price << endl;
                }
                
                userFile.close(); //closes ofstream
                cout << "Continue? (Y/N): ";
                cin >> continueChar1; //prompts user for whether to continue
                
                break;
            }
            
            else if(i == linecount - 1 && (format(snacks[i].code) != format(userInput))) //runs when input fails
            {
                cout << "Item not found" << endl;
                cout << "Continue? (Y/N): ";
                cin >> continueChar1; //continue prompt
                
                userFile.close();
                
                ofstream userFile; //ofstream variable
                
                userFile.open(fileName.c_str()); //opens user file fileName
                
                for(int i = 0; i < linecount; i++) //reads into file from struct arrays
                {
                    userFile << snacks[i].name << " " << snacks[i].code << " " << snacks[i].remaining << " " << snacks[i].price << endl;
                }
                userFile.close();
                
                break;
            }
        }
        
        while(!(toupper(continueChar1) == 'N' || toupper(continueChar1) == 'Y')) //checks for valid continueChar1 variable and prompts accordingly
        {
            
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Continue? (Y/N): ";
            cin >> continueChar1;
        }
    }
    while(toupper(continueChar1) == 'Y'); //end of do/while loop
    
    return 0;
}






/******************************************
 FUNCTION NAME : readItems
 RETURN TYPE : int
 PARAMETERS : ifstream& userFile, string snackName[MAX_ITEMS]
 DESCRIPTION :
 This function reads a file into a set of struct arrays while counting the number of lines, and returns the number of lines.
 
 ******************************************/

int readItems(ifstream& userFile, snackType snacks[MAX_ITEMS])
{
    int count = 0;
    string line;
    
    while(!(userFile.eof()))
    {
        for(int i = 0; i < MAX_ITEMS; i++)
        {
            userFile >> snacks[i].name >> snacks[i].code >> snacks[i].remaining >> snacks[i].price;
            while(getline(userFile, line))
            {
                
                count++;
                break;
                
            }
        }
    }
    return count;
}



/******************************************
 FUNCTION NAME : outputItem
 RETURN TYPE : void
 PARAMETERS : string name, string itemCode, double price
 DESCRIPTION :
 
 This function outputs formatted strings and a double.
 ******************************************/


void outputItem(string name, string itemCode, double price)
{
    cout << name << setw(20) << left << itemCode << setw(20) << left << price << setw(20) << left << endl;
}



/******************************************
 FUNCTION NAME : format
 RETURN TYPE : string
 PARAMETERS : string str
 DESCRIPTION :
 
 This functions takes a string, capitalizes the first character, then makes the rest of string lowercase and returns it.
 ******************************************/

string format(string str)
{
    for(int i = 0; i < str.length(); i++)
    {
        if(i == 0)
            str[i] = toupper(str[i]);
        else
            str[i] = tolower(str[i]);
    }
    return str;
}









