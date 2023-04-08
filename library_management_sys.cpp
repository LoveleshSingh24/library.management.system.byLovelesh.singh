#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
class Date
{
    int dd;
    int mm;
    int yy;
    void rectifyDate()
    {
        if (dd > 30)
        {
            dd -= 30;
            mm++;
        }
        if (mm > 12)
        {
            mm -= 12;
            yy++;
        }
    }

public:
    Date()
    {
        dd = 1;
        mm = 1;
        yy = 2018;
    }
    void setDate()
    {
        cout << "ENTER DATE : ";
        cin >> dd;
        cout << "ENTER THE MONTH : ";
        cin >> mm;
        cout << "ENTER THE YEAR : ";
        cin >> yy;
    }
    void setDate(Date temp)
    {
        dd = temp.dd + 15;
        mm = temp.mm;
        yy = temp.yy;
        rectifyDate();
    }
    void showDate()
    {
        cout << dd << "/" << mm << "/" << yy;
    }
};
class Menu
{
public:
    void mainMenu();
    void studentMenu();
    void bookMenu();
    void issueBook();
    void returnBook();
};
void Menu::mainMenu()
{
    cout << "%%%%%%%%%%%%%%%%%%%% MAIN MENU %%%%%%%%%%%%%%%%%%%%%" << endl
         << endl;
    cout << "1)STUDENT MENU\n2)BOOK MENU\n3)ISSUE BOOK\n4)RETURN BOOK" << endl;
    cout << "5)EXIT" << endl;
}
void Menu::studentMenu()
{
    cout << "%%%%%%%%%%%%%%%%%%%%% STUNDENT MENU %%%%%%%%%%%%%%%%%%%%" << endl
         << endl;
    cout << "1)NEW REGISTRATION\n2)MODIFY ENTRY\n3)SEARCH ENTERY\n4)DELETE ENTRY"
         << endl;
    cout << "5)VIEW STUDENT DETAILS\n6)GO BEACK TO MAIN MEMORY" << endl;
}
void Menu::bookMenu()
{
    cout << "%%%%%%%%%%%%%%%%%% BOOK MENU %%%%%%%%%%%%%%%%%%%%" << endl
         << endl;
    cout << "1. NEW ENTRY 2.MODIFY ENTRY 3.SEARCH ENTRY 4.DELETE ENTRY " << endl;
    cout << "5.VIEW ALL BOOK DETAILS 6.GO BACK TO PREVIOUS MENU " << endl;
}
class BookData
{
public:
    char title[30];
    char author[30];
    char publisher[30];
    int status;
    float price;
    int issueRollNo;
    Date issueDate;
    Date returnDate;
    BookData()
    {
        status = 0;
        issueRollNo = -99999;
    }
};
class StudentData
{
public:
    int rollNo;
    char name[30];
    char adress[50];
    char branch[50];
    int status;
    char bookTitle[30];
    StudentData()
    {
        status = 0;
    }
};
class Book
{
public:
    void inputDetails();
    void modifyDetails();
    void searchDetails();
    void deleteDetails();
    void viewAllDetails();
};
void Book::inputDetails()
{
    fstream ofp;
    ofp.open("bookDatabase.data", ios::out | ios::binary | ios::app);
    BookData book;
    cout << "ENTER BOOK TITLE : ";
    cin >> book.title;
    cout << "ENTER AUTHOR NAME : ";
    cin >> book.publisher;
    cout << "ENTER BOOK PUBLISHER : ";
    cin >> book.publisher;
    cout << "ENTER THE BOOK PRICE : ";
    cin >> book.price;
    ofp.write((char *)&book, sizeof(BookData)); ///////////
}
void Book::modifyDetails()
{
    fstream file;
    file.open("bookDatabse.dat", ios::binary | ios::in | ios::out | ios::ate);
    if (!file)
    {
        cout << "UNABLE TO OPEN FILE " << endl;
    }
    file.seekg(0, ios::beg);
    BookData book;
    char title[50];
    cout << "ENTER BOOK TITLE OF THE BOOK YOU WANT TO MODIFY : ";
    cin >> title[50];

    while (file.read((char *)&book, sizeof(BookData)))
    {
        if (strcmp(book.title, title) == 0)
        {
            int position = (-1) * sizeof(BookData);
            file.seekp(position, ios::cur);

            cout << "ENTER NEW BOOK TITLE : ";
            cin >> book.title;
            cout << "ENTER THE NEW AUTHOR NAME : ";
            cin >> book.author;
            cout << "ENTER THE NEW BOOK PUBLISHER : ";
            cin >> book.publisher;
            cout << "ENTER THE NEW BOOK PRIZE : ";
            cin >> book.price;

            cout << "RECORD UPDATED";
            cin.get();
            cin.get();
            return;
        }
    }
    cout << "BOOK NOT FOUND !";
    cin.get();
    cin.get();
    return;
}
void Book::searchDetails()
{
    fstream file;
    file.open("bookDatabase.dat", ios::in | ios::binary);
    if (!file)
    {
        cout << "UNABLE TO OPEN FILE ";
        cin.get();
        cin.get();
        return;
    }
    BookData book;
    char title[30];
    cout << "ENTER THE TITLE OF THE BOOK YOU WANT TO MODIFY : ";
    cin >> title;
    while (file.read((char *)&book, sizeof(BookData)))
    {
        if (strcmp(book.title, title) == 0)
            ;
        cout << "BOOK TITLE : " << book.title << endl;
        cout << "BOOK AUTHOR : " << book.author << endl;
        cout << "BOOK PUBLISHER : " << book.publisher << endl;
        cout << "BOOK PRIZE : " << book.price << endl;
        if (book.status == 1)
        {
            cout << "ISSUED STAUS : " << book.issueRollNo << endl;
            cout << "ISSUED DATE : ";
            book.issueDate.showDate();
            cout << endl;
            cout << "RETURN DATE : ";
            book.returnDate.showDate();
        }
        else
        {
            cout << "ISSUED STATUS : NONE " << endl;
        }
        cin.get();
        cin.get();
        return;
    }
    cout << "BOOK NOT FOUND " << endl;
    cin.get();
    cin.get();
    return;
}
void Book::deleteDetails()
{
    fstream file, temp;
    file.open("bookDatabase.dat", ios::binary | ios::in);
    temp.open("temp.dat", ios::binary | ios ::out);
    char title[25];
    BookData book;
    int flag = 0;

    cout << "ENTER THR TITLE OF REMOVE : ";
    cin >> title;
    while (file.read((char *)&book, sizeof(BookData)))
    {
        if (strcmp(book.title, title) == 0)
        {
            flag++;
            continue;
        }
        temp.write((char *)&book, sizeof(BookData));
    }
    file.close();
    temp.close();
    remove("bookDatabase.dat");
    rename("temp.dat", "bookDatabase.dat");

    if (flag == 1)
    {
        cout << "RECORD DELETED " << endl;
    }
    else
    {
        cout << "RECORD NOT FOUND " << endl;
    }
    cin.get();
    cin.get();
    return;
}
void Book::viewAllDetails()
{
    fstream file;
    file.open("bookDatabase.dat", ios::binary | ios::in);

    BookData book;
    int choice = 1;
    while (file.read((char *)&book, sizeof(BookData)) && choice)
    {
        system("clear");
        cout << "BOOK TITILE : " << book.title << endl;
        cout << "BOOK AUTHOR : " << book.author << endl;
        cout << "BOOK PULICHER : " << book.publisher << endl;
        cout << "BOOK PRICE : " << book.price << endl;
        if (book.status == 1)
        {
            cout << "ISSUED STATUS : " << book.issueRollNo << endl;
            cout << "ISSUED DATE : ";
            book.issueDate.showDate();
        }
        else
        {
            cout << "ISSUED STATUS : NONE " << endl;
        }
        cout << "PRESS 1 TO VIEW THE NEXT BOOK ELSE PRESS 0";
        cin >> choice;
    }
    cin.get();
    cin.get();
}
class Student
{
public:
    void inputDetails();
    void modifyDetails();
    void searchDetails();
    void deleteDetails();
    void viewAllStudentDetails();
};
void Student::inputDetails()
{
    fstream ofp;
    ofp.open("studentDatabase.dat", ios::out | ios::app | ios::binary);
    if (!ofp)
    {
        cerr << "UNABLE TO OPEN FILE " << endl;
        return;
    }
    StudentData student;
    cout << "ENTER STUDENT ROLL NO. : ";
    cin >> student.rollNo;
    cout << "ENTER STUDENT NAME : ";
    cin >> student.name;
    cout << "ENTER STUDENT BRANCH : ";
    cin >> student.branch;
    cout << "ENTER THE ADRESS : ";
    cin >> student.adress;

    cout << "RECORD ADDED TO DATABASE !";
    ofp.write((char *)&student, sizeof(StudentData));
    ofp.close();
}
void Student::modifyDetails()
{
    fstream fp;
    fp.open("studentDatabase.dat", ios::binary | ios::out | ios::ate);

    if (!fp)
    {
        cerr << "UNABLE TO OPEN FILE!!" << endl;
    }
    fp.seekg(0, ios::beg);
    int target;
    cout << "ENTER STUDNET ROLL NUM TO MODIFY";
    cin >> target;
    StudentData student;
    while (fp.read((char *)&student, sizeof(student)))
    {
        if (target == student.rollNo)
        {
            int position = (-1) * sizeof(StudentData);
            fp.seekp(position, ios::cur);
            cout << "ENTER STUDENT'S NEW ROLL NO. : ";
            cin >> student.rollNo;
            cout << "ENTER STUDENT'S NEW NAME : ";
            cin >> student.name;
            cout << "ENTER STUDENT'S NEW BRANCH : ";
            cin >> student.branch;
        }
        fp.write((char *)&student, sizeof(StudentData));
        fp.close();
        cout << "RECORD UPDATED" << endl;
        return;
    }
    cout << "ROLL NO. NOT FOUND " << endl;
    return;
}
void Student::searchDetails()
{
    fstream ifp;
    ifp.open("studentDatabase.dat", ios::in | ios::binary);
    if (!ifp)
    {
        cerr << "UNABLE TO OEPN FILE " << endl;
        return;
    }
    int target;
    cout << "ENTER THE ROLL NUMBER TO SEARCH : ";
    cin >> target;
    StudentData student;
    while (ifp.read((char *)&student, sizeof(student)))
    {
        if (target == student.rollNo)
        {
            cout << "RECORDS FOUND " << endl;
            cout << "STUDENT NAME : " << student.name << endl;
            cout << "STUDENT ROLL : " << student.rollNo << endl;
            cout << "STUDENT'S BRANCH " << student.branch << endl;
            cout << "STUDENT ADRESS " << student.adress << endl;
        }
        if (student.status == 1)
        {
            cout << "ISSUED BOOK NAME IS : " << student.bookTitle << endl;
        }
        else
        {
            cout << "NO BOOK ARE ISSUDE THIS ROLL NO.";
        }
        cin.get();
        cin.get();
        return;
    }
}
void Student::viewAllStudentDetails()
{
    system("clear");
    fstream ifp;
    ifp.open("studentDatabase.dat", ios::in | ios::binary);
    if (!ifp)
    {
        cerr << "UNABLE TO OPEN FILE " << endl;
    }
    StudentData student;
    int choice = 1;
    while (ifp.read((char *)&student, sizeof(student)) && choice)
    {
        system("clear");
        cout << "STUDENT NAME : " << student.name << endl;
        cout << "STUDENT ROLL NO " << student.rollNo << endl;
        cout << "STUDENT BRANCH : " << student.branch << endl;
        cout << "STUDENT ADDRESS : " << student.adress << endl;

        if (student.status == 1)
        {
            cout << "ISSUED BOOK NAME IS : " << student.bookTitle << endl;
        }
        else
        {
            cout << "NO BOOK IS ISSUED FOR THE ROLL NO. " << endl;
        }

        cout << "TO VIEW NEXT STUDENT PRESS 1 ELSE PRESS 0";
        cin >> choice;
    }
    return;
}
void Student::deleteDetails()
{
    fstream file;
    file.open("studentDatabase.dat", ios::in | ios::binary);
    fstream temp;
    temp.open("temp.dat", ios::out | ios::binary);
    StudentData student;
    int target;
    int flag = 0;
    cout << "ENTER THE ROLL NO. TO DELETE : ";
    cin >> target;
    while (file.read((char *)&student, sizeof(student)))
    {
        if (student.rollNo == target)
        {
            flag++;
            continue;
        }
        temp.write((char *)&student, sizeof(student));
    }
    file.close();
    remove("studentDatabase.dat");
    rename("temp.dat", "studentDatabase.dat");
    if (flag == 1)
    {
        cout << "RECORD DELETED " << endl;
    }
    else
    {
        cout << "Roll np. not found " << endl;
    }
    cin.get();
    cin.get();
    return;
}
void Menu::issueBook()
{
    fstream sp, bp;
    sp.open("studentDatabase.dat", ios::in | ios::ate | ios::ate | ios::binary);
    bp.open("bookDatabase.dat", ios::in | ios::out | ios::ate | ios::binary);
    bp.seekg(0, ios::beg);
    sp.seekg(0, ios::beg);

    int rollNo, flagS = 0, flagB = 0, position;
    char title[30];
    StudentData student;
    BookData book;
    cout << "ENTER STUDENT ROLL NO. TO ISSIE BOOK " << endl;
    cin >> rollNo;
    while (sp.read((char *)&student, sizeof(StudentData)))
    {
        if (student.rollNo == rollNo)
        {
            position = (-1) * sizeof(StudentData);
            sp.seekp(position, ios::cur);
            flagS++;

            break;
        }
    }
    if (flagS != 1)
    {
        cout << "RECORD NOT FOUND " << endl;
        cin.get();
        cin.get();
        sp.close();
        bp.close();
        return;
    }
    cout << "ENTER THE TITLE OF THE BOOK ";
    cin >> title;
    while (bp.read((char *)&book, sizeof(BookData)))
    {
        if (strcmp(book.title, title) == 0)
        {
            position = (-1) * sizeof(BookData);
            bp.seekp(position, ios::cur);
            flagB++;
            break;
        }
    }
    if (flagB != 1)
    {
        cout << "RECORDS NOT FOUND " << endl;
        cin.get();
        cin.get();
        sp.close();
        bp.close();
        return;
    }
    if (student.status != 1 && book.status != 1)
    {
        strcpy(student.bookTitle, title);
        student.status = 1;
        student.status = 1;
        book.issueRollNo = student.rollNo;
        book.issueDate.setDate();
        book.returnDate.setDate(book.issueDate);
        sp.write((char *)&student, sizeof(StudentData));
        bp.write((char *)&student, sizeof(StudentData));
        sp.close();
        bp.close();
    }
    else
    {
        if (student.status == 1)
        {
            cout << "STUDENT ACCOUNT IS ALREADY FILL" << endl;
            cin.get();
            cin.get();
            sp.close();
            bp.close();
            return;
        }
        else
        {
            cout << "BOOK IS ALREADY ISSUED " << endl;
            cin.get();
            cin.get();
            return;
        }
    }
}
void Menu::returnBook()
{
    fstream sp, bp;
    sp.open("studentDatabase.dat", ios::in | ios::out | ios::ate | ios::binary);
    sp.open("bookDatabase.dat", ios::in | ios::out | ios::ate | ios::binary);
    bp.seekg(0, ios::beg);
    sp.seekg(0, ios::beg);

    int rollNo, flagS = 0, flageB = 0, position;
    char title[30];
    StudentData student;
    BookData book;

    cout << "ENTER THE STUDENT ROLL NUMBER TO RETURN BOOK ";
    cin >> rollNo;
    while (sp.read((char *)&student, sizeof(StudentData)))
    {
        if (student.rollNo == rollNo)
        {
            position = (-1) * sizeof(StudentData);
            sp.seekp(position, ios::cur);
            flagS++;
            break;
        }
    }
    if (flagS != 1)
    {
        cout << "RECORDS NOT FOUNR " << endl;
        cin.get();
        cin.get();
        sp.close();
        bp.close();
        return;
    }
    while (bp.read((char *)&book, sizeof(BookData)))
    {
        if (strcmp(book.title, student.bookTitle) == 0)
        {
            position = (-1) * sizeof(BookData);
            bp.seekp(position, ios::cur);
            flageB++;
            break;
        }
    }
    if (flageB != 0)
    {
        cout << "RECORDS NOT FOUND " << endl;
        cin.get();
        cin.get();
        sp.close();
        sp.close();
        return;
    }
    if (student.status == 1 && book.status == 1)
    {
        student.status = 0;
        book.status = 0;
        book.issueRollNo = 9999;
        sp.write((char *)&student, sizeof(StudentData));
        bp.write((char *)&book, sizeof(BookData));
        sp.close();
        bp.close();
    }
    else
    {
        if (student.status == 0)
        {
            cout << "STUDENT ACCOUNT IS ALREADY FULL " << endl;
            cin.get();
            cin.get();
            sp.close();
            bp.close();
            return;
        }
        else
        {
            cout << "BOOK ID ALREADY ISUUED " << endl;
            cin.get();
            cin.get();
            sp.close();
            bp.close();
            return;
        }
    }
}
int main()
{
    Menu menu;
    int quite = 0;
    char choice[3];
    while (!quite)
    {
        system("clear");
        menu.mainMenu();
        cout << "PLEASE ENTER YOUR CHOICE : " << endl;
        cin >> choice;
        switch (atoi(choice))
        {
        case 1:
        {
            system("clear");
            menu.studentMenu();
            cout << "PLEASE ENTER YOUR CHOICE : " << endl;
            cin >> choice;
            Student s1;
            switch (atoi(choice))
            {
            case 1:
                s1.inputDetails();
                break;
            case 2:
                s1.modifyDetails();
                break;
            case 3:
                s1.searchDetails();
                break;
            case 4:
                s1.deleteDetails();
                break;
            case 5:
                s1.viewAllStudentDetails();
                break;
            case 6:
                break;

            default:
                cout << "WRONG INPUT RECEVIED " << endl;
            }
            break;
        }
        case 2:
        {
            system("clear");
            menu.bookMenu();
            cout << "PLEASE ENTER YOUR CHOICE :" << endl;
            cin >> choice;
            Book b1;
            switch (atoi(choice))
            {
            case 1:
                b1.inputDetails();
                break;
            case 2:
                b1.modifyDetails();
                break;
            case 3:
                b1.searchDetails();
                break;
            case 4:
                b1.deleteDetails();
                break;
            case 5:
                b1.viewAllDetails();
                break;

            case 6:
                break;

            default:
                cout << "WRONG INPUT RECIEVED " << endl;
            }
            break;
        }
        case 3:
            menu.issueBook();
            break;
        case 4:
            menu.returnBook();
            break;
        case 5:
            quite++;
            break;
        default:
            cerr << "PLEASE ENTER CORRECT INPUT " << endl;
            cin >> choice;
        }
    }
    return 0;
}