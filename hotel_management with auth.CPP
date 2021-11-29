#include<iostream.h>
#include<dos.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
#include<process.h>
void Menu();
void Menu1();
void customers();
void rooms();
void employees();
void foodings();
void members();
void regster();
void login();
void bypass();
char first_name[15],last_name[15];
int a=1;
class room
{
private:
int roomno;
char category[10];
int roomprice;
public:
int roomstatus;
room()
{
	roomstatus=0;
}
void getroom()
{
	cout<<"\nEnter the Room No.:";
	cin>>roomno;
	cout<<"\nEnter the Category of Room:";
	gets(category);
	cout<<"\nEnter the Rent of Room:";
	cin>>roomprice;
}
void showroom()
{
	cout<<"\nRoom no.: ";
	cout<<roomno;
	cout<<"\nRoom Type: ";
	cout<<category;
	cout<<"\nRoom Rent: ";
	cout<<roomprice;
	cout<<"\nRoom Status: ";
	if(roomstatus==0)
	cout<<"Not Booked";
	else
	cout<<"Booked";
}
int rmno()
{
	return roomno;
}
};
void write_room()
{       char ch;
	room ro;
	ofstream outFile;
	outFile.open("room.dat",ios::binary|ios::app);
	ro.getroom();
	outFile.write((char*)&ro,sizeof(room));
	outFile.close();
	cout<<"\nRoom record Has Been Created ";
	do{
	cout<<"\n\nPress y to go back and n for Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	rooms();
	}
	else if(ch=='n'|| ch=='N')
	     {
	     Menu();
	     }
	     else
	     {
		cout<<"\nWrong Input........."<<endl;
	     }
	}while(ch=='y'||ch=='Y'||ch=='n'||ch=='N');
}
void display_room()
{       char ch;
	room ro;
	ifstream inFile;
	inFile.open("room.dat",ios::binary);
	if(!inFile)
	{
		cout<<"\nFile not  found in the Database !!!";
		cout<<"\nPlease Add Atleast 1 Room's Detail";
		delay(55000);
		rooms();
	}
	cout<<"\n\t\t!!! DISPLAY ALL RECORD !!!\n";
	while(inFile.read((char*)&ro,sizeof(room)))
	{
		ro.showroom();
		cout<<"\n====================================";
	}
	inFile.close();
	D:cout<<"\n\nPress y to go back and n for Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	rooms();
	}
	else if(ch=='n'|| ch=='N')
	      {
	      Menu();
	      }
	      else
	      {
		cout<<"\nWrong Input........."<<endl;
		goto D;
	      }
}
void modify_room(int n)
{       char ch;
	int found = 0;
	room ro;
	fstream File;
	File.open("room.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"\nFile not found in the Database !!!";
		cout<<"\nPlease Add Add Atleast 1 Room's Detail";
		delay(55000);
		rooms();
	}
	while(!File.eof() && found==0)
	{

		File.read((char*)&ro,sizeof(room));
		if(ro.rmno()==n)
		{
			ro.showroom();
			cout<<"\n\nPlease Enter The New Details of Room"<<endl;
			ro.getroom();
			int pos=(-1)*(int)(sizeof(ro));
			File.seekp(pos,ios::cur);
			File.write((char*)&ro,sizeof(room));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}
	File.close();
	if(found==0)
	cout<<"\n\n Record Not Found ";
	E:cout<<"\n\nPress y to go back and n for Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	rooms();
	}
	else if(ch=='n'|| ch=='N')
	     {
	      Menu();
	     }
	     else
		{
		cout<<"\nWrong Input........."<<endl;
		goto E;
		}
}
void delete_room(int n)
{        char ch,cnfrm;
	room ro;
	ifstream inFile;
	inFile.open("room.dat",ios::binary);
	if(!inFile)
	{
		cout<<"\nFile not found in the Database !!!";
		cout<<"\nPlease Add Atleast 1 Room's Detail";
		delay(55000);
		rooms();
	}
	while(inFile.read((char*)&ro,sizeof(room)))
	{    if(ro.rmno()==n && ro.roomstatus==1)
	     {
	     cout<<"\n!! Sorry this Room can't be Deleted Because it is Booked !!";
	     cout<<"\nPress any key to Proceed...";
	     cin>>ch;
	     rooms();
	     }
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char*)&ro,sizeof(room)))
	{
	      if(ro.rmno()!=n)
		{
			outFile.write((char*)&ro,sizeof(room));
		}
	       else
		ro.showroom();
	}
	cout<<"\nAre you sure want to delete the above record (y/n)";
	cin>>cnfrm;
	if(cnfrm=='y'||cnfrm=='Y')
	{
	outFile.close();
	inFile.close();
	remove("room.dat");
	rename("Temp.dat","room.dat");
	cout<<"\n\n\tRecord Deleted ..";
	}
	else
	{
	cout<<"\nDeletion aborted!!!!!!!!!!";
	cout<<"\nPress any key to proceed";
	cin>>cnfrm;
	rooms();
	}
	F:cout<<"\n\nPress y to go back and n for Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	rooms();
	}
	else if(ch=='n'|| ch=='N')
	      {
		Menu();
	      }
	      else
	      {
	      cout<<"\nWrong Input........."<<endl;
	      goto F;
	      }
}

void rooms()
{
char ch;
int num;
clrscr();
cout<<"\t\t**************************************************\n";
cout<<"\t\t*                  DO YOU WANT TO                *\n ";
cout<<"\t\t**************************************************\n\n\n\n";
cout<<"\n\t\t\t\t1. Add New Room ";
cout<<"\n\t\t\t\t2. View Room ";
cout<<"\n\t\t\t\t3. Edit Room ";
cout<<"\n\t\t\t\t4. Delete Room ";
cout<<"\n\t\t\t\t5. Back to Category Menu";
cout<<"\n\n\n\n\n\t\t\t\tEnter your choice ";
cin>>ch;
system("cls");
switch(ch)
	{
	case '1':write_room(); break;
	case '2':display_room(); break;
	case '3':cout<<"\nPlease Enter Room No. to Edit: ";
		 cin>>num;
		 modify_room(num);break;
	case '4':cout<<"\nPlease Enter Room No. to Delete: ";
		 cin>>num;
		 delete_room(num);break;
	case '5':if(a==0)
		 {
		   Menu();
		 }
		 else
		 Menu1();
	}
}



class customer
{
private:
int sno;
char name[20];
char contactno[15];
int age;
char sex[7];
char aadharno[15];
int clength;
int alength;
public:
int room_no;
customer()
{
clength=0;
alength=0;
}
void getcust()
	{
	cout<<"\nEnter the Seriol no. Customer:";
	cin>>sno;
	cout<<"\nEnter the Name of Customer:";
	gets(name);
	cout<<"\nEnter the Gender of Customer:";
	gets(sex);
	cout<<"\nEnter the Age of Customer:";
	cin>>age;
	cout<<"\nEnter the Contact no. of Customer:";
	gets(contactno);
	while(clength!=10)
	{
	clength=strlen(contactno);
	if(clength!=10)
	{
	cout<<"\nPlease Provide the Correct Contact No.";
	gets(contactno);
	}
	else
	break;
	}
	cout<<"\nEnter the Aadhar No. of Customer:";
	gets(aadharno);
	while(alength!=12)
	{
	alength=strlen(aadharno);
	if(alength!=12)
	{
	cout<<"\nPlease Provide the Correct Aadhar No.";
	gets(aadharno);
	}
	else
	break;
	}
	cout<<"\nEnter the Room No. for Customer:";
	cin>>room_no;
	}
void showcust()
	{
	cout<<"\nSno: ";
	cout<<sno;
	cout<<"\nName: ";
	cout<<name;
	cout<<"\nGender: ";
	cout<<sex;
	cout<<"\nAge: ";
	cout<<age;
	cout<<"\nContact No.: ";
	cout<<contactno;
	cout<<"\nAadhar No.: ";
	cout<<aadharno;
	cout<<"\nRoom No.: ";
	cout<<room_no;
	}
int getSno()
{
return sno;
}
};
void roomcheck(int n)
 {
	int found=0;
	char ch,cnfrm;
	room ro;
	customer cu;
	fstream inFile;
	inFile.open("room.dat",ios::binary|ios::in|ios::out);
	if(!inFile)
	{
		cout<<"\nFile not found in the Database !!!";
		cout<<"\nPlease Add Atleast 1 Room's Detail";
		delay(55000);
		rooms();
	}
	while(!inFile.eof() && found==0)
	{
		inFile.read((char*)&ro,sizeof(room));
		if(ro.rmno()==n)
		{
			if(ro.roomstatus==0)
			{
				cout<<"\nThis Room is available.....";
				cout<<"\nPress (y) to Allocate this Room: ";
				cin>>cnfrm;
				if(cnfrm=='y'||cnfrm=='Y')
				{
					cu.room_no=ro.rmno();;
					ro.roomstatus=1;
				}
				else
				{
					cout<<"Process Aborted";
					delay(50000);
					customers();
				}
			int pos=(-1)*(int)(sizeof(ro));
			inFile.seekp(pos,ios::cur);
			inFile.write((char*)&ro,sizeof(room));

			}
			else
			{
			cout<<"Sorry!!!!!! This Room is already Booked";
			cout<<"\nPress any key to Proceed";
			cin>>ch;
			customers();
			}
		    found=1;
		}
	}
	if(ro.rmno()!=n)
		{
		cout<<"\n!!! This specific Room No. not Present !!!! ";
		cout<<"\nPlease Add this Room's Detail";
		delay(60000);
		customers();
		}

	inFile.close();
	if(found==0)
	cout<<"\nRoom Not Found";
 }
void write_cust()
{       char ch;
	customer cu;
	ofstream outFile;
	outFile.open("customer.dat",ios::binary|ios::app);
	cu.getcust();
	roomcheck(cu.room_no);
	outFile.write((char*)&cu,sizeof(customer));
	outFile.close();
	cout<<"\nCustomer record Has Been Created ";
	do{
	cout<<"\n\nPress y to go back and n for Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	customers();
	}
	else if(ch=='n'|| ch=='N')
	     {
	     Menu();
	     }
	     else
	     {
		cout<<"\nWrong Input........."<<endl;
	     }
	}while(ch=='y'||ch=='Y'||ch=='n'||ch=='N');
}
void display_cust()
{       char ch;
	customer cu;
	ifstream inFile;
	inFile.open("customer.dat",ios::binary);
	if(!inFile)
	{
		cout<<"\nFile not found in the Database !!! ";
		cout<<"\nPlease Add Atleast 1 Customer's Detail";
		delay(55000);
		customers();
	}
	cout<<"\n\t\t!!! DISPLAY ALL RECORD !!!\n";
	while(inFile.read((char*)&cu,sizeof(customer)))
	{
		cu.showcust();
		cout<<"\n====================================";
	}
	inFile.close();
	D:cout<<"\n\nPress y to go back and n for Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	customers();
	}
	else if(ch=='n'|| ch=='N')
	      {
	      Menu();
	      }
	      else
	      {
		cout<<"\nWrong Input........."<<endl;
		goto D;
	      }
}
void modify_cust(int n)
{       char ch;
	int found = 0;
	customer cu;
	fstream File;
	File.open("customer.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"\n!!! File not found in the Database !!!";
		cout<<"\nPlease Add Atleast 1 Customer's Detail";
		delay(55000);
		customers();
	}
	while(!File.eof() && found==0)
	{

		File.read((char*)&cu,sizeof(customer));
		if(cu.getSno()==n)
		{
			cu.showcust();
			cout<<"\n\nPlease Enter The New Details of Customer"<<endl;
			cu.getcust();
			int pos=(-1)*(int)(sizeof(cu));
			File.seekp(pos,ios::cur);
			File.write((char*)&cu,sizeof(customer));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}
	File.close();
	if(found==0)
	cout<<"\n\n Record Not Found ";
	E:cout<<"\n\nPress y to go back and n for Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	customers();
	}
	else if(ch=='n'|| ch=='N')
	     {
	      Menu();
	     }
	     else
		{
		cout<<"\nWrong Input........."<<endl;
		goto E;
		}
}
void delete_cust(int n)
{	char ch,cnfrm;
	int found=0;
	room ro;
	customer cu;
	ifstream inFile;
	inFile.open("customer.dat",ios::binary);
	if(!inFile)
	{
		cout<<"\nFile not found in the Database !!!";
		cout<<"\nPlease Add Atleast 1 Customer's Detail";
		delay(55000);
		customers();
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char*)&cu,sizeof(customer)))
	{
		if(cu.getSno()!=n)
		{
			outFile.write((char*)&cu,sizeof(customer));
		}
		else
		{
		cu.showcust();
		fstream File;
		File.open("room.dat",ios::binary|ios::in|ios::out);
		if(!File)
		{
			cout<<"File could not be open !! Press any Key...";
			cin>>ch;
			customers();
		}
		while(!File.eof() && found==0)
		{

			File.read((char*)&ro,sizeof(room));
			if(cu.room_no==ro.rmno())
			{
				ro.roomstatus=0;
				int pos=(-1)*(int)(sizeof(ro));
				File.seekp(pos,ios::cur);
				File.write((char*)&ro,sizeof(room));
				found=1;
			}
		}
		File.close();
		}
	}
	cout<<"\nAre you sure want to delete the above record (y/n)";
	cin>>cnfrm;
	if(cnfrm=='y'||cnfrm=='Y')
	{
	outFile.close();
	inFile.close();
	remove("customer.dat");
	rename("Temp.dat","customer.dat");
	cout<<"\n\n\tRecord Deleted ..";
	}
	else
	{
	cout<<"\nDeletion aborted!!!!!!!!!!";
	cout<<"\nPress any key to proceed";
	cin>>cnfrm;
	customers();
	}
	F:cout<<"\n\nPress y to go back and n for Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	customers();
	}
	else if(ch=='n'|| ch=='N')
	      {
		Menu();
	      }
	      else
	      {
	      cout<<"\nWrong Input........."<<endl;
	      goto F;
	      }
}
void customers()
{
char ch;
int num;
clrscr();
cout<<"\t\t**************************************************\n";
cout<<"\t\t*                  DO YOU WANT TO                *\n ";
cout<<"\t\t**************************************************\n\n\n\n";
cout<<"\n\t\t\t\t1. Add New Customer ";
cout<<"\n\t\t\t\t2. View Customer ";
cout<<"\n\t\t\t\t3. Edit Customer ";
cout<<"\n\t\t\t\t4. Delete Customer ";
cout<<"\n\t\t\t\t5. Back to Category Menu";
cout<<"\n\n\n\n\n\t\t\t\tEnter your choice ";
cin>>ch;
system("cls");
switch(ch)
	{
	case '1':write_cust(); break;
	case '2':display_cust(); break;
	case '3':cout<<"\nPlease Enter Customer's Sno. to Edit: ";
		 cin>>num;
		 modify_cust(num);break;
	case '4':cout<<"\nPlease Enter Customer's Sno. to Delete: ";
		 cin>>num;
		 delete_cust(num);break;
	case '5':if(a==0)
		 {
		  Menu();
		 }
		 else
		  Menu1();
	}
}



class employee
{
private:
int Sno;
char empname[15];
char department[15];
float salary;
char dateofjoin[15];
int age;
char sex[7];
public:
employee()
{
}
void getemp()
	{
	cout<<"\nEnter the Seriol no. of Employee:";
	cin>>Sno;
	cout<<"\nEnter the Name of Employee:";
	gets(empname);
	cout<<"\nEnter the Age of Employee:";
	cin>>age;
	cout<<"\nEnter the Gender of Employee:";
	gets(sex);
	cout<<"\nEnter the Date of Join of Employee:";
	gets(dateofjoin);
	cout<<"\nEnter the Depatment of Employee:";
	gets(department);
	cout<<"\nEnter the Salary of Employee:";
	cin>>salary;
	}
void showemp()
	{
	cout<<"\nSno: ";
	cout<<Sno;
	cout<<"\nName: ";
	cout<<empname;
	cout<<"\nAge: ";
	cout<<age;
	cout<<"\nGender: ";
	cout<<sex;
	cout<<"\nDate of Join: ";
	cout<<dateofjoin;
	cout<<"\nDepartment: ";
	cout<<department;
	cout<<"\nSalary: ";
	cout<<salary;
	}
int getSno()
{
return Sno;
}
};
void write_emp()
{       char ch;
	employee st;
	ofstream outFile;
	outFile.open("employee.dat",ios::binary|ios::app);
	st.getemp();
	outFile.write((char *) &st, sizeof(employee));
	outFile.close();
	cout<<"\nEmployee record Has Been Created ";
	do{
	cout<<"\n\nPress y to go back and n for Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	employees();
	}
	else if(ch=='n'|| ch=='N')
	     {
	     Menu();
	     }
	     else
	     {
		cout<<"\nWrong Input........."<<endl;
	     }
	}while(ch=='y'||ch=='Y'||ch=='n'||ch=='N');
}
void display_emp()
{       char ch;
	employee st;
	ifstream inFile;
	inFile.open("employee.dat",ios::binary);
	if(!inFile)
	{
		cout<<"\nFile not found in the Database !!!";
		cout<<"\nPlease Add Atleast 1 Employee's Detail";
		delay(55000);
		employees();
	}
	cout<<"\n\t\t!!! DISPLAY ALL RECORD !!!\n";
	while(inFile.read((char *) &st, sizeof(employee)))
	{
		st.showemp();
		cout<<"\n====================================";
	}
	inFile.close();
	D:cout<<"\n\nPress y to go back and n for Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	employees();
	}
	else if(ch=='n'|| ch=='N')
	      {
	      Menu();
	      }
	      else
	      {
		cout<<"\nWrong Input........."<<endl;
		goto D;
	      }
}
void modify_emp(int n)
{       char ch;
	int found = 0;
	employee st;
	fstream File;
	File.open("employee.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin>>ch;
		employees();
	}
	while(!File.eof() && found==0)
	{

		File.read((char *) &st, sizeof(employee));
		if(st.getSno()==n)
		{
			st.showemp();
			cout<<"\n\nPlease Enter The New Details of Employee"<<endl;
			st.getemp();
			int pos=(-1)*(int)(sizeof(st));
			File.seekp(pos,ios::cur);
			File.write((char *) &st, sizeof(employee));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}
	File.close();
	if(found==0)
	cout<<"\n\n Record Not Found ";
	E:cout<<"\n\nPress y to go back and n for Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	employees();
	}
	else if(ch=='n'|| ch=='N')
	     {
	      Menu();
	     }
	     else
		{
		cout<<"\nWrong Input........."<<endl;
		goto E;
		}
}
void delete_emp(int n)
{        char ch,cnfrm;
	employee st;
	ifstream inFile;
	inFile.open("employee.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin>>ch;
		employees();
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) &st, sizeof(employee)))
	{
		if(st.getSno()!=n)
		{
			outFile.write((char *) &st, sizeof(employee));
		}
	}
	st.showemp();
	cout<<"\nAre you sure want to delete the above record (y/n)";
	cin>>cnfrm;
	if(cnfrm=='y'||cnfrm=='Y')
	{
	outFile.close();
	inFile.close();
	remove("employee.dat");
	rename("Temp.dat","employee.dat");
	cout<<"\n\n\tRecord Deleted ..";
	}
	else
	{
	cout<<"\nDeletion aborted!!!!!!!!!!";
	cout<<"\nPress any key to proceed";
	cin>>cnfrm;
	employees();
	}
	F:cout<<"\n\nPress y to go back and n for Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	employees();
	}
	else if(ch=='n'|| ch=='N')
	      {
		Menu();
	      }
	      else
	      {
	      cout<<"\nWrong Input........."<<endl;
	      goto F;
	      }
}
void employees()
{
char ch;
int num;
clrscr();
cout<<"\t\t**************************************************\n";
cout<<"\t\t*                  DO YOU WANT TO                *\n ";
cout<<"\t\t**************************************************\n\n\n\n";
cout<<"\n\t\t\t\t1. Add New Employee ";
cout<<"\n\t\t\t\t2. View Employee ";
cout<<"\n\t\t\t\t3. Edit Employee ";
cout<<"\n\t\t\t\t4. Delete Employee ";
cout<<"\n\t\t\t\t5. Back to Category Menu";
cout<<"\n\n\n\n\n\t\t\t\tEnter your choice ";
cin>>ch;
system("cls");
switch(ch)
	{
	case '1':write_emp(); break;
	case '2':display_emp(); break;
	case '3':cout<<"\nPlease Enter Employee Sno. to Edit: ";
		 cin>>num;
		 modify_emp(num);break;
	case '4':cout<<"\nPlease Enter Employee Sno. to Delete: ";
		 cin>>num;
		 delete_emp(num);break;
	case '5':if(a==0)
		  Menu();
		 else
		 Menu1();
	}
}


class fooding
{
private:
int dishcode;
char dishname[15];
char category[10];
int halfprice;
int fullprice;
public:
void getdish()
{
	cout<<"\nEnter the Dishcode of Dish:";
	cin>>dishcode;
	cout<<"\nEnter the Name of Dish:";
	gets(dishname);
	cout<<"\nEnter the Type of Dish:";
	gets(category);
	cout<<"\nEnter the Half Plate Price of Dish:";
	cin>>halfprice;
	cout<<"\nEnter the Full Plate Price of Dish:";
	cin>>fullprice;
}
void showdish()
{
	cout<<"\nDishcode:";
	cout<<dishcode;
	cout<<"\nDish Name:";
	cout<<dishname;
	cout<<"\nDish Type:";
	cout<<category;
	cout<<"\nDish Half Price:";
	cout<<halfprice;
	cout<<"\nDish Full Price:";
	cout<<fullprice;
}
int discode()
{
return dishcode;
}
};
void write_food()
{       char ch;
	fooding fo;
	ofstream outFile;
	outFile.open("fooding.dat",ios::binary|ios::app);
	fo.getdish();
	outFile.write((char*)&fo,sizeof(fooding));
	outFile.close();
	cout<<"\nDish record Has Been Created ";
	do{
	cout<<"\n\nPress y to go back and n for Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	foodings();
	}
	else if(ch=='n'|| ch=='N')
	     {
	     Menu();
	     }
	     else
	     {
		cout<<"\nWrong Input........."<<endl;
	     }
	}while(ch=='y'||ch=='Y'||ch=='n'||ch=='N');
}
void display_food()
{  char ch;
	fooding fo;
	ifstream inFile;
	inFile.open("fooding.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin>>ch;
		foodings();
	}
	cout<<"\n\t\t!!! DISPLAY ALL RECORD !!!\n";
	while(inFile.read((char*)&fo,sizeof(fooding)))
	{
		fo.showdish();
		cout<<"\n====================================";
	}
	inFile.close();
	D:cout<<"\n\nPress y to go back and n for Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	foodings();
	}
	else if(ch=='n'|| ch=='N')
	      {
	      Menu();
	      }
	      else
	      {
		cout<<"\nWrong Input........."<<endl;
		goto D;
	      }
}
void modify_food(int n)
{  char ch;
	int found = 0;
	fooding fo;
	fstream File;
	File.open("fooding.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin>>ch;
		foodings();
	}
	while(!File.eof() && found==0)
	{

		File.read((char *) &fo, sizeof(fooding));
		if(fo.discode()==n)
		{
			fo.showdish();
			cout<<"\n\nPlease Enter The New Details of Dish"<<endl;
			fo.getdish();
			int pos=(-1)*(int)(sizeof(fo));
			File.seekp(pos,ios::cur);
			File.write((char *) &fo, sizeof(fooding));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}
	File.close();
	if(found==0)
	cout<<"\n\n Record Not Found ";
	E:cout<<"\n\nPress y to go back and n for Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	foodings();
	}
	else if(ch=='n'|| ch=='N')
	     {
	      Menu();
	     }
	     else
		{
		cout<<"\nWrong Input........."<<endl;
		goto E;
		}
}
void delete_food(int n)
{        char ch,cnfrm;
	fooding fo;
	ifstream inFile;
	inFile.open("fooding.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin>>ch;
		foodings();
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) &fo, sizeof(fooding)))
	{
		if(fo.discode()!=n)
		{
			outFile.write((char *) &fo, sizeof(fooding));
		}
	}
	fo.showdish();
	cout<<"\nAre you sure want to delete the above record (y/n)";
	cin>>cnfrm;
	if(cnfrm=='y'||cnfrm=='Y')
	{
	outFile.close();
	inFile.close();
	remove("fooding.dat");
	rename("Temp.dat","fooding.dat");
	cout<<"\n\n\tRecord Deleted ..";
	}
	else
	{
	cout<<"\nDeletion aborted!!!!!!!!!!";
	cout<<"\nPress any key to proceed";
	cin>>cnfrm;
	foodings();
	}
	F:cout<<"\n\nPress y to go back and n for Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	employees();
	}
	else if(ch=='n'|| ch=='N')
	      {
		Menu();
	      }
	      else
	      {
	      cout<<"\nWrong Input........."<<endl;
	      goto F;
	      }
}
void foodings()
{
char ch;
int num;
clrscr();
cout<<"\t\t**************************************************\n";
cout<<"\t\t*                  DO YOU WANT TO                *\n ";
cout<<"\t\t**************************************************\n\n\n\n";
cout<<"\n\t\t\t\t1. Add New Dish ";
cout<<"\n\t\t\t\t2. View Dish ";
cout<<"\n\t\t\t\t3. Edit Dish ";
cout<<"\n\t\t\t\t4. Delete Dish ";
cout<<"\n\t\t\t\t5. Back to Category Menu";
cout<<"\n\n\n\n\n\t\t\t\tEnter your choice ";
cin>>ch;
system("cls");
switch(ch)
	{
	case '1':write_food(); break;
	case '2':display_food(); break;
	case '3':cout<<"\nPlease Enter Dishcode of Dish to Edit: ";
		 cin>>num;
		 modify_food(num);break;
	case '4':cout<<"\nPlease Enter Dishcode of Dishto Delete: ";
		 cin>>num;
		 delete_food(num);break;
	case '5':if(a==0)
		  Menu();
		 else
		  Menu1();
	}
}
class member
{
int mlength;
public:
int sno;
char mno[15];
char fname[10];
char lname[10];
char uname[20];
char pswrd[20];
member()
{
sno=0;
mlength=0;
}
void getmem()
{
	cout<<"\nEnter your Sno:";
	cin>>sno;
	cout<<"\nEnter your First Name:";
	gets(fname);
	cout<<"\nEnter your Last Name:";
	gets(lname);
	cout<<"\nEnter your Contact No.:";
	gets(mno);
	while(mlength!=10)
	{
	mlength=strlen(mno);
	if(mlength!=10)
	{
	cout<<"\nPlease Provide the Correct Contact No.";
	gets(mno);
	}
	else
	break;
	}
	cout<<"\nEnter your Username:";
	gets(uname);
	cout<<"\nEnter your Strong Password:";
	gets(pswrd);
}
void showmem()
{
   cout<<"\nSno.: ";
   cout<<sno;
   cout<<"\nFirst Name: ";
   cout<<fname;
   cout<<"\nLast Name: ";
   cout<<lname;
   cout<<"\nMobile No.: ";
   cout<<mno;
   cout<<"\nUsername: ";
   cout<<uname;
   cout<<"\nPassword: ";
   cout<<pswrd;
}
void showmem_user()
{
   cout<<"\nSno.: ";
   cout<<sno;
   cout<<"\nName: ";
   cout<<fname<<" "<<lname;
   if(fname=="hemal")
   cout<<" Admin";
   cout<<"\nUsername: ******";
   cout<<"\nPassword: ***********";
   cout<<"\nYou Don't have Access to see Username and Password";
}
};
void write_mem()
{       char ch;
	member me;
	cout<<"\t+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout<<"\t++\t   PLEASE PROVIDE THE DETAILS TO ADD NEW MEMBER      ++\n";
	cout<<"\t+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	ofstream outFile;
	outFile.open("member.dat",ios::binary|ios::app);
	me.getmem();
	outFile.write((char*)&me,sizeof(member));
	outFile.close();
	cout<<"\nMember record Has Been Created ";
	do{
	cout<<"\n\nPress y to go back and n for Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	members();
	}
	else if(ch=='n'|| ch=='N')
	     {
	     Menu();
	     }
	     else
	     {
		cout<<"\nWrong Input........."<<endl;
	     }
	}while(ch=='y'||ch=='Y'||ch=='n'||ch=='N');
}
void display_mem()
{  char ch;
	member me;
	ifstream inFile;
	inFile.open("member.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin>>ch;
		members();
	}
	cout<<"\n\t\t!!! DISPLAY ALL RECORD !!!\n";
	while(inFile.read((char*)&me,sizeof(member)))
	{
		me.showmem();
		cout<<"\n====================================";
	}
	inFile.close();
	D:cout<<"\n\nPress y to go back and n for Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	members();
	}
	else if(ch=='n'|| ch=='N')
	      {
	      Menu();
	      }
	      else
	      {
		cout<<"\nWrong Input........."<<endl;
		goto D;
	      }
}
void delete_mem(int n)
{        char ch,cnfrm;
	member me;
	ifstream inFile;
	inFile.open("member.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin>>ch;
		members();
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char*)&me,sizeof(member)))
	{
		if(me.sno!=n)
		{
			outFile.write((char*)&me,sizeof(member));
		}
		else
		me.showmem();
	}
	cout<<"\nAre you sure want to delete the above record (y/n)";
	cin>>cnfrm;
	if(cnfrm=='y'||cnfrm=='Y')
	{
	outFile.close();
	inFile.close();
	remove("member.dat");
	rename("Temp.dat","member.dat");
	cout<<"\n\n\tRecord Deleted ..";
	}
	else
	{
	cout<<"\nDeletion aborted!!!!!!!!!!";
	cout<<"\nPress any key to proceed";
	cin>>cnfrm;
	members();
	}
	F:cout<<"\nPress y to go back and n for Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	members();
	}
	else if(ch=='n'|| ch=='N')
	      {
		Menu();
	      }
	      else
	      {
	      cout<<"\nWrong Input........."<<endl;
	      goto F;
	      }
}
void members()
{
char ch;
int num;
clrscr();
cout<<"\t\t**************************************************\n";
cout<<"\t\t*                  DO YOU WANT TO                *\n ";
cout<<"\t\t**************************************************\n\n\n\n";
cout<<"\n\t\t\t\t1. Add New Member ";
cout<<"\n\t\t\t\t2. View Member ";
cout<<"\n\t\t\t\t3. Delete Member ";
cout<<"\n\t\t\t\t4. Back to Category Menu";
cout<<"\n\n\n\n\n\t\t\t\tEnter your choice ";
cin>>ch;
system("cls");
switch(ch)
	{
	case '1':write_mem(); break;
	case '2':display_mem(); break;
	case '3':cout<<"\nPlease Enter Member's Sno to Delete: ";
		 cin>>num;
		 delete_mem(num);break;
	case '4':if(a==0)
		  Menu();
		 else
		  Menu1();
	}
}
void Menu()
{
int n;
clrscr();
cout<<"******************************************************************************** \n";
cout<<"\t\t\tWELCOME TO THE AWM GREENISH HOTEL \n\n";
cout<<"******************************************************************************** \n";
cout<<"\t\t\t       WELCOME BACK ADMIN\n\n";
cout<<"\t\t\t\t++++++++++++++++\n";
cout<<"\t\t\t\t|   CATEGORY   |\n";
cout<<"\t\t\t\t++++++++++++++++\n\n";
cout<<"\t\t\t\t  1.Rooms \n";
cout<<"\t\t\t\t  2.Customers \n";
cout<<"\t\t\t\t  3.Employees \n";
cout<<"\t\t\t\t  4.Fooding \n";
cout<<"\t\t\t\t  5.Users \n";
cout<<"\t\t\t\t  6.Logout \n\n\n\n\n";
cout<<"\t\t\t\tEnter your choice ";
K:cin>>n;
switch(n)
{
	case 1:rooms();
		break;
	case 2:customers();
		break;
	case 3:employees();
		break;
	case 4:foodings();
		break;
	case 5:members();
		break;
	case 6:bypass();
		break;
	default:cout<<"\t\t\t Wrong input ";
		goto K;
}
}
void display_mem_user()
{  char ch;
	member me;
	clrscr();
	ifstream inFile;
	inFile.open("member.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin>>ch;
		Menu1();
	}
	cout<<"\n\t\t!!! DISPLAY ALL RECORD !!!\n";
	while(inFile.read((char*)&me,sizeof(member)))
	{
		me.showmem_user();
		cout<<"\n====================================";
	}
	inFile.close();
	cout<<"\nFor Username & Password get in touch of Admin";
	D:cout<<"\n\nPress y to go back to Main menu "<<endl;
	cin>>ch;
	if(ch=='y' || ch=='Y')
	{
	Menu1();
	}
	else
	{
		cout<<"\nWrong Input........."<<endl;
		goto D;
	}
}
void Menu1()
{
int n;
clrscr();
cout<<"******************************************************************************** \n";
cout<<"\t\t\tWELCOME TO THE AWM GREENISH HOTEL \n\n";
cout<<"******************************************************************************** \n";
cout<<"\t\t\tWelcome "<<first_name<<" "<<last_name<<" to the Database\n\n";
cout<<"\t\t\t\t++++++++++++++++\n";
cout<<"\t\t\t\t|   CATEGORY   |\n";
cout<<"\t\t\t\t++++++++++++++++\n\n";
cout<<"\t\t\t\t  1.Rooms \n";
cout<<"\t\t\t\t  2.Customers \n";
cout<<"\t\t\t\t  3.Employees \n";
cout<<"\t\t\t\t  4.Fooding \n";
cout<<"\t\t\t\t  5.View User \n";
cout<<"\t\t\t\t  6.Logout \n\n\n\n\n";
cout<<"\t\t\t\tEnter your choice ";
K:cin>>n;
switch(n)
{
	case 1:rooms();
		break;
	case 2:customers();
		break;
	case 3:employees();
		break;
	case 4:foodings();
		break;
	case 5:display_mem_user();
		break;
	case 6:bypass();
		break;
	default:cout<<"\t\t\t Wrong input ";
		goto K;
}
}
void login()
{       clrscr();
	char ch;
	char uname[20];
	char pass[20];
	char* hemal="hemal";
	int found = 0;
	H:cout<<"\t+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout<<"\t++\t      PLEASE PROVIDE THE DETAILS TO LOGIN          ++\n";
	cout<<"\t+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout<<"\nEnter your Username:";
	gets(uname);
	cout<<"\nEnter your Password:";
	R:gets(pass);
	cout<<"\n\nPlease Wait While Checking the Data";
	delay(55000);
	member me;
	ifstream File;
	File.open("member.dat",ios::binary);
	if(!File)
	{
		cout<<"\n!! Sorry Registration Data not Available in the Database !!!";
		cout<<"\nPlease Avail the Registeration Data By Registering";
		cout<<"\nPress any key to Proceed.....";
		cin>>ch;
		regster();
	}
	while(File.read((char*)&me,sizeof(member)))
	{
		int user= strcmp(uname, me.uname);
		int passw= strcmp(pass, me.pswrd);
		if(user==0)
		{
			if(passw==0)
			{       strcpy(first_name, me.fname);
				strcpy(last_name, me.lname);
				cout<<"\n\nLoggedin Successfully..........";
				cout<<"\n\nPlease Wait while Proceeding to the Database ";
				a = strcmp(me.uname, hemal);
				if(a==0)
				{
					delay(55000);
					Menu();
				}
				else
				delay(50000);
				Menu1();
				found=1;
			}
			else
			{
			cout<<"\n!!! Your Password is Incorrect !!!";
			cout<<"\nRe-enter the correct Password\n";
			goto R;
			}
		}
	}
	File.close();
	if(found==0)
	{
		cout<<"\n\n!!!!! User Not Found in the DATABASE !!!!!";
		cout<<"\n\n!!!! You Didn't Registered Yet !!!!";
		cout<<"\n\nPress y to Register Or h to Login Again ";
		cin>>ch;
		if(ch=='y'||ch=='Y')
		regster();
		else if(ch=='h'||ch=='H')
		{
		     clrscr();
			goto H;
		}
		else if(ch=='m'||ch=='M')
		Menu();
		else
		exit(0);
	}
}

void regster()
{
	clrscr();
	char ch;
	member me;
	cout<<"\t+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout<<"\t++\t   PLEASE PROVIDE THE DETAILS TO ADD NEW MEMBER      ++\n";
	cout<<"\t+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	ofstream oFile;
	oFile.open("member.dat",ios::binary|ios::app);
	me.getmem();
	oFile.write((char*)&me,sizeof(member));
	oFile.close();
	cout<<"\n\n\t\t\t\tPlease Wait";
	delay(20000);
	cout<<"\n\t\t\t\t!!! Congratulations !!!";
	delay(35000);
	cout<<"\n\t\t\tYou have Successfully Registered... ";
	delay(45000);
	cout<<"\n\t\tYou can use this Username and Password to Login";
	delay(50000);
	bypass();
}

void bypass()
{
clrscr();
int c;
cout<<"\t\t***********************************************\n";
cout<<"\t\t*                                             *\n";
cout<<"\t\t*       FOR SECURITY PURPOSE YOU HAVE TO      *\n";
cout<<"\t\t*                                             *\n";
cout<<"\t\t***********************************************\n\n";
cout<<"\n\t\t\t     +++++++++++++++++++";
cout<<"\n\t\t\t     +|---------------|+";
cout<<"\n\t\t\t     +| 1.Register    |+";
cout<<"\n\t\t\t     +|---------------|+";
cout<<"\n\t\t\t     +| 2.Login       |+";
cout<<"\n\t\t\t     +|---------------|+";
cout<<"\n\t\t\t     +| 3.Exit        |+";
cout<<"\n\t\t\t     +|---------------|+";
cout<<"\n\t\t\t     +++++++++++++++++++";
cout<<"\n\n\n\n\n\t\t\t     Enter the choice ";
L:cin>>c;
switch(c)
{
	case 1:regster();
		break;
	case 2:login();
		break;
	case 3:exit(0);
	default :cout<<"Wrong input";
		goto L;
}
}

void main()
{
char x;
int n=1000;
clrscr();
gotoxy(32,10);
cout<<"\n\n\n\n\t\t\t\t...PROGRAM LOADING...\n\n\n";
for(int i=0; i<79; i++)
{
delay(n);
cout<<"|";
n-=5;
}
sound(40);
delay(3000);
cout<<"\n\n\t\t\t\t...LOADING SUCCESSFUL...";
nosound();
delay(20000);
cout<<"\n\n\t\t\t\tPLEASE WAIT........";
delay(35000);
clrscr();
cout<<"********************************************************************************";
cout<<"+\t\t     PRABHAT SENIOR SECONDARY PUBLIC SCHOOL  \n";
cout<<"+\t\t\t      R.S.PURAM, KAKADEO \n";
cout<<"+\t\t\t\t    KANPUR\n+\n";
cout<<"********************************************************************************\n \n \n";
cout<<"\t\t\t++++++++++++++++++++++++++++++++\n";
cout<<"\t\t\t+|----------------------------|+\n";
cout<<"\t\t\t+| COMPUTER SCIENCE PROJECT   |+\n";
cout<<"\t\t\t+|----------------------------|+\n";
cout<<"\t\t\t+| DEVELOPED BY: HEMAL VERMA  |+\n";
cout<<"\t\t\t+|----------------------------|+\n";
cout<<"\t\t\t+|      CLASS: XII(SCI.)      |+\n";
cout<<"\t\t\t+|----------------------------|+\n";
cout<<"\t\t\t+| TO: SANDEEP TRIPATHI SIR   |+\n";
cout<<"\t\t\t+|----------------------------|+\n";
cout<<"\t\t\t++++++++++++++++++++++++++++++++\n\n\n\n";
cout<<"\t\t\t Proceed to the Hotel (Y/N)...";
A:cin>>x;
if(x=='y'||x=='Y')
{
bypass();
}
else if(x=='n'||x=='N')
{
exit(0);
}
else
{
cout<<"\t\t\t Wrong Input Try Again ";
goto A;
}
}
