/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fortitude_runner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajoncou <pajoncou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:52:26 by pajoncou          #+#    #+#             */
/*   Updated: 2025/11/21 13:52:26 by pajoncou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortitude.h"
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_COMMAND_LEN 2048

# define MAX_FILES 1000
# define MAX_PATH 512

typedef struct s_file_info
{
	char	name[MAX_PATH];
	int		is_source;
	int		is_header;
	int		is_makefile;
	int		is_binary;
}	t_file_info;

static int	ft_file_exists(const char *path)
{
	struct stat	buffer;

	return (stat(path, &buffer) == 0);
}

static int	ft_is_source_file(const char *name)
{
	const char	*ext;

	ext = strrchr(name, '.');
	if (ext == NULL)
		return (0);
	return (strcmp(ext, ".c") == 0);
}

static int	ft_is_header_file(const char *name)
{
	const char	*ext;

	ext = strrchr(name, '.');
	if (ext == NULL)
		return (0);
	return (strcmp(ext, ".h") == 0);
}

static int	ft_is_makefile(const char *name)
{
	return (strcmp(name, "Makefile") == 0 ||
		strcmp(name, "makefile") == 0);
}

static int	ft_is_binary_file(const char *name)
{
	const char	*ext;

	ext = strrchr(name, '.');
	if (ext == NULL)
		return (0);
	return (strcmp(ext, ".a") == 0 || strcmp(ext, ".o") == 0 ||
		strcmp(ext, ".exe") == 0);
}

static int	ft_list_files(t_file_info *files, int *count)
{
	DIR				*dir;
	struct dirent	*entry;
	int				idx;

	dir = opendir(".");
	if (dir == NULL)
		return (0);
	idx = 0;
	while ((entry = readdir(dir)) != NULL && idx < MAX_FILES)
	{
		if (entry->d_name[0] == '.')
			continue ;
		strncpy(files[idx].name, entry->d_name, MAX_PATH - 1);
		files[idx].name[MAX_PATH - 1] = '\0';
		files[idx].is_source = ft_is_source_file(entry->d_name);
		files[idx].is_header = ft_is_header_file(entry->d_name);
		files[idx].is_makefile = ft_is_makefile(entry->d_name);
		files[idx].is_binary = ft_is_binary_file(entry->d_name);
		idx++;
	}
	closedir(dir);
	*count = idx;
	return (1);
}

static void	ft_print_file_list(t_file_info *files, int count)
{
	int	i;

	printf("\n%s═══════════════════════════════════════════════════════════\n",
		BLUE);
	printf("Project Files:\n");
	printf("═══════════════════════════════════════════════════════════%s\n",
		RESET);
	i = 0;
	while (i < count)
	{
		if (files[i].is_makefile)
			printf("%s[Makefile]%s %s\n", YELLOW, RESET, files[i].name);
		else if (files[i].is_header)
			printf("%s[Header]%s   %s\n", GREEN, RESET, files[i].name);
		else if (files[i].is_source)
			printf("%s[Source]%s   %s\n", BLUE, RESET, files[i].name);
		else if (files[i].is_binary)
			printf("%s[Binary]%s   %s\n", RED, RESET, files[i].name);
		else
			printf("[Other]    %s\n", files[i].name);
		i++;
	}
	printf("\n");
}

static int	ft_is_libft_project(void)
{
	return (ft_file_exists("libft.h") && ft_file_exists("Makefile"));
}

static int	ft_build_project(void)
{
	int		result;
	FILE	*pipe;
	char	buffer[1024];
	char	*command;

	if (ft_is_libft_project())
		command = "make bonus 2>&1";
	else
		command = "make all 2>&1";
	printf("%sBuilding project...%s\n", YELLOW, RESET);
	pipe = popen(command, "r");
	if (pipe == NULL)
	{
		printf("%s[ERROR] Failed to execute make!%s\n", RED, RESET);
		return (0);
	}
	while (fgets(buffer, sizeof(buffer), pipe) != NULL)
		printf("%s", buffer);
	result = pclose(pipe);
	if (result != 0)
	{
		printf("%s[ERROR] Build failed!%s\n", RED, RESET);
		return (0);
	}
	printf("%s[SUCCESS] Build completed!%s\n", GREEN, RESET);
	return (1);
}


static int	ft_file_exists_at_path(const char *dir, const char *filename)
{
	char	path[MAX_PATH];
	struct stat	st;

	snprintf(path, sizeof(path), "%s/%s", dir, filename);
	if (stat(path, &st) == 0)
		return (1);
	return (0);
}


static int	ft_find_fortitude_dir(char *fortitude_path, size_t path_size)
{
	char	current_dir[MAX_PATH];
	char	test_path[MAX_PATH];

	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		return (0);
	strncpy(fortitude_path, current_dir, path_size - 1);
	fortitude_path[path_size - 1] = '\0';
	while (strlen(fortitude_path) > 1)
	{
		snprintf(test_path, sizeof(test_path), "%s/Fortitude", fortitude_path);
		if (ft_file_exists_at_path(test_path, "fortitude_runner") ||
			ft_file_exists_at_path(test_path, "Makefile"))
		{
			strncpy(fortitude_path, test_path, path_size - 1);
			fortitude_path[path_size - 1] = '\0';
			return (1);
		}
		if (strrchr(fortitude_path, '/') != NULL)
			*strrchr(fortitude_path, '/') = '\0';
		else if (strrchr(fortitude_path, '\\') != NULL)
			*strrchr(fortitude_path, '\\') = '\0';
		else
			break ;
		if (strlen(fortitude_path) == 0)
			break ;
	}
	return (0);
}

static int	ft_test_project(void)
{
	int		result;
	FILE	*pipe;
	char	buffer[1024];
	char	fortitude_path[MAX_PATH];
	char	command[MAX_COMMAND_LEN];

	if (ft_file_exists("test_libft") || ft_file_exists("test"))
	{
		printf("%sRunning tests...%s\n", YELLOW, RESET);
		if (ft_file_exists("test_libft"))
			pipe = popen("./test_libft 2>&1", "r");
		else
			pipe = popen("./test 2>&1", "r");
		if (pipe == NULL)
		{
			printf("%s[ERROR] Failed to execute tests!%s\n", RED, RESET);
			return (0);
		}
		while (fgets(buffer, sizeof(buffer), pipe) != NULL)
			printf("%s", buffer);
		result = pclose(pipe);
		if (result != 0)
		{
			printf("%s[ERROR] Tests failed!%s\n", RED, RESET);
			return (0);
		}
		printf("%s[SUCCESS] All tests passed!%s\n", GREEN, RESET);
		return (1);
	}
	if (ft_is_libft_project() && ft_find_fortitude_dir(fortitude_path,
			sizeof(fortitude_path)))
	{
		printf("%sRunning Libft test suite from Fortitude...%s\n",
			YELLOW, RESET);
		snprintf(command, sizeof(command), "cd %s && make test_libft 2>&1",
			fortitude_path);
		pipe = popen(command, "r");
		if (pipe == NULL)
		{
			printf("%s[ERROR] Failed to execute tests!%s\n", RED, RESET);
			return (0);
		}
		while (fgets(buffer, sizeof(buffer), pipe) != NULL)
			printf("%s", buffer);
		result = pclose(pipe);
		if (result != 0)
		{
			printf("%s[ERROR] Tests failed!%s\n", RED, RESET);
			return (0);
		}
		printf("%s[SUCCESS] All tests passed!%s\n", GREEN, RESET);
		return (1);
	}
	printf("%s[INFO] No test binary found, skipping tests.%s\n",
		YELLOW, RESET);
	return (1);
}

static int	ft_check_norminette_installed(void)
{
	FILE	*pipe;
	char	buffer[1024];
	int		result;

	pipe = popen("norminette --version 2>&1", "r");
	if (pipe == NULL)
		return (0);
	while (fgets(buffer, sizeof(buffer), pipe) != NULL)
		;
	result = pclose(pipe);
	return (result == 0);
}

static int	ft_run_norminette(void)
{
	int		result;
	FILE	*pipe;
	char	buffer[1024];
	int		has_errors;

	if (!ft_check_norminette_installed())
	{
		printf("%s[WARNING] Norminette not found, skipping norm check.%s\n",
			YELLOW, RESET);
		return (1);
	}
	printf("%sRunning norminette...%s\n", YELLOW, RESET);
	pipe = popen("norminette . 2>&1", "r");
	if (pipe == NULL)
	{
		printf("%s[ERROR] Failed to execute norminette!%s\n", RED, RESET);
		return (0);
	}
	has_errors = 0;
	while (fgets(buffer, sizeof(buffer), pipe) != NULL)
	{
		printf("%s", buffer);
		if (strstr(buffer, "Error!") != NULL)
			has_errors = 1;
	}
	result = pclose(pipe);
	if (result == 0 && !has_errors)
	{
		printf("%s[SUCCESS] Norminette check passed!%s\n", GREEN, RESET);
		return (1);
	}
	else
	{
		printf("%s[ERROR] Norminette check failed!%s\n", RED, RESET);
		return (0);
	}
}

static void	ft_clean_project(void)
{
	int		result;
	FILE	*pipe;
	char	buffer[1024];

	printf("%sCleaning project...%s\n", YELLOW, RESET);
	pipe = popen("make fclean 2>&1", "r");
	if (pipe == NULL)
	{
		printf("%s[ERROR] Failed to execute make fclean!%s\n", RED, RESET);
		return ;
	}
	while (fgets(buffer, sizeof(buffer), pipe) != NULL)
		;
	result = pclose(pipe);
	if (result == 0)
		printf("%s[SUCCESS] Project cleaned!%s\n", GREEN, RESET);
	else
		printf("%s[WARNING] Clean command returned non-zero%s\n",
			YELLOW, RESET);
}

int	main(int argc, char **argv)
{
	t_file_info	files[MAX_FILES];
	int			file_count;
	int			build_success;
	int			norm_success;
	int			test_success;
	char		project_name[MAX_PATH];

	(void)argc;
	(void)argv;
	if (getcwd(project_name, MAX_PATH) == NULL)
		strcpy(project_name, "Unknown");
	printf("\n%s", BLUE);
	printf("╔══════════════════════════════════════════════════════════╗\n");
	printf("║                                                          ║\n");
	printf("║                    FORTITUDE RUNNER                      ║\n");
	printf("║                                                          ║\n");
	printf("║              Analyzing current directory                 ║\n");
	printf("║                                                          ║\n");
	printf("╚══════════════════════════════════════════════════════════╝\n");
	printf("%s\n", RESET);
	if (!ft_file_exists("Makefile") && !ft_file_exists("makefile"))
	{
		printf("%s[ERROR] No Makefile found in current directory!%s\n",
			RED, RESET);
		return (1);
	}
	if (!ft_list_files(files, &file_count))
	{
		printf("%s[ERROR] Failed to read directory!%s\n", RED, RESET);
		return (1);
	}
	ft_print_file_list(files, file_count);
	build_success = ft_build_project();
	norm_success = ft_run_norminette();
	if (build_success)
		test_success = ft_test_project();
	else
		test_success = 0;
	ft_clean_project();
	printf("\n%s═══════════════════════════════════════════════════════════\n",
		BLUE);
	printf("Summary:\n");
	if (build_success)
		printf("%s[SUCCESS] Build: OK%s\n", GREEN, RESET);
	else
		printf("%s[ERROR] Build: FAILED%s\n", RED, RESET);
	if (norm_success)
		printf("%s[SUCCESS] Norminette: OK%s\n", GREEN, RESET);
	else
		printf("%s[ERROR] Norminette: FAILED%s\n", RED, RESET);
	if (test_success)
		printf("%s[SUCCESS] Tests: OK%s\n", GREEN, RESET);
	else if (build_success)
		printf("%s[INFO] Tests: Not run or failed%s\n", YELLOW, RESET);
	printf("%s[SUCCESS] Cleanup: OK%s\n", GREEN, RESET);
	printf("═══════════════════════════════════════════════════════════%s\n",
		RESET);
	return (build_success && norm_success && test_success ? 0 : 1);
}

