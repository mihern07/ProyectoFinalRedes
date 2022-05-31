#ifndef _H_Decision_H_
#define _H_Decision_H_

#include <string>

struct Decision
{
        std::string text1;
    std::string text2;
    std::string text3;

    //converts data separated by '\0' to string
    std::string toString()
    {
        std::string str = text1;
        str += '\0';
        str += text2;
        str += '\0';
        str += text3;
        str += '\0';
        return str;
    }

    //reconstructs data from string, or const char * due to simplicity
    void fromString(const char* str)
    {
        int i = 0; std::string aux = "";

        while(str[i] != '\0') { aux += str[i]; i++; };
        
        text1 = std::stoi(aux); 
        
        i++; aux = ""; //discard '\0' and old aux data

        while(str[i] != '\0') { aux += str[i]; i++; };

        text2 = std::stoi(aux);

        i++; aux = ""; //discard '\0' and old aux data

        while(str[i] != '\0') { aux += str[i]; i++; };

        text3 = std::stoi(aux);
    }
};
#endif