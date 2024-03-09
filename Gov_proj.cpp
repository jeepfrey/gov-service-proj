// 2/23/2024 11:50 
// ^ Latest Date Change
// pre-processor directives
#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <stdlib.h>
using namespace std;

void Start_Menu();
void Main_Menu();
void registration();
void login();
void IncorrectLogin();
void register_profile();
void View_Profile();

struct Profile{
	string name, address, phone_number;
	double monthly_salary;
};

int main(){
    Start_Menu();

    return 0;
}

void Start_Menu(){ // Display Starting Menu
    system("clear");
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
    system("clear");
    system("color 03");
    int option;
    cout << "[1] TAX CALCULATOR\n";
    cout << "[2] TAX PAYMENT\n";
    cout << "[3] VIEW PROFILE\n";
    cout << "[4] LOG-OUT\n";
    cout << "Enter option: ";
    cin >> option;
    switch(option){
        case 3:
            View_Profile();
            break;
        case 4:
            Start_Menu();
            break;
    }
}

void registration(){
    system("clear"); // clears system terminal
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
            system("clear");
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
    register_profile();
}

void login(){ // Log-in Function
    system("clear");
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
                system("clear");
                cout << "Welcome " << UserName <<"!"<<endl;
                found = true;
            }
        }
    }  
    if (!found){
        system("clear");
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
            system("clear");
            system("color 04");
            cout << "\nPlease enter a valid option!\n";
            IncorrectLogin();
    }
}
void register_profile(){
	Profile profile;
	string user_input;
	ofstream profile_input("profiles.txt", ios::app);
	
	cout << "Enter Your name: ";
	getline(cin, profile.name);
	
	cout << "Enter your Address: ";
	getline(cin, profile.address);
	
	cout << "Enter your Phone Number: ";
	getline(cin, profile.phone_number);
	
	cout << "Enter your Monthly Salary: ";
	cin >> profile.monthly_salary;
	
	profile_input << profile.name <<endl<< profile.address <<endl<< profile.phone_number <<endl<< profile.monthly_salary<<endl;
	profile_input.close();
    Main_Menu();
}

void View_Profile(){
    system("clear");
	string output, tempfile2;
    int count = 0;
	ifstream profile_output("profiles.txt");
	while(getline(profile_output,output)){
        switch(count){
            case 0:
            cout << "Name: ";
            break;
            case 1:
            cout << "Address: ";
            break;
            case 2:
            cout << "Phone Number: ";
            break;
            case 3:
            cout << "Monthly Salary: ";
            break;
        }
        cout << output << endl;
        count ++;
	}
	profile_output.close();     
}

void TIN (int tin, string fullName, int age, string bday, string compAddress) //This function will display the TIN number and the details of the user
{
	srand(time(0));
	int tin1 = rand() % 1000 + 1; //Generates a random number for the TIN number
	int tin2 = rand() % 1000 + 1;
	int tin3 = rand() % 1000 + 1;

	cout << "Your TIN number is: " << tin1 << "-" << tin2 << "-" << tin3 << "-" << "00000" << endl;
	cout << "Your full name is :" << fullName << endl;
	cout << "Your age is: " << age << endl;
	cout << "Your birthday is: " << bday << endl;
	cout << "Your complete address is: " << compAddress << endl;
	cout << "Please proceed to your nearest BIR office for further instructions." << endl;	
}

void TINMenu (string fullName, int age, string bday, string compAddress, char prompt2) //This function will ask for the details of the user
{
	cout << "Welcome to the TIN Number Generator, please proceed with the required inputs below." << endl;
	cout << "Enter your full name: ";
	getline(cin,fullName);
	cout << "What is your age?: ";
	cin >> age;
	cout << "When is your birthday?: ";
	cin >> bday;
	cout << "What is your complete address?: ";
	cin >> compAddress;
	cout<<"Please double check your inputs before proceeding." << endl;
	cout <<"Are you sure?" << endl;
	cout <<"Y - Yes" << endl;
	cout <<"N - No" << endl;
	cin >> prompt2;
	if (prompt2 == 'Y' || prompt2 == 'y')
	{
		TIN(tin, fullName, age, bday, compAddress);
	}
	else if (prompt2 == 'N' || prompt2 == 'n')
	{
		system("clear");
		cout << "Please try again: \n" << endl;
		cin.ignore();
		TINMenu(fullName, age, bday, compAddress, prompt2);
	}
	else
	{
		cout << "Invalid input." << endl;
	}
}