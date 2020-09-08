#include "../unity/src/unity.h"
#include "Time.h"



void setUp (void) {} /* Is run before every test, put unit init calls here. */
void tearDown (void) {} /* Is run after every test, put unit clean-up calls here. */

void test_getStepTime(void)
{
	//(struct timespec * start, struct timespec * end, struct timespec * step)
	struct timespec start;
	struct timespec end;
	struct timespec step;
	struct timespec ans;

	start.tv_sec = 1;
	start.tv_nsec = 3000;
	end.tv_sec = 1;
	end.tv_nsec = 9000;
	ans.tv_sec = 0;
	ans.tv_nsec = 6000;

	getStepTime(&start,&end,&step);
	TEST_ASSERT_EQUAL_INT(ans.tv_sec,step.tv_sec);
	TEST_ASSERT_EQUAL_INT(ans.tv_nsec,step.tv_nsec);

	start.tv_sec = 1;
	start.tv_nsec = 3000;
	end.tv_sec = 2;
	end.tv_nsec = 3000;
	ans.tv_sec = 1;
	ans.tv_nsec = 0;

	getStepTime(&start,&end,&step);
	TEST_ASSERT_EQUAL_INT(ans.tv_sec,step.tv_sec);
	TEST_ASSERT_EQUAL_INT(ans.tv_nsec,step.tv_nsec);

	start.tv_sec = 1;
	start.tv_nsec = NSEC_IN_SEC*0.9;
	end.tv_sec = 2;
	end.tv_nsec = NSEC_IN_SEC*0.3;
	ans.tv_sec = 0;
	ans.tv_nsec = NSEC_IN_SEC*0.4 ;

	getStepTime(&start,&end,&step);
	TEST_ASSERT_EQUAL_INT(ans.tv_sec,step.tv_sec);
	TEST_ASSERT_EQUAL_INT(ans.tv_nsec,step.tv_nsec);
}


int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_getStepTime);

	return UNITY_END();
}