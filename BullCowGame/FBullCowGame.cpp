#include "FBullCowGame.h"

using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length(); }

void FBullCowGame::Reset()
{
	const int32 MAX_TRIES = 3;
	const FString HIDDEN_WORD = "skin";

	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	return;
}
// receives a VALID guess, increments and turn and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	// increment the return number
	MyCurrentTry++;
	// setup a return number
	FBullCowCount BullCowCount;
	// loop through all letters in guess
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++)
	{
		// compare letters against hidden word
		for (int32 GWChar = 0; GWChar < HiddenWordLength; GWChar++)
		{
			// if they match then
			if (Guess[GWChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GWChar)
				{
					BullCowCount.Bulls++; //incriment bulls if in the same place
				}
				else
				{
					BullCowCount.Cows++; //increment cows if not
				}
			}
		}
	}
	return BullCowCount;
}

bool FBullCowGame::IsGameWon() const
{
	return false;
}

EGuessWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (false)//if guess isn't isogram 
	{
		return EGuessWordStatus::Not_Isogram;
	}
	else if (false)	//if not lower case 
	{
		return EGuessWordStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())//if length is wrong
	{
		return EGuessWordStatus::Wrong_Length;
	}
	else //otherwise
	{
		return EGuessWordStatus::OK;
	}
}