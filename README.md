<div align="center">
  <h1>Evidence 4 - Pandemic Simulator</h1>
</div>

To run the simulator:

```
g++ main.cpp
```

To run the tests:

```
g++ tests.cpp
```

For my final project of the Object Oriented Programming course during second semester, I built a pandemic simulator. As cool as I though it was, the real value of tools like this one relies on the ability to run multiple different scenarios to make informed decisions. However, between the amount of inputs needed to run a simulation, as well as the computational demands, the program couldn't be properly used as a tool to assess decision-making based on simulating multiple scenarios. 

The moment we saw the concurrent and parallel programming paradigms, I thought it would be a great improvement to my pandemic simulator, as I could use threads to simulate multiple scenarios at the same time.

## Threads

Contrary to popular missinterpreation, a thread is not a process.

A thread is the smallest unit of CPU execution within a process. It contains its own program counter, register set, and stack, but shares the process's memory and resources with other threads.

Threads enable a program to perform multiple tasks concurrently. In my simulator, each thread is responsible for handling an individual simulation scenario, allowing multiple scenarios to be processed simultaneously, especially on multi-core processors. This design improves performance by overlapping computation and making efficient use of system resources.

## Concurrency 

Concurrency is a programming paradigm where multiple tasks are designed to make progress in overlapping time periods.

The idea is to structure a program to handle many things at once, even if they aren't all executing at the exact same physical moment. This is useful for:

- Server Management: Handling multiple client connections simultaneously.
- Simulations: Organizing different components or scenarios that can logically operate independently.

## Parallelism

Parallelism, on the other hand, refers to the simultaneous execution of multiple tasks at the exact same physical moment. This requires CPUs with multiple cores.

The intention of parallelism is to improve performance by literally doing more work in the same amount of time. This is mostly used for programs that require executing lots of matrix operations, like neural networks or videogame graphic engines.


In simpler terms, parallelism is a subset of concurrency. We can't have have parallelism without concurrency, because we need the program to first express multiple tasks that can be run independently. 

![diagram](diagram.png)

----

This pandemic simulator uses concurrency by using the threads to manage multiple simulation scenarios. 


For each simulation scenario requested by the user, the program creates a new thread. Each thread will be an independent path of execution responsible for a single scenario.


* Within each thread:
    *   A Population object is instantiated with its specific parameters.
    *   The simulation() method runs the  logic of the pandemic simulation for that scenario.

By structuring the simulations to run in separate threads, the program allows the operating system to execute these threads in parallel if multiple CPU cores are available. We use the join() method to ensure that the main program waits for all simulation threads to complete their execution before it finishes.

The simulator is designed concurrently (managing multiple scenario tasks), to enable parallelism on multi-core CPUs, leading to a significant speed-up in processing multiple scenarios compared to running them sequentially.

---
The SIR mathematical model is used for describing the spread of infectious diseases within a population. It divides the population into three groups:

- **Susceptible (S)**: Individuals who are not infected but can get infected.
- **Infectious (I)**: Individuals who are currently infected and can transmit the disease.
- **Removed (R)**: Individuals who have either recovered or died from the disease.


## Differential Equations

The SIR model is described by the following set of differential equations:

1. **Susceptible Population (S)**:
   $\frac{dS}{dt} = -\beta \frac{SI}{N}$


2. **Infected Population (I)**:
   $\frac{dI}{dt} = \beta \frac{SI}{N} - \gamma I$

3. **Recovered Population (R)**:
   $\frac{dR}{dt} = \gamma I$

> Where $\beta$ is the transmission rate and $\gamma$ is the recovery rate.

In order to solve the differential equations, thus allowing us to know the number of susceptibles, infected, and removed individuals at a particular momment in time, I used Euler's numeric method:

1. **Susceptible Population (S)**:
   ${S_{n+1}} = {S_n}-\beta {S_nI_n \Delta t}$


2. **Infected Population (I)**:
   ${I_{n+1}} = {I_n}+ (\beta {S_nI_n - \gamma I_n \Delta t})$

3. **Recovered Population (R)**:
   ${R_{n+1}} = {R_n} + {\gamma I_n \Delta t}$


## Functionality

The user can set:

*  Average age of the population (affects transmission rate)
*  Variant of the virus (affects transmission rate)
*  Percentage of the population that is vaccinated (affects transmission rate)
*  Initial number of infected individuals
*  Number of days to run the simulation

For further customization, you can change the base tranmission rates for each variant in the constructor of the Population.h file.
---

## Algorithmic Complexity

The time complexity of the simulator is primarily determined by the number of simulation scenarios and the number of steps in each scenario. For each scenario, the simulation iterates over a number of steps proportional to the number of days divided by the time increment.

For each scenario, the main simulation loop runs in O(D/dt) time, where D is the number of days to simulate per scenario, and dt is the time step used in Euler's method for the simulation.

Since each scenario runs in its own thread, the total work done is O(S*D/dt), where S is the number of threads or scenarios.
With enough CPU cores, scenarios can be processed in parallel.

The space complexity is also O(D/dt) per scenario, due to the arrays storing the S, I, and R values for each time step.