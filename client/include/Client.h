#ifndef _H_Client_H_
#define _H_Client_H_

class Socket;
class ClientGame;

class Client
{
public:

    /**
     * Initializes client's resources for connection with server
     * @param s ip to connect socket to 
     * @param p port to connect socket to
     */
    static void Init(const char * s, const char * p);

    /**
     * Releases resources
     */
    static void Release();

    /**
     * Method for receiving messages through thread
     */
    static void* net_thread(void*);

    /**
     * Login to game server
     */
    static void Login();

    /**
     * Logout from game server
     */
    static void Logout(); 

    /**
     * Notifies server that the client's game has been initialized
     * and is ready to start
     */
    static void SendGameReady();

    /**
     * @return if ready to start game
     */
    static inline bool StartGame(){ return _startGame; };

    /**
     * @return if ready to initilize game as player id has been registered
     */
    static inline bool InitGame(){ return _initGame; };

    /**
     * @return player id -> Player 1 or Player 2
     */
    static inline char GetID() { return _id; };

private:
    static Socket* _socket;
    static volatile bool _startGame; //true to start game
    static volatile bool _initGame; //true to init game once player id has been saved

    static ClientGame* _game;
    static char _id; //player id -> Player 1 or Player 2 -> values: (0,1)
};
#endif