#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
 
//  int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//  void *(*start_routine)(void *), void *arg);
//  첫번째 파라미터 : 쓰레드 식별자
//  두번쨰 파라미터 : 쓰레드 특성 (기본은 NULL)
//  세번째 파라미터 : 분기시켜서 실행하게 될 쓰레드 함수
//  네번째 파라미터 : 쓰레드 함수가 넘겨받을 매개변수
void *thread_function(void *data){
        pid_t pid;
        pthread_t tid;
 
        char* thread_name = (char*) data;
         pid = getpid();         // 프로세스의 id 
        tid = pthread_self();   // pthread 식별
 
        int i = 0;
 
        while(i < 3){
                // pthread 이름, id, 식별자, loop횟수 
                printf("[%s] pid : %u, tid:%x --- %d\n",
                                thread_name, (unsigned int) pid, (unsigned int) tid,i);
                i++;
                sleep(1);
        }
		return (0);
}
int main(){
        pthread_t p_thread[2];
        int thr_id;
        int status;
        char p1[] = "thread_1";
        char p2[] = "thread_2";
        char pp[] = "thread_Main";
 
        sleep(1);
 
        // 1번 쓰레드 생성
        thr_id = pthread_create(&p_thread[0], NULL, thread_function, (void *) p1);
 
        if(thr_id < 0)
                perror("쓰레드 생성 실패");
 
        // 2번 쓰레드 생성
        thr_id = pthread_create(&p_thread[1], NULL, thread_function, (void *) p2);
 
        if(thr_id < 0)
                perror("쓰레드 생성 실패");
 
        // main함수에서도 쓰레드가 실행되고 있는 동일한 함수 실행
        thread_function((void *) pp);
 
        // wating pthread end
        pthread_join(p_thread[0], (void **)&status);
        pthread_join(p_thread[1], (void **)&status);
 
        return 0;
}
 