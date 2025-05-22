#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include "Person.h"
#include "Population.h"

using namespace std;

mutex m1;

int main() {
  int numScenarios;
  cout << "How many scenarios to run? ";
  cin >> numScenarios;
  class Scenario {
  public:
    int population_size;
    int virus;
    double vaccination_rate;
    double vaccine_effectiveness;
    int average_age;
    int I0;
    int days;
  };
  vector<Scenario> scenarios(numScenarios);
  for (int i = 0; i < numScenarios; ++i) {
    cout << "--- Scenario " << i + 1 << " ---" << endl;
    cout << "Population size: "; cin >> scenarios[i].population_size;
    cout << "Variant (1:Original,2:Omnicron,3:Delta): "; cin >> scenarios[i].virus;
    cout << "Vaccination rate (0-1): "; cin >> scenarios[i].vaccination_rate;
    cout << "Vaccine effectiveness (0-1): "; cin >> scenarios[i].vaccine_effectiveness;
    cout << "Average age: "; cin >> scenarios[i].average_age;
    cout << "Initial infected count: "; cin >> scenarios[i].I0;
    cout << "Days to simulate: "; cin >> scenarios[i].days;
  }
  vector<thread> threads; //all the threads to run the simulation. 1 thread per scenario.
  for (const Scenario &sc : scenarios) {
    threads.emplace_back([sc]() {
      Population p(
        sc.population_size, sc.virus, sc.vaccination_rate,
        sc.vaccine_effectiveness, sc.average_age, sc.I0, sc.days);
      p.create_population();
      p.simulation(m1);
    });
  }
  for (thread &t : threads) {
    t.join();
  }
  return 0;
}
