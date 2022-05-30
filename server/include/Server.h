#ifndef _H_Server_H_
#define _H_Server_H_

#include <vector>

class Socket;
class ServerGame;
class Message;
// struct InputInfo;

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

    /**
     *  Lista de clientes conectados al servidor de Chat, representados por
     *  su socket
     */
    std::vector<Socket *> _clients;

    /**
     * Socket del servidor
     */
    Socket* _socket = nullptr;

    const int MAX_PLAYERS = 2;

    static ServerGame* _game;

    static volatile bool _inputRegistered; //set to true when al player input is collected for update

    static volatile bool _gameEnd; //when there are not enough clients to run game, true

    // static InputInfo* _playersInput; //collects all player input
};
#endif