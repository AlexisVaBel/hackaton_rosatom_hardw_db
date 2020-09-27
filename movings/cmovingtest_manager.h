#ifndef CMOVINGTEST_MANAGER_H
#define CMOVINGTEST_MANAGER_H

#include <QObject>

#include <producer/ccodes_producer.h>
#include <producer/cundestr_producer.h>

#include <holder/cdb_holder.h>

class CMovingTest_Manager : public QObject
{
    Q_OBJECT
public:
    explicit CMovingTest_Manager(QObject *parent = nullptr);

    void test_income_register_set_rfid();
    void test_income_register_set_rfid_notenough();
    void test_income_register_move_in_order();
    void test_income_register_move_in_disorder();

signals:

public slots:

    void procs_new_rfid_income(QString &strCode, QString &strDev, uint32_t &idDev);

    void procs_new_container(QString &strCode, QString &strDev, uint32_t &idDev);

private:

    CDB_Holder             *m_db;

    void unpack_rfids(QList<QPair<QString, int> > &rfids, QList<CCODEs_Producer*> *lstRFID);
    CUndestr_Producer *unpack_undestr(QPair<QString, int> &undestr);

};

#endif // CMOVINGTEST_MANAGER_H
