#include <QString>

#include <movings/cmovingmanager.h>


int main(int argc, char ** argv){

    CMovingManager *mng = new CMovingManager();
    mng->process();

    delete mng;

    return 0;
}
