#include <stdio.h>   
#include <stdlib.h>     
#include <time.h>     
#include <windows.h>
#include <iostream>


int CardPick(int b[36]) {/*b - deck check for duclicate*/
	int cardElement;

	cardElement = rand() % 52;

	if (b[cardElement] == 1) {
		CardPick(b);
	}
	else {
		b[cardElement] = 1;

		return cardElement;

	}

	

	
}



int main() {
	srand(time(NULL));

	std::string answerAllGame = "yes";/*Хочет ли игрок продолжать играть*/

	int balance = 10000;/*переменная котороя отображает баланс игрока*/

	std::cout << "Welcome to 'Blackajack'!" << std::endl;


	while (balance != 0) {


		std::string DilerPrintCards;/*переменная которая отображает только одну карту дилера*/

		int DilerPrintScore;/*переменная которая отображает только очки дилера за одну карту*/

		int PlayerCheckA = 0;/*переменная для проверки руки игрока на наличие туза */

		int DilerCheckA = 0;/*переменная для проверки руки дилера на наличие туза*/

		std::string playerCards;/*Переменная в которой хранятся взятые карты*/

		std::string dilerCards;/*Переменная в которой хранятся взятые карты*/

		int bet;/*Переменная в которой хранится ставка игрока*/

		float koef;/*коеффицент выплат(x2.5|x1.5|x1)*/

		int playerScore = 0;/*Переменная в которой хранятся набранные очки игрока */

		int dilerScore = 0;/*Переменная в которой хранятся набранные очки дилера*/

		int CardNumber;/*Переменная в которой хранится номер карты*/

		int blackjackPlayer = 0;/*Переменная для проверки на блекджек у игрока(|Если 0 - нету блекджека|Если 1 - то есть блекджек||)*/

		int blackjackDiler = 0;/*Переменная для проверки на блекджек у игрока(|Если 0 - нету блекджека|Если 1 - то есть блекджек||)*/

		std::string answer;/*Перемення для всех ответов, например(yes/no,+/-)*/

		std::string deck[52] = {/*Колода карты(Для вывода на экран)*/
			"2 ","2 ","2 ","2 ",
			"3 ","3 ","3 ","3 ",
			"4 ","4 ","4 ","4 ",
			"5 ","5 ","5 ","5 ",
			"6 ","6 ","6 ","6 ",
			"7 ","7 ","7 ","7 ",
			"8 ","8 ","8 ","8 ",
			"9 ","9 ","9 ","9 ",
			"10 ","10 ","10 ","10 ",
			"J ","J ","J ","J ",
			"Q ","Q ","Q ","Q ",
			"K ","K ","K ","K ",
			"A ","A ","A ","A " };

		int deckPoints[52] = {/*Колода карты(Для вывода подсчёта очков)*/
			2,2,2,2,
			3,3,3,3,
			4,4,4,4,
			5,5,5,5,
			6,6,6,6,
			7,7,7,7,
			8,8,8,8,
			9,9,9,9,
			10,10,10,10,
			10,10,10,10,
			10,10,10,10,
			10,10,10,10,
			11,11,11,11, };

		int checkDeck[52]{};/*Массив в котором записываются карты которые повторились*/



		std::cout << "Want to play ('+'to continue / '-' to exit): ";

		std::cin >> answer;

		std::cout << std::endl;

		answerAllGame = answer;

		if (answerAllGame == "-") {
			break;
		}

		while (answer != "-" && answer != "+") {
			std::cout << "Dont understand: ";
			std::cin >> answer;

		};

		if (answer == "no") {
			std::cout << "OK! See you next time!";
			return 0;
		}

		std::cout << "" << std::endl;
		std::cout << "Payouts for combinations(win): Blackjack(|10 A|J A|Q A|K A|) - 2.5x  " << std::endl;
		std::cout << "Other combinations(win) - 2x" << std::endl;
		std::cout << "Draw - 1x" << std::endl;
		std::cout << "" << std::endl;


		std::cout << "Balance:" << balance << std::endl;
		std::cout << "Your bet:";
		std::cin >> bet;


		while (bet > balance) {
			std::cout << "Your bet more than balance(input again):";
			std::cin >> bet;
		}

		balance = balance - bet;


		for (int n = 0; n < 2; n++) {/*Player take two cards*/

			CardNumber = CardPick(checkDeck);/*выберает случайную карту*/
			if (deck[CardNumber] == "A ") {
				PlayerCheckA++;
			}
			playerScore += deckPoints[CardNumber];
			playerCards += deck[CardNumber];
		}


		for (int n = 0; n < 2; n++) {/*Dealer take two cards*/

			CardNumber = CardPick(checkDeck);
			if (deck[CardNumber] == "A ") {
				DilerCheckA++;
			}
			dilerScore += deckPoints[CardNumber];
			dilerCards += deck[CardNumber];


		}

		system("cls");

		DilerPrintScore = deckPoints[CardNumber];

		DilerPrintCards = deck[CardNumber];

		std::cout << "Your cards: " << playerCards << " Points: " << playerScore << std::endl;
		std::cout << "Dealer cards: X " << DilerPrintCards << " Points: X + " << DilerPrintScore << std::endl;

		Sleep(500);


		if (playerScore == 21) {/*проверка на блекжек у игрока*/
			std::cout << "Player got a BLACKJACK!" << std::endl;
			blackjackPlayer++;
		}

		if (dilerScore == 21) {
			blackjackDiler++;
		}

		/*Player take a card*/

		while (answer != "-" && playerScore != 21 && playerScore < 21) {
			std::cout << "more(+/-):";
			std::cin >> answer;

			if (answer == "-") {
				break;
			}

			system("cls");


			CardNumber = CardPick(checkDeck);/*выберает случайную карту*/


			if (deckPoints[CardNumber] == 11 && deckPoints[CardNumber] + dilerScore > 21) {
				playerScore += 1;
				playerCards += "A ";

			}
			else {
				playerScore += deckPoints[CardNumber];
				playerCards += deck[CardNumber];

			}

			if (PlayerCheckA > 0 && playerScore + deckPoints[CardNumber] > 21) {
				playerScore = playerScore - 10;

				PlayerCheckA = PlayerCheckA - 1;
			}



			std::cout << "Your cards: " << playerCards << " Points: " << playerScore << std::endl;
			std::cout << "Dealer cards: X " << DilerPrintCards << " Points: X + " << DilerPrintScore << std::endl;

			Sleep(500);

		}
		system("cls");


		if (blackjackPlayer == 1) {/*проверка на блекжек у игрока*/
			std::cout << "Player got a BLACKJACK!" << std::endl;

		}
		std::cout << "Your cards: " << playerCards << " Points: " << playerScore << std::endl;
		std::cout << std::endl;

		if (blackjackDiler == 1) {
			std::cout << "dealer got a BLACKJACK!" << std::endl;

		}
		std::cout << "Dealer cards: " << dilerCards << " Points: " << dilerScore << std::endl;
		std::cout << std::endl;

		Sleep(500);

		/*Diler take card*/
		while (dilerScore < 17) {
			system("cls");


			CardNumber = CardPick(checkDeck);

			if (deckPoints[CardNumber] == 11 && deckPoints[CardNumber] + dilerScore > 21) {
				dilerScore += 1;
				dilerCards += "A ";


			}
			else {
				dilerScore += deckPoints[CardNumber];
				dilerCards += deck[CardNumber];
			}

			if (DilerCheckA > 0 && dilerScore + deckPoints[CardNumber] > 21) {
				dilerScore = dilerScore - 10;

				DilerCheckA = DilerCheckA - 1;
			}

			if (blackjackPlayer == 1) {
				std::cout << "Player got a BLACKJACK!" << std::endl;
			}
			std::cout << "Your cards: " << playerCards << " Points: " << playerScore << std::endl;
			std::cout << std::endl;


			if (blackjackDiler == 1) {
				std::cout << "dealer got a BLACKJACK!" << std::endl;
			}
			std::cout << "Dealer cards: " << dilerCards << " Points: " << dilerScore << std::endl;
			std::cout << std::endl;


			Sleep(700);

		}

		std::cout << std::endl;
		if (playerScore > 21 || playerScore < dilerScore && dilerScore <= 21 || blackjackPlayer == 0 && blackjackDiler == 1) {
			std::cout << "You lose!" << std::endl;
			std::cout << "Your current balance:" << balance << std::endl;
		}

		if (playerScore <= 21 && dilerScore > 21 && blackjackPlayer == 0 || dilerScore < playerScore && playerScore <= 21 && blackjackPlayer == 0) {
			koef = 2;

			std::cout << "You win!(+" << bet * koef << ")" << std::endl;

			balance += bet * koef;

			std::cout << "Your current balance:" << balance << std::endl;
		}

		if (blackjackPlayer == 1) {
			koef = 2.5;

			std::cout << "You win!!!(Blackjack!)(+" << bet * koef << ")" << std::endl;

			balance += bet * koef;

			std::cout << "Your current balance:" << balance << std::endl;
		}

		if (playerScore == dilerScore && dilerScore <= 21 && blackjackPlayer == 0 && blackjackDiler == 0) {
			koef = 1;

			std::cout << "It's a draw! (+" << bet * koef << ")" << std::endl;

			balance += bet * koef;

			std::cout << "Your current balance:" << balance << std::endl;

		}

		Sleep(5000);

		system("cls");

	}

	std::cout << std::endl;


	if (balance == 0) {
		std::cout << "You lost all your money." << std::endl;
		std::cout << "Your current balance is 0. " << std::endl;
		std::cout << "So you can leave :(" << std::endl;
	}
	else{
		std::cout << "Ok. Until next time";
	}

	return 0;
}

