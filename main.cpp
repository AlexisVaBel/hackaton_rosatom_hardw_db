#include <QString>

//#include <movings/cmovingmanager.h>
#include <movings/cmovingtest_manager.h>


int main(int argc, char ** argv){


    CMovingTest_Manager *mng = new CMovingTest_Manager();

//    mng->test_income_register_set_rfid();
//    mng->test_income_register_set_rfid_notenough();
//    mng->test_income_register_move_in_order();
    mng->test_income_register_move_in_disorder();

    delete mng;

    return 0;
}
