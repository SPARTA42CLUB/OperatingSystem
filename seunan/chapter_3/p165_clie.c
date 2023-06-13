#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rpc/rpc.h>

#define ADD_PROG 0x20000001
#define ADD_VERS 1
#define ADD_PROC 1

struct intpair { // 서버와 클라이언트 간에 주고받을 매개변수 구조체로 사용
    int a;
    int b;
};

int main() {
    CLIENT *cl;
    struct intpair args;
    int *result;

    args.a = 10;
    args.b = 20;

    cl = clnt_create("localhost", ADD_PROG, ADD_VERS, "udp");
    if (cl == NULL) {
        clnt_pcreateerror("clnt_create error");
        exit(1);
    }

    result = add_1(&args, cl);
    if (result == NULL) {
        clnt_perror(cl, "add_1 call failed");
        exit(1);
    }

    printf("Result: %d\n", *result);
    clnt_destroy(cl);

    return 0;
}
