#ifndef CMOVINGMANAGER_H
#define CMOVINGMANAGER_H

#include <QObject>

#include "holder/cdb_dummy.h"
#include "producer/crfid_producer.h"

class CMovingManager: QObject
{
    Q_OBJECT
public:
    CMovingManager();
    ~CMovingManager();


    void process();

public slots:

    void finish_work();


    void procs_new_rfid_income(QString &strCode, QString &strDev, uint32_t &idDev);

    void procs_new_container(QString &strCode, QString &strDev, uint32_t &idDev);


private:


    CDB_Holder             *m_db;
    QList<CCODEs_Producer*> m_lstRFID;
    CCODEs_Producer        *m_undestrMarker;


    bool m_bWork;

    void prepare();
    void finish_it();

    void unpack_rfids(QList<QPair<QString, int> > &rfids);
    void unpack_undestr(QPair<QString, int> &undestr);
};

#endif // CMOVINGMANAGER_H
