# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pajoncou <pajoncou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/21 13:52:26 by pajoncou          #+#    #+#              #
#    Updated: 2025/11/21 13:52:26 by pajoncou         ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

NAME = fortitude
RUNNER_NAME = fortitude_runner
CC = cc
CFLAGS = -Wall -Wextra -Werror

FORTITUDE_SRCS = fortitude.c
FORTITUDE_OBJS = $(FORTITUDE_SRCS:.c=.o)

RUNNER_SRCS = fortitude_runner.c
RUNNER_OBJS = $(RUNNER_SRCS:.c=.o)

all: $(FORTITUDE_OBJS) $(RUNNER_OBJS)
	$(CC) $(CFLAGS) -o $(RUNNER_NAME) $(RUNNER_OBJS) $(FORTITUDE_OBJS)
	@echo "Fortitude framework and runner compiled"

$(FORTITUDE_OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(RUNNER_OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(FORTITUDE_OBJS) $(RUNNER_OBJS) $(TEST_LIBFT_OBJ)

fclean: clean
	rm -f $(RUNNER_NAME)

re: fclean all

.PHONY: all clean fclean re

