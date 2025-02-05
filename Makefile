CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g
SRCS_DIR = src

SLSRCS = philo.c init.c utils.c threads.c routine.c valid.c

SRCS = $(addprefix $(SRCS_DIR)/, $(SLSRCS))
OBJS = $(SRCS:.c=.o)
NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ 

$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re