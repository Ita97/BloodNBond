//
// Created by ita on 31/12/17.
//

#ifndef BLOODBOND_UTILITIES_H
#define BLOODBOND_UTILITIES_H

#include <string>
#include <sstream>

template <typename T>
std::string toString(T arg){//trasforma numeri in stringhe
    std::stringstream ss;
    ss << arg;
    return ss.str();
}


#endif //BLOODBOND_UTILITIES_H
