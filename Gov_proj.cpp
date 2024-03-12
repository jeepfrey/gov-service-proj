// 2/23/2024 11:50 
// ^ Latest Date Change
// pre-processor directives
#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <sstream>
#include <limits>
#include <cctype>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int tin;
double monthly1Salary = 0;

bool validSalary(const string& input);
void Start_Menu();
void Main_Menu();
void registration();
void login();
void IncorrectLogin();
void register_profile();
void View_Profile();
void TIN();
double thirteenmonthpay(double salary);
double annual_salary(double salary);
double taxable_income(double ms);	
double tax_incomeTable(int choose, double ms, double thirteenmonthpay);
double regular_Tax(double monthly1Salary, double tmp, double TI, double AS);

struct Profile{
	string name, address, phone_number;
	double monthly1salary;
};

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
    cout << "[2] Generate Tin\n";
    cout << "[3] VIEW PROFILE\n";
    cout << "[4] LOG-OUT\n";
    cout << "Enter option: ";
    cin >> option;
    switch(option){
        case 1:
            regular_Tax(monthly1Salary, 0, 0, 0);
            break;
        case 2:
            TIN();
            break;
        case 3:
            View_Profile();
            break;
        case 4:
            Start_Menu();
            break;
    }
}

void registration(){
    system("cls"); // clss system terminal
    system("color 04");
    ofstream UsernameInput("Usernames.txt", ios::app); // opens Usernames text file to append user input 

    string Register_Username, RegisterPassword;
    bool valid = false;

    cin.ignore(1, '\n'); // clss input buffer/queue
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
    register_profile();
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
bool ValidSalary(const string& input) //This function checks if the input is a valid number
{   
    if (input.empty())
    {
        return false;
    }

    #include <algorithm>

    for (const char& ch : input) {
        if (!(isdigit(ch) || ch == '!' || ch == '@' || ch == '#' || ch == '$' || ch == '%' || ch == '^' || ch == '&' || ch == '*' || ch == '(' || ch == ')' || ch == '-' || ch == '+' || ch == '=' || ch == '_' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == ':' || ch ==';' || ch == '"' || ch == '<' || ch == '>' || ch == '?' || ch == '/' || ch == '|' || ch == '\\' || ch == ',' || ch == '.' || ch == '~' || ch == '`' || ch ==' ')) {
            return false;
        }
      
    }

    size_t decimalCount = count(input.begin(), input.end(), '.');
    return decimalCount <= 1;
}
void register_profile(){
	Profile profile;
	string user_Input;
	ofstream profile_input("profiles.txt", ios::app);
	
	cout << "Enter Your name: ";
	getline(cin, profile.name);
	
	cout << "Enter your Address: ";
	getline(cin, profile.address);
	
	cout << "Enter your Phone Number: ";
	getline(cin, profile.phone_number);
	
    do {
        cout << "Enter your Monthly Salary: ";
        getline(cin, user_Input);

        if (!ValidSalary(user_Input))
        {
            cout << "Invalid input! Please enter a valid number!" << endl;
        }
        else
        {
            istringstream(user_Input) >> profile.monthly1salary;
            break;
        }

    } while (true);

	
	profile_input << profile.name <<endl<< profile.address <<endl<< profile.phone_number <<endl<< profile.monthly1salary<<endl;
	profile_input.close();
    Main_Menu();
}

void View_Profile(){
    system("cls");
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

void TIN () //This function will display the TIN number and the details of the user
{
	int tin;
    srand(time(0));
	int tin1 = rand() % 1000 + 1; //Generates a random number for the TIN number
	int tin2 = rand() % 1000 + 1;
	int tin3 = rand() % 1000 + 1;

	cout << "Your TIN number is: " << tin1 << "-" << tin2 << "-" << tin3 << "-" << "00000" << endl;
	cout << "Please proceed to your nearest BIR office for further instructions." << endl;	
}
double thirteenmonthpay(double salary){
    if(salary > 90000)
    {
        double monthly_salary = salary - 90000;
        return monthly_salary;
    }
    else
    {
        double monthly_salary = 0;
        return monthly_salary;
    }
    return salary;
}
double annual_salary(double salary){
    int x = salary * 12;
    return x;
}
double taxable_income(double ms)
{
    const double sss = 1350;
    const double pagIbig = 100;
    const double philHealth = ms * 0.025;
    double monthlyTax = ms - (sss + pagIbig + philHealth);
    return monthlyTax;
}
double tax_incomeTable(int choose, double ms, double thirteenmonthpay) //This function represents the latest tax table from BIR
{
    double mS = ms;
    double MS = ms * 12 + thirteenmonthpay;
    switch(choose)
    {
        case 1:
            cout<<"Your monthly tax is: ";
            if (mS>=666667)
            {
                double x = ((ms - 666667) * 0.35) + 200833.33;
                return x;
            }
            else if (mS<=666666 && mS>=166667)
            {
                double x = ((ms - 166667 ) * 0.30) + 40833.33;
                return x;
            }
            else if (mS<=166667 && mS>= 66667)
            {
                double x = ((ms - 66667) * 0.25) + 10833.33;
                return x;
            }
            else if (mS<=66666 && mS>=33333)
            {
                double x = ((ms - 66666) * 0.20) + 2500;
                return x;
            }   
            else if (mS<=33332 && mS>=20833)
            {
                double x = ((ms - 33332) * 0.15);
                return x;
            }
            else 
            {
                cout<<"No withholding tax.";
                return 0;
            }
        case 2:
            cout<<"Your annual tax is: " << endl;
            if (MS>=8000000)
            {
                double x = ((MS - 8000000) * 0.35) + 2410000;
                return x;
            }
            else if (MS<=8000000 && MS>=2000000)
            {
                double x = ((MS - 2000000) * 0.32) + 490000;
                return x;
            }
            else if (MS<=2000000 && MS>=800000)
            {
                double x = ((MS - 800000) * 0.30) + 130000;
                return x;
            }
            else if (MS<=800000 && MS>=400000)
            {
                double x = ((MS - 400000) * 0.25) + 30000;
                return x;
            }
            else if (MS<=400000 && MS>=250000)
            {
                double x = ((MS - 250000) * 0.20);
                return x;
            }
            else
            {
                cout<<"No withholding tax.";
                return 0;
            }
    }
    return 0;
}
double regular_Tax(double monthly1Salary, double tmp, double TI, double AS)
{
    int choice;
    cout << "Choice:" << endl; // Asks for user choice
	cout << "1 - Monthly Tax" << endl;
	cout << "2 - Annual  Tax" << endl;
	do
	{
		cout << "Enter your choice: ";
		cin >> choice;
	} while (choice != 1 && choice != 2);
	tmp = thirteenmonthpay(monthly1Salary);
				
	TI = taxable_income(monthly1Salary);
				
	AS = annual_salary(monthly1Salary);
				
	cout << "\n"; //Displays output of the entire program
	cout << "Monthly Salary: " << monthly1Salary << endl;
	cout << "Your taxable monthly income is: " << TI << endl;
	cout << "Your annual salary: " << AS << endl;
	cout << tax_incomeTable(choice, monthly1Salary, tmp) << endl;
}