//
// Created by ita on 26/02/18.
//

#ifndef BLOODBOND_SUBJECT_H
#define BLOODBOND_SUBJECT_H

#include "Observer.h"

class Subject {
protected:
    virtual ~Subject(){}
public:
    virtual void subscribe(Observer *o)=0;
    virtual void unsubscrive(Observer *o)=0;
    virtual void notify()=0;



};
#endif //BLOODBOND_SUBJECT_H
