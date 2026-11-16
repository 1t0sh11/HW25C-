#include "Time.h"

int main() {

    Time t1(10, 30, 0, true);
    cout << "Initial t1: " << t1 << endl;

    ++t1;
    cout << t1 << endl;

    t1++;
    cout << t1 << endl;

    --t1;
    cout << t1 << endl;

    Time t2 = 15 + t1;
    cout << t2 << endl;

    Time startBus(6, 0, 0, true);
    Time endBus(11, 0, 0, true);
    Bus route1(startBus, endBus, 30, 10);
    route1.generateBusSchedule();
    return 0;
}