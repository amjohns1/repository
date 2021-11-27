#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct date
{
	unsigned int month;
	unsigned int day;
	unsigned int year;
};
// Define a structure for a student record. (Note that the Homework and Exams are arrays of numbers. 
// There are 7 homework scores and 3 exam scores.)
struct student_record
{
	string firstname;
	string lastname;		
    date birthdate;
    string year;
    string major;
	string ID;
	double exam_grades[7];
	double homework_grades[3];
	float grade;
    //insert link
    student_record *link;
	};
// Declare an array of student records to hold all the data from the file.
// Read in the student data from the file to initialize the array of student records.
const int RECORDS = 10;    


void print_data(student_record person);
void enter_data(student_record* root);
double get_average(double *array, int length);
void compute_grade(student_record person);
int main(void)
{
        ifstream infile;
        infile.open("/Users/adam/desktop/temp/student_records.txt");
       
        string line;
        student_record *student = new student_record; // Pointer to student_record type
       
        if (!infile)
        {
                cout << "Unable to open the student data file." << endl;
                return 1; // Error code for file open error
        }

        cout << "Student File opened." << endl;
        // Read and ingnore the first line of the file.
        // They are not data lines.

        getline(infile, line);
        
        
        // Read in the data for the first student
        infile >> student->firstname >> student->lastname >> student->birthdate.month 
                  >> student->birthdate.day >> student->birthdate.year
                   >> student->ID >> student->year >> student->major;
        
        for (int k = 0; k < 7; k++)
            infile >> student->homework_grades[k];
        
        for (int k = 0; k < 3; k++)
            infile >> student->exam_grades[k];     
        
        student_record *root=NULL, *new_node;
        
        // making first node
        root=student;
        student->link=NULL;
        
        
        // reading remaining 9 data and making node
        
        for(int i=0;i<9;i++)
        {
                student_record *new_node = new student_record;
                student_record *current_node=root;
                while(current_node->link)                                      // traversing till last so that we can add node there
                {
                        current_node=current_node->link;
                        }
                        
                        infile >> new_node->lastname >> new_node->firstname >> new_node->birthdate.month
                              >> new_node->birthdate.day >> new_node->birthdate.year        // reading data
                               >> new_node->ID >> new_node->year >> new_node->major;
                    
                    
                    for (int k = 0; k < 7; k++)
            		infile >> new_node->homework_grades[k];
        
        		    for (int k = 0; k < 3; k++)
           		    infile >> new_node->exam_grades[k];          
                       
                    current_node->link=new_node;       // adding node
                    new_node->link=NULL;
                    
                }
                
                
                // Printing
                
                
                student_record *current_node=root;
                while(current_node)
                {
                print_data(*current_node);
                
                current_node=current_node->link;
                }
        enter_data(root);
        return 0;
}

void enter_data(student_record *root)
{
    cout << "Enter first and last name." << endl;
    string firstname, lastname;
    cin >> firstname >> lastname;
    student_record* current_node = root;
    while (current_node != nullptr)
    {
        if (current_node->lastname == lastname && current_node->firstname == firstname)
        {
            cout << "Birthdate: " << current_node->birthdate.month << " " << current_node->birthdate.day << " " << current_node->birthdate.year << endl; 
            cout << "ID: " << current_node->ID << endl;
            cout << "Class: " << current_node->year << endl;
            cout << "Major: " << current_node->major << endl;
            for ( int k = 0; k < 1; k++)
            {
            cout << "Homeworks: " << current_node->homework_grades[k] << endl;
            }
            for ( int k = 0; k < 1; k++)
            {
            cout << "Exams: " << current_node->exam_grades[k] << endl;
            }
            break;
        }
        current_node = current_node->link;
    }
    return;
}

void print_data(student_record person)
{
        cout << endl;
        cout << fixed << setprecision(2) << left;
        cout << person.firstname << " " << person.lastname << endl;
        cout << setw(15) << "Birthdate: " << person.birthdate.month << " " << person.birthdate.day << " " << person.birthdate.year << endl; //error
        cout << setw(15) << "ID: " << person.ID << endl;
        cout << setw(15) << "Class: " << person.year << endl;
        cout << setw(15) << "Major: " << person.major << endl;
        for ( int k = 0; k < 1; k++)
        {
            cout << setw(15) << "Homework Average: " << person.homework_grades[k] << endl;
        }
        for (int k = 0; k < 1; k++)
        {
        cout << setw(15) << "Exam Average: " << person.exam_grades[k] << endl;
        }

        cout << right;
        return;
}
// Write a function that will compute the grade for a given student. 
// (Grade should be one of the members of the struct you define.)
// Grade = (average of homework) * 0.40 + (average of exams) * 0.60
// Note: Your program will have to calculate the homework average and the exam average.)
double get_average(double *array, int length)
{
    double sum = 0;
    double avg;
    for(int i=0; i<length; i++)
    {
        sum=sum + array[i];
    }
    avg = sum / length;
    return avg;
}


void compute_grade(student_record person)
{
	cout << "In function compute grade." << endl;
	cout << "Exams Average= " << get_average(person.exam_grades, 3) << endl;
	cout << "Homeworks Average= " << get_average(person.homework_grades, 7) << endl;
	person.grade = get_average(person.exam_grades, 3) * 0.40 + get_average(person.homework_grades, 7)  * 0.60;
	cout << "Grade = " << person.grade << endl;
	return;
}