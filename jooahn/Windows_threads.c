#include <windows.h>
#include <stdio.h>
DWORD Sum; // 공유되는 데이터

// 스레드가 실행할 함수
DWORD WINAPI Summation(LPVOID Param) {
	DWORD Upper = *(DWORD*)Param;
	for (DWORD i = 1; i <= Upper; i++)
		sum += i;
	return 0;
}

int main(int argc, char *argv[]) {
	DWORD ThreadId;
	HANDLE ThreadHandle;
	int Param;

	Param = atoi(argv[1]);

	// create the thread
	ThreadHandle = CreateThread(
			NULL, // default security attributes
			0, // default stack size
			Summation, // thread function
			&Param, // parameter to thread function
			0, // default creation flags
			&ThreadId); // returns the thread identifier

	// wait for the thread to finish
	WaitForSingleObject(ThreadHandle, INFINITE);

	// close the thread handle
	CloseHandle(ThreadHandle);

	printf("sum = %d\n", Sum);
}
