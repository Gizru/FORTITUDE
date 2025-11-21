/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fortitude.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajoncou <pajoncou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:52:26 by pajoncou          #+#    #+#             */
/*   Updated: 2025/11/21 13:52:26 by pajoncou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortitude.h"

void	ft_print_header(const char *project_name)
{
	printf("\n%s", BLUE);
	printf("╔══════════════════════════════════════════════════════════╗\n");
	printf("║                                                          ║\n");
	printf("║                    FORTITUDE TESTING                     ║\n");
	printf("║                                                          ║\n");
	printf("║                    Testing: %-30s ║\n", project_name);
	printf("║                                                          ║\n");
	printf("╚══════════════════════════════════════════════════════════╝\n");
	printf("%s\n", RESET);
}

void	ft_print_test_result(const char *test_name, int passed)
{
	if (passed)
	{
		printf("%s[PASS]%s %s\n", GREEN, RESET, test_name);
	}
	else
	{
		printf("%s[FAIL]%s %s\n", RED, RESET, test_name);
	}
}

void	ft_print_suite_summary(t_suite *suite)
{
	int	failed;

	failed = suite->test_count - suite->passed_count;
	printf("\n%s", BLUE);
	printf("═══════════════════════════════════════════════════════════\n");
	printf("Suite: %s\n", suite->name);
	printf("Total tests: %d\n", suite->test_count);
	printf("%sPassed: %d%s\n", GREEN, suite->passed_count, RESET);
	if (failed > 0)
		printf("%sFailed: %d%s\n", RED, failed, RESET);
	else
		printf("%sFailed: %d%s\n", GREEN, failed, RESET);
	printf("═══════════════════════════════════════════════════════════\n");
	printf("%s\n", RESET);
}

int	ft_assert_int(int expected, int actual, const char *test_name)
{
	if (expected == actual)
	{
		ft_print_test_result(test_name, 1);
		return (1);
	}
	printf("%s[FAIL]%s %s (expected: %d, got: %d)\n", RED, RESET,
		test_name, expected, actual);
	return (0);
}

int	ft_assert_str(const char *expected, const char *actual,
		const char *test_name)
{
	if (expected == NULL && actual == NULL)
	{
		ft_print_test_result(test_name, 1);
		return (1);
	}
	if (expected == NULL || actual == NULL)
	{
		printf("%s[FAIL]%s %s (one is NULL)\n", RED, RESET, test_name);
		return (0);
	}
	if (strcmp(expected, actual) == 0)
	{
		ft_print_test_result(test_name, 1);
		return (1);
	}
	printf("%s[FAIL]%s %s (expected: \"%s\", got: \"%s\")\n", RED, RESET,
		test_name, expected, actual);
	return (0);
}

int	ft_assert_ptr(void *expected, void *actual, const char *test_name)
{
	if (expected == actual)
	{
		ft_print_test_result(test_name, 1);
		return (1);
	}
	printf("%s[FAIL]%s %s (pointers don't match)\n", RED, RESET, test_name);
	return (0);
}

int	ft_assert_null(void *ptr, const char *test_name)
{
	if (ptr == NULL)
	{
		ft_print_test_result(test_name, 1);
		return (1);
	}
	printf("%s[FAIL]%s %s (expected NULL, got non-NULL)\n", RED, RESET,
		test_name);
	return (0);
}

int	ft_assert_not_null(void *ptr, const char *test_name)
{
	if (ptr != NULL)
	{
		ft_print_test_result(test_name, 1);
		return (1);
	}
	printf("%s[FAIL]%s %s (expected non-NULL, got NULL)\n", RED, RESET,
		test_name);
	return (0);
}

int	ft_assert_true(int condition, const char *test_name)
{
	if (condition)
	{
		ft_print_test_result(test_name, 1);
		return (1);
	}
	printf("%s[FAIL]%s %s (expected true, got false)\n", RED, RESET,
		test_name);
	return (0);
}

int	ft_assert_false(int condition, const char *test_name)
{
	if (!condition)
	{
		ft_print_test_result(test_name, 1);
		return (1);
	}
	printf("%s[FAIL]%s %s (expected false, got true)\n", RED, RESET,
		test_name);
	return (0);
}

void	ft_print_part_header(const char *part_name)
{
	printf("\n%s", YELLOW);
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  %s\n", part_name);
	printf("─────────────────────────────────────────────────────────────%s\n",
		RESET);
}

void	ft_print_part_summary(t_part *part)
{
	int	failed;

	failed = part->test_count - part->passed_count;
	if (part->is_bonus && part->test_count == 0)
	{
		printf("%s[INFO] Bonus part not present (this is OK)%s\n",
			YELLOW, RESET);
		return ;
	}
	printf("\n%sSummary for %s:%s\n", BLUE, part->name, RESET);
	printf("  Total: %d  ", part->test_count);
	printf("%sPassed: %d%s  ", GREEN, part->passed_count, RESET);
	if (failed > 0)
		printf("%sFailed: %d%s\n", RED, failed, RESET);
	else
		printf("%sFailed: %d%s\n", GREEN, failed, RESET);
}

int	ft_run_part(t_part *part)
{
	int	i;
	int	result;

	if (part->is_bonus && part->test_count == 0)
	{
		ft_print_part_summary(part);
		return (1);
	}
	i = 0;
	part->passed_count = 0;
	while (i < part->test_count)
	{
		result = part->tests[i].func();
		part->tests[i].passed = result;
		part->passed_count += result;
		i++;
	}
	ft_print_part_summary(part);
	return (part->passed_count == part->test_count);
}

int	ft_run_suite(t_suite *suite)
{
	int	i;
	int	result;

	i = 0;
	suite->passed_count = 0;
	printf("\n%sRunning suite: %s%s\n\n", YELLOW, suite->name, RESET);
	while (i < suite->test_count)
	{
		result = suite->tests[i].func();
		suite->tests[i].passed = result;
		suite->passed_count += result;
		i++;
	}
	ft_print_suite_summary(suite);
	return (suite->passed_count == suite->test_count);
}

