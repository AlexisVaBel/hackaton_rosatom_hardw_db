#include <QString>

#include <movings/cmovingmanager.h>
#include <movings/cmovingtest_manager.h>


int main(int argc, char ** argv){

//    CMovingManager *mng = new CMovingManager();
//    mng->process();
    CMovingTest_Manager *mng = new CMovingTest_Manager();

    mng->test_from_income_to_outcome();

    delete mng;

    return 0;
}
