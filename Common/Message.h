#ifndef _H_Message_H_
#define _H_Message_H_

#include <string>
#include "Decision.h"
// #include "InputInfo.h"

class Message
{
public:
    /**
     * Constructors for different types of message
     */
    Message();
    Message(const uint8_t type);
    // Message(const uint8_t type, const InputInfo &info, char player);
    Message(const uint8_t type, char player);

    Message(const uint8_t type, std::string dialogueContent1, std::string dialogueContent2);
    Message(const uint8_t type, Decision decision);

    ~Message();

    void to_bin();

    int from_bin(char *data);

    /**
     *  Devuelve un puntero al buffer interno con la representación del objeto.
     *  Debe inicializarse previamente via Serializable::to_bin()
     *    @return objeto serializado
     */
    inline char *data() { return _data; }

    /**
     *  @return tamaño del objeto serializado
     */
    inline int32_t size() { return _size; };

    /**
     * Possible types of message
     */
    enum MessageType
    {
        LOGIN,
        INIT,
        READY,
        START,
        NEW_SCENE,
        NEW_WAITING_SCENE,
        NEW_DIALOGUE,
        NEW_WAITING_DIALOGUE,
        NEW_DECISION,
        NEW_WAITING_DECISION,
        NEXT_DIALOGUE,
        CHOSE_DECISION,
        LOGOUT
    };

    uint8_t _type;

    char _player;

    // InputInfo _inputInfo;
    std::string _dialogueContent1;
    std::string _dialogueContent2;

private:
    /**
     * Allocates dinamyc memory for _data
     * @param size of memory to alloc
     */
    void AllocData(size_t size);

    int32_t _size = 0;

    char *_data = nullptr;


    Decision _decision;
};
#endif