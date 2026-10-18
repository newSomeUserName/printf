
#include "ft_printf.h"
#include <stdio.h>


int main(void)
{
	int x = ft_strlen("German");
	char *arr = NULL;
	int *p = &x;
	int count;
	(void)p;
	count = ft_printf("%X\n%u\n%s\n%p\n%p\n%s%%\n",170, 0XAA, "FUCK", p, NULL, arr);
	ft_printf("%d\n", count);
	printf("\n-------------\n");
	printf("%X\n%u\n%s\n%p\n%p\n%s%%\n",170, 0XAA, "FUCK", p, NULL, arr);
	printf("%d\n", count);

	// ft_printf("%p\n",NULL);
	// printf("%p\n", NULL);
	// printf("\n-------------\n");
	// printf("%p", NULL);
	// printf(">%1d\n>   <\n%d\n%d%d<\n%% \nl \n%%\n");
	return (0);
}

