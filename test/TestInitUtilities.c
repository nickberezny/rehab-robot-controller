#include "../unity/src/unity.h"
#include "InitUtilities.h"

void setUp (void) {} /* Is run before every test, put unit init calls here. */
void tearDown (void) {} /* Is run after every test, put unit clean-up calls here. */

void test_initThread(void)
{
	struct sched_param param;
    pthread_attr_t attr;
    pthread_t thread;

	TEST_ASSERT_TRUE(initThread(&attr, &param, 98));
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_initThread);
	return UNITY_END();
}