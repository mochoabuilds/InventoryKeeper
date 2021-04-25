// ** PSUEDOCODE **

 // psuedocode for main()

// open partfile.dat
// do
// 	get main menu choice

// switch
// 	case add:		add_record
// 	case delete:	delete_record
// 	case change:	change_record
// 	case display:	display_file
// 	case quit:		quit program
// 	default:		display "Wrong Choice, Please Try Again"
// endswitch
// while( !quit )
// close partfile.dat


// psuedocode for add_record:

// get record number
// validate record number
// get rest of record data
// find record position in file
// if record does not exist
// 	write record onto file
// else 
// 	display "Part Already Exists"
// endif		


// psuedocode for delete_record:

// get record number
// validate record number 
// find and read record from file
// if record position is not occupied
// 	display "Record does not exist"
// else
// 	delete record from file
// endif


// psuedocode for change_record:

// get record number
// validate record 	
// find and record from file
// if record position is not occupied
// 	display "Record does not exist"
// else 
// 	display current record contents
// do 
// 	get change menu choice
// 	switch (change menu choice)
// 		case change q_o_h: 		get new q_o_h
// 		case change price: 		get price
// 		case quit and write:	write changed record onto file
// 		default:				display "invalid choice"
// 	endswitch
// while (!quit)


// psuedocode for display_file

// move to start of file
// display column headings
// for (rec_num = 1; rec_num <= 99; ++rec_num)
// 	read record
// 	if record is not empty
// 		print record
// 			increment record count
// 		endif	
// 	endfor	
// print record count


// ** change_record of a file in a records system **
//
// ** assumes an empty part records file already exists **


// PREPROCESSOR DIRECTIVES
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

// data type
struct Part_Record
{
    char    id_no[3];
    int     qoh;
    double  price;
};

// function prototypes
int Get_Menu_Choice();
void Add_Record(fstream&);
void Delete_Record(fstream&);
void Change_Record(fstream&);
int Get_Change();
void Display_File(fstream&);
bool Valid_Rec_Num(long);

// DEFINITION OF MAIN()
int main()
{
    int choice;
    bool quit = false;

    // helper functions
    cout << setprecision(2)
         << setiosflags(ios::fixed)
         << setiosflags(ios::showpoint);

    fstream part_file;

    Part_Record null_part = {" ", 0, 0.0};

    // open the file for reading to see if file exists
    part_file.open("partfile.dat", ios::in | ios::binary);

    // if file does not exist, display message and end program
    if (part_file.fail())
    {
        cerr << "Part File Does Not Exist" << endl;
        cerr << "Run Part File Creation Program" << endl;
        part_file.close();
        exit(1);
    }

    // close file
    part_file.close();

    // open file for both input and output
    part_file.open("partfile.dat", ios::in | ios::out | ios::binary);

    // processing loop

    do
    {
        choice = Get_Menu_Choice();
        switch (choice)
        {
            case 1:
                Add_Record(part_file); break;
            case 2:
                Delete_Record(part_file); break;
            case 3:
                Change_Record(part_file); break;
            case 4:
                Display_File(part_file); break;
            case 5:
                quit = true; break;
            default:
                cout << endl << endl;
                cout << "Wrong Choice. Please Try Again" << endl << endl; break;
        }
    }
    while (!quit);

    part_file.close();

    cout << endl;
    cout << "Program Ended" << endl;

    return 0;
}

int Get_Menu_Choice()
{
    int choice;
    cout << endl << endl;
    cout << "Main Menu" << endl << endl;
    cout << "1 - Add Record" << endl
         << "2 - Delete Record" << endl
         << "3 - Change Record" << endl
         << "4 - Display File" << endl
         << "5 - Quit Program" << endl << endl;

    cout << "Enter Choice: ";
    cin >> choice;

    return choice;
}

// End Get_Menu_Choice()

void Add_Record(fstream& file)
{
    Part_Record part;
    Part_Record temp_part;

    long rec_num;

    cin.get();

    cout << endl;
    cout << "Enter the data for a part:" << endl << endl;
    cout << "Part Number (01-99): ";
    cin.getline(part.id_no, 3);

    rec_num = atol(part.id_no);
    if ( !Valid_Rec_Num(rec_num) )
        return;

    cout << endl;
    cout << "Quantity On Hand: ";
    cin >> part.qoh;

    cout << endl;
    cout << "Price: ";
    cin >> part.price;

    file.seekg( (rec_num - 1) * sizeof(Part_Record), ios::beg);

    file.read( (char *)& temp_part, sizeof(Part_Record) );

    if ( strcmp(temp_part.id_no, " ") == 0) {
        file.seekg(-(long) sizeof(Part_Record), ios::cur);
        file.write((char *) &part, sizeof(Part_Record));
        cout << endl;
        cout << "Record " << part.id_no << " added to file." << endl;
        }
        else
        {
            cout << endl;
            cout << "Part already exists. Please make another selection." << endl;
    }
} // End of Add_Record

void Delete_Record(fstream& file)
{
    Part_Record part;
    Part_Record null_part = {" ", 0, 0.0};

    long rec_num;

    cout << endl;
    cout << "Enter the number of records to delete: ";
    cin >> rec_num;

    if (!Valid_Rec_Num(rec_num))
        return;

    file.seekg( (rec_num - 1) * sizeof(Part_Record), ios::beg);
    file.read( (char *) &part, sizeof(Part_Record) );

    if ( strcmp (part.id_no, " ") == 0)
    {
        cout << endl;
        cout << "The record does not exist. Please make another selection.";
    }
    else
    {
        file.seekg(-(long)sizeof(Part_Record), ios::cur);
        file.write( (char *) &null_part, sizeof(Part_Record) );
        cout << endl;
        cout << "Record " << rec_num << " deleted from file.";
    }
} // End of Delete_Record

void Change_Record(fstream& file)
{
    Part_Record part;
    long rec_num;
    int change;
    bool quit = false;

    cout << endl;
    cout << "Enter number of record to change: ";
    cin >> rec_num;

    if (!Valid_Rec_Num(rec_num))
        return;

    file.seekg( (rec_num - 1) * sizeof(Part_Record), ios::beg);
    file.read( (char *) &part, sizeof(Part_Record) );

    if ( strcmp(part.id_no, " ") == 0)
    {
        cout << endl;
        cout << "The record does not exist. Please make another selection.";
        return;
    }

    cout << endl;
    cout << "The current record contents are:" << endl << endl;
    cout << setw(20) << "Part Number"
         << setw(20) << "Quantity On Hand"
         << setw(20) << "Price" << endl << endl;
    cout << setw(20) << part.id_no
         << setw(20) << part.qoh
         << setw(20) << part.price << endl;

    do
    {
        change = Get_Change();
        switch (change)
        {
            case 1:
                cout << endl;
                cout << "Enter Quantity On Hand: ";
                cin >> part.qoh;
                break;
            case 2:
                cout << endl;
                cout << "Enter Price: ";
                cin >> part.price;
                break;
            case 3:
                quit = true;
                file.seekg(-(long)sizeof(Part_Record), ios::cur);
                file.write( (char *) &part, sizeof(Part_Record) );
                cout << endl;
                cout << "Change made to record" << rec_num;
                break;
            default:
                cout << endl;
                cout << "Wrong Choice. Try Again";
                break;
        }
    }
    while (!quit);
} // End of Change_Record()

int Get_Change()
{
    int change;

    cout << endl << endl;
    cout << "Change Menu" << endl << endl;
    cout << "1 - Change Quantity On Hand" << endl
         << "2 - Change Price" << endl
         << "3 - Write Changes and return to Main Menu" << endl << endl;
    cout << "Enter your choice: ";
    cin >> change;
} // End Get_Change()

void Display_File(fstream& file)
{
    Part_Record part;
    long rec_num;
    long rec_count = 0L;

    file.seekg( 0L, ios::beg);

    cout << endl;
    cout << setw(20) << "Part Number"
         << setw(20) << "Quantity On Hand"
         << setw(20) << "Price" << endl << endl;

    for (rec_num = 1L; rec_num <= 99L; ++rec_num)
    {
        file.read( (char *) &part, sizeof(Part_Record) );
        if (strcmp(part.id_no, " ") != 0)
        {
            cout << setw(20) << part.id_no
                 << setw(20) << part.qoh
                 << setw(20) << part.price << endl;
            ++rec_count;
        }
    }
    cout << endl << endl;
    cout << "File contains " << rec_count << " records" << endl;
} // End of Display_File()

bool Valid_Rec_Num(long rec_num)
{
    if ( rec_num < 1L || rec_num > 99L )
    {
        cout << endl << endl;
        cout << "ERROR: Wrong record number. Please try again." << endl;
        return false;
    }
    else
        return true;
} // End of Valid_Rec_Num()




