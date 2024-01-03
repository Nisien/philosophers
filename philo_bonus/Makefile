# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/17 03:47:11 by nrossa            #+#    #+#              #
#    Updated: 2024/01/03 19:59:09 by nrossa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean norme compilation noflags

NAME = philo_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = /bin/rm -f

HDR = philo_bonus.h

SRC = philo_bonus.c ft_init_data.c ft_start_simulation.c ft_utils.c
OBJS = $(SRC:.c=.o)

BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
WHITE = \033[37m
NC = \033[0m

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	@echo "$(RED)Compilation in progress...$(NC)"
	@$(CC) $(CFLAGS) -g -o $(NAME) $(OBJS) -lpthread
	@echo "$(GREEN)Compilation complete !$(NC)"

all: $(NAME)

clean:
	@echo "$(YELLOW)Cleaning object files...$(NC)"
	@$(RM) $(OBJS)
	@echo "$(GREEN)Cleaning complete !$(NC)"

fclean: clean
	@echo "$(YELLOW)Cleaning...$(NC)"
	@$(RM) $(NAME)
	@echo "$(GREEN)Cleaning complete !$(NC)"

re: fclean all

norme:
	@echo "$(YELLOW)Checking Norme...$(NC)"
	@norminette $(SRC) $(HDR)
	@echo "$(GREEN)Checking complete !$(NC)"

compilation:
	$(CC) $(CFLAGS) -fsanitize=thread -g -o $(NAME) $(SRC) -lpthread

noflags:
	$(CC) -g -o $(NAME) $(SRC) -lpthread
