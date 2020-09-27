#include "cdb_dummy.h"


#include <iostream>

const char * CDB_Dummy::RFID_REGISTER = "Register_container_RFID";
const char * CDB_Dummy::RFID_PLACE_1 = "OOVT";
const char * CDB_Dummy::RFID_PLACE_2 = "OOGP";
const char * CDB_Dummy::RFID_PLACE_3 = "Production";

CDB_Dummy::CDB_Dummy()
{
    mapContainers.clear();
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
    lst.append(qMakePair(RFID_REGISTER, 2));
    lst.append(qMakePair(RFID_PLACE_1, 3));
    lst.append(qMakePair(RFID_PLACE_2, 4));
    lst.append(qMakePair(RFID_PLACE_3, 5));

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
//    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if(mapRFIDContainers.contains(strRFIDCode)) return false;

    std::cout << "register code " << strRFIDCode.toStdString() << std::endl;

    mapRFIDContainers.insert(strRFIDCode, strNonDestrCode);
    return  true;
}

bool CDB_Dummy::append_moving(const uint32_t &iDevID, const QString &strContainerRFIDCode)
{
//    std::cout << __PRETTY_FUNCTION__ << " " << strContainerRFIDCode.toStdString() << std::endl;
    if(!mapRFIDContainers.contains(strContainerRFIDCode)) return false; //no such rfid


    std::cout << mapRFIDContainers.value(strContainerRFIDCode).toStdString() << " moving to " << iDevID<< std::endl;
    lstOfMovings.push_back(qMakePair(strContainerRFIDCode, iDevID));
    return  true;
}

bool CDB_Dummy::add_container(QString &strNonDestrCode, int &id)
{
//    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if(mapContainers.contains(strNonDestrCode)) return false;
    id = mapContainers.keys().count();
    mapContainers.insert(strNonDestrCode, id);
    std::cout << "nondestr code "<< strNonDestrCode.toStdString() << std::endl;
    return  true;
}
