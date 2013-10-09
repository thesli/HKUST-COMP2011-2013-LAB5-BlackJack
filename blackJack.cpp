#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;
int main();

enum suit { 
	HEART,
	DIAMOND,
	SPADE,
	CLUB
 };

class Poker{
public:
	suit type;
	int value;
	Poker(suit t,int v){
		type = t;
		value = v;
	};
	static Poker getRandomCard(){
		suit tp = static_cast<suit>(rand()%4);
		int val = rand()%13 + 1;
		Poker card(tp,val);
		return card;
	};
	void printCard(){
		switch(value){
			case 13:
				cout << "K";
			break;
			case 12:
				cout << "Q";
			break;
			case 11:
				cout << "J";
			break;
			default:
				cout << value;
			break;
		}
		switch(type){
			case HEART:
				cout << "H\t";
			break;
			case CLUB:
				cout << "C\t";
			break;
			case DIAMOND:
				cout << "D\t";
			break;
			case SPADE:
				cout << "S\t";
			break;
		};
	};
};

class Player{
public:
	vector<Poker> cardList;	
	bool isUniqueCard(Player otherPlayer,Poker card){
		int i = 0;
		while(i<cardList.size()){
			if(cardList[i].type == card.type && cardList[i].value == card.value){
				return false;
			}
			i++;
		}
		i = 0;
		while(i<otherPlayer.cardList.size()){
			if(otherPlayer.cardList[i].type == card.type && otherPlayer.cardList[i].value == card.value){
				return false;
			}
			i++;
		}
		return true;
	};
	int getCardSum(){
		int i = 0;
		int sum = 0;
		while(i<cardList.size()){			
			if(cardList[i].value==11||cardList[i].value==12||cardList[i].value==13){				
				sum+=10;
			}else{
				sum+=cardList[i].value;		
			}			
			i++;
		}
		return sum;
	};
	void printAllCard(){
		for (int i = 0; i < cardList.size(); ++i)
		{
			cardList[i].printCard();
		}
	}
	void printAllCardHost(){
		cout << "XX\t";
		for (int i = 1; i < cardList.size(); ++i)
		{
			cardList[i].printCard();
		}
	}
};

Player Host;
Player User;

void getACardUser(){
	Poker card = Poker::getRandomCard();
	if(User.isUniqueCard(Host,card)){
		User.cardList.push_back(card);
	}else{
		getACardUser();
	}
}

void getACardHost(){
	Poker card = Poker::getRandomCard();
	if(Host.isUniqueCard(Host,card)){
		Host.cardList.push_back(card);
	}else{
		getACardUser();
	}
}

void userPharse();

void init(){
	User.cardList.clear();
	Host.cardList.clear();
	getACardUser();
	getACardHost();
	getACardUser();
	getACardHost();	
	cout << "You:\t\t";
	User.printAllCard();
	cout << "(" << User.getCardSum() << ")\n";
	cout << "House:\t\t";	
	Host.printAllCardHost();
	cout << "\n";
	userPharse();
}
void doReplay();

void resultPharse();
void resultPharse(){
	cout << "Result:\n";
	cout << "You:\t\t" << User.getCardSum() << "\n";
	cout << "House:\t\t" << Host.getCardSum() << "\n";
	if(User.getCardSum()>Host.getCardSum()){
		cout << "You win.\n";
	}else if(User.getCardSum()==Host.getCardSum()){
		cout << "Draw.\n";
	}else{
		cout << "House win.\n";
	}
	doReplay();
}


void hostPharse();
void hostPharse(){
	while(true){
		getACardHost();
		cout << "House:\t\t";
		Host.printAllCardHost();
		cout << "(" << Host.getCardSum() << ")\n";
		if(Host.getCardSum()>21){
			cout << "House bursts\n";
			doReplay();
		}else if(Host.getCardSum()>User.getCardSum()){
			resultPharse();
			break;
		}
	}	
}

void doReplay(){
	cout << "Do you want to play again?(Y/N)";
	char y;
	cin >> y;
	if(y=='y'||y=='Y'){
		cout << "\n";
		main();
	}else{
		exit(0);
	}
}
char x;
void userPharse(){
	cout << "\n";
	x='n';
	while(User.getCardSum()<21){
		cout << "Do you want a hit?(Y/N)";
		cin >> x;
		if(x!='Y'&&x!='y'){
			break;
		}
		getACardUser();
		cout << "You:\t\t";
		User.printAllCard();
		cout << "(" << User.getCardSum() << ")\n";
	}
	if(User.getCardSum()<=21){
		hostPharse();
	}else{
		x = 'n';
		cout << "You burst.\n";
		doReplay();
	}
}

int main()
{
	srand(time(NULL));
	cout << "Welcome to BlackJack\n";
	init();		
	return 0;
}