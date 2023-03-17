# get_next_line
- You can use at most 10 functions in this project. 

## Definition of Variables
- char buffer[BUFFER_SIZE]: stores texts after the read function.  
- static char *save: if '\n' is in the buffer, then the rest of the characters are copied to the save.
- result: a string to return.

## How does it work
```c
char	*get_next_line(int fd)
{
	static char	*save;
	char		*result;
	ssize_t		return_val;
	char		*buffer;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	*(buffer + BUFFER_SIZE) = '\0';
	result = NULL;
	return_val = save_to_result(&buffer, &result, &save);
	if (return_val == 1)
	{
		free(buffer);
		return (result);
	}
	else if (return_val == -1)
		return (exit_free(&buffer, &result, &save));
	return_val = read_line_continue(&buffer, &result, &save, &fd);
	if ((return_val == -1) || (result != NULL && ft_strlen(result) < 1))
		return (exit_free(&buffer, &result, &save));
	free(buffer);
	return (result);
}
```

### check save
- if the 'save' is NULL, read the 'buffer size' in the text and the result to the 'buffer'.
- else if the 'save' isn't NULL, you have to move the data in the 'save' to the 'buffer', and the 'save' set to NULL.
```c
static int	save_to_result(char **buffer, char **result, char **save)
{
	if ((*save) == NULL)
		return (-2);
	ft_strlcpy(*buffer, *save, ft_strlen(*save) + 1);
	free(*save);
	*save = NULL;
	return (put_line(buffer, result, save));
}
```

### find '\n' in the buffer
- Find '\n' in the buffer
- If '\n' in the buffer
    - the former append to the 'result'
        : [0th] index to the [index of '\n']
    - the others to the save 
        : [index + 1] to the [BUFFER_SIZE - 1]
    - return 'result'
- If '\n' is not in the buffer
    - entire 'buffer' copy to the 'result'
    - until you find the '\n', read the text.
```c
static int	put_line(char **buffer, char **result, char **save)
{
	ssize_t		index;

	index = find_char(*buffer, '\n');
	if (index == -1)
	{
		*result = append_buffer(*result, *buffer, ft_strlen(*buffer));
		if (*result == NULL)
			return (-1);
		free(*save);
		*save = NULL;
		return (0);
	}
	*result = append_buffer(*result, *buffer, index + 1);
	if (*result == NULL)
		return (-1);
	if (BUFFER_SIZE - (index + 1) > 0)
	{
		*save = append_buffer(*save, (*buffer + index + 1), \
			BUFFER_SIZE - (index + 1));
		if (*save == NULL)
			return (-1);
	}
	return (1);
}
```
```c
static int	read_line_continue(char **buffer, \
char **result, char **save, int *fd)
{
	ssize_t		return_val;

	while (1)
	{
		return_val = read(*fd, *buffer, BUFFER_SIZE);
		if (return_val <= 0)
			break ;
		*(*buffer + return_val) = '\0';
		return_val = put_line(buffer, result, save);
		if (return_val == 1 || return_val == -1)
			break ;
	}
	return (return_val);
}
```


## exception: return NULL
- if the read failed: return value of read is -1 or 0
- fd value error: fd < 0
```c
static char	*exit_free(char **buffer, char **result, char **save)
{
	free(*buffer);
	(*buffer) = NULL;
	free(*save);
	(*save) = NULL;
	free(*result);
	(*result) = NULL;
	return (NULL);
}
```
## Help Functions
- find_char : function for finding the index of '\n', if not return -1
```c
ssize_t	find_char(const char *s, int c)
{
	char	*dummy;
	ssize_t	index;

	dummy = (char *)s;
	index = 0;
	while (*(dummy + index))
	{
		if (((char)*(dummy + index)) == (char)c)
			return (index);
		index++;
	}
	if ((char)c == '\0')
		return (index);
	return (-1);
}
```
- append_buffer: after the 'result' of 'save', append a part of the 'buffer'
```c
char	*append_buffer(char const *s1, char const *s2, size_t len)
{
	char	*arr;
	size_t	len_s1;

	if (s1 == NULL && s2 != NULL)
	{
		arr = malloc(sizeof(char) * (len + 1));
		if (!arr)
			return (NULL);
		ft_strlcpy(arr, s2, len + 1);
		return (arr);
	}
	else if (s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	arr = (char *)malloc(sizeof(char) * (len_s1 + len + 1));
	if (!arr)
		return (NULL);
	ft_strlcpy(arr, s1, len_s1 + 1);
	ft_strlcat(arr, s2, len_s1 + len + 1);
	free((void *)s1);
	return (arr);
}
```