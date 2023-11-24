#include <stdio.h>
#include <stdlib.h>
#include "ft_list.h"

#define LIST_LEN 5 

int     ft_strcmp(char *s1, char *s2)
{
    unsigned char   c1;
    unsigned char   c2;

    while (*s1 != '\0')
    {
        c1 = *s1++;
        c2 = *s2++;
        if (c1 != c2)
            return c1 < c2 ? -1 : 1;
    }
    return (0);
}

int     main(void)
{
    t_list  *list;
    t_list  *current;
    char    *strs[LIST_LEN];
    t_list  *found;

    strs[0] = "Ecole42";   
    strs[1] = "Push_one";   
    strs[2] = "Compiler";   
    strs[3] = "Push";   
    strs[4] = "Action That";   
    list = ft_list_push_strs(LIST_LEN, strs);
    current = list;
    while (current)
    {
        printf("%s -> ", (char*)current->data);
        current = current->next;
    }
    printf("\n");
    found = ft_list_find(list, strs[1], &ft_strcmp);
    printf("Found: %s\n", (char*)found->data);
    ft_list_clear(&list, free_fct);
    if (list == NULL)
        printf("\nList empty\n");
    return(0);
}

void        ft_list_push_front(t_list **begin_list, void *data)
{
    t_list      *elem;
    t_list      *current;

    elem = ft_create_elem(data);
    if (elem == NULL)
        return;
    if (*begin_list == NULL)
    {
        *begin_list = elem;
    }
    else 
    {
        current = *begin_list;
        while (current->next != NULL)
            current = current->next;
        elem->next = current->next;
        current->next = elem;
    }
}

t_list      *ft_create_elem(void *data)
{
    t_list      *elem;

    elem = (t_list*)malloc(sizeof(t_list));
    if (elem == NULL)
        return NULL;
    elem->next = NULL;
    elem->data = data;
    return (elem);
}

void        ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
    t_list      *list_ptr;

    if (!begin_list)
        return;
    list_ptr  = begin_list;
    while (list_ptr != NULL)
    {
        f(list_ptr->data);
        list_ptr = list_ptr->next;
    }
}

void        ft_list_clear(t_list **begin_list, void (*free_fct)(void *))
{
    t_list      *current;

    if (!begin_list || !(*begin_list))
        return;
    while (*begin_list)
    {
        
        current = *begin_list;
        *begin_list = (*begin_list)->next;
        // free_fct(current->data);
        current->data = NULL;
        free_fct(current);
    }
    *begin_list = NULL;
}

int         ft_list_size(t_list *begin_list)
{
    int          i;
    t_list      *current;

    i = 0;
    current = begin_list;
    while (current)
    {
        i++;
        current = current->next;
    }
    return (i);
}

t_list      *ft_list_last(t_list *begin_list)
{
    t_list      *current;

    current = begin_list;
    while (current->next != NULL)
        current = current->next;
    return (current);
}

void        ft_list_push_back(t_list **begin_list, void *data)
{
    t_list      *elem;

    elem = ft_create_elem(data);
    if (elem == NULL)
        return;
    elem->next = *begin_list;
    *begin_list = elem;
}

t_list      *ft_list_push_strs(int size, char **strs)
{
    int         i;
    t_list      *list_strs;

    list_strs = NULL;
    i = 0;
    while (i < size)
    {
        ft_list_push_front(&list_strs, strs[i]);
        i++;
    }
    return(list_strs);
}

t_list      *ft_list_at(t_list *begin_list, unsigned int nbr)
{
    unsigned int    i;
    t_list          *elem;

    i = 0;
    elem = begin_list;  
    while (elem)
    {
        if (i == nbr)
            return (elem);
        i++;
        elem = elem->next;
    }
    return (NULL);
}

void        ft_list_reverse(t_list **begin_list) 
{
    t_list     *prev;
    t_list     *next;
    t_list     *current;

    prev = NULL;
    current = *begin_list;
    while (current) 
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *begin_list = prev;
}

void        ft_list_foreach_if(t_list *begin_list, void (*f)(void *), 
                void *data_ref, int(*cmp)())
{
    t_list  *current;

    current = begin_list;
    while (current != NULL)
    {
        if ((cmp(current->data, data_ref)) == 0)
            f(current->data);
        current = current->next;
    }
}

t_list      *ft_list_find(t_list *begin_list, void *data_ref, int (*cmp)())
{
    t_list  *current;

    current = begin_list;
    while (current != NULL)
    {
        if ((cmp(current->data, data_ref)) == 0)
            return (current);
        current = current->next;
    }
    return (NULL);
}

void        free_fct(void *ptr)
{
    free(ptr);
}

void        print_elem_data(void *data)
{
    printf("Element: %s\n", (char*)data);
}