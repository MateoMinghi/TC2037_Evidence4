<div align="center">
  <h1>Evidence 4 - Pandemic Simulator</h1>
</div>

To run the Simulator:

```
g++ main.cpp
```

For my final project of the Object Oriented Programming course during second semester, I built a pandemic simulator. As cool as I though it was, the real value of tools like this one relies on the ability to run multiple different scenarios to make informed decisions. However, between the amount of inputs needed to run a simulation, as well as the computational demands, the program couldn't be properly used as a tool to assess decision-making based on simulating multiple scenarios. 

The moment we saw the concurrent and parallel programming paradigms, I thought it would be a great improvement to my pandemic simulator, as I could use threads to simulate multiple scenarios at the same time.

## Threads

Contrary to popular missinterpreation, a thread is not a process.

A thread is the smallest unit of CPU execution within a process. It contains its own program counter, register set, and stack, but shares the process's memory and resources with other threads.

Threads enable a program to perform multiple tasks concurrently. In my simulator, each thread is responsible for handling an individual simulation scenario, allowing multiple scenarios to be processed simultaneously, especially on multi-core processors. This design improves performance by overlapping computation and making efficient use of system resources.

## Concurrency 

Concurrency is a programming paradigm that allows for multiple tasks to make progress during overlapping time periods without necessarily running simultaneously. This is particularly useful in areas such as:

- **Server Management:** Managing multiple client connections or requests at the same time.
- **Simulations and Complex Systems:** Organizing different components or scenarios that can logically operate in parallel.

## Parallelism

Parallelism on the other hand, refers to the simultaneous execution of multiple tasks at exactly the same time, often on different cores or processors. Parallelism is about literally running tasks at the same time to improve performance.

This technique is whidely used in programs that require lots of matrix multiplications, such as Neural Networks or video game graphic engines.

![diagram](diagram.png)

----

The simulator uses C++'s standard threading library to run multiple simulation scenarios concurrently. In main.cpp, for each scenario defined by the user, a new thread is created.

Each thread

- Instantiates a Population object using scenario-specific parameters.
- Calls the create_population() method to initialize the population.
- Runs the simulation() method to perform the  simulation.

After launching all threads, the main function waits for each thread to complete using the join() method. This approach allows multiple scenarios to be processed in parallel, taking advantage of multi-core processors for improved performance.


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