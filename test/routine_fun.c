# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

void    *compute(void *arg)
{
    int *res = malloc(sizeof(int));
    *res = 42;
    return res;
}

int main(void)
{
    pthread_t thread;
    void    *res;

    pthread_create(&thread, NULL, compute, NULL);
    pthread_join(&thread, &res);

    int value = *(int *)res;
    printf("the value = %d\n", value);
    free(res);

    return 0;
}