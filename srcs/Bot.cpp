#include "../include/Bot.hpp"

short Bot::bot_count = 0;

Bot::Bot(string botname, Server& server) : Client(), server(server){
    this->isBot = true;
    bot_count++;
    string str = botname + to_string(bot_count);
    this->setNickname(str);
    this->setUsername(str);
    this->setHostname(str);
    this->setServername(str);
    this->setRealname(str);
}

Bot::~Bot(){
    bot_count--;
}

void Bot::sendMessage(const string &message, const string &target){
    vector<string> params;
    params.push_back(target);
    params.push_back(message);
    server.PRIVMSG(params, *this);
}
void Bot::takeMessage(const string &message, const string &target){
    cout << "Taking message from [" << target << "] : [" << message << "]" << endl;
}

int Bot::getServerfd() const{
    return server.getServerfd();
}  