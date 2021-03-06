#include "Stack.h"
#include "../Utilities/c_dangeon.h"
#include "../Utilities/Log/gcc_trace.h"
#include "../Utilities/Log/log.h"

#include <stdio.h>
#include <assert.h>

void print_int (FILE *file, const void *pint);

/*


@bug: canary verifying 


*/

int main()
{
    int data = 5;
    auto *stk_int = stack_ctor (10, sizeof (int));
    
    if (!stk_int) LOG_MSG (FATAL, "Stack was not created");

    //CAST (char *, stk_int)[0] = 0;

    if (!stack_verify (stk_int))
    {
        LOG_MSG (FATAL, "ver failed");
        exit (2);
    }

    stack_dump_to_log (stk_int);

    for (int i = 0; i < 128; ++i)
        stack_push (stk_int, &i), printf ("%d\n", i);

    int i = 0;
    do 
    {
        if (stack_top (stk_int, &data) == STACK_OK)
            printf ("[%d] = %d\n", i++, data);
    } while (stack_pop (stk_int) == STACK_OK);

    //*(*(char **)((char *)stk_int + sizeof (canary_t)) + 32) = 0x69;
    //*((char *)stk_int + sizeof (ProtectedBuffer) + sizeof (canary_t) + 3) = 0x69;
    //*((char *)stk_int + sizeof (ProtectedBuffer) + sizeof (canary_t) + 4) = 0x69;
    //*((char *)stk_int + sizeof (ProtectedBuffer) + sizeof (canary_t) + 6) = 0x69;

    stack_set_elem_printer (stk_int, print_int);



    stack_dump_to_log (stk_int);
    stack_dtor (stk_int);    

    return 0;
}

void print_int (FILE *file, const void *pint)
{
    assert (pint);

    int val = *(int *)(pint);
    fprintf (file, "%d", val);
}