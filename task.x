struct task {
    int id;
    int type;
    string payload<256>;
}; /* [cite: 31-35, 49] */

struct result {
    string output<256>;
    int id;
}; /* [cite: 36-39] */

program TASKPROG {
    version TASKVERS {
        int SUBMIT_TASK(task) = 1;
        result GET_RESULT(int) = 2;
    } = 1; /* [cite: 42-46] */
} = 0x23451111; /* [cite: 47] */
