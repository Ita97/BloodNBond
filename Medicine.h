//
// Created by ita on 04/10/17.
//

#ifndef BLOODBOND_MEDICINE_H
#define BLOODBOND_MEDICINE_H

#include <string>
enum class medType{hp,sp};

class Medicine {
public:
    explicit Medicine(int value, medType type);

    bool isPsichic(){
        return type == medType::sp;
    }
    bool isPhisical(){
        return type == medType::hp;
    }
    const std::string &getName() const{
        return name;
    }
    int getHP() const {
        return healtPoint;
    }

    int getSanityPoint() const {
        return sanityPoint;
    }

private:
    std::string name;
    int healtPoint;
    int sanityPoint;
    medType type;
};



#endif //BLOODBOND_MEDICINE_H
