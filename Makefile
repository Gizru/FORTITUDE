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

# Test targets - LIBFT_DIR can be set via environment or detected
LIBFT_DIR ?= ../PROJECTS/Libft
LIBFT = $(LIBFT_DIR)/libft.a
TEST_LIBFT = tests/test_libft.c
TEST_LIBFT_OBJ = $(TEST_LIBFT:.c=.o)
TEST_LIBFT_BIN = test_libft

test_libft: $(FORTITUDE_OBJS) $(TEST_LIBFT_OBJ)
	@if [ ! -f "$(LIBFT)" ]; then \
		echo "Building libft with bonus..."; \
		cd $(LIBFT_DIR) && make bonus; \
	fi
	$(CC) $(CFLAGS) -o $(TEST_LIBFT_BIN) $(TEST_LIBFT_OBJ) \
		$(FORTITUDE_OBJS) -L$(LIBFT_DIR) -lft
	@echo "Running Libft tests..."
	@./$(TEST_LIBFT_BIN) || true
	@echo "\nCleaning target repository..."
	@cd $(LIBFT_DIR) && make fclean
	@echo "Cleaning test artifacts..."
	@rm -f $(TEST_LIBFT_BIN)
	@echo "Cleanup complete!"

$(TEST_LIBFT_OBJ): $(TEST_LIBFT)
	$(CC) $(CFLAGS) -I. -I$(LIBFT_DIR) -c $< -o $@

clean:
	rm -f $(FORTITUDE_OBJS) $(RUNNER_OBJS) $(TEST_LIBFT_OBJ)

fclean: clean
	rm -f $(RUNNER_NAME) $(TEST_LIBFT_BIN)

re: fclean all

.PHONY: all clean fclean re test_libft

