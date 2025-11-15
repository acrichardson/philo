NAME = philo

SRCS =	main.c\
		init.c\
		utils.c\
		routine_utils.c\
		routine.c\
		utils_init.c\
		utils_data_check.c\

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g
#  -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re