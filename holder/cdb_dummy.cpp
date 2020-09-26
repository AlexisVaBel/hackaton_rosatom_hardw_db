#include "cdb_dummy.h"


#include <iostream>

const char * CDB_Dummy::RFID_PLACE_1 = "OOVT";
const char * CDB_Dummy::RFID_PLACE_2 = "OOGP";
const char * CDB_Dummy::RFID_PLACE_3 = "Production";

CDB_Dummy::CDB_Dummy()
{

}

CDB_Dummy::~CDB_Dummy()
{
    //delete pnts from list
}

bool CDB_Dummy::db_connect()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    this->bConnected = true;
    return true;
}

bool CDB_Dummy::db_diconnect()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    this->bConnected = false;
    return true;
}

QPair<QString, int> CDB_Dummy::get_main_dev()
{
    QPair<QString,int> main_dev("TP001", 1);
    QPair<QString,int> &ret_dev = main_dev; // to make copy of returning value
    return ret_dev;
}

QList<QPair<QString, int> > CDB_Dummy::get_devs()
{
    QList<QPair<QString, int> >  lst;
    lst.append(qMakePair(RFID_PLACE_1, 2));
    lst.append(qMakePair(RFID_PLACE_2, 3));
    lst.append(qMakePair(RFID_PLACE_3, 4));

    QList<QPair<QString, int> >  &ret_lst = lst;
    return ret_lst;  // to make copy of returning value
}

QList<QPair<QString, int> > CDB_Dummy::get_containers()
{
    QList<QPair<QString, int> >  lst;

    for(auto i = 0; i < 10 ; ++i){
        lst.append(qMakePair(QString("Container_3%1").arg(i), 30 + i));
    }

    QList<QPair<QString, int> >  &ret_lst = lst;
    return ret_lst;
}

bool CDB_Dummy::unregister_container(QString &strRFIDCode)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return  true;
}

bool CDB_Dummy::register_container(QString &strNonDestrCode, QString &strRFIDCode)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return  true;
}

bool CDB_Dummy::append_moving(uint32_t &iDevID, QString &strContainerRFIDCode)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return  true;
}

bool CDB_Dummy::add_container(QString &strNonDestrCode, int &id)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return  true;
}
