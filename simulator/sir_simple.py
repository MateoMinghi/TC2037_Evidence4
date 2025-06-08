# Simple SIR Model Simulation in Python with User Input

def get_float(prompt, min_value=None, max_value=None):
    while True:
        try:
            value = float(input(prompt))
            if (min_value is not None and value < min_value) or (max_value is not None and value > max_value):
                print(f"Value must be between {min_value} and {max_value}.")
                continue
            return value
        except ValueError:
            print("Please enter a valid number.")

def get_int(prompt, min_value=None, max_value=None):
    while True:
        try:
            value = int(input(prompt))
            if (min_value is not None and value < min_value) or (max_value is not None and value > max_value):
                print(f"Value must be between {min_value} and {max_value}.")
                continue
            return value
        except ValueError:
            print("Please enter a valid integer.")

from functools import reduce

def sir_step(state, params):
    S, I, R = state
    beta, gamma = params
    N = S + I + R  # Total population
    # Calculate new infections and recoveries for this step
    new_infected = beta * S * I / N
    new_recovered = gamma * I
    # Update the state for the next step
    S_new = S - new_infected
    I_new = I + new_infected - new_recovered
    R_new = R + new_recovered
    return (S_new, I_new, R_new)

def run_simulation(S, I, R, beta, gamma, days, step_function=sir_step, combine_history_fn=None):
    params = (beta, gamma)
    # We can provide a custom function to change how the simulation works
    #Without modifying the main simulation code!
    if combine_history_fn is None:
        combine_history_fn = lambda history, next_state: history + [next_state]
    # step_fn applies the step_function to the last state and combines it with the history
    step_fn = lambda history, _: combine_history_fn(history, step_function(history[-1], params))
    # Use reduce to iteratively build the history of states over the given number of days
    history = reduce(step_fn, range(days), [(S, I, R)])
    return history

def main():
    print("--- SIR Model Simulation ---")
    population_size = get_int("Population size: ", 1)
    I0 = get_int("Initial infected count: ", 0, population_size)
    R0 = get_int("Initial recovered count: ", 0, population_size - I0)
    S = population_size - I0 - R0
    I = I0
    R = R0
    beta = get_float("Infection rate (beta, e.g., 0.3): ", 0)
    gamma = get_float("Recovery rate (gamma, e.g., 0.1): ", 0)
    days = get_int("Days to simulate: ", 1)

    history = run_simulation(S, I, R, beta, gamma, days,
                            step_function=sir_step,
                            combine_history_fn=lambda history, next_state: history + [next_state])
    for day, (S, I, R) in enumerate(history):
        print(f"Day {day}: S={S:.1f}, I={I:.1f}, R={R:.1f}")

if __name__ == "__main__":
    main()
