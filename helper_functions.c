#include "shell.h"

/**
 * _strcmp - compare two strings
 * @first: first string to be compared
 * @second: second string to be compared
 *
 * Return: difference of the two strings
 */
int _strcmp(char *first, char *second)
{
    int i = 0;

    while (first[i] != '\0')
    {
        if (first[i] != second[i])
            break;
        i++;
    }
    return (first[i] - second[i]);
}

/**
 * _strcat - concatenates two strings
 * @destination: string to be concatenated to
 * @source: string to concatenate
 *
 * Return: address of the new string
 */
char *_strcat(char *destination, char *source)
{
    char *new_string = NULL;
    int len_dest = _strlen(destination);
    int len_source = _strlen(source);

    new_string = malloc(sizeof(*new_string) * (len_dest + len_source + 1));
    _strcpy(destination, new_string);
    _strcpy(source, new_string + len_dest);
    new_string[len_dest + len_source] = '\0';
    return (new_string);
}

/**
 * _strspn - gets the length of a prefix substring
 * @str1: string to be searched
 * @str2: string to be used
 *
 * Return: number of bytes in the initial segment of str1 which are part of str2
 */
int _strspn(char *str1, char *str2)
{
    int i = 0;
    int match = 0;

    while (str1[i] != '\0')
    {
        if (_strchr(str2, str1[i]) == NULL)  /* Corrected argument type */
            break;
        match++;
        i++;
    }
    return (match);
}

/**
 * _strcspn - computes segment of str1 which consists of characters not in str2
 * @str1: string to be searched
 * @str2: string to be used
 *
 * Return: index at which a char in str1 exists in str2
 */
int _strcspn(char *str1, char *str2)
{
    int len = 0, i;

    for (i = 0; str1[i] != '\0'; i++)
    {
        if (_strchr(str2, str1[i]) != NULL)  /* Corrected argument type */
            break;
        len++;
    }
    return (len);
}

/**
 * _strchr - Locate character in a string.
 * @s: String to search.
 * @c: Character to locate.
 *
 * Return: Pointer to the first occurrence of c in s, or NULL if not found.
 */
char *_strchr(char *s, char c)
{
    while (*s)
    {
        if (*s == c)
            return s;
        s++;
    }

    if (c == '\0')  /* Check for the null terminator case */
        return s;

    return NULL;
}
