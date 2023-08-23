#define DEFINE_VARIABLES
#include "global.h"
#include "monty.h"
/**
 * clean_up - a helper function for the main program that helps clean up
 * @bytecode_file: the file to execute
 * @line: line
 * @stack: stack
 */
void clean_up(FILE *bytecode_file, char *line, stack_t *stack)
{
	if (line != NULL)
		free(line);
	if (bytecode_file != NULL)
		fclose(bytecode_file);
	free_stack(stack);
}
/**
 * process - a helper function for main
 * @bytecode_file: file to execute
 * @instructions: functions
 * @stack: stack
 * Return: int
 */
int process(FILE *bytecode_file, instruction_t *instructions, stack_t **stack)
{
	char *line = NULL, *opcode;
	size_t len = 0;
	unsigned int line_number = 0;
	int found = 0, i;

	while (getline(&line, &len, bytecode_file) != -1)
	{
		line_number++;
		opcode = strtok(line, " \t\n");
		if (opcode == NULL || strncmp(opcode, "#", 1) == 0)
			continue;
		global_data.arg = strtok(NULL, " \t\n");
		for (i = 0; instructions[i].opcode != NULL; i++)
			if (strcmp(opcode, instructions[i].opcode) == 0)
			{
				instructions[i].f(stack, line_number);
				found = 1;
				break;
			}
		if (!found)
		{
			fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
			clean_up(bytecode_file, line, *stack);
			return (EXIT_FAILURE);
		}
		found = 0;
	}
	clean_up(bytecode_file, line, *stack);
	return (EXIT_SUCCESS);
}
/**
 * main - main
 * @argc: arguments count
 * @argv: arguments
 * Return: int
 */
int main(int argc, char *argv[])
{

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
		{"div", div_p},
		{"mul", mul},
		{"mod", mod},
		{"pchar", pchar},
		{"pstr", pstr},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};
	int result;
	FILE *bytecode_file;

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
	result = process(bytecode_file, instructions, &stack);
	return (result);
}
