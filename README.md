# 42_philosophers
These project simulate the dining philosophers problem.
It takes 4 to 5 arguments (the last one is optinal):
  -number of philosophers
  -time to die (ms)
  -time to eat (ms)
  -time to sleep (ms)
  -numbers of times each philosophers eat (optionel, if not set the simalation will be endless).
Complition:
  gcc -Wall -Wextra -Werror -g3 \*.c -lpthread
Usage:
./a.out 5 810 200 200 10
