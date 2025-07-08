NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c init.c thread.c cleanup.c utils.c time_utils.c atoi.c philosopher.c print.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
