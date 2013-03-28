#include "pomdp.h"

void test_backup(){
	pomdp problem;
	problem.init();
	problem.backup_helper(3);
}