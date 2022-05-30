#ifndef _H_ServerGame_H_
#define _H_ServerGame_H_
#include <vector>

//FORWARD DECLARATIONS
class Server;
class GameObject;
class ServerPlayer;
// struct InputInfo;
class Message;

class ServerGame 
{
public:
    ServerGame(Server* server);
    ~ServerGame();

    /**
     * Initializes game
     */
    void Init();

    /**
     * Updates GameObjects
     */
    void Update();

    /**
     * Sets the received input of each player
     * @param info InputInfo of current clients
     */
    // void SetInputInfo(InputInfo* info);

    /**
     * Sends message to all clients
     * @param msg message to send
     */
    void SendToClients(Message msg);

private: 

    Server* _server = nullptr;

    bool _gameLost = false; //true when a player has collided
};
#endif