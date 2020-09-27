#ifndef CDB_DUMMY_H
#define CDB_DUMMY_H

#include "cdb_holder.h"

#include <QMap>



class CDB_Dummy : public CDB_Holder
{
    Q_OBJECT
public:
    CDB_Dummy();
    ~CDB_Dummy();

    // CDB_Holder interface
public:
    bool db_connect();
    bool db_diconnect();

    QPair<QString, int> get_main_dev();
    QList<QPair<QString, int>> get_devs();
    QList<QPair<QString, int>> get_containers();
    bool unregister_container(QString &strRFIDCode);
    bool register_container(QString &strNonDestrCode, QString &strRFIDCode);
    bool append_moving(uint32_t &iDevID, QString &strContainerRFIDCode);
    bool add_container(QString &strNonDestrCode, int &id);

private:
    QMap<QString, int> mapContainers;
    QMap<QString, QString> mapRFIDContainers;


    // data for tests
    static const int RFID_CNT = 3;
    static const int NONDESTR_CNT = 1;


    static const char * RFID_REGISTER;
    static const char * RFID_PLACE_1;
    static const char * RFID_PLACE_2;
    static const char * RFID_PLACE_3;

    static const char * NONDESTRUCT;



    // CDB_Holder interface

};

#endif // CDB_DUMMY_H
