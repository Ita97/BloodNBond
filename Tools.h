//
// Created by ita on 25/09/17.
//

#ifndef BLOODBOND_TOOLS_H
#define BLOODBOND_TOOLS_H
#include <string>
#include "Character.h"
#include "Detective.h"

enum class toolType{ medicine, key, message, torch };

class Tools{
protected:
    toolType category;
    std::string description;

public:

explicit Tools(toolType cat);
virtual ~Tools(){}


};


#endif //BLOODBOND_TOOLS_H