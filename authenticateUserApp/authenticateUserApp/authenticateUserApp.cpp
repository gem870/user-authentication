

#include <iostream>
#include <string>
#include <map>
#include <fstream>
using namespace std;

string  dortLine = "  ....................................... ",
longDashLesft = "---------------->>> ",
longDashRight = " <<<----------------",
shortDashLesft = "------>> ",
shortDashRight = " <<------",
greaterThan = ">> ",
lessThan = " <<",
shortStars = " ******************* ",
longStars = "*****************************************************************************",
longQualTo = "=========================================================",
shortSpace = "\t",
longSapce = "\t\t";

const string Database = "userAthenticationData.txt";
//---------------------------------- functions --------------------------------------------<

// --------> MENU
void displayMenu() {
	system("cls");
	cout << endl << endl;
	cout << longSapce << longStars << endl << endl;
	cout << longSapce << shortDashLesft << "                     USER AUTHENTICATION                   " << shortDashRight << endl;
	cout << longSapce << "                         Please choose the option below.    " << endl << endl;
	cout << longSapce << longStars << endl << endl;
	cout << longSapce << "                     LogIn                      >   .1" << endl << endl;
	cout << longSapce << "                     SignIn                     >   .2" << endl << endl;
	cout << longSapce << "                     Forgotten password         >   .3" << endl << endl;
	cout << longSapce << "                     Exit                       >   .4" << endl << endl;
	cout << longSapce << longSapce << dortLine << endl << endl;
	cout << ">>  Enter option number: ";
}

// ------------ TO CHECK ERROR INPUT
int validate() {
	int number;
	while (!(cin >> number)) {
		cout << " ......... ?? Invalid operation..!! " << endl;
		cout << shortDashLesft << " pls choose number from the option: ";
		cin.clear();
		cin.ignore(123, '\n');
	}
	return number;
}

//  ----------- SIGN-UP FUNCTION FOR USER REGISTERATION
void signin(map <string, string>& userDatabase) {

	string userID, password, comfirmPassword;

m:
	system("cls");
	cout << endl << endl;
	cout << longQualTo << endl;
	cout << "            >>     SIGN-IN SECTION      <<" << endl;
	cout << longQualTo << endl << endl;
	cout << ">> Enter your new user ID:    ";
	cin >> userID;
	if (userDatabase.find(userID) == userDatabase.end()) {
		cout << ">> Enter your password:  ";
		cin >> password;
		cout << ">> Pls comfirm password: ";
		cin >> comfirmPassword;
		if (password == comfirmPassword) {
			userDatabase[userID] = comfirmPassword;
			ofstream dataFile(Database, ios::app);
			if (dataFile.is_open()) {
				dataFile << userID << " " << password << endl;
				cout << "Registration successful!\n";
			}
			else {
				cerr << "Error: Unable to open file for writing.\n";
			}
			cout << endl;
			cout << ">>     ********* Registeration soccessfull.!! ********** " << endl << endl;
			system("PAUSE");
			return;
		}
		else
			cout << endl;
		cerr << ">>       ******** Password do not march. ********* " << endl;
		cout << "                      Try again !! " << endl << endl;
		system("PAUSE");
		
	}
	cout << endl << endl;
	cout << ">>       UserID is registered. Pls go and retreive your password.!!" << endl << endl;
	system("PAUSE");
	return;
}

// ------------ LOG IN FUNCTION
void login(map <string, string>& userDatabase) { // map with it key and value
	string userID, password; 
	system("cls");
	cout << endl << endl;
	cout << longQualTo << endl;
	cout << "            >>     LOGIN SECTION      <<" << endl;
	cout << longQualTo << endl << endl;
	cout << ">> Enter your user ID: ";
	cin >> userID;
	if (userDatabase.find(userID) != userDatabase.end()) { // tis check if the user is already existing
		cout << ">> Enter password: ";
		cin >> password;
		if (userDatabase.at(userID) == password) {
			cout << endl;
			cout << ">>              LOADING....!!        " << endl << endl;
			system("PAUSE");
			return;
		}
		else {
			cout << endl;
			cerr << ">>     ********  Password not correct.!! ******** " << endl << endl;
			cerr << ">>                     Try again.!! " << endl << endl;
			system("PAUSE");
			return;
		}
	
	}
	cout << endl;
	cerr << ">>     ********  UserID not registered. ******** " << endl << endl;
	cout << ">>      !!  Please go and register your user ID .. " << endl << endl;
	system("PAUSE");
	return;
}

// ------------ FUNCTION FOR RESTORING PASSWORD
void retrieve(map<string, string>& userDatabase) {
	system("clr");
	string userID;
	cout << endl << endl;
	cout << longQualTo << endl;
	cout << "            >>     Retrieve password      <<" << endl;
	cout << longQualTo << endl << endl;
	cout << ">> Enter your user ID: ";
	cin >> userID;
	if (userDatabase.find(userID) != userDatabase.end()) {
		cout << endl << endl;
		cout << ">>       This is your password: " << userDatabase.at(userID) << endl << endl;
		system("PAUSE");
		return;
	}
	cout << endl << endl;
	cout << ">>         User ID not found !! " << endl << endl;
	system("PAUSE");
	return;
}



int main()
{
	// --------- FILE UPLOAD TO MY USERDATABASE
	ifstream dataFile(Database);
	map<string, string> userDatabase;

	if (dataFile.is_open()) {
		string userID, password;
		while (dataFile >> userID >> password) {
			userDatabase[userID] = password;
		}
		dataFile.close();
	}
	else {
		cerr << "Warning: No user data file found. Creating a new one.\n"; // ERROR CHECK
	}

	int done = false;
	while (!done) {
		displayMenu();
		int choice = validate();
		switch (choice)
		{
		case 1:
			login(userDatabase); break;
		case 2:
			signin(userDatabase); break;
		case 3:
			retrieve(userDatabase); break;
		case 4:
			cout << endl << endl;
			cout << ">>        shoting down application..... " << endl;
			done = true; break;
		default:
			cout << endl << endl;
			cout << ">>   -------- Option invalide !! -------- " << endl;
			break;
		}
	}


	// SECTION THAT STORES USER ID AND PASSWORD TO THE FILE
	ofstream updatedDataFile(Database);
	if (updatedDataFile.is_open()) {
		for (const auto& entry : userDatabase) {
			updatedDataFile << entry.first << " " << entry.second << endl;
		}
		updatedDataFile.close();
	}
	else {
		cerr << "Error: Unable to update user data file.\n"; //ERROR CHECK
	}

	system("pause > null");
}

