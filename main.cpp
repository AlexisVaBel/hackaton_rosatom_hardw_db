#include <QString>

#include <movings/cmovingmanager.h>
#include <movings/cmovingtest_manager.h>


int main(int argc, char ** argv){

//    CMovingManager *mng = new CMovingManager();
//    mng->process();
    CMovingTest_Manager *mng = new CMovingTest_Manager();

    mng->test_income_register_set_rfid();
    mng->test_income_register_move_in_order();

    delete mng;

    return 0;
}
