#include<iostream>
#include<fstream>  
#include<cstdlib> //for cinclear and cin ignore
#include<vector> 
#include<cctype>//isdigit
 // for sort method
#include <algorithm>
using namespace std;
class Emp
{   
    public:
	string username,id,filename,fileid;
	string searchkey,searchname;
	void add();
	void display();
	void search();
	void sort();
	string validname();
	string validid();
	int choicevalid();
};

int main()
{  
   Emp object;
	int choice;
do{
	cout<<"1) ADD 2) DISPLAY 3) SEARCH 4) SORT 5) CLEAR 6) EXIT"<<endl;
	cout<<"ENTER CHOICE"<<endl;
	choice=object.choicevalid();
	switch(choice)
	{
		case 1:object.add();
			break;
		case 2:object.display();
			break;
		case 3:object.search();
		break;
		case 4:object.sort();
		break;
		case 5:system("cls");
		break;
		case 6:cout<<"THANKS FOR USING OUR SYSTEM"<<endl;
		break;
		default:
			cout<<"INVALID CHOICE"<<endl;
	}//switch
}while(choice!=6);  // do while	
} //int main


string Emp::validname()
{
	string name;
//	cin.clear();
//	cin.ignore(1000,'\n');
	while(true)
{
	//getline(cin,name);
	getline(cin>>ws,name); // ws means whitespace manipulator , rmeove cin clear , this alone will work 
    bool check=false;
	for(char c:name)
	{  
		if(isdigit(c))
		{
			cout<<"ENTER ONLY ALPHABETS"<<endl;
			check=true;
			break;
		}
	}
	if(check==false)return name;
}
}

int Emp::choicevalid()
{
	string a;
	while(true)
	{    
	    bool check=true;
	    cin>>a;
		if(a.length()!=1)
		{
			cout<<"ENTER 1 DIGIT ONLY "<<endl;
		    continue;
		}
		for(char c:a)
		{
			if(!(isdigit(c)) || c=='0')
			{
				cout<<"ENTER ONLY NUMBERS"<<endl;
				check=false;
				break;
			}
		}if(check==true)return stoi(a);
	}
}
string Emp::validid(){
	string id;
	while(true)
	{   
	    bool check=false;
		cin>>id;
		for(char c:id)
		{
			if(!(isdigit(c)))
			{
				cout<<"ENTER ONLY NUMBERS"<<endl;
				check=true;
				break;
			}
		}if(check==false)return id;
	}
}
void Emp::add(){
	cout<<"ENTER USERNAME"<<endl;
	username=validname();
	ifstream myfile("emp.txt");
	while(getline(myfile,filename,'*') && getline(myfile,fileid))
	{
		if(username==filename ){
			cout<<"EMPLOYEE DETAILS ALREADY PRESENT IN FILE"<<endl;
			myfile.close();
			return;
		}
	}  
	    myfile.close();
	    ofstream myfile1("emp.txt",ios::app);
		cout<<"ENTER ID"<<endl;
	    id=validid();
	    myfile1<<username<<"*"<<id<<endl;
	    cout<<"SUCCESFULLY ADDED NEW ENTRY"<<endl;
	    myfile1.close();
	    return;
//removing temp file method and directly appending in same file , bcoz for larger data temp file is not safe
}

void Emp::sort()
{
	ifstream myfile("emp.txt");
	vector<string> name;
	vector<string>id;
	string n,i;
	int choice;
	while(getline(myfile,n,'*')&&getline(myfile,i))
	{
		name.push_back(n);
		id.push_back(i);
	}
myfile.close();
cout<<"1) SORT_BY_NAME 2) SORT_BY_ID"<<endl;
cout<<"ENTER CHOICE"<<endl;
choice=choicevalid();
if(choice==1)
{
for(int i=0;i<name.size();i++)
	{
		for(int j=0;j<name.size()-i-1;j++)
		{
			if(name[j]>name[j+1])
			{
				string tempname=name[j];
				name[j]=name[j+1];
				name[j+1]=tempname;
				
				string tempid=id[j];
				id[j]=id[j+1];
				id[j+1]=tempid;
			}
		}
	}
 /*sort(name.begin(),name.end());*/
	cout<<"EMPLOYESS NAME IN SORTED ORDER"<<endl;	
	for(int i=0;i<name.size();i++)
	cout<<name[i]<<"*"<<id[i]<<endl;
}
else if(choice==2)
{
	for(int i=0;i<id.size();i++)
	{
		for(int j=0;j<id.size()-i-1;j++)
		{
			if(id[j]>id[j+1])
			{
				string tempname=name[j];
				name[j]=name[j+1];
				name[j+1]=tempname;
				
				string tempid=id[j];
				id[j]=id[j+1];
				id[j+1]=tempid;
			}
		}
	}
	cout<<endl;
	cout<<"EMPLOYEES ID IN SORTED ORDER"<<endl;	
	for(int i=0;i<id.size();i++)
	cout<<name[i]<<"*"<<id[i]<<endl;
}
else
cout<<"INVALID CHOICE"<<endl;
}

void Emp::display()
{
	ifstream myfile("emp.txt");
	while(getline(myfile,filename,'*') && getline(myfile,fileid))
	{
		cout<<filename<<"*"<<fileid<<endl;
	}
	myfile.close();
} //display

void Emp::search()
{      
     int choice; 
     cout<<"1) SEARCH_ID 2) SEARCH_NAME"<<endl;
     choice=choicevalid();
//replacing string name[100] id[100] , bcoz if emp numbers are more  , program will crash
	vector<string> name;
	vector<string> id;
	string n,i;// for storing each values form file
	bool found=false;
	ifstream myfile("emp.txt");
	while(getline(myfile,n,'*')&&getline(myfile,i))
	{
		name.push_back(n);
		id.push_back(i);
	}
	myfile.close();
	cout<<"ENTER KEY "<<endl;
		if(choice==1)
		{
			searchkey=validid();
	for(int i=0;i<id.size();i++)
	{
		if(searchkey==id[i])
		{
			cout<<"KEY FOUND AT "<<name[i]<<" "<<id[i]<<endl;
			found=true;
			break;
		}
	}
	if(found==false)cout<<"KEY NOT FOUND"<<endl;
}
else if(choice==2)
{
	searchkey=validname();
		for(int i=0;i<name.size();i++)
	{
		if(searchkey==name[i])
		{
			cout<<"KEY FOUND AT "<<name[i]<<" "<<id[i]<<endl;
			found=true;
			break;
		}
	}
	if(found==false)cout<<"KEY NOT FOUND"<<endl;
}
else
cout<<"INVALID CHOICE"<<endl;
}
