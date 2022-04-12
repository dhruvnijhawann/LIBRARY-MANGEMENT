#include<iostream>
#include<string>
using namespace std;



class bookList
{
public:
    class bookNode
    {
        public:
        int serialNo;
        unsigned long long int isbn;
        string bookName;
        string author;
        bool issued=false;      
        bookNode *nextNode;     
        bookNode *prevNode;
    };
    bookNode *headNode=new bookNode();      
    bookNode *tailNode;                     
    bookNode *currentNode;                  
    bookNode *temp;                         
    class bookBorrower
    {
        public:
        unsigned long int ID;
        unsigned long int isbn;
        string personName;
        string bookName;
        bookBorrower *next;
        bookBorrower *prev;
    };
    bookBorrower *head=new bookBorrower();      
    bookBorrower *tail;                     
    bookBorrower *current;                 
    bookBorrower *tempp;                         
    int totalBooks=0;
    int totalBorrower=0;

public:

    void addBook(int srNo,unsigned long int isbN,string name,string auth)
    {
        currentNode=new bookNode();     

        currentNode->serialNo=srNo;
        currentNode->isbn=isbN;
        currentNode->bookName=name;
        currentNode->author=auth;
        currentNode->nextNode= nullptr;

        if(totalBooks==0)
        {

            headNode=currentNode;
            tailNode=currentNode;
            totalBooks++;
        }

        else{
            tailNode->nextNode=currentNode;
            currentNode->prevNode=tailNode;
            tailNode=currentNode;
            totalBooks++;
        }
    }
    void issueBook(unsigned long int isbN, unsigned long int borrower_id,string borrower_name)
    {
        temp=headNode;
        bool found= false;
        string book_name;
        for (int i = 0; i < totalBooks; ++i) {
            if (temp->isbn==isbN)
            {
                temp->issued=true;
                book_name=temp->bookName;
                found=true;
                break;
            }
            temp=temp->nextNode;
        }
        if (found==true)
        {
            current=new bookBorrower();
            current->ID=borrower_id;
            current->personName=borrower_name;
            current->isbn=isbN;
            current->bookName=book_name;
            if (totalBorrower==0)
            {
                head=current;
                tail=current;
                totalBorrower++;
            } else{
                tail->next=current;
                tail=current;
                totalBorrower++;
            }
            cout<<"\nBook Issued!!\n";
        }
        else{
            cout<<"\nBook not found!!\n";
        }
    }

    void issuedBooks()
    {
        tempp=head;
        for (int i = 0; i < totalBorrower; ++i) {
            cout<<"\n-----------------------------------------";
            cout<<"\nBorrower ID : "<<tempp->ID;
            cout<<"\nBorrower Name : "<<tempp->personName;
            cout<<"\nBook Borrowed : "<<tempp->bookName;
            cout<<"\nBook ISBN : "<<tempp->isbn;
            cout<<"\n-----------------------------------------";
            tempp=tempp->next;
        }
    }

    void depositBook(unsigned long int isbN)
    {
        tempp=head;
        bool found=false;
        for (int i = 0; i < totalBorrower; ++i) {
            if (tempp->isbn==isbN)
            {
                found=true;
                break;
            }
            tempp=tempp->next;
        }
        if(found==true){if (tempp==head)
        {
            head=head->next;
            delete tempp;
            totalBorrower--;
        } else{
            tempp->prev=current;
            current->next=tempp->next;
            delete tempp;
            totalBorrower--;
        }

        temp=headNode;
        for (int i = 0; i < totalBooks; ++i) {
            if (temp->isbn==isbN)
            {
                temp->issued= false;
            }
        }
        cout<<"\nBook Deposit Successful\n";
        }
        else{
            cout<<"\nBook not issued\n";
        }
        
    }

    void displayByAuthor(string authorName ){		
        temp=headNode;
        bool found= false;
        cout<<"\nBooks by Author "<<authorName;
        for (int i = 0; i < totalBooks; ++i) {
            if (temp->author==authorName)
            {
                found= true;
                cout<<"\n--------------------------------------------------";
                cout<<"\nSerial Number: "<<temp->serialNo;
                cout<<"\nISBN: "<<temp->isbn;
                cout<<"\nBook Name : "<<temp->bookName;
                cout<<"\nAuthor: "<<temp->author;
                cout<<"\nIssued? : "<<temp->issued;
                cout<<"\n--------------------------------------------------";
            }
            temp=temp->nextNode;
        }
        if (found== false)
        {
            cout<<"\nNo Book Found!!";
            cout<<"\n--------------------------------------------------";
        }
    }
    void searchByISBN(unsigned long int isbN){           	
        temp=headNode;
        bool found= false;
        cout<<"\nBook by ISBN "<<isbN;
        for (int i = 0; i < totalBooks; ++i) {
            if (temp->isbn==isbN)
            {
                found= true;
                cout<<"\n--------------------------------------------------";
                cout<<"\nSerial Number: "<<temp->serialNo;
                cout<<"\nISBN: "<<temp->isbn;
                cout<<"\nBook Name : "<<temp->bookName;
                cout<<"\nAuthor: "<<temp->author;
                cout<<"\nIssued? : "<<temp->issued;
                cout<<"\n--------------------------------------------------";
            }
            temp=temp->nextNode;
        }
        if (found== false)
        {
            cout<<"\nNo Book Found!!";
            cout<<"\n--------------------------------------------------";
        }
    }


    void display()
    {
        temp=headNode;
        for (int i = 0; i < totalBooks; ++i) {
            cout<<"\n--------------------------------------------------";
            cout<<"\nSerial Number: "<<temp->serialNo;
            cout<<"\nISBN: "<<temp->isbn;
            cout<<"\nBook Name : "<<temp->bookName;
            cout<<"\nAuthor: "<<temp->author;
            cout<<"\nIssued? : "<<temp->issued;
            cout<<"\n--------------------------------------------------\n";
            temp=temp->nextNode;
        }
    }

    void deleteBook(unsigned long int isbN)
    {
        temp=headNode;
        bool found=false;
        for (int i = 0; i < totalBooks; ++i) {
            if (temp->isbn==isbN)
            {
                found=true;
                break;
            }
            temp=temp->nextNode;
        }
        if (found)
        {
            if (temp==headNode)
            {
                headNode=headNode->nextNode;
                delete temp;
            } else{
                currentNode=temp->prevNode;
                currentNode->nextNode=temp->nextNode;
                delete temp;
            }
            totalBooks--;
            cout<<"\nBook Deleted!!";
        }
        else
        {
            cout<<"\nBook not Found!!";
        }
    }
};


void mainMenu(bookList ls)
{
    int choice,srno=0;
    unsigned long int id,isbn;
    string bookName,author,borrowerName;
    cout<<"\n\n-------------------------WELCOME TO LIBRARY MANAGMENT SYSTEM----------------------------\n\nCreated by Dhruv Nijhawan and Devansh Garg\n";
    cout<<"\n What task do you want to perform ? \n\n";
    cout<<"1: Insert a book\n";
    cout<<"2: Issue a book\n";
    cout<<"3: Deposit a book\n";
    cout<<"4: Search a book by Author\n";
    cout<<"5: Search a book by ISBN\n";
    cout<<"6: Delete a book\n";
    cout<<"7: Display all books\n";
    cout<<"8: Display issued books\n";
    cout<<"9: Exit\n\n";
    cout<<"-----------------------------------------------------------------------------------------\n\n";
    loop:cin>>choice;
    switch (choice) {
        case 1:
            srno++;
            cout<<"Enter ISBN of Book: ";
            cin>>isbn;
            cout<<"Enter Name of Book: ";
            getline(cin ,bookName);
            getline(cin ,bookName);
            cout<<"Enter name of Author of Book: ";
            getline(cin,author);
            ls.addBook(srno,isbn,bookName,author);
            cout<<"\nBook Added!!\n";
            mainMenu(ls);
            break;
        case 2:
            cout<<"Enter borrower ID: ";
            cin>>id;
            if(id>100){
                cout<<"\nwrong id!\n";
                mainMenu(ls);
                break;
            }
            else{
            cout<<"Enter borrower name: ";
            cin>>borrowerName;
            cout<<"Enter ISBN of Book to borrow: ";
            cin>>isbn;
            ls.issueBook(isbn,id,borrowerName);
            cout<<"\n";
            mainMenu(ls);
            break;
            }
        case 3:
            cout<<"Enter ISBN of Book to deposit: ";
            cin>>isbn;
            ls.depositBook(isbn);
            cout<<"\n";
            mainMenu(ls);
            break;
        case 4:
            cout<<"Enter Author Name: ";
            cin>>author;
            ls.displayByAuthor(author);
            mainMenu(ls);
            break;
        case 5:
            cout<<"Enter ISBN: ";
            cin>>isbn;
            ls.searchByISBN(isbn);
            mainMenu(ls);
            break;
        case 6:
            cout<<"Enter ISBN to delete a book: ";
            cin>>isbn;
            ls.deleteBook(isbn);
            mainMenu(ls);
            break;
        case 7:
            ls.display();
            mainMenu(ls);
            break;
        case 8:
            ls.issuedBooks();
            mainMenu(ls);
            break;
        case 9:
            cout<<"\nExited successfully\n";
            cout<<"\nHOPEFULLY YOU LIKED IT\n\n";
            exit(0);
        default:
            cout<<"\nWrong Value Entered Please try again!!\n";
            goto loop;

    }
}

int main()
{
    bookList l1;
    mainMenu(l1);
}

