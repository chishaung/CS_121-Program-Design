/**
* Library
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
* Prototype
*/
void print_game_rules(void);
double get_bank_balance(void);
double get_wager_amount(void);
int calculate_sum_dice(int die1_value, int die2_value);
int is_win_loss_or_point(int sum_dice);
double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract);
void chatter_messages(int Game, double balance, double wager);
int check_wager_amount(double wager, double balance);
int roll_die(void);

/**
* Globol Varaiables
*/
double balance;


/**
* [Main Function]
*/
int main() {

	srand((unsigned)time(NULL));
	int Game = 1;
	int win_lose_point;
	int legal;
	int sum;
	int target;
	double wager;
	balance = 100.00;
	print_game_rules();

	while (balance > 0) {



		balance = get_bank_balance();
		printf("Your bank balance is: %lf\n", balance);

		// Game start to roll the dice
		printf("How much wager you want to bet for?\n");



		// Looping till the wager is valid	
		do {
			// return 2 numbers: 0 for no, 1 for yes
			wager = get_wager_amount();
			printf("You placed %lf bucks.\n", wager);
			legal = check_wager_amount(wager, balance);
		} while (legal == 0);

		// Bet Accepted. Game start!

		chatter_messages(Game, balance, wager);

		// Rolling the dice first time.
		int value_1, value_2;
		value_1 = roll_die();
		value_2 = roll_die();

		printf("Die 1: %d.\nDie 2: %d.\n", value_1, value_2);
		sum = calculate_sum_dice(value_1, value_2);
		printf("Sum of dices is: %d\n", sum);
		target = sum;


		win_lose_point = is_win_loss_or_point(sum);

		if (win_lose_point == 1) {
			printf("You Win\n");
			// pass 1 for add
			balance = adjust_bank_balance(balance, wager, 1);
			printf("Your bank balance is: %lf\n", balance);

		}

		else if (win_lose_point == 0) {
			// pass 2 for substract
			balance = adjust_bank_balance(balance, wager, 0);
			printf("You Lose\n");
			printf("Your bank balance is: %lf\n", balance);
		}

		else if (win_lose_point == -1) {
			printf("The Target is %d\n", sum);
			// Here we are try 7 times, same point is win, or lose
			int try_time = 1;
			int win = 0;
			do {
				printf("Round %d\n", try_time);
				try_time++;
				value_1 = roll_die();
				value_2 = roll_die();
				printf("Die 1: %d.\nDie 2: %d.\n", value_1, value_2);
				sum = calculate_sum_dice(value_1, value_2);
				printf("Sum of dices is: %d\n", sum);
				if (sum == target) {
					try_time = 9;
					win = 1;
				}

				printf("Press Enter for next round.\n");
				getchar();


			} while (try_time < 8);

			// lose
			if (win == 0) {
				// pass 2 for substract
				balance = adjust_bank_balance(balance, wager, 0);
				printf("You Lose\n");
				printf("Your bank balance is: %lf\n", balance);
			}

			// win 
			else if (win == 1) {
				printf("You Win\n");
				// pass 1 for add
				balance = adjust_bank_balance(balance, wager, 1);
				printf("Your bank balance is: %lf\n", balance);
			}

		}

		Game++;
	}


	return 0;
}


void print_game_rules(void) {
	printf("The Rule is to win the game.\n");
}


double get_bank_balance(void) {

	return balance;

}

double get_wager_amount(void) {

	double wager;
	scanf_s("%lf", &wager);

	return wager;

}

int check_wager_amount(double wager, double balance) {

	if (wager > balance) {

		printf("Not a Valid bet. Do it again.\n");
		return 0;
	}

	else {
		printf("Valid bet.\n");
		return 1;
	}
}

int roll_die(void) {
	int value;

	// Create random number between 0 ~ 5
	value = rand() % 6;

	// value = value + 1
	value++;

	return value;

}

int calculate_sum_dice(int value_1, int value_2) {

	int sum;
	sum = value_1 + value_2;

	return sum;
}

int is_win_loss_or_point(int sum) {

	// means the player win 
	if (sum == 7 || sum == 11)
		return 1;

	// means thr player lose 
	else if (sum == 2 || sum == 3 || sum == 12)
		return 0;

	// Sum become target
	else
		return -1;


}

int is_point_loss_or_neither(int sum_dice, int point_value) {
	//Determines the result of any successive roll after the first roll. 
	//If the sum of the roll is the point_value, then 1 is returned. 
	//If the sum of the roll is a 7, then 0 is returned. 
	//Otherwise, -1 is returned.
	int a = 10;
	return a;
}

double adjust_bank_balance(double balance, double wager, int add_or_subtract) {
	// pass 1 for add
	// pass 2 for substract
	double result;

	if (add_or_subtract == 1) {
		result = balance + wager * 2;
	}

	else if (add_or_subtract == 0) {
		result = balance - wager;
	}

	return result;


}

void chatter_messages(int Game, double balance, double wager) {
	if (Game == 1)
		printf(" ****here we go for the first game!**** \n");

	if (balance == wager)
		printf(" ****Show hand! I like it!**** \n");

	if (balance < 30)
		printf(" ****careful buddy, you are gonna break soon**** \n");

	if (wager >= 50)
		printf(" ****WoW! You bet a huge amount!**** \n");


}
