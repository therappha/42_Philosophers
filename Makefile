NAME= philo
CC= cc
CFLAGS = -g -Wall -Werror -pthread -Wextra -I $(INCLUDES)
INCLUDES= ./includes
SRCS_DIR= ./srcs
SRCS= $(SRCS_DIR)/main.c $(SRCS_DIR)/ft_atoi.c $(SRCS_DIR)/pthread_helpers.c
OBJS= $(SRCS:.c=.o)

all: $(NAME)
	@echo "Project built, execute with ./philo"

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c $^ -o $@

clean:
	@rm -rf $(OBJS)
	@echo "Cleaning Objects!"
fclean: clean
	@rm -rf $(NAME)
	@echo "Cleaning Objects and philos!"
re: fclean all

.PHONY: all clean fclean re

