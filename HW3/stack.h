#ifndef __STACK__
#define __STACK__

#include <stddef.h>  /* size_t */
#include <stdbool.h> /* bool   */ 
#include "stdlib.h"
#include "stdio.h"

typedef enum { SUCCESS = 0, FAIL } Result; 

typedef struct stack *pstack_t;
typedef void *elem_t;

typedef elem_t (*clone_t)(elem_t e);
typedef void (*destroy_t)(elem_t e);
typedef void (*print_t)(elem_t e);

pstack_t stack_create(size_t max_num_of_elem, clone_t clone, destroy_t destroy, 
						print_t print);

/**
 * @fn void stack_destroy(pstack_t s);
 * @brief destroys the user_stack. free all the memory of the elements in the
 * stack. user_stack must be a stack created by StackCreate otherwise
 * undefined behavior)
 * @param stack - pointer to the stack to destroy
 * @return none
 */
Result stack_destroy(pstack_t stack);
/* ------------------------------------------ */
/* Add here the rest of the declarations      */
/* ------------------------------------------ */
/*
 * @fn Result stack_push(pstack_t stack, elem_t e)
 * @brief Pushes an element onto the stack.
 * @param stack - pointer to the stack
 * @param e - element to be pushed onto the stack
 * @return SUCCESS if the element was successfully pushed, FAIL otherwise
 */

Result stack_push(pstack_t stack, elem_t e);
/*
 * @fn Result stack_push(pstack_t stack, elem_t e)
 * @brief Pushes an element onto the stack.
 * @param stack - pointer to the stack
 * @param e - element to be pushed onto the stack
 * @return SUCCESS if the element was successfully pushed, FAIL otherwise
 */

void stack_pop(pstack_t stack);
/*
 * @fn void stack_pop(pstack_t stack)
 * @brief Removes the top element from the stack.
 * @param stack - pointer to the stack
 * @return none
 */

elem_t stack_peek(pstack_t stack);
/*
 * @fn elem_t stack_peek(pstack_t stack)
 * @brief Returns the top element of the stack without removing it.
 * @param stack - pointer to the stack
 * @return the top element of the stack, or NULL if the stack is empty
 */

size_t stack_size(pstack_t stack);
/*
 * @fn size_t stack_size(pstack_t stack)
 * @brief Returns the number of elements in the stack.
 * @param stack - pointer to the stack
 * @return the number of elements in the stack
 */

bool stack_is_empty(pstack_t stack);
/*
 * @fn bool stack_is_empty(pstack_t stack)
 * @brief Checks if the stack is empty.
 * @param stack - pointer to the stack
 * @return true if the stack is empty, false otherwise
 */

size_t stack_capacity(pstack_t stack);
/*
 * @fn size_t stack_capacity(pstack_t stack)
 * @brief Returns the maximum number of elements the stack can hold.
 * @param stack - pointer to the stack
 * @return the maximum number of elements the stack can hold
 */

void stack_print(pstack_t stack);
/*
 * @fn void stack_print(pstack_t stack)
 * @brief Prints the elements of the stack.
 * @param stack - pointer to the stack
 * @return none
 */

#endif /* __STACK__ */