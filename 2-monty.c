#include "monty.h"
/**
 * rotl - Rotates the stack to the left (to the top).
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number in Monty byte code file.
 */
void rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *first, *second;
	(void) line_number;

	if (*stack == NULL || (*stack)->next == NULL)
		return;
	first = *stack;
	second = first->next;
	while (first->next != NULL)
		first = first->next;
	first->next = *stack;
	(*stack)->prev = first;
	(*stack)->next = NULL;
	*stack = second;
}
/**
 * pstr - Prints the string starting at the top of the stack.
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number in Monty byte code file.
 */
void pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *c;
	(void) line_number;

	c = *stack;
	while (c != NULL && c->n != 0 && c->n >= 0 && c->n <= 127)
	{
		putchar(c->n);
		c = c->next;
	}
	putchar('\n');
}
/**
 * pchar - Prints the character at the top of the stack.
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number in Monty byte code file.
 */
void pchar(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;
	int value;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	value = (*stack)->n;
	if (value < 0 || value > 127)
	{
		fprintf(stderr, "L%u: can't pchar, value out of range\n", line_number);
		exit(EXIT_FAILURE);
	}
	putchar(value);
	putchar('\n');
	temp = *stack;
	*stack = (*stack)->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(temp);
}
/**
 * mod - Computes the rest of the division of the second top element
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number in Monty byte code file.
 */
void mod(stack_t **stack, unsigned int line_number)
{
	stack_t *top1, *top2;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	top1 = *stack;
	top2 = top1->next;
	if (top1->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}
	top2->n %= top1->n;
	*stack = top2;
	top2->prev = NULL;
	free(top1);
}
/**
 * mul - Multiplies the second top element of the stack by the top element.
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number in Monty byte code file.
 */
void mul(stack_t **stack, unsigned int line_number)
{
	stack_t *top1, *top2;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	top1 = *stack;
	top2 = top1->next;
	top2->n *= top1->n;
	*stack = top2;
	top2->prev = NULL;
	free(top1);
}
