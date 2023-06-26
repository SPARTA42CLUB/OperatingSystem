#include <stdio.h>
#include <pthread.h>

// 스레드 함수
void *thread_function(void *arg)
{
    int thread_arg = *((int *)arg);
    printf("스레드 실행 중: %d\n", thread_arg);
    // 여기에 스레드가 수행할 작업을 추가할 수 있습니다.
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread;
    int arg = 123;

    // 스레드 생성
    int result = pthread_create(&thread, NULL, thread_function, &arg);
    if (result != 0) {
        printf("스레드 생성 실패\n");
        return 1;
    }

    printf("메인 스레드 실행 중\n");

    // 여기에 메인 스레드가 수행할 작업을 추가할 수 있습니다.

    // 스레드 종료 대기
    pthread_join(thread, NULL);

    printf("스레드 종료\n");

    return 0;
}
