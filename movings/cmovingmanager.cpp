#include "cmovingmanager.h"

#include "../producer/crfid_producer.h"
#include <iostream>
#include <QThread>
#include <producer/cundestr_producer.h>

CMovingManager::CMovingManager(): m_db(new CDB_Dummy()), m_lstRFID(), m_undestrMarker(nullptr),
    m_bWork(true)
{
}

CMovingManager::~CMovingManager()
{
    delete m_db;
    delete m_undestrMarker;
}

void CMovingManager::process()
{
    prepare();

    int iCntLocal = 0;
    int iErrCnt = 0;

    while(m_bWork){
        if(iErrCnt > 10){
            break;
        }
        if(m_lstRFID.isEmpty() || m_undestrMarker == nullptr){
            prepare();
            ++iErrCnt;
            QThread::usleep(200);
            continue;
        }

        std::cout << __PRETTY_FUNCTION__ << " process ..." << std::endl;

        m_undestrMarker->process();

        for(auto i = 0 ; i < m_lstRFID.length(); ++i){
            m_lstRFID.at(i)->process();
            QThread::usleep(100);
        }

        //  for test reasons
        ++iCntLocal;
        if(iCntLocal > 100) break; // finish
        // ~for test reasons

        QThread::usleep(200);
    }
    finish_it();
}

void CMovingManager::finish_work()
{
    m_bWork = false;
}


void CMovingManager::procs_new_rfid_income(QString &strCode, QString &strDev, uint32_t &idDev)
{
    std::cout << __PRETTY_FUNCTION__ << " " << strCode.toStdString() << " " << strDev.toStdString() << std::endl;

    m_db->append_moving(idDev, strCode);
}

void CMovingManager::procs_new_container(QString &strCode, QString &strDev, uint32_t &idDev)
{
    std::cout << "New container incoming .... " << " " << strCode.toStdString() << " " << strDev.toStdString() << std::endl;
    bool containerFound = false;
    auto lstContainers = m_db->get_containers();
    for(auto i = 0; i < lstContainers.length(); ++i){
        if(QString(lstContainers.at(i).second).compare(strCode) == 0){
            containerFound = true;
        }
    }
    int id = 0;
    if(!containerFound) m_db->add_container(strCode, id);
}


void CMovingManager::prepare()
{
    std::cout << __PRETTY_FUNCTION__ << " prepare ..." << std::endl;
    if(!m_db->is_connected()){
        m_db->db_connect();
    }else{

        if(m_lstRFID.isEmpty()){
            auto devs_pair = m_db->get_devs();
            unpack_rfids(devs_pair);

        }

        if(m_undestrMarker == nullptr){
            auto undestr   = m_db->get_main_dev();
            unpack_undestr(undestr);
        }
    }
}

void CMovingManager::finish_it()
{
    m_db->db_diconnect();
}

void CMovingManager::unpack_rfids(QList<QPair<QString, int> > &rfids)
{
    if(rfids.isEmpty())return;
    for(auto i = 0; i < rfids.length(); ++i){
        auto *pnt = new CRFID_Producer(rfids.at(i).second, rfids.at(i).first) ;

        connect(pnt, SIGNAL(received_new_code(QString &, QString &, uint32_t &)),this, SLOT(procs_new_rfid_income(QString &, QString &, uint32_t &)));

        m_lstRFID.append(std::move(pnt));
    }
}

void CMovingManager::unpack_undestr(QPair<QString, int> &undestr)
{
    m_undestrMarker = new CUndestr_Producer(undestr.second, undestr.first);

    connect(m_undestrMarker, SIGNAL(received_new_code(QString &, QString &, uint32_t &)),this, SLOT(procs_new_container(QString &, QString &, uint32_t &)));
}
