#include<iostream>
#include<fstream>
#include<stdio.h>
using namespace std;

class bank{
	private:
		int acc_no;
		int balance;
		char name[50];
	public:
		//function for new account
		void new_acc(){
			cout<<"Enter account number: ";
			cin>>acc_no;
			cout<<"Enter name: ";
			cin>>name;
			cout<<"Enter balance: ";
			cin>>balance;
		}
		//function for displaying all accounts
		void display(){
			cout<<acc_no<<"\t"<<name<<"\t"<<balance<<endl;
		}
		//function for returning account
		int get_acc(){
			return acc_no;
		}
		//function for deposition into an account
		void deposit(int deposit){
			balance = balance + deposit;
			cout<<"Amount deposited: "<<deposit<<endl;
		}
		//function for withdrawing from an account
		void withdraw(int withdraw){
			if(withdraw<=balance){
				balance = balance - withdraw;
				cout<<"Amount withdrew: "<<withdraw<<endl;	
			}
			else{
				cout<<"Not enough balance"<<endl;
			}
		}
		//function for editing name
		void edit(){
			cout<<"Enter name: ";
			cin>>name;
		}
};

int main(){
	struct bank b;
	int ch=0;
	int search_acc_no;
	int withdraw, deposit;

	ofstream x;
	ifstream y;
	
	do{
		//Asking for choice to the user
		cout<<endl<<"Press 1 for Adding new account"<<endl;
		cout<<"Press 2 for Displaying all accounts"<<endl;
		cout<<"Press 3 for Displaying specific account"<<endl;
		cout<<"Press 4 for Deposit"<<endl;
		cout<<"Press 5 for Withdraw"<<endl;
		cout<<"Press 6 for Editing account details"<<endl;
		cout<<"Press 7 for Deleting an account"<<endl;
		cout<<"Press 8 for EXIT"<<endl;

		cout<<"Enter a choice: ";
		cin>>ch;
		
		switch(ch){
			//Adding new account to the bank
			case 1:
				x.open("bank.txt",ios::app|ios::binary);
				b.new_acc();
				x.write((char*)&b,sizeof(bank));
				x.close();
				break;

			//Displaying all existing accounts
			case 2:
				y.open("bank.txt",ios::binary);
				cout<<"\nAccNo.\tName\tBalance"<<endl;
				while(y.read((char*)&b,sizeof(bank))){
					b.display();
				}
				y.close();
				break;
			
			//Displaying a particular account
			case 3:
				cout<<"Enter account number: ";
				cin>>search_acc_no;
				y.open("bank.txt",ios::binary);

				while(y.read((char*)&b,sizeof(bank))){
					if(search_acc_no == b.get_acc()){
					b.display();
					break;
					}
				}
				y.close();
				break;

			//Depositing into an account
			case 4:
				cout<<"Enter account number: ";
				cin>>search_acc_no;
				y.open("bank.txt",ios::binary);
				x.open("temporary_bank.txt",ios::binary);
				while(y.read((char*)&b,sizeof(bank))){
					if(search_acc_no == b.get_acc()){
						cout<<"Enter amount to deposit: ";
						cin>>deposit;
						b.deposit(deposit);
						b.display();
					}
					x.write((char*)&b,sizeof(bank));
				}
				x.close();
				y.close();
				remove("bank.txt");
				rename("temporary_bank.txt","bank.txt");
				break;

			//Withdrawing from an account
			case 5:
				cout<<"Enter account number: ";
				cin>>search_acc_no;
				y.open("bank.txt",ios::binary);
				x.open("temporary_bank.txt",ios::binary);
				while(y.read((char*)&b,sizeof(bank))){
					if(search_acc_no == b.get_acc()){
						cout<<"Enter amount to withdraw: ";
						cin>>withdraw;
						b.withdraw(withdraw);
						cout<<endl;
						b.display();
					}
					x.write((char*)&b,sizeof(bank));
				}
				x.close();
				y.close();
				remove("bank.txt");
				rename("temporary_bank.txt","bank.txt");
				break;
			
			//Editing name in an account
			case 6:
				cout<<"Enter account number: ";
				cin>>search_acc_no;
				y.open("bank.txt",ios::binary);
				x.open("temporary_bank.txt",ios::binary);
				while(y.read((char*)&b,sizeof(bank))){
					if(b.get_acc()==search_acc_no){
						b.edit();
					}
					x.write((char*)&b,sizeof(bank));
				}
				x.close();
				y.close();
				remove("bank.txt");
				rename("temporary_bank.txt","bank.txt");
				break;

			//Closing an account
			case 7:
				cout<<"Enter account number: ";
				cin>>search_acc_no;
				y.open("bank.txt",ios::binary);
				x.open("temporary_bank.txt",ios::binary);
				while(y.read((char*)&b,sizeof(bank))){
					if(b.get_acc()!=search_acc_no){
						x.write((char*)&b,sizeof(bank));
					}
				}
				x.close();
				y.close();
				remove("bank.txt");
				rename("temporary_bank.txt","bank.txt");
				break;

			default:
				cout<<"Thank you.";
		}
	}while(ch<=7);	
}
