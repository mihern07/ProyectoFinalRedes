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

    Message(const uint8_t type, int dialogueNum1, int dialogueNum2);
    Message(const uint8_t type, int decision1, int decision2, int decision3);
    Message(const uint8_t type, int nextDialogue);

    ~Message();

    void to_bin();
    int from_bin(char *data);

    /**
     *  Devuelve un puntero al buffer interno con la representación del objeto.
     *  Debe inicializarse previamente via Serializable::to_bin()
     *    @return objeto serializado
     */
    inline char *data() { return _data; }

    inline int getDialogueNum1(){ return _dialogueNum1; }
    inline int getDialogueNum2(){ return _dialogueNum2; }

    inline int getDecision1(){ return _decision1; }
    inline int getDecision2(){ return _decision2; }
    inline int getDecision3(){ return _decision3; }

    inline int getNextDialogue(){ return _nextDialogue; }

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

private:
    /**
     * Allocates dinamyc memory for _data
     * @param size of memory to alloc
     */
    void AllocData(size_t size);

    int32_t _size = 0;

    char *_data = nullptr;

    int _dialogueNum1;
    int _dialogueNum2;

    int _decision1;
    int _decision2;
    int _decision3;

    int _nextDialogue;
};
#endif