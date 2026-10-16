
#include "ft_printf.h"
#include <stdio.h>


int main(void)
{
	int x = ft_strlen("German");
	int *p = &x;
	// ft_printf("%X\n%u\n%s\n%p\n",170, 0XAA, "FUCK", p);
	ft_printf("%p\n",NULL);
	printf("%p\n", NULL);
	// printf("\n-------------\n");
	// printf("%p", NULL);
	// printf(">%1d\n>   <\n%d\n%d%d<\n%% \nl \n%%\n");
	return (0);
}

