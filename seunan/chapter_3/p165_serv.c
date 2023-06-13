#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rpc/rpc.h>

#define ADD_PROG 0x20000001
#define ADD_VERS 1
#define ADD_PROC 1

struct intpair {
    int a;
    int b;
};

int *add_1(struct intpair *args, CLIENT *clnt) {
    static int result;

    result = args->a + args->b;
    return &result;
}

int main() {
    if (!svc_create(add_1, ADD_PROG, ADD_VERS, "udp")) {
        fprintf(stderr, "unable to register (ADD_PROG, ADD_VERS, udp)\n");
        exit(1);
    }

    svc_run();
    fprintf(stderr, "Error: svc_run returned\n");
    exit(1);
}
