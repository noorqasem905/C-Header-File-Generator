#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <ctype.h>
#include "libft/libft.h"

#define MAX_PROTOTYPES 1024
#define MAX_LINE_LEN 1024

typedef struct s_prototype
{
	char	ret_type[512];
	char	prototype[1024];
}	t_prototype;

int	ends_with_c(const char *filename)
{
	int	len;

	len = strlen(filename);
	if (len > 2 && strcmp(filename + len - 2, ".c") == 0)
		return (1);
	return (0);
}

int	is_function_signature(const char *line)
{
	if (!line || line[0] == '\n' || line[0] == ' ' || line[0] == '\t')
		return (0);
	if (ft_strncmp(line, "static ", 7) == 0)
		return (0);
	if (strstr(line, "//") || strstr(line, "/*") || strstr(line, "*/"))
		return (0);
	if (!strchr(line, '(') || !strchr(line, ')') || strchr(line, '{'))
		return (0);
	if (strstr(line, "return") || strstr(line, "printf") || strchr(line, '"'))
		return (0);
	if (strstr(line, "main("))
		return (0);
	return (1);
}

int	extract_prototype(const char *line, t_prototype *p)
{
	char	buffer[MAX_LINE_LEN];
	char	*newline;
	char	*paren;
	int		i;
	char	*end;

	strncpy(buffer, line, sizeof(buffer));
	buffer[sizeof(buffer) - 1] = '\0';
	newline = strchr(buffer, '\n');
	if (newline)
		*newline = '\0';
	if (ft_strlen(buffer) < 3)
		return (0);
	paren = ft_strchr(buffer, '(');
	if (!paren)
		return (0);
	i = paren - buffer;
	while (i > 0 && (isalnum((unsigned char)buffer[i - 1]) || buffer[i - 1] == '_'
			|| buffer[i - 1] == ' ' || buffer[i - 1] == '*'))
		i--;
	strncpy(p->ret_type, buffer, i);
	p->ret_type[i] = '\0';
	end = p->ret_type + strlen(p->ret_type) - 1;
	while (end > p->ret_type && isspace((unsigned char)*end))
		*end-- = '\0';
	snprintf(p->prototype, sizeof(p->prototype), "%s;", buffer);
	return (1);
}

int	compare_prototypes(const void *a, const void *b)
{
	const t_prototype	*p1 = (const t_prototype *)a;
	const t_prototype	*p2 = (const t_prototype *)b;

	return (strcmp(p1->ret_type, p2->ret_type));
}

void	process_file(const char *filepath, t_prototype *prototypes, int *count)
{
	int		fd;
	char	*line;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return ;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (is_function_signature(line)
			&& *count < MAX_PROTOTYPES
			&& extract_prototype(line, &prototypes[*count]))
			(*count)++;
		free(line);
	}
	close(fd);
}

void	process_directory(const char *dir_path, t_prototype *prototypes, int *count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			fullpath[1024];

	dir = opendir(dir_path);
	if (!dir)
		return ;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == DT_REG && ends_with_c(entry->d_name))
		{
			snprintf(fullpath, sizeof(fullpath), "%s/%s", dir_path,
				entry->d_name);
			process_file(fullpath, prototypes, count);
		}
	}
	closedir(dir);
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

int	main(int argc, char *argv[])
{
	t_prototype	prototypes[MAX_PROTOTYPES];
	int			count;
	FILE		*out;
	int			i;

	if (argc != 3)
	{
		write(2, "Usage: ./generate_header_file <src_path> <output.h>\n", 52);
		return (1);
	}
	count = 0;
	if (is_directory(argv[1]))
		process_directory(argv[1], prototypes, &count);
	else
		process_file(argv[1], prototypes, &count);
	qsort(prototypes, count, sizeof(t_prototype), compare_prototypes);
	out = fopen(argv[2], "w");
	if (!out)
		return (1);
	fprintf(out, "#ifndef GENERATED_H\n# define GENERATED_H\n\n");
	i = 0;
	while (i < count)
	{
		fprintf(out, "%-10s\t\t%s\n", prototypes[i].ret_type,
			prototypes[i].prototype + strlen(prototypes[i].ret_type));
		i++;
	}
	fprintf(out, "\n#endif\n");
	fclose(out);
	return (0);
}

