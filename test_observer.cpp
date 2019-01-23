#include <iostream>
#include <vector>
using namespace std;

//class Observer;

class Subject
{
    int value;
    vector<class Observer *> views;
public:
    void attach(Observer* observer)
    {
        views.push_back(observer);
    }
    void setValue(int val)
    {
        value = val;
        notify();
    }
    int getValue()
    {
        return value;
    }
    void notify();
};

class Observer
{
    Subject *model;
    int denom;
protected:
    Subject *getSubject()
    {
        return model;
    }
    int getDivisor()
    {
        return denom;
    }

public:
    Observer(Subject *mod, int div)
    {
        model = mod;
        denom = div;
        model->attach(this);
    }
    virtual void update() = 0;
};

void Subject::notify()
{
    for(int i=0; i < views.size();i=i+1)
    {
        views[i]->update();
    }
}

class DivObserver : public Observer
{
public:
    DivObserver(Subject *mod, int div) : Observer(mod, div){}
    void update()
    {
        int v = getSubject()->getValue();
        int d = getDivisor();
        cout << v << " div " << d << " is " << v/d << "\n";
    }
};

class ModObserver : public Observer
{
public:
    ModObserver(Subject *mod, int div) : Observer(mod, div){}
    void update()
    {
        int v = getSubject()->getValue();
        int d = getDivisor();
        cout << v << " mod " << d << " is " << v%d << "\n";
    }
};

int main()
{
    Subject subj;

    DivObserver divObs1(&subj, 4);
    DivObserver divObs2(&subj, 3);
    ModObserver modObs1(&subj, 3);

    subj.setValue(14);

    cout << "....................................\n";
    ModObserver modObs2(&subj, 7);

    subj.setValue(20);
        
    return 0;
}
