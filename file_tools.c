#include "monty.h"

stack_t *stack_head = NULL; // Renaming 'head' to 'stack_head'

/**
 * open_data_file - opens a file
 * @file_path: the file path
 * Return: void
 */
void open_data_file(char *file_path)
{
	FILE *file_descriptor = fopen(file_path, "r");

	if (file_path == NULL || file_descriptor == NULL)
		troubleshooter(2, file_path);

	read_data_file(file_descriptor);
	fclose(file_descriptor);
}

/**
 * read_data_file - reads a file
 * @file_descriptor: pointer to file descriptor
 * Return: void
 */
void read_data_file(FILE *file_descriptor)
{
	int line_num, format = 0;
	char *line = NULL;
	size_t line_length = 0;

	for (line_num = 1; getline(&line, &line_length, file_descriptor) != -1; line_num++)
	{
		format = parse_line(line, line_num, format);
	}
	free(line);
}

/**
 * parse_line - Separates each line into tokens to determine
 * which function to call
 * @line: line from the file
 * @line_num: line number
 * @format: storage format. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 * Return: Returns 0 if the opcode is stack. 1 if queue.
 */
int parse_line(char *line, int line_num, int format)
{
	char *opcode, *argument;
	const char *delim = "\n ";

	if (line == NULL)
		troubleshooter(4);

	opcode = strtok(line, delim);
	if (opcode == NULL)
		return (format);
	argument = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	find_command(opcode, argument, line_num, format);
	return (format);
}

/**
 * find_command - find the appropriate function for the opcode
 * @opcode: opcode
 * @argument: argument of opcode
 * @format: storage format. If 0 Nodes will be entered as a stack.
 * @line_num: line number
 * if 1 nodes will be entered as a queue.
 * Return: void
 */
void find_command(char *opcode, char *argument, int line_num, int format)
{
	int i;
	int flag;

	instruction_t command_list[] = {
		{"push", push_to_stack},
		{"pall", print_stack},
		{"pint", print_top},
		{"pop", pop_top},
		{"nop", nop},
		{"swap", swap_nodes},
		{"add", add_nodes},
		{"sub", sub_nodes},
		{"div", div_nodes},
		{"mul", mul_nodes},
		{"mod", mod_nodes},
		{"pchar", print_char},
		{"pstr", print_str},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; command_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, command_list[i].opcode) == 0)
		{
			call_command(command_list[i].func, opcode, argument, line_num, format);
			flag = 0;
		}
	}
	if (flag == 1)
		troubleshooter(3, line_num, opcode);
}

/**
 * call_command - Calls the required function.
 * @func: Pointer to the function that is about to be called.
 * @op: String representing the opcode.
 * @arg: String representing a numeric value.
 * @line_num: Line number for the instruction.
 * @format: Format specifier. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 * Return: Void.
 */
void call_command(op_func func, char *op, char *arg, int line_num, int format)
{
	stack_t *node;
	int flag;
	int i;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (arg != NULL && arg[0] == '-')
		{
			arg = arg + 1;
			flag = -1;
		}
		if (arg == NULL)
			troubleshooter(5, line_num);
		for (i = 0; arg[i] != '\0'; i++)
		{
			if (isdigit(arg[i]) == 0)
				troubleshooter(5, line_num);
		}
		node = create_node(atoi(arg) * flag);
		if (format == 0)
			func(&node, line_num);
		if (format == 1)
			push_to_queue(&node, line_num);
	}
	else
		func(&stack_head, line_num);
}
