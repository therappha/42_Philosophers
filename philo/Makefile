NAME= philo

CC= cc

INCLUDES= ./philo.h

CFLAGS = -Wall -Werror -Wextra -pthread -I $(INCLUDES)

SRCS_DIR= ./

SRCS= $(SRCS_DIR)/main.c \
$(SRCS_DIR)/ft_atoll.c \
$(SRCS_DIR)/pthread_helpers.c \
$(SRCS_DIR)/get_time.c \
$(SRCS_DIR)/state.c \
$(SRCS_DIR)/routine.c \
$(SRCS_DIR)/eat.c \
$(SRCS_DIR)/think.c \
$(SRCS_DIR)/sleep.c \
$(SRCS_DIR)/monitor.c \
$(SRCS_DIR)/getters_setters.c \
$(SRCS_DIR)/init_forks.c \
$(SRCS_DIR)/free_philo.c \
$(SRCS_DIR)/input_handler.c \


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

