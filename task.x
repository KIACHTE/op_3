
struct task {
    int id;
    int type;
    string payload<256>;
};

struct result {
    string output<256>;
    int id;
};

program TASKPROG {
    version TASKVERS {
        int SUBMIT_TASK(task) = 1;
        result GET_RESULT(int) = 2;
    } = 1;
} = 0x23451111;
