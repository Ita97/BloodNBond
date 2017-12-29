//
// Created by ita on 29/12/17.
//

#ifndef BLOODBOND_MESSAGE_H
#define BLOODBOND_MESSAGE_H

#include <string>

class Message {
private:
    std::string content;
public:
    explicit Message(std::string strings=""){
        //todo enter a sprite
    }
    void setContent(std::string& message){
        content=message;
    }
    std::string readMessage(){
        return content;
    }
};


#endif //BLOODBOND_MESSAGE_H
