#include "monty.h"

/**
 * multiply_nodes - Multiplies the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @line_number: Integer representing the line number of the opcode.
 */
void multiply_nodes(stack_t **stack, unsigned int line_number)
{
	int product;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "mul");

	(*stack) = (*stack)->next;
	product = (*stack)->value * (*stack)->prev->value;
	(*stack)->value = product;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}


/**
 * modulo_nodes - Computes the modulo of the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @line_number: Integer representing the line number of the opcode.
 */
void modulo_nodes(stack_t **stack, unsigned int line_number)
{
	int remainder;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "mod");


	if ((*stack)->value == 0)
		more_err(9, line_number);
	(*stack) = (*stack)->next;
	remainder = (*stack)->value % (*stack)->prev->value;
	(*stack)->value = remainder;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}
