#include<fstream>
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<process.h>
#include<dos.h>

using namespace std;
void intro() {
	cout<<"\n\t            ";
	cout<<"     Hotel Booking Management System";
	cout<<"\n°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°";
	cout<<"°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°";
	cout<<"||\t\t\t\t\t\t\t\t\t      ||";
	cout<<"||\t\t\t\t\t\t\t\t\t      ||";
	cout<<"||\t\t\t\t\t\t\t\t\t      ||";
	cout<<"||\t\t\t\t\t\t\t\t\t      ||";
	cout<<"||\t\t\t\t\t  \t\t\t\t      ||";
	cout<<"°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°";
	cout<<"°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°";
}
void head() {

	cout<<"\n°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°";
	cout<<"°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°";

}
void time() {
	int i=0;
	long long j;
	cout<<"	\n\n\n	Connecting to Server\n 	Syncing DaTa";
	while(i<10)	{
		for (j=5;j>4;j++) {
			if (j==99999) {
				cout<<".";
				break;
			}
		}
		++i;
	}
}

class hotel {
	private:
			int room_no;
			char name[30];
			char address[50];
			char phone[15];
			int days;
			float fare;
	public:
			void main_menu();		//to display the main menu
			void add();				//to book a room
			void display(); 		//to display the customer record
			void rooms();			//to display allotted rooms
			void edit();			//to edit the customer record
			int check(int);	     	//to check room status
			void modify(int);		//to modify the record
			void delete_rec(int);   //to delete the record
};


void hotel::main_menu() {
	int choice;
	while(choice!=5) {
        system("cls");
		head();
		cout<<"\n\t\t\t\t*************";
		cout<<"\n\t\t\t\t* MAIN MENU *";
		cout<<"\n\t\t\t\t*************";
		cout<<"\n\n\n\t\t\t1.Book A Room";
		cout<<"\n\t\t\t2.Customer Record";
		cout<<"\n\t\t\t3.Rooms Allotted";
		cout<<"\n\t\t\t4.Edit Record";
		cout<<"\n\t\t\t5.Exit";
		cout<<"\n\n\t\t\tEnter Your Choice: ";
		cin>>choice;
		switch(choice) {
			case 1:	add();
					break;
			case 2: display();
					break;
			case 3: rooms();
					break;
			case 4:	edit();
					break;
			case 5: break;
			default: {
				cout<<"\n\n\t\t\tWrong choice.....!!!";
				cout<<"\n\t\t\tPress any key to continue....!!";
				getch();
			}
		}
	}
}

void hotel::add() {
	head();
	int r,flag;
	ofstream fout("Record.dat",ios::app);
	cout<<"\n Enter Customer Details";
	cout<<"\n ----------------------";
	cout<<"\n\n Room no: ";
	cin>>r;
	fflush(stdin);
	flag=check(r);
	if(flag)
		cout<<"\n Sorry..!!!Room is already booked";
	else {
		room_no=r;
		cout<<" Name: ";
		gets(name);
		cout<<" Address: ";
		gets(address);
		cout<<" Phone No: ";
		gets(phone);
		cout<<" No of Days to Checkout: ";
		cin>>days;
		fare=days*20;

		fout.write((char*)this,sizeof(hotel));
		cout<<"\n Room is booked...!!!";
	}
	cout<<"\n Press any key to continue.....!!";
	getch();
	fout.close();
}

void hotel::display() {
    system("cls");
	head();
	ifstream fin("Record.dat",ios::in | ios::binary);
	int r,flag;
	cout<<"\n Enter room no: ";
	cin>>r;
	while(fin.read((char*)this,sizeof(hotel))) {
		if(room_no==r) {

			head();
			cout<<"\n Customer Details";
			cout<<"\n ----------------";
			cout<<"\n\n Room no: "<<room_no;
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<address;
			cout<<"\n Phone no: "<<phone;
			cout<<"\n Days: "<<days;
			cout<<"\n Total Fare: "<<fare;
			flag=1;
		}
	}
	if(flag==0)
		cout<<"\n Sorry Room no. not found or vacant....!!";
	cout<<"\n\n Press any key to continue....!!";
	getch();
	fin.close();
}

void hotel::rooms() {
    system("cls");
	head();
	ifstream fin("Record.dat",ios::in | ios::binary);
	cout<<"\n\t\t\t    List Of Rooms Allotted";
	cout<<"\n\t\t\t    ----------------------";
	while(fin.read((char*)this,sizeof(hotel))) {
		cout<<"\n Room no: "<<room_no<<"\n Name: "<<name;
		cout<<"\n Address: "<<address<<"\n Phone: "<<phone;
		cout<<"\n Days: "<<days<<"\n Total: "<<fare;
		cout<<"\n**********************************";
	}
	cout<<"\n\n\n\t\t\tPress any key to continue.....!!";
	getch();
	fin.close();
}

void hotel::edit() {
    system("cls");
	head();
	int choice,r;
	cout<<"\n EDIT MENU";
	cout<<"\n ---------";
	cout<<"\n\n 1.Modify Customer Record";
	cout<<"\n 2.Delete Customer Record";
	cout<<"\n Enter your choice: ";
	cin>>choice;

    system("cls");
	head();
	cout<<"\n Enter room no: " ;
	cin>>r;
	switch(choice) {
		case 1:	modify(r);
				break;
		case 2:	delete_rec(r);
				break;
		default: cout<<"\n Wrong Choice.....!!";
	}
	cout<<"\n Press any key to continue....!!!";
	getch();
}


int hotel::check(int r) {
	int flag=0;
	ifstream fin("Record.dat",ios::in);
	while(!fin.eof()) {
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r) {
			flag=1;
			break;
		}
	}
    system("cls");
	fin.close();
	return(flag);
}

void hotel::modify(int r) {
    system("cls");
	head();
	long pos,flag=0;
	fstream file("Record.dat",ios::in|ios::out|ios::binary);
	while(!file.eof()) {
		pos=file.tellg();
		file.read((char*)this,sizeof(hotel));
		fflush(stdin);
		if(room_no==r) {
			cout<<"\n Enter New Details";
			cout<<"\n -----------------";
			cout<<"\n Name: ";
			gets(name);
			cout<<" Address: ";
			gets(address);
			cout<<" Phone no: ";
			gets(phone);
			cout<<" Days: ";
			cin>>days;
			fare=days*900;
			file.seekg(pos);
			file.write((char*)this,sizeof(hotel));
			cout<<"\n Record is modified....!!";
			flag=1;
			break;
		}
	}
    system("cls");
	if(flag==0)
		cout<<"\n Sorry Room no. not found or vacant...!!";
	file.close();
}

void hotel::delete_rec(int r) {
    system("cls");
	head();
	int flag=0;
	char ch;
	ifstream fin("Record.dat",ios::in);
	ofstream fout("temp.dat",ios::out);
	while(!fin.eof()) {
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r) {
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<address;
			cout<<"\n Phone No: "<<phone;
			cout<<"\n Days: "<<days;
			cout<<"\n Total Fare: "<<fare;
			cout<<"\n\n Do you want to delete this record(y/n): ";
			cin>>ch;
			if(ch=='n')
				fout.write((char*)this,sizeof(hotel));
			flag=1;
			break;
		}
		else
			fout.write((char*)this,sizeof(hotel));
	}
    system("cls");
	fin.close();
	fout.close();
	if(flag==0)
		cout<<"\n Sorry room no. not found or vacant...!!";
	else {
		remove("Record.dat");
		rename("temp.dat","Record.dat");
	}
}

//MARK:- Main() Function Here =>

int main() {
	hotel h;

	cout<<"\n\n\n";
	intro();
	time();
	cout<<"\n\n\n\t\t\tPress any key to continue....!!";

	getch();

	head();
	char id[5],pass[7];
	cout<<"\n\n\t\t\t\tusername => ";
	cin>>id;
	cout<<"\n\t\t\t\tpassword => ";
	cin>>pass;
	cout<<"\n\n\t";
	time();
	cout<<"\t";
	if(strcmp(id,"admin")==0&&strcmp(pass, "admin")==0)
		cout<<"\n\n\t\t\t  !!!Login Successfull!!!";
	else {
		cout<<"\n\n\t\t\t!!!INVALID CREDENTIALS!!!";
		getch();
		exit(-1);
	}

	h.main_menu();
	getch();

	return 0;
}
