#ifndef GUESSBOT_HPP
# define GUESSBOT_HPP 202408

# include "Bot.hpp"
# include <cstdlib> // rand, srand
# include <ctime>   // time

class GuessBot : public Bot {
private:
    int targetNumber;
    int guessCount;
    bool flag;

public:
    GuessBot(Server &server);
    ~GuessBot();

    void startGame();
    void takeMessage(const string &message, const string &target);
    string makeGuess(int guess);
};

#endif /* GUESSBOT_HPP */