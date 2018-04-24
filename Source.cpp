#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
#include<cctype>
#include<cstdlib>
#define maxnumber 100
using namespace std;

//function prototype
void initializeFile();
void loadFile();
void saveFile();
void inputData();
void listFruits(void);
void updateRecord(void);
void insertRecord(void);
void deleteRecord(void);
void sortFruit(void);
int instructions();

int idArray[maxnumber];
char nameArray[maxnumber][15];
char numberArray[maxnumber][11];
int counter;

int main(){

	int choice;
	//file stream used for input and output 
	ifstream file("Fruits.dat", ios::in);
	void(*f[])(void) = { listFruits, updateRecord, insertRecord, deleteRecord, saveFile };
	//terminate program if file cannot be opened
	if (!file){
		cout << "There is no file: Fruits.dat!\n";
		cout << "New file is initialize!\n";
		initializeFile();
	}

	else{
		file.close();
		loadFile();
		cout << "Data of Fruits.data is loaded!\n";
	}

	//perform user instructions until 5 is entered
	while ((choice = instructions() != 6))
		(*f[choice - 1])();
	saveFile();

	system("pause");
	return 0;
}
void initializeFile(){
	ofstream fRef("Fruits.dat", ios::out | ios::binary);
	counter = 0;
	int id = -1;
	char name[15] = "";
	char number[11] = "";

	//fill file with blank records
	for (int i = 0; i < maxnumber; i++){
		fRef.write(reinterpret_cast<char *>(&id), sizeof (id));
		fRef.write(reinterpret_cast<char *>(&name), sizeof (name));
		fRef.write(reinterpret_cast<char *>(&number), sizeof(number));
		idArray[i] = id;
		strcpy_s(nameArray[i], name);
		strcpy_s(numberArray[i], number);
	}
	fRef.close();
}
void saveFile(){
	fstream fRef("Fruits.dat", ios::out | ios::binary);
	
	for (int i = 0; i < maxnumber; i++){
		fRef.write(reinterpret_cast<char *>(&idArray[i]), sizeof(idArray[i]));
		fRef.write(reinterpret_cast<char *>(&nameArray[i]), sizeof(nameArray[i]));
		fRef.write(reinterpret_cast<char *>(&numberArray[i]), sizeof(numberArray[i]));
	}
	fRef.close();
}

int instructions(){
	int choice;
	//ask user to enter a choice
	cout << "\nEnter a choice:\n1 List all Fruits." << "\n2 Update Fruits.\n3 Insert fruits."
		<< "\n4 Delete fruit.\n5 Save fruit\n6 End program.\n";
	//ask user for choice until a valid choice is entered

	do{
		cout << "?";
		cin >> choice;
	} while (choice <1 || choice >6);
	return choice;
}
//function that lists fruits in file
void listFruits(void){
	cout << setw(7) << "Record#" << " " << left
		<< setw(18) << "Name" << left
		<< setw(13) << "FruitNumber" << endl;

	//continue until 100 fruits number are displayed
	for (int i = 0; i < maxnumber; i++){
		//if id is valid, displayed fruit information
		if (idArray[i]>0 && idArray[i] <= maxnumber){
			cout << fixed << showpoint;
			cout << left << setw(7) << idArray[i] << " "
				<< left << setw(18) << nameArray[i] << left
				<<setw(13) << numberArray[i] << '\n';
		}
	}
}
void updateRecord(void){
	int id;
	char name[15];
	char number[11];
	//ask user what record to update
	cout << "Update a fruit number\nEnter the fruit Record#for update:";
	cin >> id;

	//read information 
	//display fruit information if id is not-1
	if (( id > 1 ) && (id < maxnumber) && (idArray[id - 1] != -1)){
		cout << setw(7) << "Record#" << " " << left
			<< setw(18) << "Name" << left << setw(13) << "Phonenumber" << endl;
		cout << fixed << showpoint;
		cout << setw(7) << idArray[id - 1] << " " << left << setw(18) << nameArray[id - 1]
			<< "Enter the name: "; //ask user for the name

		cin.ignore(); ///ignore the newline on the input stream
		cin.getline(name, 15, '\n'); //set new name
		cout << "Enter the phone number: "; //ask for phone number
		cin.getline(number, 11, '\n'); //set new name

		strcpy_s(nameArray[id - 1], name);
		strcpy_s(numberArray[id - 1], number);

		cout << "Phone updated.\n";
		sortFruit();
	}

	else
		cerr << "Cannot update. The record is empty.\n";
}

//function to insert a new record
void insertRecord(void){
	char name[15];
	char number[11];
	int i = 0;
	//as long as record is empty get information from user
	while ((idArray[i] != -1) && (i < maxnumber))
		i++;

	if (i <= maxnumber){
		cout << "Insert a fruit number\nEnter the name: ";//ask user for name
		cin.ignore();//ignore the newline on the input stream
		cin.getline(name, 15, '\n');
		//ask user for new number 
		cout << "Enter the fruit number: ";//ask user for name
		cin.getline(number, 11, '\n');
		idArray[i] = i + 1;
		strcpy_s(nameArray[i], name);
		strcpy_s(numberArray[i], number);
		counter++;
		cout << "Fruit inserted.\n";
		sortFruit();
	}

	else
		cerr << "Cannot insert. The file is full.\n";
}
//function to delete a record
void deleteRecord(void){
	int id;
	//get fruit user wants to delete
	cout << "Delete a fruit number\nEnter the fruit Record# for deletion: ";
	cin >> id;

	//if record contain data, set record to an empty Tool object
	if ((id < 1) && (id < maxnumber) && (idArray[id - 1] != -1)){
		idArray[id - 1] = id;
		strcpy_s(nameArray[id - 1], nameArray[counter - 1]);
		strcpy_s(numberArray[id - 1], numberArray[counter - 1]);
		counter--;
		idArray[counter] = -1;
		strcpy_s(nameArray[counter], "");
		strcpy_s(numberArray[counter], "");

		cout << "Fruit deleted.\n";
		sortFruit();
	}

	else
		cerr << "Cannot delete. The record is empty.\n";
}
void sortFruit(void){
	char hold[15];
	//Bubble sort
	for (int pass = 0; pass < counter - 1; pass ++)
		//loop to control number of comparisons per pass
	for (int j = 0; j < counter - 1;j++)
		//compare side-by-side elements and swap them if
		//first element is great than second element
	if (strcmp(nameArray[j], nameArray[j + 1])>0){
		strcpy_s(hold, nameArray[j]);
		strcpy_s(nameArray[j], nameArray[j + 1]);
		strcpy_s(nameArray[j + 1], hold);

		strcpy_s(hold, numberArray[j]);
		strcpy_s(numberArray[j], numberArray[j + 1]);
		strcpy_s(numberArray[j + 1], hold);
	}

	cout << "Fruit sorted by name.\n";
	saveFile();
}









