#include "Message.h"
#include <string.h>
#include <iostream>

Message::Message(){}

Message::Message(const uint8_t type) : _type(type){} //LOGIN, LOGOUT, START

Message::Message(const uint8_t type, char player)
    : _type(type), _player(player){}

Message::Message(const uint8_t type, int dialogueNum1, int dialogueNum2)    //NEW_DIALOGUE, NEW_WAITING_DIALOGUE
    : _type(type), _dialogueNum1(dialogueNum1), _dialogueNum2(dialogueNum2){}

Message::Message(const uint8_t type, int decision1, int decision2, int decision3)   //NEW_DECISION, NEW_WAITING_DECISION
    : _type(type), _decision1(decision1), _decision2(decision2), _decision3(decision3){}

Message::Message(const uint8_t type, int nextDialogue) : _type(type), _nextDialogue(nextDialogue){} //NEXT_DIALOGUE

//Allocates dinamyc memory for _data
void Message::AllocData(size_t size)
{
    _data = new char[size];
    _size = size; 
}

void Message::to_bin()
{
    if (_type == Message::NEW_DIALOGUE || _type == Message::NEW_WAITING_DIALOGUE){
        AllocData(sizeof(uint8_t) + (sizeof(char) * 32) * 2);
        char* tmp = _data;

        memcpy((void*)tmp, (void*)&_type, sizeof(uint8_t));
        tmp += sizeof(uint8_t);

        memcpy((void*)tmp, (void*)&_dialogueNum1, sizeof(int));
        tmp += sizeof(int);

        memcpy((void*)tmp, (void*)&_dialogueNum2, sizeof(int));
        tmp += sizeof(int);
    }else if (_type == Message::NEW_DECISION || _type == Message::NEW_WAITING_DECISION){
        AllocData(sizeof(uint8_t) + (sizeof(int) * 3));
        char* tmp = _data;

        memcpy((void*)tmp, (void*)&_type, sizeof(uint8_t));
        tmp += sizeof(uint8_t);

        memcpy((void*)tmp, (void*)&_decision1, sizeof(int));
        tmp += sizeof(int);

        memcpy((void*)tmp, (void*)&_decision2, sizeof(int));
        tmp += sizeof(int);

        memcpy((void*)tmp, (void*)&_decision3, sizeof(int));
        tmp += sizeof(int);

    }else if (_type == Message::CHOSE_DECISION){
        AllocData(sizeof(uint8_t) + sizeof(int));
        char* tmp = _data;

        memcpy((void*)tmp, (void*)&_type, sizeof(uint8_t));
        tmp += sizeof(uint8_t);

        memcpy((void*)tmp, (void*)&_nextDialogue, sizeof(int));
    }else if (_type == Message::NEXT_DIALOGUE){
        AllocData(sizeof(uint8_t));
        char* tmp = _data;

        memcpy((void*)tmp, (void*)&_type, sizeof(uint8_t));
    }
    else if(_type == Message::INIT || _type == Message::LOGOUT) //package init/logout info
    {
        AllocData(sizeof(uint8_t) + sizeof(char));
        
        char* tmp = _data;

        memcpy((void*)tmp, (void*)&_type, sizeof(uint8_t));
        tmp += sizeof(uint8_t);
        memcpy(tmp, &_player, sizeof(char));
    }
    else
    {
        AllocData(sizeof(uint8_t));
        memcpy((void*)_data, (void*)&_type, sizeof(uint8_t));
    }
}

int Message::from_bin(char * data)
{   
   //if type = LOGIN | START only _type is read
    char* tmp = data;
    memcpy(&_type, tmp, sizeof(uint8_t)); //read type of message from data
    tmp += sizeof(uint8_t); 

    if (_type == Message::NEW_DIALOGUE || _type == Message::NEW_WAITING_DIALOGUE){
        memcpy(&_dialogueNum1, tmp, sizeof(int));
        tmp += sizeof(int);

        memcpy(&_dialogueNum2, tmp, sizeof(int));
    }else if (_type == Message::NEW_DECISION || _type == Message::NEW_WAITING_DECISION){
        memcpy(&_decision1, tmp, sizeof(int));
        tmp += sizeof(int);

        memcpy(&_decision2, tmp, sizeof(int));
        tmp += sizeof(int);

        memcpy(&_decision3, tmp, sizeof(int));
    }else if (_type == Message::CHOSE_DECISION){
        memcpy(&_nextDialogue, tmp, sizeof(int));
    }
    else if(_type == Message::INIT || _type == Message::LOGOUT) //save init/logout info
    {
        memcpy(&_player, tmp, sizeof(char));
    }

    return 0;
}

Message::~Message()
{
    if(_data != nullptr)
    {
         delete[] _data;
         _data = nullptr;
    }
    //TODO: deletes
}