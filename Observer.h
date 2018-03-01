//
// Created by ita on 26/02/18.
//

#ifndef BLOODBOND_OBSERVER_H
#define BLOODBOND_OBSERVER_H

class Observer{
protected:
    virtual ~Observer(){}

public:
    virtual void update()=0;
    virtual void attach()=0;
    virtual void detach()=0;
};

#endif //BLOODBOND_OBSERVER_H
