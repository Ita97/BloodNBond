//
// Created by ita on 04/10/17.
//

#ifndef BLOODBOND_MEDICINE_H
#define BLOODBOND_MEDICINE_H
#include "Tools.h"

class Medicine: virtual public Tools{
public:
    explicit Medicine(int hp, int sp=0):Tools(toolType::medicine),healingPoint(hp), sanityPoint(sp){};
    bool isPsichic(){
        return sanityPoint!=0;
    }
    bool isPhisical(){
        return healingPoint!=0;
    }

    int getHealingPoint() const {
        return healingPoint;
    }

    void setHealingPoint(int healingPoint) {
        Medicine::healingPoint = healingPoint;
    }

private:
    int healingPoint;
    int sanityPoint;
};
/*

    int useTool() override;

};

*/
#endif //BLOODBOND_MEDICINE_H
