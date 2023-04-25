#include "student.h"

typedef enum { SUCCESS = 0, FAIL } Result; 

typedef struct stack *pstack_t;
typedef void *elem_t;



pstack_t stack_create(size_t max_num_of_elem, size_t elem_size)
{
	return malloc(max_num_of_elem * elem_size ); //////////////////////////////////////////////////////////check if null check newded 
}


Result stack_destroy(pstack_t stack)
{
	free(pstack_t); 
	assert(pstack_t ==NULL); /////////////////////////////////////////////////////////////////////////// check how to failure 

}
Result stack_push (pstack_t stack, elem_t e) 
{
	
}

void stack_pop(pstack_t stack) 

elem_t stack_peek(pstack_t stack) //check if to add null incase of failure/ 

size_t stack_size(pstack_t stack)

bool stack_is_empty(pstack_t stack)

size_t stack_capacity(pstack_t stack)

void stack_print(pstack_t stack)