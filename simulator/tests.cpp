#include <iostream>
#include <cassert>
#include "Population.h"
#include <mutex>
#include <thread>

using namespace std;



int main() {
    cout << "Running parallel simulation test...\n";
    mutex m1;
    bool finished1 = false, finished2 = false;
    bool finished3 = false, finished4 = false;
    thread t1([&]() {
        Population p(500, 1, 0.5, 0.8, 30, 5, 1);
        p.create_population();
        p.simulation(m1);
        finished1 = true;
    });
    thread t2([&]() {
        Population p(800, 2, 0.3, 0.7, 50, 10, 1);
        p.create_population();
        p.simulation(m1);
        finished2 = true;
    });
    thread t3([&]() {
        Population p(1200, 3, 0.9, 0.95, 40, 20, 2);
        p.create_population();
        p.simulation(m1);
        finished3 = true;
    });
    thread t4([&]() {
        Population p(300, 1, 0.1, 0.2, 70, 2, 3);
        p.create_population();
        p.simulation(m1);
        finished4 = true;
    });
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    assert(finished1 && finished2 && finished3 && finished4);
    cout << "Parallel simulation test: PASSED\n";
    cout << "All tests passed!\n";
    return 0;
}