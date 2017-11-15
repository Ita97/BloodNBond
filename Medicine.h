//
// Created by ita on 04/10/17.
//

#ifndef BLOODBOND_MEDICINE_H
#define BLOODBOND_MEDICINE_H


class Medicine {
public:
    explicit Medicine(int hp, int sp=0): healingPoint(hp), sanityPoint(sp){};

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

    int getSanityPoint() const {
        return sanityPoint;
    }

    void setSanityPoint(int sanityPoint) {
        Medicine::sanityPoint = sanityPoint;
    }

private:
    int healingPoint;
    int sanityPoint;
};



#endif //BLOODBOND_MEDICINE_H
