#include <stdio.h>

void subByVal(int b)
{
	b = b - 1;
}

void subByRef(int *b)
{
	*b = *b - 1;
}

void main()
{
	int a = 10;

	subByVal(a);
	printf("surprise, suprise, it's still: %d\n", a);

	subByRef(&a);
	printf("by ref works better: %d\n", a);
}
