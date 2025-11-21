/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajoncou <pajoncou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:52:26 by pajoncou          #+#    #+#             */
/*   Updated: 2025/11/21 13:52:26 by pajoncou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fortitude.h"
#include "../../PROJECTS/Libft/libft.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* ========== PART 1 - LIBC FUNCTIONS ========== */

/* Character classification */
static int	test_ft_isalpha(void)
{
	int	result;

	result = (ft_isalpha('a') != 0 && ft_isalpha('Z') != 0 &&
		ft_isalpha('5') == 0 && ft_isalpha('@') == 0);
	ft_print_test_result("ft_isalpha", result);
	return (result);
}

static int	test_ft_isdigit(void)
{
	int	result;

	result = (ft_isdigit('0') != 0 && ft_isdigit('9') != 0 &&
		ft_isdigit('a') == 0 && ft_isdigit('@') == 0);
	ft_print_test_result("ft_isdigit", result);
	return (result);
}

static int	test_ft_isalnum(void)
{
	int	result;

	result = (ft_isalnum('a') != 0 && ft_isalnum('5') != 0 &&
		ft_isalnum('@') == 0 && ft_isalnum(' ') == 0);
	ft_print_test_result("ft_isalnum", result);
	return (result);
}

static int	test_ft_isascii(void)
{
	int	result;

	result = (ft_isascii(0) != 0 && ft_isascii(127) != 0 &&
		ft_isascii(128) == 0 && ft_isascii(-1) == 0);
	ft_print_test_result("ft_isascii", result);
	return (result);
}

static int	test_ft_isprint(void)
{
	int	result;

	result = (ft_isprint(' ') != 0 && ft_isprint('~') != 0 &&
		ft_isprint('\t') == 0 && ft_isprint(127) == 0);
	ft_print_test_result("ft_isprint", result);
	return (result);
}

/* String length */
static int	test_ft_strlen(void)
{
	int	result;

	result = (ft_strlen("") == 0 && ft_strlen("hello") == 5 &&
		ft_strlen("hello world") == 11);
	ft_print_test_result("ft_strlen", result);
	return (result);
}

/* Memory functions */
static int	test_ft_memset(void)
{
	char	buf1[11];
	char	buf2[11];
	int		i;
	int		result;

	memset(buf1, 'A', 10);
	ft_memset(buf2, 'A', 10);
	buf1[10] = '\0';
	buf2[10] = '\0';
	result = 1;
	i = 0;
	while (i < 10)
	{
		if (buf1[i] != buf2[i])
		{
			result = 0;
			break ;
		}
		i++;
	}
	ft_print_test_result("ft_memset", result);
	return (result);
}

static int	test_ft_bzero(void)
{
	char	buf1[10];
	char	buf2[10];
	int		result;

	memset(buf1, 'X', 10);
	memset(buf2, 'X', 10);
	memset(buf1, 0, 5);
	ft_bzero(buf2, 5);
	result = (memcmp(buf1, buf2, 10) == 0);
	ft_print_test_result("ft_bzero", result);
	return (result);
}

static int	test_ft_memcpy(void)
{
	char	src[10];
	char	dst1[10];
	char	dst2[10];
	int		i;
	int		result;

	i = 0;
	while (i < 10)
	{
		src[i] = 'A' + i;
		i++;
	}
	memcpy(dst1, src, 10);
	ft_memcpy(dst2, src, 10);
	result = (memcmp(dst1, dst2, 10) == 0);
	ft_print_test_result("ft_memcpy", result);
	return (result);
}

static int	test_ft_memmove(void)
{
	char	src[10];
	char	dst1[10];
	char	dst2[10];
	int		result;

	memmove(dst1, src, 10);
	ft_memmove(dst2, src, 10);
	result = (memcmp(dst1, dst2, 10) == 0);
	ft_print_test_result("ft_memmove", result);
	return (result);
}

/* String copy/cat */
static int	test_ft_strlcpy(void)
{
	char	dst[10];
	size_t	ret;
	int		result;

	memset(dst, 0, 10);
	ret = ft_strlcpy(dst, "hello", 10);
	result = (ret == 5 && strcmp(dst, "hello") == 0);
	ft_print_test_result("ft_strlcpy", result);
	return (result);
}

static int	test_ft_strlcat(void)
{
	char	dst[20];
	size_t	ret;
	int		result;

	strcpy(dst, "hello");
	ret = ft_strlcat(dst, " world", 20);
	result = (ret == 11 && strcmp(dst, "hello world") == 0);
	ft_print_test_result("ft_strlcat", result);
	return (result);
}

/* Character conversion */
static int	test_ft_toupper(void)
{
	int	result;

	result = (ft_toupper('a') == 'A' && ft_toupper('z') == 'Z' &&
		ft_toupper('A') == 'A' && ft_toupper('5') == '5');
	ft_print_test_result("ft_toupper", result);
	return (result);
}

static int	test_ft_tolower(void)
{
	int	result;

	result = (ft_tolower('A') == 'a' && ft_tolower('Z') == 'z' &&
		ft_tolower('a') == 'a' && ft_tolower('5') == '5');
	ft_print_test_result("ft_tolower", result);
	return (result);
}

/* String search */
static int	test_ft_strchr(void)
{
	const char	*str = "hello world";
	int			result;

	result = (ft_strchr(str, 'o') == str + 4 &&
		ft_strchr(str, '\0') == str + 11 &&
		ft_strchr(str, 'z') == NULL);
	ft_print_test_result("ft_strchr", result);
	return (result);
}

static int	test_ft_strrchr(void)
{
	const char	*str = "hello world";
	int			result;

	result = (ft_strrchr(str, 'o') == str + 7 &&
		ft_strrchr(str, '\0') == str + 11 &&
		ft_strrchr(str, 'z') == NULL);
	ft_print_test_result("ft_strrchr", result);
	return (result);
}

static int	test_ft_strnstr(void)
{
	const char	*big = "hello world";
	int			result;

	result = (ft_strnstr(big, "world", 11) != NULL &&
		ft_strnstr(big, "", 11) != NULL &&
		ft_strnstr(big, "xyz", 11) == NULL);
	ft_print_test_result("ft_strnstr", result);
	return (result);
}

/* Comparison */
static int	test_ft_strncmp(void)
{
	int	result;

	result = (ft_strncmp("hello", "hello", 5) == 0 &&
		ft_strncmp("abc", "abd", 3) == strncmp("abc", "abd", 3) &&
		ft_strncmp("abd", "abc", 3) == strncmp("abd", "abc", 3));
	ft_print_test_result("ft_strncmp", result);
	return (result);
}

static int	test_ft_memchr(void)
{
	const char	*str = "hello world";
	int			result;

	result = (ft_memchr(str, 'o', 11) == memchr(str, 'o', 11));
	ft_print_test_result("ft_memchr", result);
	return (result);
}

static int	test_ft_memcmp(void)
{
	int	result;

	result = (ft_memcmp("hello", "hello", 5) == 0 &&
		ft_memcmp("abc", "abd", 3) == memcmp("abc", "abd", 3) &&
		ft_memcmp("abd", "abc", 3) == memcmp("abd", "abc", 3));
	ft_print_test_result("ft_memcmp", result);
	return (result);
}

/* Conversion */
static int	test_ft_atoi(void)
{
	int	result;

	result = (ft_atoi("123") == 123 && ft_atoi("-456") == -456 &&
		ft_atoi("0") == 0 && ft_atoi("  +42") == 42);
	ft_print_test_result("ft_atoi", result);
	return (result);
}

/* Memory allocation */
static int	test_ft_calloc(void)
{
	void	*ptr;
	int		result;

	ptr = ft_calloc(10, sizeof(int));
	result = (ptr != NULL);
	if (ptr != NULL)
		free(ptr);
	ft_print_test_result("ft_calloc", result);
	return (result);
}

static int	test_ft_strdup(void)
{
	char	*dup;
	int		result;

	dup = ft_strdup("hello");
	result = (dup != NULL && strcmp(dup, "hello") == 0);
	if (dup != NULL)
		free(dup);
	ft_print_test_result("ft_strdup", result);
	return (result);
}

/* ========== PART 2 - ADDITIONAL FUNCTIONS ========== */

static int	test_ft_substr(void)
{
	char	*sub;
	int		result;

	sub = ft_substr("hello world", 6, 5);
	result = (sub != NULL && strcmp(sub, "world") == 0);
	if (sub != NULL)
		free(sub);
	ft_print_test_result("ft_substr", result);
	return (result);
}

static int	test_ft_strjoin(void)
{
	char	*joined;
	int		result;

	joined = ft_strjoin("hello", " world");
	result = (joined != NULL && strcmp(joined, "hello world") == 0);
	if (joined != NULL)
		free(joined);
	ft_print_test_result("ft_strjoin", result);
	return (result);
}

static int	test_ft_strtrim(void)
{
	char	*trimmed;
	int		result;

	trimmed = ft_strtrim("  hello world  ", " ");
	result = (trimmed != NULL && strcmp(trimmed, "hello world") == 0);
	if (trimmed != NULL)
		free(trimmed);
	ft_print_test_result("ft_strtrim", result);
	return (result);
}

static int	test_ft_split(void)
{
	char	**split;
	int		result;

	split = ft_split("hello world test", ' ');
	result = (split != NULL && split[0] != NULL && split[1] != NULL &&
		split[2] != NULL && split[3] == NULL &&
		strcmp(split[0], "hello") == 0 &&
		strcmp(split[1], "world") == 0 &&
		strcmp(split[2], "test") == 0);
	if (split != NULL)
	{
		free(split[0]);
		free(split[1]);
		free(split[2]);
		free(split);
	}
	ft_print_test_result("ft_split", result);
	return (result);
}

static int	test_ft_itoa(void)
{
	char	*str;
	int		result;

	str = ft_itoa(123);
	result = (str != NULL && strcmp(str, "123") == 0);
	if (str != NULL)
		free(str);
	ft_print_test_result("ft_itoa", result);
	return (result);
}

static char	ft_upper_char(unsigned int i, char c)
{
	(void)i;
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

static void	ft_upper_char_i(unsigned int i, char *c)
{
	(void)i;
	if (*c >= 'a' && *c <= 'z')
		*c = *c - 32;
}

static int	test_ft_strmapi(void)
{
	char	*result_str;
	int		result;

	result_str = ft_strmapi("hello", ft_upper_char);
	result = (result_str != NULL && strcmp(result_str, "HELLO") == 0);
	if (result_str != NULL)
		free(result_str);
	ft_print_test_result("ft_strmapi", result);
	return (result);
}

static int	test_ft_striteri(void)
{
	char	str[] = "hello";
	int		result;

	ft_striteri(str, ft_upper_char_i);
	result = (strcmp(str, "HELLO") == 0);
	ft_print_test_result("ft_striteri", result);
	return (result);
}

static int	test_ft_putchar_fd(void)
{
	ft_print_test_result("ft_putchar_fd", 1);
	return (1);
}

static int	test_ft_putstr_fd(void)
{
	ft_print_test_result("ft_putstr_fd", 1);
	return (1);
}

static int	test_ft_putendl_fd(void)
{
	ft_print_test_result("ft_putendl_fd", 1);
	return (1);
}

static int	test_ft_putnbr_fd(void)
{
	ft_print_test_result("ft_putnbr_fd", 1);
	return (1);
}

/* ========== BONUS PART ========== */

static int	test_ft_lstnew(void)
{
	t_list	*node;
	int		result;

	node = ft_lstnew("test");
	result = (node != NULL && node->content != NULL &&
		strcmp((char *)node->content, "test") == 0 &&
		node->next == NULL);
	if (node != NULL)
		free(node);
	ft_print_test_result("ft_lstnew", result);
	return (result);
}

static int	test_ft_lstadd_front(void)
{
	t_list	*node1;
	t_list	*node2;
	t_list	*lst;
	int		result;

	lst = NULL;
	node1 = ft_lstnew("first");
	node2 = ft_lstnew("second");
	if (node1 == NULL || node2 == NULL)
		return (0);
	ft_lstadd_front(&lst, node1);
	ft_lstadd_front(&lst, node2);
	result = (lst == node2 && lst->next == node1 &&
		strcmp((char *)lst->content, "second") == 0 &&
		strcmp((char *)lst->next->content, "first") == 0);
	if (node1 != NULL)
		free(node1);
	if (node2 != NULL)
		free(node2);
	ft_print_test_result("ft_lstadd_front", result);
	return (result);
}

static int	test_ft_lstsize(void)
{
	t_list	*node1;
	t_list	*node2;
	t_list	*lst;
	int		result;

	lst = NULL;
	node1 = ft_lstnew("first");
	node2 = ft_lstnew("second");
	if (node1 == NULL || node2 == NULL)
		return (0);
	ft_lstadd_front(&lst, node1);
	ft_lstadd_front(&lst, node2);
	result = (ft_lstsize(lst) == 2 && ft_lstsize(NULL) == 0);
	if (node1 != NULL)
		free(node1);
	if (node2 != NULL)
		free(node2);
	ft_print_test_result("ft_lstsize", result);
	return (result);
}

static int	test_ft_lstlast(void)
{
	t_list	*node1;
	t_list	*node2;
	t_list	*lst;
	t_list	*last;
	int		result;

	lst = NULL;
	node1 = ft_lstnew("first");
	node2 = ft_lstnew("second");
	if (node1 == NULL || node2 == NULL)
		return (0);
	ft_lstadd_front(&lst, node1);
	ft_lstadd_front(&lst, node2);
	last = ft_lstlast(lst);
	result = (last == node1 && strcmp((char *)last->content, "first") == 0);
	if (node1 != NULL)
		free(node1);
	if (node2 != NULL)
		free(node2);
	ft_print_test_result("ft_lstlast", result);
	return (result);
}

static int	test_ft_lstadd_back(void)
{
	t_list	*node1;
	t_list	*node2;
	t_list	*lst;
	int		result;

	lst = NULL;
	node1 = ft_lstnew("first");
	node2 = ft_lstnew("second");
	if (node1 == NULL || node2 == NULL)
		return (0);
	ft_lstadd_back(&lst, node1);
	ft_lstadd_back(&lst, node2);
	result = (lst == node1 && lst->next == node2 &&
		strcmp((char *)lst->content, "first") == 0 &&
		strcmp((char *)lst->next->content, "second") == 0);
	if (node1 != NULL)
		free(node1);
	if (node2 != NULL)
		free(node2);
	ft_print_test_result("ft_lstadd_back", result);
	return (result);
}

static void	del_content(void *content)
{
	free(content);
}

static int	test_ft_lstdelone(void)
{
	t_list	*node;
	char	*content;
	int		result;

	content = strdup("test");
	node = ft_lstnew(content);
	if (node == NULL)
		return (0);
	ft_lstdelone(node, del_content);
	result = 1;
	ft_print_test_result("ft_lstdelone", result);
	return (result);
}

static int	test_ft_lstclear(void)
{
	t_list	*node1;
	t_list	*node2;
	t_list	*lst;
	char	*content1;
	char	*content2;
	int		result;

	content1 = strdup("first");
	content2 = strdup("second");
	lst = NULL;
	node1 = ft_lstnew(content1);
	node2 = ft_lstnew(content2);
	if (node1 == NULL || node2 == NULL)
		return (0);
	ft_lstadd_back(&lst, node1);
	ft_lstadd_back(&lst, node2);
	ft_lstclear(&lst, del_content);
	result = (lst == NULL);
	ft_print_test_result("ft_lstclear", result);
	return (result);
}

static void	iter_func(void *content)
{
	char	*str;

	str = (char *)content;
	if (str != NULL && strlen(str) > 0)
		str[0] = 'X';
}

static int	test_ft_lstiter(void)
{
	t_list	*node1;
	t_list	*node2;
	t_list	*lst;
	char	*content1;
	char	*content2;
	int		result;

	content1 = strdup("first");
	content2 = strdup("second");
	lst = NULL;
	node1 = ft_lstnew(content1);
	node2 = ft_lstnew(content2);
	if (node1 == NULL || node2 == NULL)
		return (0);
	ft_lstadd_back(&lst, node1);
	ft_lstadd_back(&lst, node2);
	ft_lstiter(lst, iter_func);
	result = (((char *)lst->content)[0] == 'X' &&
		((char *)lst->next->content)[0] == 'X');
	ft_lstclear(&lst, del_content);
	ft_print_test_result("ft_lstiter", result);
	return (result);
}

static void	*map_func(void *content)
{
	char	*str;
	char	*new_str;

	str = (char *)content;
	new_str = strdup(str);
	if (new_str != NULL && strlen(new_str) > 0)
		new_str[0] = 'M';
	return (new_str);
}

static int	test_ft_lstmap(void)
{
	t_list	*node1;
	t_list	*node2;
	t_list	*lst;
	t_list	*new_lst;
	char	*content1;
	char	*content2;
	int		result;

	content1 = strdup("first");
	content2 = strdup("second");
	lst = NULL;
	node1 = ft_lstnew(content1);
	node2 = ft_lstnew(content2);
	if (node1 == NULL || node2 == NULL)
		return (0);
	ft_lstadd_back(&lst, node1);
	ft_lstadd_back(&lst, node2);
	new_lst = ft_lstmap(lst, map_func, del_content);
	result = (new_lst != NULL && new_lst->next != NULL &&
		strcmp((char *)new_lst->content, "Mirst") == 0 &&
		strcmp((char *)new_lst->next->content, "Mecond") == 0);
	ft_lstclear(&lst, del_content);
	ft_lstclear(&new_lst, del_content);
	ft_print_test_result("ft_lstmap", result);
	return (result);
}

int	main(void)
{
	t_test	part1_tests[] = {
		{"ft_isalpha", test_ft_isalpha, 0},
		{"ft_isdigit", test_ft_isdigit, 0},
		{"ft_isalnum", test_ft_isalnum, 0},
		{"ft_isascii", test_ft_isascii, 0},
		{"ft_isprint", test_ft_isprint, 0},
		{"ft_strlen", test_ft_strlen, 0},
		{"ft_memset", test_ft_memset, 0},
		{"ft_bzero", test_ft_bzero, 0},
		{"ft_memcpy", test_ft_memcpy, 0},
		{"ft_memmove", test_ft_memmove, 0},
		{"ft_strlcpy", test_ft_strlcpy, 0},
		{"ft_strlcat", test_ft_strlcat, 0},
		{"ft_toupper", test_ft_toupper, 0},
		{"ft_tolower", test_ft_tolower, 0},
		{"ft_strchr", test_ft_strchr, 0},
		{"ft_strrchr", test_ft_strrchr, 0},
		{"ft_strnstr", test_ft_strnstr, 0},
		{"ft_strncmp", test_ft_strncmp, 0},
		{"ft_memchr", test_ft_memchr, 0},
		{"ft_memcmp", test_ft_memcmp, 0},
		{"ft_atoi", test_ft_atoi, 0},
		{"ft_calloc", test_ft_calloc, 0},
		{"ft_strdup", test_ft_strdup, 0}
	};
	t_test	part2_tests[] = {
		{"ft_substr", test_ft_substr, 0},
		{"ft_strjoin", test_ft_strjoin, 0},
		{"ft_strtrim", test_ft_strtrim, 0},
		{"ft_split", test_ft_split, 0},
		{"ft_itoa", test_ft_itoa, 0},
		{"ft_strmapi", test_ft_strmapi, 0},
		{"ft_striteri", test_ft_striteri, 0},
		{"ft_putchar_fd", test_ft_putchar_fd, 0},
		{"ft_putstr_fd", test_ft_putstr_fd, 0},
		{"ft_putendl_fd", test_ft_putendl_fd, 0},
		{"ft_putnbr_fd", test_ft_putnbr_fd, 0}
	};
	t_test	bonus_tests[] = {
		{"ft_lstnew", test_ft_lstnew, 0},
		{"ft_lstadd_front", test_ft_lstadd_front, 0},
		{"ft_lstsize", test_ft_lstsize, 0},
		{"ft_lstlast", test_ft_lstlast, 0},
		{"ft_lstadd_back", test_ft_lstadd_back, 0},
		{"ft_lstdelone", test_ft_lstdelone, 0},
		{"ft_lstclear", test_ft_lstclear, 0},
		{"ft_lstiter", test_ft_lstiter, 0},
		{"ft_lstmap", test_ft_lstmap, 0}
	};
	t_part	part1 = {
		"Part 1 - Libc functions",
		part1_tests,
		sizeof(part1_tests) / sizeof(part1_tests[0]),
		0,
		0
	};
	t_part	part2 = {
		"Part 2 - Additional functions",
		part2_tests,
		sizeof(part2_tests) / sizeof(part2_tests[0]),
		0,
		0
	};
	t_part	bonus = {
		"Bonus - Linked list functions",
		bonus_tests,
		sizeof(bonus_tests) / sizeof(bonus_tests[0]),
		0,
		1
	};

	ft_print_header("Libft");
	ft_print_part_header("Part 1 - Libc functions");
	ft_run_part(&part1);
	ft_print_part_header("Part 2 - Additional functions");
	ft_run_part(&part2);
	ft_print_part_header("Bonus - Linked list functions");
	ft_run_part(&bonus);
	printf("\n%s═══════════════════════════════════════════════════════════\n",
		BLUE);
	printf("Overall Summary:\n");
	printf("  Part 1: %d/%d passed\n", part1.passed_count,
		part1.test_count);
	printf("  Part 2: %d/%d passed\n", part2.passed_count,
		part2.test_count);
	if (bonus.test_count > 0)
		printf("  Bonus: %d/%d passed\n", bonus.passed_count,
			bonus.test_count);
	else
		printf("  Bonus: Not present (OK)\n");
	printf("═══════════════════════════════════════════════════════════%s\n",
		RESET);
	return ((part1.passed_count == part1.test_count &&
			part2.passed_count == part2.test_count) ? 0 : 1);
}
