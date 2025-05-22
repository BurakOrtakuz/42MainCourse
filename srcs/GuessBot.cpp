#include "../include/GuessBot.hpp"

GuessBot::GuessBot(Server& server) : Bot("GuessBot", server){
	srand(time(NULL));
	startGame();
	flag = false;
}

GuessBot::~GuessBot(){}

void GuessBot::startGame(){
	this->guessCount = 0;
	this->targetNumber = rand() % 100 + 1;
}

void GuessBot::takeMessage(const string &message, const string &target){
	if (message.at(0) == 'p' || message.at(0) == 'P'){
		this->startGame();
		this->sendMessage("Game started! Target number is between 1 and 100.", target);
		flag = true;
		return ;
	}
	else if (message.at(0) == 'q' || message.at(0) == 'Q'){
		this->sendMessage("Game over! The number was " + to_string(this->targetNumber), target);
		this->sendMessage("Playing with yoy was fun! Goodbye!", target);
		flag = false;
		return ;
	}
	else if (message.at(0) == 'r' || message.at(0) == 'R'){
		this->sendMessage("My number was " + to_string(this->targetNumber), target);
		this->startGame();
		this->sendMessage("Game restarted! Target number is between 1 and 100.", target);
		flag = true;
		return ;
	}
	else if (message.at(0) == 'h' || message.at(0) == 'H'){
		sendMessage("Benim anladığım komutlar şunlardır {p, q, r, h} \r\n", target);
		sendMessage("> p(play: Oyunu başlatır) \r\n", target);
		sendMessage("> q(quit: Oyunu bitirir) \r\n", target);
		sendMessage("> r(restart: Oyunu sıfırlar) \r\n", target);
		sendMessage("> h(help: Yardım menüsünü açar) \r\n", target);
		return ;
	}
	else if (flag && message.find_first_of("0123456789") != string::npos){
		int guess = stoi(message);
		string result = makeGuess(guess);
		this->sendMessage(result, target);
		return ;
	}
	else{
		this->sendMessage("Invalid command! Type 'h' for help.", target);
		return ;
	}
}

string GuessBot::makeGuess(int guess){
	this->guessCount++;
	if (guess == this->targetNumber){
		flag = false;
		return "Correct! You guessed the number in " + to_string(this->guessCount) + " tries.";
	}
	else if (guess < this->targetNumber){
		return "Higher!";
	}
	else{
		return "Lower!";
	}
}