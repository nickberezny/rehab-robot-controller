#include "../unity/src/unity.h"
#include "Example.h"

void setUp (void) {} /* Is run before every test, put unit init calls here. */
void tearDown (void) {} /* Is run after every test, put unit clean-up calls here. */



int main(void)
{
UNITY_BEGIN();
return UNITY_END();
}