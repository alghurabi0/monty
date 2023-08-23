#include "monty.h"
/**
 * free_stack - Frees all elements of a stack.
 * @stack: Double pointer to the head of the stack.
 */
void free_stack(stack_t *stack)
{
	stack_t *current;

	while (stack != NULL)
	{
		current = stack;
		stack = stack->next;
		free(current);
	}
}
