#ifndef _H_Decision_H_
#define _H_Decision_H_

#include <string>

struct Decision
{
    int text1;
    int text2;
    int text3;

    //converts data separated by '\0' to string
    std::string toString()
    {
        std::string str = std::to_string(text1);
        str += '\0';
        str += std::to_string(text2);
        str += '\0';
        str += std::to_string(text3);
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