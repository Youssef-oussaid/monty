#include "monty.h"

/**
 * print_character - Prints the ASCII value.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @line_number: Integer representing the line number of the opcode.
 */
void print_character(stack_t **stack, unsigned int line_number)
{
	int ascii_value;

	if (stack == NULL || *stack == NULL)
		string_issue(11, line_number);

	ascii_value = (*stack)->value;
	if (ascii_value < 0 || ascii_value > 127)
		string_issue(10, line_number);
	printf("%c\n", ascii_value);
}

/**
 * print_string - Prints a string.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @line_number: Integer representing the line number of the opcode.
 */
void print_string(stack_t **stack, __attribute__((unused))unsigned int line_number)
{
	int ascii_value;
	stack_t *temp;

	if (stack == NULL || *stack == NULL)
	{
		printf("\n");
		return;
	}

	temp = *stack;
	while (temp != NULL)
	{
		ascii_value = temp->value;
		if (ascii_value <= 0 || ascii_value > 127)
			break;
		printf("%c", ascii_value);
		temp = temp->next;
	}
	printf("\n");
}

/**
 * rotate_left - Rotates the first node of the stack to the bottom.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @line_number: Integer representing the line number of the opcode.
 */
void rotate_left(stack_t **stack, __attribute__((unused))unsigned int line_number)
{
	stack_t *temp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		return;

	temp = *stack;
	while (temp->next != NULL)
		temp = temp->next;

	temp->next = *stack;
	(*stack)->prev = temp;
	*stack = (*stack)->next;
	(*stack)->prev->next = NULL;
	(*stack)->prev = NULL;
}


/**
 * rotate_right - Rotates the last node of the stack to the top.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @line_number: Integer representing the line number of the opcode.
 */
void rotate_right(stack_t **stack, __attribute__((unused))unsigned int line_number)
{
	stack_t *temp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		return;

	temp = *stack;

	while (temp->next != NULL)
		temp = temp->next;

	temp->next = *stack;
	temp->prev->next = NULL;
	temp->prev = NULL;
	(*stack)->prev = temp;
	(*stack) = temp;
}
