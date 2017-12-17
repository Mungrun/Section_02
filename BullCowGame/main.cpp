/* This is the console excutable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all 
user interaction. For game logic see the FBullCowGame */


#include <iostream>
#include <string>
#include "FBullCowGame.h"

using int32 = int;
using FText = std::string;

void PrintIntro();
void PlayGame();
void PrintGameSummary();

FText GetValidGuess();

bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	}
	while (AskToPlayAgain() == 1);
	return 0; //exit the application
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop for the number of trys asking for guesses
	// while game is NOT won
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		//submit valid guess to game and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows;
		std::cout << std::endl;
		std::cout << std::endl;
	}

	PrintGameSummary();

	return;
}

void PrintIntro()
{
	//introduce the game
	std::cout << std::endl;
	std::cout << "Welcome to Bulls and Cows\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I am thinking of?\n";
	std::cout << std::endl;
	return;
}

//loop unitl valid guess
FText GetValidGuess() 
{
	EGuessWordStatus Status = EGuessWordStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		//get a guess from the player
		int32 MyCurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << MyCurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessWordStatus::Not_Isogram:
			std::cout << "Please enter an isogram.\n\n";
			break;
		case EGuessWordStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessWordStatus::Not_Lowercase:
			std::cout << "Please use lower case.\n\n";
			break;
		case EGuessWordStatus::Contains_Special:
			std::cout << "Special characters are not allowed.\n\n";
			break;
		default: //assume valid guess
			break;
		}
	} 
	while (Status != EGuessWordStatus::OK); // Keep looping until no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Play again? ";
	FText Responce = "";
	std::getline(std::cin, Responce);
		
	return ((Responce[0] == 'y') || (Responce[0] == 'Y'));
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations! You are a winner :)\n\n";
	}
	else
	{
		std::cout << "You ran out of tries :( better luck next time!\n\n";
	}
	return;
}