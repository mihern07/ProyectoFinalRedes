#ifndef _H_Server_H_
#define _H_Server_H_

#include <vector>
#include <unordered_map>

class SocketServer;
class ServerGame;
class Message;

struct neededInfo{
    neededInfo(std::string person, std::string isDecision, std::string nextDialogue) :
    person_(person), isDecision_(isDecision), nextDialogue_(nextDialogue){};

    std::string person_;
    std::string isDecision_;
    std::string nextDialogue_;
};

class Server 
{
public:
    /**
     * @param s ip to connect to
     * @param p port to connect to
     */
    Server(const char * s, const char * p);

    ~Server();

    /**
     * Launched on main thread, receives and processes messages from clients
     */
    void ProcessMessages();

    /**
     * Sends a message to all clients connected to the server
     * @param msg message to send
     */
    void SendToClients(Message msg);

private:

    /**
     * Creates and sets the thread that runs the game on the server
     * While main thread takes care of receiving messages
     */
    void CreateGameThread();

    /**
     * Thread function that runs the game server side
     */
    static void* RunGame(void*);

    int numRegisteredClients;
    SocketServer* _client1;
    SocketServer* _client2;

    int maxDialogueNumber;
    std::unordered_map<std::string, neededInfo> msgs_;

    /**
     * Socket del servidor
     */
    SocketServer* _socket = nullptr;

    const int MAX_PLAYERS = 2;

    static volatile bool _gameEnd; //when there are not enough clients to run game, true
};
#endif