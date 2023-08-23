#include "monty.h"
/**
 * div_p - Divides the second top element of the stack by the top element.
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number in Monty byte code file.
 */
void div_p(stack_t **stack, unsigned int line_number)
{
	stack_t *top1, *top2;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	top1 = *stack;
	top2 = top1->next;
	if (top1->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}
	top2->n /= top1->n;
	*stack = top2;
	top2->prev = NULL;
	free(top1);
}
/**
 * sub - Subtracts the top element of the stack from the second top element.
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number in Monty byte code file.
 */
void sub(stack_t **stack, unsigned int line_number)
{
	stack_t *top1, *top2;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	top1 = *stack;
	top2 = top1->next;
	top2->n -= top1->n;
	*stack = top2;
	top2->prev = NULL;
	free(top1);
}
/**
 * nop - Does nothing.
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number in Monty byte code file.
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
/**
 * add - Adds the top two elements of the stack.
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number in Monty byte code file.
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *top1, *top2;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	top1 = *stack;
	top2 = top1->next;
	top2->n += top1->n;
	*stack = top2;
	top2->prev = NULL;
	free(top1);
}
/**
 * swap - Swaps the top two elements of the stack.
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number in Monty byte code file.
 */
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *top1, *top2;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	top1 = *stack;
	top2 = top1->next;
	top1->next = top2->next;
	top2->prev = NULL;
	top2->next = top1;
	top1->prev = top2;
	*stack = top2;
}
