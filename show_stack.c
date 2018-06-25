#include <stdio.h>
#include <stdlib.h>

void function2()
{
    void *trace[16];
    char **messages = (char **)NULL;
    int i, trace_size = 0;

    trace_size = backtrace(trace, 16);
    messages = backtrace_symbols(trace, trace_size);
    
    for (i=0; i < trace_size; i++)
        printf("%s\n", messages[i]);
    free(messages);
    return;
}

void function1()
{
    function2();
}

int main()
{
    function1();
    return 0;
}
