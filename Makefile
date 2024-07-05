CC = cc 
CFLAGS = #-Wall -Wextra -Werror	
CFILES = dinner_set.c dinner_actions.c death_checkers.c philo_timers.c checks.c main.c
OFILES = $(CFILES:.c=.o)

PROG_NAME = philo
all : $(PROG_NAME)
$(PROG_NAME) : $(OFILES) 
	$(CC) $(CFLAGS) $(OFILES) -o $(PROG_NAME)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OFILES) $(OBFILES) 
	
fclean: clean 
	 rm -f $(OFILES) $(PROG_NAME) 
	 
re: fclean all