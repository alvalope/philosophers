# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 17:27:34 by alvalope          #+#    #+#              #
#    Updated: 2023/08/08 14:57:25 by alvalope         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = ./src

OBJ_DIR = ./ojb

INCLUDE_DIR = ./include

INCLUDES = -I $(INCLUDE_DIR)

HEADER = $(INCLUDE_DIR)/ft_philosophers.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = ft_philosophers.c ft_philosophers_utils.c ft_configure.c

SRC_FILES = $(addprefix $(SRC_DIR)/, $(SRCS))

OBJS = $(SRCS:.c=.o)

OBJS_FILES = $(addprefix $(OBJ_DIR)/, $(OBJS))

RM = rm -f

RM_DIR = rm -rf

LIB = ar rcs

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compilando archivos de philosophers..."
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS_FILES) $(HEADER)
	@echo "Compilando ejecutable..."
	@$(CC) $(CFLAGS) $(OBJS_FILES) $(INCLUDES) -o $(NAME)
	@echo "\033[0;32mPROCESO TERMINADO.\033[0m"

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS) $(HEADER)
	@echo "Compilando ejecutable..."
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(INCLUDES) -o $(BONUS_NAME)
	@echo "\033[0;32mPROCESO TERMINADO.\033[0m"

$(BONUS_OBJS): $(BONUS_SRCS)
	@echo "Compilando archivos del bonus..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $(BONUS_SRCS)
	
ph: all clean

clean:
	@echo "\033[0;31mBorrando archivos generados en la compilacion...\033[0m"
	@$(RM) $(OBJS_FILES) $(BONUS_OBJS)
	@$(RM_DIR) $(OBJ_DIR)
	@echo "\033[0;33mLIMPIEZA TERMINADA.\033[0m"

fclean: clean
	@echo "\033[0;31mBorrando librerias generadas...\033[0m"
	@$(RM) $(NAME) $(BONUS_NAME)
	@echo "\033[0;33mLIMPIEZA TOTAL TERMINADA.\033[0m"

re: fclean all

.PHONY: all clean fclean re