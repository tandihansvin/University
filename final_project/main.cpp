/*
	hansvin tandi sugata
	2001586685
	"HANOI TOWER"
*/

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <queue>
#include <utility>
#include "tower.hpp"
using namespace std;

Tower t[3];
int n_peg;		//to store number of peg

void initialize(int n){	//initialize the towers
	t[0].counter=0;
	t[0].push(n_peg+1);
	
	t[1].counter=0;
	t[1].push(n_peg+1);
	
	t[2].counter=0;
	t[2].push(n_peg+1);
	 
	for(int i=1;i<=n;i++){
		t[0].push(n+1-i);
		t[1].push(0);
		t[2].push(0);
	}
	t[1].counter=1;
	t[2].counter=1;
}

void show_tower(){
	cout<<endl<<"*********************************"<<endl;
	cout	  <<"*                               *"<<endl;
	for(int i=n_peg ; i>=1 ; i--){
		cout<<"*\t"<<t[0].getTower(i)<<"\t"<<t[1].getTower(i)<<"\t"<<t[2].getTower(i)<<"\t*"<<endl;
		cout  <<"*                               *"<<endl;
	}
	cout	  <<"*********************************"<<endl;
	cout<<endl<<endl;
}

bool check_tower3(){
	bool flag=true;
	for(int i=n_peg;i>=1;i--){
		if( t[2].getTower(i) != (n_peg+1-i) ){
			flag = false;
		}
	}
	return flag;
}

bool check_input(int x, int y){
	if( (0<x && x<4) && (0<y && y<4) ){
		if( t[x-1].counter > 1 ){
			if(t[x-1].last_position() <= t[y-1].last_position()) {
				cout<<"input accepted\n";
				Sleep(1000);
				return true;
			}
			else {
				cout<<"invalid input\n";
				Sleep(1000);
				return false;
			}
		}
		else{
			cout<<"invalid input\n";
			Sleep(1000);
			return false;
		}
	}
	else {
		cout<<"invalid input\n";
		Sleep(1000);
		return false;
	}
}

void move(int x, int y){
	int temp;
	temp = t[x-1].last_position();
	t[x-1].pop();
	t[y-1].push( temp );
}

void rules(){
    system("cls");
    cout<<"1. There are three rods and n pegs. The aim of this game is to move all the pegs from rod 1 to rod 3 in an ascending order from top to bottom.\n\n";
    cout<<"2. You can only shift one peg at a time.\n\n";
    cout<<"3. To shift a peg, enter the rod 'from' where you want to shift the peg, and then enter the rod 'to' where you want to shift the peg.\n\n";
    cout<<"4. You can place a small peg over a large peg but you can't place a large peg over a small peg\n\n";
    system("pause");
}

int step;

void solve( int n , int from , int dummy , int to ){
	if (n == 1){
		system("CLS");
		step++;
		cout <<"Step "<<step<<" = Move peg from : " << from << " to "<< to << endl;
		move(from,to);
		show_tower();
		Sleep(1000);
	}
	else
	{
		solve(n-1 , from , to , dummy);
		solve(1 , from , dummy , to);
		solve(n-1 , dummy , from , to);
	}
}

struct property{
	queue< pair<int,int> > way;
	Tower twr[3];
};

bool memo[1025][1025][1025];

queue<property> Q;

queue< pair<int, int> > answer;

void check(int from, int to){
	struct property dummy = Q.front();
	if(dummy.twr[from].counter > 1){
		if(dummy.twr[from].last_position() <= dummy.twr[to].last_position()) {
			int temp = dummy.twr[from].last_position();
			dummy.twr[from].pop();
			dummy.twr[to].push( temp );
			
			//turning the condition of each tower to bitmask
			int mask1=0, mask2=0, mask3=0;
			for(int i=1;i<dummy.twr[0].counter;i++){
				mask1 = mask1 | (1 << (dummy.twr[0].getTower(i)-1) );
			}
			for(int i=1;i<dummy.twr[1].counter;i++){
				mask2 = mask2 | (1 << (dummy.twr[1].getTower(i)-1) );
			}
			for(int i=1;i<dummy.twr[2].counter;i++){
				mask3 = mask3 | (1 << (dummy.twr[2].getTower(i)-1) );
			}
			
			//for checking whether this condition have been visited or not
			if(memo[mask1][mask2][mask3]){
				memo[mask1][mask2][mask3]=false;
				dummy.way.push({from,to});
				Q.push(dummy);
			}
		}
	}
}

//Breadth First Search
void hint(Tower t1, Tower t2, Tower t3){
	//initialize
	struct property dummy;
	memset(memo,true,sizeof(memo));
		//copy all condition of each tower
	dummy.twr[0] = t1;	
	dummy.twr[1] = t2;
	dummy.twr[2] = t3;
	
	Q.push(dummy);
	
	while(!Q.empty()){
		dummy = Q.front();
		if(dummy.twr[2].counter == n_peg+1){
			answer = dummy.way;
			break;
		}
		//roaming to all vertex
		check(0,1);		//from tower 1 to 2
		check(0,2);		//from tower 1 to 3
		check(1,0);		//from tower 2 to 1
		check(1,2);		//from tower 2 to 3
		check(2,0);		//from tower 3 to 1
		check(2,1);		//form tower 3 to 2
		
		Q.pop();
	}
}

int main(){
	int choice;
	char x,y;
	string code;
	
	ifstream infile;
	
	while( true ){
		system("CLS");
		infile.open("logo.txt", ios::in);
		while(getline(infile,code)){ 
			cout<<code<<endl;
		}
		infile.close();
		cout<<endl;
		cout<<"Press 1 to play"<<endl;
		cout<<"Press 2 to show the rules"<<endl;
		cout<<"Press 3 to show the best solution"<<endl;
		cout<<"Press 0 to exit"<<endl;
		
		cin>>choice;
		if(choice == 1){	//playing
			cout<<"How many peg(stage, no more than 10) ? : ";
			do{		//validate the number of peg
				cin>>n_peg;
			}while(n_peg>10 || n_peg<=0);
			
			initialize(n_peg);
			
			while( true ){
					// validate the input
				do{
					system("CLS");		//clear screen
					show_tower();
					cout<<"Press x to give up(exit)"<<endl;
					cout<<"Press y to ask a hint"<<endl;
					
					cout<<"From : ";
					x=getch();
					if( x != 'y' )cout<<x;
					if(x=='x') break;		// x to exit
					
					if( x != 'y' ){
						cout<<" To : ";
						y=getch();
						cout<<y<<endl;
					}
					if(y=='x') break;
					
					if(x=='y'){	//ask for hint
						system("CLS");
						x='1';
						y='1';
						
						queue<property> dummy_queue;
						Q = dummy_queue;	//clear the queue
						
						cout<<"Please wait....."<<endl;
						hint(t[0],t[1],t[2]);
						
						pair<int,int> ans;
						ans = answer.front();
						cout<<"@ Please move :"<<ans.first+1<<" to "<<ans.second+1<<endl;
						Sleep(1000);
					}
				}while(!check_input(x-48,y-48));
				
				system("CLS");
				
				if(x=='x' || y=='x') break;
				else {
					move(x-48,y-48);
				}
		
				if(check_tower3()) {
					cout<<"Congratulation !! YOU WIN "<<char(1)<<endl<<endl;
					system("pause");
					break;
				}
			}
					
		}
		
		if(choice == 2){	//show the rules
			rules();
			system("CLS");
		}
		
		if(choice == 3){	//show the best solution
			step=0;
			cout<<"How many peg(stage) ? : ";
			cin>>n_peg;
			initialize(n_peg);
			solve(n_peg , 1 , 2 , 3);
			system("pause");
		}
		
		if(choice == 0){	//exit
			break;
		}
	}
	return 0;
}
