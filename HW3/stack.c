#include "stack.h"

typedef struct stack {
    elem_t *data;
    size_t elements_count;
    int free_capacity;
    clone_t clone;
    destroy_t destroy;
    print_t print;
} stack_t;

pstack_t stack_create(size_t max_num_of_elem, clone_t clone, destroy_t destroy, 
                        print_t print)
{
    pstack_t stack = malloc(sizeof(stack_t));  // Allocate memory for the stack
    if (stack == NULL) {
        return NULL;
    }

    stack->data = malloc(max_num_of_elem * sizeof(elem_t));  // Allocate memory for the stack data
    if (stack->data == NULL) {
        free(stack);
        return NULL;
    }

    stack->elements_count = 0;  // Initialize the number of elements in the stack
    stack->free_capacity = max_num_of_elem;  // Initialize the free capacity of the stack
    stack->clone = clone;  // Set the element cloning function
    stack->destroy = destroy;  // Set the element destruction function
    stack->print = print;  // Set the element printing function

    return stack;
}
/* 
 * @fn pstack_t stack_create(size_t max_num_of_elem, clone_t clone, destroy_t destroy, print_t print)
 * @brief Creates and initializes a stack with the specified capacity and element handling functions.
 * @param max_num_of_elem - maximum number of elements the stack can hold
 * @param clone - function pointer to the element cloning function
 * @param destroy - function pointer to the element destruction function
 * @param print - function pointer to the element printing function
 * @return pointer to the created stack, or NULL if the creation failed
 */

Result stack_destroy(pstack_t stack)
{
    if (stack == NULL) {
        return SUCCESS;
    }
    if (stack->data != NULL) {
        for (int i = 0; i < stack->elements_count; i++) {
            stack->destroy(stack->data[i]);
        }
        free(stack->data);
    }
    free(stack);
    return SUCCESS;
}
/* 
 * @fn Result stack_destroy(pstack_t stack)
 * @brief Destroys the stack and frees all the memory associated with it.
 * @param stack - pointer to the stack to destroy
 * @return SUCCESS if the stack was successfully destroyed, FAIL otherwise
 */

Result stack_push(pstack_t stack, elem_t e)
{
    if (stack == NULL) {
        return FAIL;
    }
    if (stack->free_capacity > 0) {
        stack->data[stack->elements_count] = stack->clone(e);  // Clone and add the element to the stack
        stack->elements_count++;  // Increment the number of elements in the stack
        stack->free_capacity--;  // Decrement the free capacity of the stack
        return SUCCESS;
    }
    return FAIL;
}
/* 
 * @fn Result stack_push(pstack_t stack, elem_t e)
 * @brief Pushes an element onto the stack.
 * @param stack - pointer to the stack
 * @param e - the element to push onto the stack
 * @return SUCCESS if the element was successfully pushed, FAIL otherwise
 */

void stack_pop(pstack_t stack)
{
    if (stack == NULL) {
        return;
    }
    if (stack->elements_count == 0) {
        return;
    }
    stack->destroy(stack->data[stack->elements_count-1]);  // Destroy the top element of the stack
    stack->elements_count--;  // Decrement the number of elements in the stack
    stack->free_capacity++;  // Increment the free capacity of the stack
    return;
}
/* 
 * @fn void stack_pop(pstack_t stack)
 * @brief Removes the top element from the stack.
 * @param stack - pointer to the stack
 * @return none
 */

elem_t stack_peek(pstack_t stack)
{
    if (stack == NULL) {
        return NULL;
    }
    if (stack->elements_count == 0) {
        return NULL;
    }
    return stack->data[stack->elements_count-1];  // Return the top element of the stack
}
/* 
 * @fn elem_t stack_peek(pstack_t stack)
 * @brief Returns the top element of the stack without removing it.
 * @param stack - pointer to the stack
 * @return the top element of the stack, or NULL if the stack is empty
 */

size_t stack_size(pstack_t stack)
{
    if (stack == NULL) {
        return 0;
    }
    return stack->elements_count;  // Return the number of elements in the stack
}
/* 
 * @fn size_t stack_size(pstack_t stack)
 * @brief Returns the number of elements in the stack.
 * @param stack - pointer to the stack
 * @return the number of elements in the stack
 */

bool stack_is_empty(pstack_t stack)
{
    if (stack == NULL) {
        return false;
    }
    return stack->elements_count ? false : true;  // Return true if the stack is empty, false otherwise
}
/* 
 * @fn bool stack_is_empty(pstack_t stack)
 * @brief Checks if the stack is empty.
 * @param stack - pointer to the stack
 * @return true if the stack is empty, false otherwise
 */

size_t stack_capacity(pstack_t stack)
{
    if (stack == NULL) {
        return 0;
    }
    return stack->free_capacity;  // Return the free capacity of the stack
}
/* 
 * @fn size_t stack_capacity(pstack_t stack)
 * @brief Returns the free capacity of the stack.
 * @param stack - pointer to the stack
 * @return the free capacity of the stack
 */

void stack_print(pstack_t stack)
{
    if (stack == NULL) {
        return;
    }

    if (stack->elements_count == 0) {
        return;
    }

    for (size_t i = 0; i < stack->elements_count; i++) {
        stack->print(stack->data[stack->elements_count - 1 - i]);  // Print each element of the stack in reverse order
    }
}
/* 
 * @fn void stack_print(pstack_t stack)
 * @brief Prints the elements of the stack in reverse order.
 * @param stack - pointer to the stack
 * @return none
 */
