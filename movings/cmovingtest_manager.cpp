#include "cmovingtest_manager.h"

#include <iostream>


#include "holder/cdb_dummy.h"
#include "producer/crfid_producer.h"

#include <producer/cundestr_producer.h>

CMovingTest_Manager::CMovingTest_Manager(QObject *parent) : QObject(parent)
{

}

void CMovingTest_Manager::test_from_income_to_outcome()
{
    m_db = new CDB_Dummy();
    std::cout << "Test case: add 10 containers, link to them rfids " << std::endl;

    QList<CCODEs_Producer*> lstRFID;
    lstRFID.reserve(10);
    CUndestr_Producer        *undestrMarker = nullptr;

    m_db->db_connect();
    auto devs_pair = m_db->get_devs();
    unpack_rfids(devs_pair, &lstRFID);

    auto undestrDev_pair = m_db->get_main_dev();
    undestrMarker = unpack_undestr(undestrDev_pair);


    QList<QString> lstCollars;
    QList<QString> lstRFIDInContainers;
    QString strCode = "";
    int id = 0;
    //getting available collars wich we set to container

    for(auto i = 0; i < 10; ++i){
        lstRFID.first()->process();
        lstCollars.push_back(lstRFID.first()->getNewCode());
    }
    auto *tmp = lstRFID.first();
    lstRFID.pop_front();
    delete tmp;

    //adding container by nodestructible code, check that same code doesn`t affect
    for(auto i = 0; i < 100; ++i){
        undestrMarker->process();
        strCode = undestrMarker->getNewCode();
        if(m_db->add_container(strCode, id)){
            std::cout << "adding container " << std::endl;
            if(lstCollars.isEmpty()) continue;
            m_db->register_container(strCode, lstCollars.first());
            std::cout << "register rfid to container " << std::endl;
            lstRFIDInContainers.push_back(lstCollars.first());
            lstCollars.pop_front();
        }
    }


    m_db->db_diconnect();


    delete m_db;
    m_db = nullptr;

}

void CMovingTest_Manager::procs_new_rfid_income(QString &strCode, QString &strDev, uint32_t &idDev)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void CMovingTest_Manager::procs_new_container(QString &strCode, QString &strDev, uint32_t &idDev)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void CMovingTest_Manager::unpack_rfids(QList<QPair<QString, int> > &rfids, QList<CCODEs_Producer *> *lstRFID)
{
    if(rfids.isEmpty())return;
    for(auto i = 0; i < rfids.length(); ++i){
        auto *pnt = new CRFID_Producer(rfids.at(i).second, rfids.at(i).first) ;
        connect(pnt, SIGNAL(received_new_code(QString &, QString &, uint32_t &)),this, SLOT(procs_new_rfid_income(QString &, QString &, uint32_t &)));
        lstRFID->append(std::move(pnt));
    }
}

CUndestr_Producer * CMovingTest_Manager::unpack_undestr(QPair<QString, int> &undestr)
{
    CUndestr_Producer *pnt = new CUndestr_Producer(undestr.second, undestr.first);

    connect(pnt, SIGNAL(received_new_code(QString &, QString &, uint32_t &)),this, SLOT(procs_new_container(QString &, QString &, uint32_t &)));
    return pnt;
}





//}
