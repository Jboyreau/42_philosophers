NAME=philo

SRC=api.c main.c\
	parsing.c timestamp.c\
	utils.c utilz.c\

OBJ=api.o main.o\
	parsing.o timestamp.o\
	utils.o utilz.o\

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
