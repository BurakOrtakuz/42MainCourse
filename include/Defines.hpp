#ifndef DEFINES_HPP
# define DEFINES_HPP 202408L

#include <string>
/*


netstat -t

lsof -i:<portId>
*/
/*PASS, USER, NICK
<message>  ::= [':' <prefix> <SPACE> ] <command> <params> <crlf>
<prefix>   ::= <servername> | <nick> [ '!' <user> ] [ '@' <host> ]
<command>  ::= <letter> { <letter> } | <number> <number> <number>
<SPACE>    ::= ' ' { ' ' }
<params>   ::= <SPACE> [ ':' <trailing> | <middle> <params> ]

<middle>   ::= <Any *non-empty* sequence of octets not including SPACE
               or NUL or CR or LF, the first of which may not be ':'>
<trailing> ::= <Any, possibly *empty*, sequence of octets not including
                 NUL or CR or LF>

<crlf>     ::= CR LF
*/
#define MAX_USER 100
#define MAX_EVENTS 1024
#define CRLF "\r\n"
#define ERR_UNKNOWNCOMMAND(command)        ": 421 " + command + " :Unknown command\r\n" CRLF

//DONE
#define ERR_NONICKNAMEGIVEN                 "ERROR[431]: No nickname given"                            CRLF
#define ERR_ERRONEUSNICKNAME(nick)          "ERROR[432]: " + nick    + " Erroneus nickname"            CRLF
#define ERR_NICKNAMEINUSE(nick)             "ERROR[433]: " + nick    + " Nickname is already in use"   CRLF
#define ERR_NEEDMOREPARAMS(command)         "ERROR[461]: " + command + " Not enough parameters"        CRLF
#define ERR_ALREADYREGISTERED               "ERROR[462]: You may not reregister"                       CRLF


# define BLACK		"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define PURPLE		"\033[0;35m"
# define CYAN		"\033[0;36m"
# define WHITE		"\033[0;37m"
# define END		"\033[m"
# define RESET		"\033[0m"

#endif /* DEFINES_HPP */