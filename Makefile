NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/parsing.c $(SRC_DIR)/cleanup.c $(SRC_DIR)/init.c $(SRC_DIR)/time.c \
$(SRC_DIR)/simulation.c $(SRC_DIR)/actions.c $(SRC_DIR)/utils.c

OBJS = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re