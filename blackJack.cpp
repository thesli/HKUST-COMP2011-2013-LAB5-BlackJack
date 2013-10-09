#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

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
		suit tp = (suit) rand()%4;
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
			sum+=cardList[i].value;
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

void init(){
	User.cardList.clear();
	Host.cardList.clear();
	getACardUser();
	getACardHost();	
}

void printStatus(){
	cout << "Host:\t";
	Host.printAllCardHost();	
	cout << "\n";
	cout << "User:\t";
	User.printAllCard();
	cout << User.getCardSum();
	cout << "\n";
	if(User.getCardSum()<21){
		char t;
		cout << "want a new Card?";
		cin >> t;
		if(t == 'Y'|| t == 'y'){
			getACardUser();
			printStatus();
		}
	}else if(User.getCardSum()==21){
		cout << "You win somewho";
	}else{
		cout << "You busted";
	}
}

int main()
{
	srand(time(NULL));
	cout << "Welcome to BlackJack\n";
	init();	
	printStatus();
	getACardUser();	
	cout << "Play Again?";
	char again;
	cin >> again;
	if(again == 'Y'||again == 'y'){
		main();
	}
	return 0;
}