#include "../unity/src/unity.h"
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "InitUtilities.h"



void setUp (void) {} /* Is run before every test, put unit init calls here. */
void tearDown (void) {} /* Is run after every test, put unit clean-up calls here. */

void test_initThread(void)
{
	struct sched_param param[4];
    pthread_attr_t attr[4];
    pthread_t thread[4];
    int priorities[4] = {98,97,96,95};

	TEST_ASSERT_TRUE(initThread(attr, param, priorities,4));
}

void test_initSock(void)
{
	struct sockaddr_in serv_addr; 
	int port = 8081;
	int listen_fd = 0, conn_fd = 0;

	TEST_ASSERT_EQUAL_INT(initSock(&serv_addr, &listen_fd, port), 1);


}

void test_initMemory(void)
{
	pthread_mutex_t lock[3]; 

	TEST_ASSERT_TRUE(initMemory(lock, 3));
}

void test_initDataLog(void)
{
	FILE testFile;
	TEST_ASSERT_TRUE(initDataLog(&testFile, "test_file.txt"));
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_initThread);
	RUN_TEST(test_initSock);
	RUN_TEST(test_initMemory);
	RUN_TEST(test_initDataLog);
	return UNITY_END();
}