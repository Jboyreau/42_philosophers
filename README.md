# 42_philosophers
Project philosophers from 42 school.
This projrct is a simultaion of the dining philosophers problem.
The executable takes 4 to 5 arguments:

	-number of philosophers
	-time to die
	-time to eat
	-time to spleed
	-number of time each philosophers must eat (optional)
Time to think is set by the executable.

OS: Ubuntu

Compilation:

	gcc -Wall -Wextra -Werror -g3 \*.c -lpthread
Usage:

    ./a.out 5 810 200 200 10
	
