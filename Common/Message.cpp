#include "Message.h"
#include <string.h>
#include <iostream>

Message::Message(){}

Message::Message(const uint8_t type) : _type(type){} //LOGIN, LOGOUT, START

// Message::Message(const uint8_t type, const InputInfo &info, char player) //INPUT
//     : _type(type), _inputInfo(info), _player(player){} 

Message::Message(const uint8_t type, char player)  
    : _type(type), _player(player){}

Message::Message(const uint8_t type, int dialogueNum1, int dialogueNum2)
    : _type(type), _dialogueNum1(dialogueNum1), _dialogueNum2(dialogueNum2){}

Message::Message(const uint8_t type, int decision1, int decision2, int decision3)
    : _type(type), _decision1(decision1), _decision2(decision2), _decision3(decision3){}

//Allocates dinamyc memory for _data
void Message::AllocData(size_t size)
{
    _data = new char[size];
    _size = size; 
}

void Message::to_bin()
{
// if(_type == INPUT) //package input info
    // {
    //     AllocData(sizeof(uint8_t) + sizeof(char) * (sizeof(InputInfo) + 1)); 
    //     char* tmp = _data; 

    //     memcpy((void*)tmp, (void*)&_type, sizeof(uint8_t));
    //     tmp += sizeof(uint8_t);

    //     memcpy((void*)tmp, &_player, sizeof(char));
    //     tmp += sizeof(char);

    //     memcpy((void*)tmp, _inputInfo.toString().c_str(), sizeof(char) * (sizeof(InputInfo) + 1)); 
    // }
    // else
    if (_type == Message::NEW_SCENE || _type == Message::NEW_WAITING_SCENE){
        // AllocData(sizeof(uint8_t) + sizeof(char) * (sizeof(InputInfo) + 1)); 
        // char* tmp = _data; 

        // memcpy((void*)tmp, (void*)&_type, sizeof(uint8_t));
        // tmp += sizeof(uint8_t);

        // memcpy((void*)tmp, &_player, sizeof(char));
        // tmp += sizeof(char);

        // memcpy((void*)tmp, _inputInfo.toString().c_str(), sizeof(char) * (sizeof(InputInfo) + 1));  
    }else if (_type == Message::NEW_DIALOGUE || _type == Message::NEW_WAITING_DIALOGUE){
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

        memcpy((void*)tmp, (void*)&_decision.text1, sizeof(int));
        tmp += sizeof(int);

        memcpy((void*)tmp, (void*)&_decision.text2, sizeof(int));
        tmp += sizeof(int);

        memcpy((void*)tmp, (void*)&_decision.text3, sizeof(int));
        tmp += sizeof(int);

    }else if (_type == Message::NEXT_DIALOGUE){
        AllocData(sizeof(uint8_t));
        char* tmp = _data;

        memcpy((void*)tmp, (void*)&_type, sizeof(uint8_t));
    }else
    if(_type == Message::INIT || _type == Message::LOGOUT) //package init/logout info
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

    // if(_type == INPUT) //save inputinfo
    // {
    //     //  memcpy(&_player,  tmp, sizeof(char));
    //     // tmp += sizeof(char);
        
    //     // char* str = new char[sizeof(char) * (sizeof(InputInfo) + 1)];
    //     // memcpy(&str[0], tmp, sizeof(char) * (sizeof(InputInfo) + 1));

    //     // _inputInfo.fromString(str);
    //     // delete[] str;
    // }
    // else
    if (_type == Message::NEW_SCENE || _type == Message::NEW_WAITING_SCENE){

    }else if (_type == Message::NEW_DIALOGUE || _type == Message::NEW_WAITING_DIALOGUE){
        memcpy(&_dialogueNum1, tmp, sizeof(int));
        tmp += sizeof(int);

        memcpy(&_dialogueNum2, tmp, sizeof(int));
    }else if (_type == Message::NEW_DECISION || _type == Message::NEW_WAITING_DECISION){
        memcpy(&_decision.text1, tmp, sizeof(int));
        tmp += sizeof(int);

        memcpy(&_decision.text2, tmp, sizeof(int));
        tmp += sizeof(int);

        memcpy(&_decision.text3, tmp, sizeof(int));
    }else
    if(_type == Message::INIT || _type == Message::LOGOUT) //save init/logout info
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