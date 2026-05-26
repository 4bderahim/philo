# philo


Philosophers is a multithreading and synchronization project from 42 School based on the classic Dining Philosophers problem.

The goal is to understand thread management, mutexes, race conditions, and synchronization in C by simulating philosophers eating, thinking, and sleeping while sharing limited resources.

Features
  Thread creation and management
  Mutex synchronization
  Race condition prevention
  Time and state monitoring
  Resource sharing simulation
  Technologies
  C
  POSIX Threads (pthreads)
  Mutexes
  Unix/Linux
  Usage


--- compile :

make

Run the program:

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]

Example:
./philo 5 800 200 200
