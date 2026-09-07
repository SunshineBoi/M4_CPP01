# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kong <kong@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/23 14:18:51 by kong              #+#    #+#              #
#    Updated: 2026/09/07 23:30:04 by kong             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and Flags
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

# Archive and Flags
AR = ar
ARFLAGS = rcs

SRC_DIR = .
BUILD_DIR = build
HEADER_DIR = includes

# Source Files
SRC_FILES := $(SRC_DIR)/main.cpp \
             $(SRC_DIR)/newZombie.cpp \
             $(SRC_DIR)/randomChump.cpp \
             $(SRC_DIR)/Zombie.cpp
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Executable
NAME = zombie

# Header Files
# INCLUDES = -I${HEADER_DIR}

# OBJS = $(SRCS:.c=.o)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Default Target
all: $(NAME)

# Build Executable
$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re