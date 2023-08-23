#include "monty.h"
/**
 * rotr - Rotates the stack to the right (to the bottom).
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number in Monty byte code file.
 */
void rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *current, *previous;
	(void) line_number;

	if (*stack == NULL || (*stack)->next == NULL)
		return;
	current = *stack;
	previous = NULL;
	while (current->next != NULL)
	{
		previous = current;
		current = current->next;
	}
	previous->next = NULL;
	current->next = *stack;
	*stack = current;
}
