// pre-processor directives
#include <iostream> 
#include <fstream>
#include <sstream>
#include <windows.h>
#include <string>
#include <cctype>
#include <stdlib.h>
using namespace std;

void Start_Menu();
void Main_Menu();
void registration();
void login();
void IncorrectLogin();

int main(){
    Start_Menu();

    return 0;
}

void Start_Menu(){ // Display Starting Menu
    system("cls");
    system("color 03");
    int option;
    cout << "=================Program  Name=================\n"; // Name of Program
    cout << "[1] LOGIN\n";
    cout << "[2] REGISTRATION\n";
    cout << "[3] EXIT PROGRAM\n";
    cout << "Enter option: ";
    cin >> option;
    
    switch(option){
        case 1:
            login();
            break;
        case 2:
            registration();
            break;
        case 3:
            return;
        default:
            system("color 04");
            cout << "\nPlease enter a valid option!\n";
            system("color 03");
            Start_Menu();
    }
}

void Main_Menu(){ // Main Menu Display
    system("cls");
    system("color 03");
    int option;
    cout << "[1] TAX CALCULATOR\n";
    cout << "[2] TAX PAYMENT\n";
    cout << "[3] VIEW PROFILE\n";
    cout << "[4] LOG-OUT\n";
    cout << "Enter option: ";
    cin >> option;
    switch(option){
        case 4:
            Start_Menu();
            break;
    }
}

void registration(){
    system("cls"); // clears system terminal
    system("color 04");
    ofstream UsernameInput("Usernames.txt", ios::app); // opens Usernames text file to append user input 

    string Register_Username, RegisterPassword;
    bool valid = false;

    cin.ignore(1, '\n'); // clears input buffer/queue
    cout << "Register Username: ";
    getline(cin, Register_Username); // Registration for username

    UsernameInput << Register_Username << "\n"; // Input Username into the text file

    UsernameInput.close(); // closes Usernames text file

    ofstream PasswordInput("Passwords.txt", ios::app); // opens Passwords text file to append user input


    do{ // do-while loop for password criteria
        bool Capital = false, Number = false, WhiteSpace = false;

        cout << "Register Password: ";
        getline(cin, RegisterPassword);

        for (int i = 0; i < RegisterPassword.length(); i++) { 
            if (isupper(RegisterPassword[i])) {
                Capital = true; 
            }
            if (isdigit(RegisterPassword[i])) {
                Number = true; 
            }
            if (isspace(RegisterPassword[i])) {
                WhiteSpace = false; 
                break; 
            }
        } // password turns valid if it meets criteria
        if (Capital & Number & !WhiteSpace){
            system("cls");
            PasswordInput << RegisterPassword <<'\n';
            system("Color 03");
            cout << "\nSuccessfully registered " << Register_Username <<'!'<<endl;
            valid = true;
            break;
        }
        else{ // repeats loop if password is invalid
            system("Color 04"); // changes system terminal color
            cout << "Ensure that your password contains a capital letter, atleast one number, and no white spaces;\n";
        }
    }while(!valid);
    PasswordInput.close();
    Start_Menu();
}

void login(){ // Log-in Function
    system("cls");
    system("color 03");
    string UserName, UserPassword, UserComparison, PasswordComparison, UserData, PasswordData;
    bool found = false;

    ifstream users("Usernames.txt"), passwords("Passwords.txt"); // opens "Usernames" and "Passwords" text file for reading
    cin.ignore (1, '\n');
    cout << "\nUsername: ";
    getline(cin, UserName);

    cout << "Password: ";
    getline(cin, UserPassword);
    
    while(getline(users, UserData) && getline(passwords, PasswordData)){ // retrieves line from text file
        istringstream issUser(UserData), issPass(PasswordData); 
        while(issUser >> UserComparison && issPass >> PasswordComparison){ 
            if (UserName == UserComparison && UserPassword == PasswordComparison){ // Compares user input with text file data base
                system("cls");
                cout << "Welcome " << UserName <<"!"<<endl;
                found = true;
            }
        }
    }  
    if (!found){
        system("cls");
        system("color 04");
        cout << "\nUsername/Password not found!";
        IncorrectLogin();
    }
    else if(found){
        Main_Menu();
    }    
}

void IncorrectLogin(){ // If the user enters non-existent/incorrect credentials
    int option;
    cout <<"\n[1] Try Again?";
    cout <<"\n[2] Main Menu";
    cout <<"\nEnter choice: ";
    cin >> option;

    switch (option){
        case 1:
            login();
            break;
        case 2:;
            Start_Menu();
            break;
        default:
            system("cls");
            system("color 04");
            cout << "\nPlease enter a valid option!\n";
            IncorrectLogin();
    }
}