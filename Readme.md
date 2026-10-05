*This project has been created as part of the 42 curriculum by haskalov*

# Philosophers

## Description

### This project is a demonstration of multithread synchronization in real time.

threads are presented as philosophers, shared recource is food, shared mutexes are forks

number_of_philosophers - number of thread to synchronize

time_to_die - time each thread can live without access to shared resource

time_to_eat - time each thread need to access the source (food) with shared mutexes (forks)
time_to_sleep - usleep time between thread access to the source 
time_to_think - extra usleep time  - used for synchronization 

if there's extra time before time_to_die is reached (set by simulations)

number_of_cycles - how many cycles (meals) should run 

if there is no number of cycles, simulation should run until user stops it


## Instructions

compile: make 

start: ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_cycles]

example: ./philo 2 800 200 200 3

## Resources

Linux programming interface https://broman.dev/download/The%20Linux%20Programming%20Interface.pdf  

Code Vault tutorial https://code-vault.net/course/6q6s9eerd0:1609007479575

### Guides:
 
https://github.com/mcombeau/philosophers   // my faforite  ![alt text](philosophersn.png)

https://github.com/TommyJD93/Philosophers  // good code 

https://github.com/MarkosComK/42-Philosophers   /// some new guide 


### Ai used

Ai used as advisor, for helping debugging and couting time for usleep in tinking section.
