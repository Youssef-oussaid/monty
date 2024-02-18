#include "monty.h"
stack_t *top = NULL;

/**
 * main - entry point
 * @argc: arguments count
 * @argv: list of arguments
 * Return: always 0
 */

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	open_data_file(argv[1]);
	free_nodes();
	return (0);
}

/**
 * create_node - Creates a node.
 * @value: Number to go inside the node.
 * Return: Upon success, a pointer to the node. Otherwise NULL.
 */
stack_t *create_node(int value)
{
	stack_t *node;

	node = malloc(sizeof(stack_t));
	if (node == NULL)
		troubleshooter(4);
	node->next = NULL;
	node->prev = NULL;
	node->n = value;
	return (node);
}

/**
 * free_nodes - Frees nodes in the stack.
 */
void free_nodes(void)
{
	stack_t *tmp;

	if (top == NULL)
		return;

	while (top != NULL)
	{
		tmp = top;
		top = top->next;
		free(tmp);
	}
}


/**
 * add_to_queue - Adds a node to the queue.
 * @new_node: Pointer to the new node.
 * @line_num: line number of the opcode.
 */
void add_to_queue(stack_t **new_node, __attribute__((unused))unsigned int line_num)
{
	stack_t *tmp;

	if (new_node == NULL || *new_node == NULL)
		exit(EXIT_FAILURE);
	if (top == NULL)
	{
		top = *new_node;
		return;
	}
	tmp = top;
	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = *new_node;
	(*new_node)->prev = tmp;

}
