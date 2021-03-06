#include "FBullCowGame.h"
#include <map>

#define TMap std::map

using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const {return bGameIsWon; }

void FBullCowGame::Reset()
{
	const int32 MAX_TRIES = 3;
	const FString HIDDEN_WORD = "skin";

	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;
	return;
}
// receives a VALID guess, increments and turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
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
	if (Guess == MyHiddenWord)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word) 	// for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) {// if the letter is in the map
			return false; // we do NOT have an isogram
		}
		else {
			LetterSeen[Letter] = true;// add the letter to the map
		}
	}

	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) // if not a lowercase letter
		{
			return false;
		}
	}
	return true;
}



EGuessWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))//if guess isn't isogram 
	{
		return EGuessWordStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))	//if not lower case 
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