#include "monty.h"
monty_global_data_t global_data;
stack_t *stack = NULL;
instruction_t instructions[] = {
	{"push", push},
	{"pall", pall},
	{"pint", pint},
	{"pop", pop},
	{"swap", swap},
	{"add", add},
	{"nop", nop},
	{"sub", sub},
	{"div_p", div_p},
	{"mul", mul},
	{"mod", mod},
	{"pchar", pchar},
	{"pstr", pstr},
	{"rotl", rotl},
	{"rotr", rotr},
	{NULL, NULL}
};
/**
 * pop - Removes the top element of the stack.
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number in Monty byte code file.
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *top;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	top = *stack;
	*stack = (*stack)->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(top);
}
/**
 * pint - Prints the value at the top of the stack.
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number in Monty byte code file.
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}
/**
 * push - Pushes an element onto the stack.
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number in Monty byte code file.
 */
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *new_node;

	if (stack == NULL || global_data.arg == NULL)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new_node->n = atoi(global_data.arg);
	new_node->prev = NULL;
	if (*stack != NULL)
	{
		new_node->next = *stack;
		(*stack)->prev = new_node;
	}
	else
		new_node->next = NULL;
	*stack = new_node;
}
/**
 * pall - Prints all values on the stack.
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number in Monty byte code file.
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current;

	(void)line_number;

	current = *stack;

	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
/**
 * main - Monty interpreter main function.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 * Return: EXIT_SUCCESS or EXIT_FAILURE.
 */
int main(int argc, char *argv[])
{
	FILE *bytecode_file;
	char *line = NULL, *opcode;
	size_t len = 0;
	unsigned int line_number = 0;
	int found = 0, i;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	bytecode_file = fopen(argv[1], "r");
	if (bytecode_file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}
	global_data.arg = NULL;
	while (getline(&line, &len, bytecode_file) != -1)
	{
		line_number++;
		opcode = strtok(line, " \t\n");
		if (opcode == NULL || strncmp(opcode, "#", 1) == 0)
			continue;
		global_data.arg = strtok(NULL, " \t\n");
		for (i = 0; instructions[i].opcode != NULL; i++)
		{
			if (strcmp(opcode, instructions[i].opcode) == 0)
			{
				instructions[i].f(&stack, line_number);
				found = 1;
				break;
			}
		}
		if (!found)
		{
			fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
			free(line);
			fclose(bytecode_file);
			free_stack(stack);
			return (EXIT_FAILURE);
		}
	}
	free(line);
	fclose(bytecode_file);
	free_stack(stack);
	return (EXIT_SUCCESS);
}
