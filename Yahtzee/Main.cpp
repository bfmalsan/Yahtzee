//Text-based Yahtzee project
//By: Brian Malsan

#include <iostream>
#include <math.h>
#include <time.h>
#include <string>

using namespace std;

/*
GAME:
1. Player's turn starts
2. Roll all 5 die, can roll 3 times per turn
3. Select which die you want to keep
4. Roll2: Either stop and score, or re-roll the dice you want
5. Roll3: Either stop and score, or re-roll the dice you want
6. Choose the location you want to place your score
7. Repeat until players score 13 times
*/

enum {ONE, TWO, THREE, FOUR, FIVE, SIX};


struct playerScoreCard {
	//Upper Section:
	int Ones = -1;
	int Twos = -1;
	int Threes = -1;
	int Fours = -1;
	int Fives = -1;
	int Sixes = -1;
	int UpperTotal = -1;
	int UpperBonus = 35;
	//Lower Section:
	int ThreeKind = -1;
	int FourKind = -1;
	int FullHouse = -1;
	int SmallS = -1;
	int LargeS = -1;
	int Yahtzee = -1;
	int Chance = -1;
	int NumberYahtzees = 0;
	int LowerTotal = -1;
	int LowerBonus = 100; //YAHTZEE bonus
	//Total (end) Score
	int TotalScore = -1;
};

//FUnction that handles the math 
int roll() {
	return rand() % 6 + 1;
}

void rollAllDice(int dice[5]) {
	//loop through all die, give each die a random number between 1 and 6

	for (int i = 0; i < 5; i++) {
		dice[i] =  roll();
	}

}

void rollSelectDice(int dice[5], int rollIndex[5]) {

	for (int i = 0; i < 5; i++) {
		//If the die is selected, then roll
		if (rollIndex[i] == 1) {
			dice[i] = roll();
		}
	}
}

void printAllDice(int dice[5]) {
	//loop through all die, print their number value
	cout << "DICE: ";
	
	for (int i = 0; i < 5; i++) {
		cout << dice[i] << " ";
	}

	cout << endl;
}


void printLine(string des, int value) {
	//Since you can have a 0 as a score, I initalized the scores to -1 and if it is that then we print a blank
	if (value == -1) {
		cout << des << endl;
	}
	//If not the original value than print the value
	else {
		cout << des << value << endl;
	}

}

int getUpperTotal(playerScoreCard score) {
	int bonus = 0;

	//The if statements are so we are not adding -1 to the score.
	if (score.Ones != -1) {
		bonus += score.Ones;
	}
	if (score.Twos != -1) {
		bonus += score.Twos;
	}
	if (score.Threes != -1) {
		bonus += score.Threes;
	}
	if (score.Fours != -1) {
		bonus += score.Fours;
	}
	if (score.Fives != -1) {
		bonus += score.Fives;
	}
	if (score.Sixes != -1) {
		bonus += score.Sixes;
	}
	return bonus;
}

/*
The player is going to want to be able to see their scorecard when they are
deciding what to try for each round. 
*/
void printPlayerScoreCard(playerScoreCard score) {
	cout << "Player Score Card" << endl;
	cout << "Upper Section:" << endl;
	printLine("\t1.Ones- " , score.Ones);
	printLine("\t2.Twos- " , score.Twos);
	printLine("\t3.Threes- " , score.Threes);
	printLine("\t4.Fours- " , score.Fours);
	printLine("\t5.Fives- " , score.Fives);
	printLine("\t6.Sixes- " , score.Sixes);
	cout << "\tBonus Progress- " << getUpperTotal(score) << "/63" << endl;
	printLine("\tUpper Total- " , score.UpperTotal);
	//printLine("\tUpper Bonus- " , score.UpperBonus);
	//Lower Section:
	cout << "Lower Section:" << endl;
	printLine("\t7.Three of a Kind- " , score.ThreeKind);
	printLine("\t8.Four of a Kind- " , score.FourKind);
	printLine("\t9.Full House- " , score.FullHouse);
	printLine("\t10.Small Straight- " , score.SmallS);
	printLine("\t11.Large Straight- " , score.LargeS);
	printLine("\t12.Yahtzee- " , score.Yahtzee);
	printLine("\t13.Chance- " , score.Chance);
	if (score.NumberYahtzees != 0) {
		printLine("\tNumber of Yahtzees- ", score.NumberYahtzees);
	}
	printLine("\tLower Total- " , score.LowerTotal);
	//printLine("\tLower Bonus- " , score.LowerBonus);
	//Total (end) Score
	printLine("TotalScore: " , score.TotalScore);
	cout << endl;
}

void parseRollResponse(string line, int rollIndex[5]) {
	//zero out the rollIndex array
	for (int i = 0; i < 5; i++) {
		rollIndex[i] = 0;
	}

	for (int i = 0; i < line.length(); i++) {

		switch (line[i]) {
		case '1':
			rollIndex[0] = 1;
			break;
		case '2':
			rollIndex[1] = 1;
			break;
		case '3':
			rollIndex[2] = 1;
			break;
		case '4':
			rollIndex[3] = 1;
			break;
		case '5':
			rollIndex[4] = 1;
			break;
		case ' ':
			break;
		default:
			break;
		}

	}
	
	//cout << "DEBUG ROLL INDEX: ";
	//for (int i = 0; i < 5; i++) {
	//	cout << rollIndex[i] << " ";
	//}
	//cout << endl;

}

//Returns the total score of all the dice added up
int getTotalOfDice(int dice[5]) {
	return dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
}

//teting for upper section
bool TestSingleNumber(int value) {
	if (value > 0) {
		return true;
	}

	return false;
}

//Testing functions for lower section
bool TestThreeKind(int amount[6]) {
	for (int i = 0; i < 6; i++) {
		if (amount[i] >= 3) {
			return true;
		}
	}

	return false;
}

bool TestFourKind(int amount[6]) {
	for (int i = 0; i < 6; i++) {
		if (amount[i] >= 4) {
			return true;
		}
	}

	return false;
}

bool TestFullHouse(int amount[6]) {

	//This is gross!
	for (int i = 0; i < 6; i++) {
		if (amount[i] == 3) {
			for (int j = 0; j < 6; j++) {
				if (amount[j] == 2) {
					return true;
				}
			}
		}
	}

	return false;
}

bool TestSmallStraight(int amount[6]) {
	if (amount[ONE] >= 1 && amount[TWO] >= 1 && amount[THREE] >= 1 && amount[FOUR] >= 1) {
		return true;
	}
	if (amount[TWO] >= 1 && amount[THREE] >= 1 && amount[FOUR] >= 1 && amount[FIVE] >= 1) {
		return true;
	}
	if (amount[THREE] >= 1 && amount[FOUR] >= 1 && amount[FIVE] >= 1 && amount[SIX] >= 1) {
		return true;
	}

	return false;
}

bool TestLargeStraight(int amount[6]) {
	if (amount[ONE] == 1 && amount[TWO] == 1 && amount[THREE] == 1 && amount[FOUR] == 1 && amount[FIVE] == 1) {
		return true;
	}
	if (amount[TWO] == 1 && amount[THREE] == 1 && amount[FOUR] == 1 && amount[FIVE] == 1 && amount[SIX] == 1) {
		return true;
	}

	return false;
}

bool TestYahtzee(int amount[6]) {
	for (int i = 0; i < 6; i++) {
		if (amount[i] == 5) {
			return true;
		}
	}

	return false;
}

void PlaceScore(int value,int roundScore,int options[13], playerScoreCard *score) {
	switch (value) {
	case 1:
		if (options[0] == 1) {
			score->Ones = roundScore;
		}
		break;
	case 2:
		if (options[1] == 1) {
			score->Twos = roundScore;
		}
		break;
	case 3:
		if (options[2] == 1) {
			score->Threes = roundScore;
		}
		break;
	case 4:
		if (options[3] == 1) {
			score->Fours = roundScore;
		}
		break;
	case 5:
		if (options[4] == 1) {
			score->Fives = roundScore;
		}
		break;
	case 6:
		if (options[5] == 1) {
			score->Sixes = roundScore;
		}
		break;
	case 7:
		if (options[6] == 1) {
			score->ThreeKind = roundScore;
		}
		break;
	case 8:
		if (options[7] == 1) {
			score->FourKind = roundScore;
		}
		break;
	case 9:
		if (options[8] == 1) {
			score->FullHouse = roundScore;
		}
		break;
	case 10:
		if (options[9] == 1) {
			score->SmallS = roundScore;
		}
		break;
	case 11:
		if (options[10] == 1) {
			score->LargeS = roundScore;
		}
		break;
	case 12:
		if (options[11] == 1) {
			score->Yahtzee = roundScore;
			//score->NumberYahtzees++;
		}
		break;
	case 13:
		if (options[12] == 1) {
			score->Chance = roundScore;
		}
		break;
	default:
		break;
	}
}

void RoundScoring(int dice[5],playerScoreCard *score) {
	/*
	1.Figure out what are the possibilities corresponding to the dice
	2.Ask the player where they want to score
	3.Place the score
	*/
	int amount[6];//array to hold the amounts
	for (int i = 0; i < 6; i++) {
		amount[i] = 0; //zero out before we add to them
	}

	//int numOnes = 0, numTwos = 0, numThrees = 0, numFours = 0, numFives = 0, numSixes = 0; //variables to hold the quantity of each number
	//I'll use the quantities to determine what can be scored

	for (int i = 0; i < 5; i++) {
		if (dice[i] == 1) {
			amount[ONE]++;
		}
		else if (dice[i] == 2) {
			amount[TWO]++;
		}
		else if (dice[i] == 3) {
			amount[THREE]++;
		}
		else if (dice[i] == 4) {
			amount[FOUR]++;
		}
		else if (dice[i] == 5) {
			amount[FIVE]++;
		}
		else if (dice[i] == 6) {
			amount[SIX]++;
		}
	}

	if (TestYahtzee(amount)) {
		cout << "YAHTZEE!!!!!" << endl;
		if (score->Yahtzee != 0) {
			score->NumberYahtzees++;
		}
	}

	
	//Test if the score had already been filled out, if not test if the current dice can be scored in any of the spots,
	//if there is no valid score spots asks the player which spot they want to place a 0
	
	int roundScore[13]; //array to hold all possible scores
	int validOptions[13]; //array to hold all valid options
	int canPlaceZeroScore[13]; //array to hold valid locations to place a 0 when there is not other options
	for (int i = 0; i < 13; i++) {
		validOptions[i] = 0;
		canPlaceZeroScore[i] = 0;
	}

	cout << "OPTIONS: " << endl;

	if (score->Ones == -1) {
		if (TestSingleNumber(amount[ONE])) {
			roundScore[0] = amount[ONE] * 1;
			cout << "1. Can score in Ones for " << roundScore[0] << " points"<<endl;
			validOptions[0] = 1;		
		}
		canPlaceZeroScore[0] = 1;
	}
	if (score->Twos == -1) {
		if (TestSingleNumber(amount[TWO])) {
			roundScore[1] = amount[TWO] * 2;
			cout << "2. Can score in Twos for " << roundScore[1] << " points" << endl;
			validOptions[1] = 1;
		}
		canPlaceZeroScore[1] = 1;
	}
	if (score->Threes == -1) {
		if (TestSingleNumber(amount[THREE])) {
			roundScore[2] = amount[THREE] * 3;
			cout << "3. Can score in Threes for " << roundScore[2] << " points" << endl;
			validOptions[2] = 1;
		}
		canPlaceZeroScore[2] = 1;
	}
	if (score->Fours == -1) {
		if (TestSingleNumber(amount[FOUR])) {
			roundScore[3] = amount[FOUR] * 4;
			cout << "4. Can score in Fours for " << roundScore[3] << " points" << endl;
			validOptions[3] = 1;
		}
		canPlaceZeroScore[3] = 1;
	}
	if (score->Fives == -1) {
		if (TestSingleNumber(amount[FIVE])) {
			roundScore[4] = amount[FIVE] * 5;
			cout << "5. Can score in Fives for " << roundScore[4] << " points" << endl;
			validOptions[4] = 1;
		}
		canPlaceZeroScore[4] = 1;
	}
	if (score->Sixes == -1) {
		if (TestSingleNumber(amount[SIX])) {
			roundScore[5] = amount[SIX] * 6;
			cout << "6. Can score in Sixes for " << roundScore[5] << " points" << endl;
			validOptions[5] = 1;
		}
		canPlaceZeroScore[5] = 1;
	}
	if (score->ThreeKind == -1) {
		if (TestThreeKind(amount)) {
			roundScore[6] = getTotalOfDice(dice);
			cout << "7. Can score in Three of a Kind for " << roundScore[6] << " points" << endl;
			validOptions[6] = 1;
		}
		canPlaceZeroScore[6] = 1;
	}
	if (score->FourKind == -1) {
		if (TestFourKind(amount)) {
			roundScore[7] = getTotalOfDice(dice);
			cout << "8. Can score in Four of a Kind for " << roundScore[7] << " points" << endl;
			validOptions[7] = 1;
		}
		canPlaceZeroScore[7] = 1;
	}
	if (score->FullHouse == -1) {
		if (TestFullHouse(amount)) {
			roundScore[8] = 25;
			cout << "9. Can score in Full House for 25 points" << endl;
			validOptions[8] = 1;
		}
		canPlaceZeroScore[8] = 1;
	}
	if (score->SmallS == -1) {
		if (TestSmallStraight(amount)) {
			roundScore[9] = 30;
			cout << "10. Can score in Small Straight for 30 points" << endl;
			validOptions[9] = 1;
		}
		canPlaceZeroScore[9] = 1;
	}
	if (score->LargeS == -1) {
		if (TestLargeStraight(amount)) {
			roundScore[10] = 40;
			cout << "11. Can score in Large Straight for 40 points" << endl;
			validOptions[10] = 1;
		}
		canPlaceZeroScore[10] = 1;
	}
	if (score->Yahtzee == -1) {
		if (TestYahtzee(amount)) {
			roundScore[11] = 50;
			cout << "12. Can score in Yahtzee for 50 points" << endl;
			validOptions[11] = 1;
		}
		canPlaceZeroScore[11] = 1;
	}
	if (score->Chance == -1) {
		roundScore[12] = getTotalOfDice(dice);
		cout << "13. Can score in Chance for " << roundScore[12] << " points" << endl;
		validOptions[12] = 1;
		canPlaceZeroScore[12] = 1;//But why you would ever do this is crazy
	}

	//If there are no available options, must ask the player which section they want to place a score of 0 for the round
	//If there is options, score as normal
	int place = 0;
	bool noValidOptions = true;

	for (int i = 0; i < 13; i++) {
		if (validOptions[i] == 1) { //If there is a valid option to score, then set noValidOption to false.
			noValidOptions = false;
		}
	}

	if (noValidOptions) {
		cout << "There are no valid scoring options" << endl;
		cout << "Enter location to place a score of 0: ";
		cin >> place;

		PlaceScore(place, 0, canPlaceZeroScore, score);
	}
	else {
		//Ask where the player wants to score this round
		cout << "Enter where to score this round: ";

		cin >> place;

		PlaceScore(place, roundScore[place - 1], validOptions, score);
	}
	cout << endl;
}


void FinalScoring(playerScoreCard* score) {
	//Upper section scoring
	score->UpperTotal = getUpperTotal(*score);

	if (score->UpperTotal >= 63) {//Get the upper bonus
		score->UpperTotal += score->UpperBonus;
	}

	//Lower section scoring
	score->LowerTotal = score->ThreeKind + score->FourKind + score->FullHouse + score->SmallS + score->LargeS + score->Yahtzee + score->Chance;

	//In the lower section you get 100 points for each Yahtzee after the player's first
	if (score->NumberYahtzees > 1) {
		score->LowerTotal += ((score->NumberYahtzees - 1) * score->LowerBonus);
	}

	//Total score is the sum of each section
	score->TotalScore = score->UpperTotal + score->LowerTotal;

}


int main(int argc, char** argv) {

	int dice[5] = { 0,0,0,0,0 };		//game dice
	int rollIndex[5] = { 0,0,0,0,0 };	//index of the sice the player wants to reroll. 0 means do not roll, 1 means roll 
	playerScoreCard playerScore;		//score
	bool gameIsNotOver = true;
	bool stillRolling = true;
	int rolls = 0;
	int roundNumber = 0;
	string response;

	//itialize random seed based on the time the application is started
	srand(time(NULL));

	//game loop
	while (gameIsNotOver) {
		//increment to next round, print Round number.
		roundNumber++;
		cout << "ROUND: " << roundNumber << endl;

		printPlayerScoreCard(playerScore);

		//Loop that deals with the player's turn. Can roll the dice up to three times
		do {
			//cout << "ROLL- " << rolls << endl;

			//If rolls == 0 is true, This means the player's turn is starting so they should roll all the dice
			if (rolls == 0) {
				//cout << "FIRST ROLL: ";
				rollAllDice(dice);
				printAllDice(dice);
			}
			else {
				cout << "Which dice would you like to roll?(1 2 3 4 5): ";
				getline(cin, response);
				//cout << "DEBUG RESPONSE: " << response << endl;

				//Test if we should start scoring
				if (response == "s") {
					stillRolling = false;
				}
				//if 0 is given, re-roll all dice, much better than no response, This way an accidental re-roll is less likely
				else if (response == "0") { 
					rollAllDice(dice);
				}
				else {
					parseRollResponse(response, rollIndex);
					
					//Roll only the die according to the rollIndex. Where there is a 1
					rollSelectDice(dice, rollIndex);
				
				}

				//cout << response << endl;
				printAllDice(dice);
			}
			
			
			//increase rolls
			rolls++;
		} while (stillRolling && rolls < 3);

		//TODO: Round Scoring
		cout << "ROUND SCORING: " << endl << endl;
		RoundScoring(dice, &playerScore);


		//test this at the end of each round to see if the last round took place
		//if yes, set gameIsNotOver to false and jump out of the game loop.
		//if no, go to next round
		if (roundNumber == 13) {
			gameIsNotOver = false;
		}
		
		//reset variables for next turn
		rolls = 0;
		stillRolling = true;
		getchar();
	}


	//Final Scoring. i.e. Totals and bonuses

	FinalScoring(&playerScore);

	printPlayerScoreCard(playerScore);

	getchar();

	return 0;
}

