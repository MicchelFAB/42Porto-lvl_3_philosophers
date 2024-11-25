# 42Porto-lvl_3_philosophers

## Objectives

The objective of this project is to simulate the dining philosophers problem. The dining philosophers problem is a classic synchronization problem in computer science. It involves a certain number of philosophers sitting at a table with a fork between each pair of adjacent philosophers. Each philosopher alternates between thinking, eating, and sleeping. To eat, a philosopher needs to pick up both forks adjacent to them. The challenge is to design a protocol that ensures no philosopher starves and that the simulation runs without any data races.

## How to Use

To use the program, you need to provide the following arguments:

1. `number_of_philosophers`: The number of philosophers and also the number of forks.
2. `time_to_die` (in milliseconds): If a philosopher didn’t start eating `time_to_die` milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
3. `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
4. `time_to_sleep` (in milliseconds): The time a philosopher will spend sleeping.
5. `number_of_times_each_philosopher_must_eat` (optional argument): If all philosophers have eaten at least `number_of_times_each_philosopher_must_eat` times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

### Example Usage

Without food limit:
```
./philo 5 800 200 200
```

With food limit:
```
./philo_bonus 5 800 200 200 7
```

## Differences Between Mandatory and Bonus Parts

### Mandatory Part

The mandatory part of the project uses threads and mutexes for synchronization. Each philosopher is represented by a thread, and mutexes are used to control access to shared resources (forks). This part is implemented in the `philo` directory.

### Bonus Part

The bonus part of the project uses processes and semaphores for synchronization. Each philosopher is represented by a process, and semaphores are used to control access to shared resources (forks). This part is implemented in the `philo_bonus` directory.

## Concepts

### Threads

A thread is a single sequence stream within a process. Threads are sometimes called lightweight processes. Threads are a way for a program to split itself into two or more simultaneously running tasks. They are used to perform multiple operations concurrently in the same program.

### Mutexes

A mutex, or mutual exclusion, is a synchronization primitive that is used to prevent multiple threads from accessing a shared resource simultaneously. It ensures that only one thread can access the resource at a time, thus preventing data races and ensuring data consistency.

### Forks

In the context of the dining philosophers problem, a fork is a shared resource that a philosopher needs to pick up in order to eat. Each philosopher needs two forks to eat, and the challenge is to design a protocol that ensures no philosopher starves and that the simulation runs without any data races.

### Semaphores

A semaphore is a synchronization primitive that is used to control access to a shared resource by multiple processes. It is a variable that is used to signal when a resource is available or unavailable. Semaphores are used to prevent data races and ensure data consistency in concurrent programming.
