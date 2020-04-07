#include <sstream>
#include <iostream>
#include <windows.h>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
class Write
{
public:
	string name;
	string model;
	int price;
	int count;
	//Add new smartphone in DB
	void add(string name,string model,int price,int count)
	{
		ofstream f;
		f.open("db.txt",ios::app);
		f<<name<<" "<<model<<" "<<price<<" "<<count<<endl;
		f.close();
	}
	void Input()
	{
		cout<<"name: ";
		cin>>name;
		cout<<"model: ";
		cin>>model;
		cout<<"price: ";
		cin>>price;
		cout<<"count: ";
		cin>>count;
	}
};

class Smartphone
{
protected:
	vector<string> name;
	vector<string> model;
	vector<int> count;
	vector<int> price;
public:
	//Print Title
	void get_title() 
	{
		string line;
		ifstream f;
		int i = 0;
		f.open("db.txt");
		if (f.is_open())
		{
			while(getline(f,line))
			{
				i++;
				if (i < 3)
				{
					cout<<line<<endl;
				}
			}
		}
	}
	//Initialization Values
	void info()
	{
		int i = 0, temp = 0;
		string line;
		ifstream f;
		f.open("db.txt");
		if (f.is_open())
		{ 
			while(getline(f,line))
			{
				i++;
				if (i > 2)
				{
					string word;
				    stringstream iss(line);
				    while(iss >> word)
					{
						temp++;
						if (temp % 4 == 1)
						{
							name.push_back(word);
						}
						if (temp % 4 == 2)
						{
							model.push_back(word);
						}
						if (temp % 4 == 3)
						{
							price.push_back(atoi(word.c_str()));
						}
						if (temp % 4 == 0)
						{
							count.push_back(atoi(word.c_str()));
						}
					}
				}				
			}	
		}
	};
	//Output all DataBase 
	void get_all(){
		name.clear();
		model.clear();
		price.clear();
		count.clear();
		get_title();
		info();
		for (int i = 0; i < name.size();i++)
		{
			cout<<i + 1<<". "<<name[i]<<"\t"<<model[i]<<"\t\t"<<price[i]<<"\t\t"<<count[i]<<endl;
		}
	};
};
class Function : public Smartphone
{
public:
	//Total price: price * count
	void total_price()
	{
		info();
		string cmd;
		int total = 0;
		cin>>cmd;
		for (int i = 0; i < name.size();i++)
		{
			if (cmd == name[i])
			{
				total = price[i] * count[i];
			}
		}
		cout<<"Total price: "<<total<<endl;
	}
	//Edit DataBase values (price,count) 
	void edit()
	{
		info();;
		string line,temp_price,new_price,name1,price_or_count;
		int i = 0,k = 0, col = 0;
		cin>>name1>>price_or_count>>new_price;
		if (price_or_count == "price")
		{
			col = 3;
		}
		if (price_or_count == "count")
		{
			col = 4;
		}
			ifstream in;
			in.open("db.txt");
			ofstream out;
			out.open("temp.txt");
			while(getline(in, line))
			{
				if (line.substr(0, name1.size()) == name1)
				{
					string word;
					stringstream iss(line);
					while(iss >> word)
					{
						k++;
						if (k == col)
						{
							temp_price = word;
						}
					}
					line.replace(line.find(temp_price),temp_price.length(),new_price);
				}
				out << line << endl;
			}
			in.close();
			out.close();
			remove("db.txt");
			rename("temp.txt","db.txt");
			cout<<"Editing was successfuly"<<endl;	
	};
	void deleteLine()
	{
		string line;
		string name;
		cin >> name;
		ifstream myfile;
		myfile.open("db.txt");
		ofstream temp;
		temp.open("temp.txt");
		while (getline(myfile, line))
		{
			if (line.substr(0, name.size()) != name)
				temp << line << endl;
		}
		cout << "Smartphone " << name <<" "<<  " successfuly deleted" << endl;
		myfile.close();
		temp.close();
		remove("db.txt");
		rename("temp.txt", "db.txt");
	}	
};
void help()
{
	cout<<"get_all                           print DataBase"<<endl;	
	cout<<"add                               add a new item to the database"<<endl;
	cout<<"delete <name>                     remove an item from the database"<<endl;
	cout<<"edit <name> <price||count> <new>  edit data"<<endl;
	cout<<"total <name>                      price * count"<<endl;
};

int main() {
	setlocale(LC_ALL, "Ukrainian");
	string cmd;
	char *temp;
	temp = "cmd~>";
	cout<<"Console App SMARTPHONES"<<endl;
	cout<<"\tuse 'help' to view a list of commands!"<<endl;
	Write w;
	Function f;
	Smartphone s;
	s.info();
	while(true)
	{
		cout<<temp;
		cin>>cmd;
		if (cmd == "add")
		{
			w.Input();
			w.add(w.name,w.model,w.price,w.count);
				
		}
		if (cmd == "get_all")
		{
			s.get_all();
		}
		if (cmd == "delete")
		{
			f.deleteLine();
		}
		if (cmd == "total")
		{
			f.total_price();
		}
		if (cmd == "edit")
		{
			f.edit();
		}
		if (cmd == "help")
		{
			help();
		}
		if (cmd == "clear")
		{
			system("cls");
		}
	}
	return 0;
}
