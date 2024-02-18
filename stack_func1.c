#include "monty.h"


/**
 * push_to_stack - Adds a node to the stack.
 * @new_node: Pointer to the new node.
 * @line_num: Integer representing the line number of the opcode.
 */
void push_to_stack(stack_t **new_node, __attribute__((unused))unsigned int line_num)
{
	stack_t *temp;

	if (new_node == NULL || *new_node == NULL)
		exit(EXIT_FAILURE);
	if (top == NULL)
	{
		top = *new_node;
		return;
	}
	temp = top;
	top = *new_node;
	top->next = temp;
	temp->prev = top;
}


/**
 * print_stack - Prints the elements of the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @line_number: Line number of the opcode.
 */
void print_stack(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	(void) line_number;
	if (stack == NULL)
		exit(EXIT_FAILURE);
	temp = *stack;
	while (temp != NULL)
	{
		printf("%d\n", temp->value);
		temp = temp->next;
	}
}

/**
 * pop_top - Removes the top element from the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @line_number: Integer representing the line number of the opcode.
 */
void pop_top(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (stack == NULL || *stack == NULL)
		more_err(7, line_number);

	temp = *stack;
	*stack = temp->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(temp);
}

/**
 * print_top - Prints the value of the top element of the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @line_number: Integer representing the line number of the opcode.
 */
void print_top(stack_t **stack, unsigned int line_number)
{
	if (stack == NULL || *stack == NULL)
		more_err(6, line_number);
	printf("%d\n", (*stack)->value);
}
