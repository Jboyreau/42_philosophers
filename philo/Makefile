NAME=philo

SRC=api.c api_.c\
	main.c main_.c\
	routine.c routine_.c\
	parsing.c\
	timestamp.c timestamp_.c

OBJ=api.o api_.o\
	main.o main_.o\
	routine.o routine_.o\
	parsing.o\
	timestamp.o timestamp_.o

CPPFLAGS= -g3 -Wall -Wextra -Werror

CFLAGS= -lpthread

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(OBJ) $(CFLAGS) -o philo

clean:
	rm -f *.o

fclean: clean
	rm -f philo

re : fclean all

#############
## PATERNS ##
#############
#$@: Nom de la regle
#$<: Nom de la premiere dépendance
#$^: Nom de la toute les dependances
%.o: %.c
	cc $(CPPFLAGS) -c $< -o $@

.PHONY: all clean fclean re
