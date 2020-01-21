/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gnl.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 22:16:52 by rbraaksm       #+#    #+#                */
/*   Updated: 2020/01/21 06:49:37 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define BUFFER_SIZE 2

size_t  ft_strlen(char *str)
{
    size_t  i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

char    *ft_strdup(char *str)
{
    char    *new;
    int     i;

    i = 0;
    new = malloc(sizeof(char *) * (ft_strlen(str) + 1));
    if (new == NULL)
        return (0);
    while (str[i] != '\0')
    {
        new[i] = str[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}

char    *ft_strjoin(char *s1, char *s2)
{
    int     i;
    int     i2;
    char    *new;

    i = 0;
    i2 = 0;
    new = malloc(sizeof(char *) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (new == NULL)
        return (0);
    while (s1[i] != '\0')
    {
        new[i] = s1[i];
        i++;
    }
    while (s2[i2] != '\0')
    {
        new[i + i2] = s2[i2];
        i2++;
    }
    new[i + i2] = '\0';
    return (new);
}

int     ft_strchr(char *str, char c)
{
    int     i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    if (str[i] == '\0' && str[i] == c)
        return (1);
    return (0);
}

char    *make_string(char *str, int *ret)
{
    char    buf[BUFFER_SIZE + 1];
    char    *tmp;

    while (*ret > 0)
    {
        *ret = read(0, buf, BUFFER_SIZE);
        tmp = str;
        str = ft_strjoin(str, buf);
        free(tmp);
        if (str == NULL)
            return (0);
        if (ft_strchr(str, '\n') == 1)
            break ;
    }
    return (str);
}

char    *make_line(char *str)
{

}

int     get_next_line(char **line)
{
    static char     *str;
    int             ret;

    ret = 1;
    if (str == NULL)
        str = ft_strdup("");
    while (ret > 0)
    {
        if (ft_strchr(str, '\n') == 1)
        {
            str = make_line(str);
            if (str == NULL)
                return (-1);
            return (1);
        }
        str = make_string(str, &ret);
        if (str == NULL)
            return (-1);
        // printf("String = %s\n", str);
    }
    return (0);
}

int     main(void)
{
    char    *str;
    int     res;

    res = 1;
    while (res > 0)
    {
        res = get_next_line(&str);
        printf("[RES] %d  [STRING]  %s\n", res, str);
        free(str);
    }
    return (0);
}
