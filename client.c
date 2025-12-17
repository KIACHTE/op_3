#include <stdio.h>
#include "task.h"

void run_client(char *host) {
    CLIENT *clnt = clnt_create(host, TASKPROG, TASKVERS, "udp");
    int choice, tid;
    char payload[256];

    while (1) {
        printf("\n1. Submit Task\n2. Get Result\n3. Exit\nChoice: "); [cite: 60]
        scanf("%d", &choice);
        if (choice == 1) {
            task t;
            printf("Type (1:Rev, 2:Sum, 3:Fib): ");
            scanf("%d", &t.type);
            printf("Payload: ");
            scanf(" %[^\n]s", payload); [cite: 61]
            t.payload = payload;
            int *id = submit_task_1(&t, clnt); [cite: 62]
            printf("Submitted. Task ID: %d\n", *id);
        } else if (choice == 2) {
            printf("Enter Task ID: ");
            scanf("%d", &tid);
            result *res = get_result_1(&tid, clnt); [cite: 63]
            printf("Result: %s\n", res->output);
        } else break;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    run_client(argv[1]);
    return 0;
}
