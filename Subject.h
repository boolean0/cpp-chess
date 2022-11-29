#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "Observer.h"

class Subject {
    private:
        std::vector<Observer *> observers;

    public:
        Subject();
        void attach(Observer *o);
        void detach(Observer *o);
        void notifyObservers();
        virtual ~Subject() = 0;
};


#endif 
