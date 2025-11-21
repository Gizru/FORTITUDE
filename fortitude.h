/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fortitude.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajoncou <pajoncou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:52:26 by pajoncou          #+#    #+#             */
/*   Updated: 2025/11/21 13:52:26 by pajoncou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORTITUDE_H
# define FORTITUDE_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define RESET	"\033[0m"
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"

typedef struct s_test
{
	char	*name;
	int		(*func)(void);
	int		passed;
}	t_test;

typedef struct s_suite
{
	char	*name;
	t_test	*tests;
	int		test_count;
	int		passed_count;
}	t_suite;

typedef struct s_part
{
	char	*name;
	t_test	*tests;
	int		test_count;
	int		passed_count;
	int		is_bonus;
}	t_part;

void	ft_print_header(const char *project_name);
void	ft_print_test_result(const char *test_name, int passed);
void	ft_print_suite_summary(t_suite *suite);
int		ft_assert_int(int expected, int actual, const char *test_name);
int		ft_assert_str(const char *expected, const char *actual,
			const char *test_name);
int		ft_assert_ptr(void *expected, void *actual, const char *test_name);
int		ft_assert_null(void *ptr, const char *test_name);
int		ft_assert_not_null(void *ptr, const char *test_name);
int		ft_assert_true(int condition, const char *test_name);
int		ft_assert_false(int condition, const char *test_name);
int		ft_run_suite(t_suite *suite);
void	ft_print_part_header(const char *part_name);
void	ft_print_part_summary(t_part *part);
int		ft_run_part(t_part *part);

#endif

