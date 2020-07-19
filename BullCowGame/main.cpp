/* This is the console executable, that makes use of the BUllCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// TODO FOR FUTURE: to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// TODO FOR FUTURE: function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate (create instance of) a new game, which we re-use across plays

// the entry point for our application
int main() 
{
	std::cout << BCGame.GetCurrentTry();

	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);
	std::cout << std::endl;
	return 0;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//std::cout << MaxTries << std::endl;
	std::cout << std::endl;

	// loop asking for guesses while the game
	//  is NOT won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	//for (int32 count = 1; count <= MaxTries; count++) // TODO change from FOR to WHILE loop once we are validating tries
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	// TODO summarise game
	PrintGameSummary();
	return;
}

// introduce the game
void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?" << std::endl;
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {

		int32 CurrentTry = BCGame.GetCurrentTry();

		
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ".";
		std::cout << " Enter your guess: ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all in lower letters. \n\n";
			break;
		default:
			// assuming the guess is valid
			break;
		}
		//std::cout << std::endl; we are going to get rid of this line because it adds an unneeded line when showing the Bull Cow score results, instead
		// we will be putting a new line after each error message above...
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations on winning!\n";
	}
	else
	{
		std::cout << "Better luck next time\n";
	}

	return;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y or n) ";
	FText Response = "";
	std::getline(std::cin, Response);

	std::cout << "First char: " << Response[0] << std::endl;

	if (Response[0] == 'y' || Response[0] == 'Y')
	{
		//std::cout << "Looks like th is is a y";
		return true;
	}
	
	else if (Response[0] == 'n' || Response[0] == 'N')
	{
		return false;
	}
	
	else
	{
		return false;
	}
}
