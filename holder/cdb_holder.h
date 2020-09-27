#ifndef CDB_HOLDER_H
#define CDB_HOLDER_H

#include <QObject>

// load  devs from database
// load  containers from database

class CDB_Holder: public QObject{
    Q_OBJECT

public:
    CDB_Holder(){}
    virtual ~CDB_Holder(){}

    bool is_connected(){return bConnected;}

    virtual bool db_connect() = 0;
    virtual bool db_diconnect() = 0;

    //    
    virtual QPair<QString, int>        get_main_dev() = 0;
    virtual QList<QPair<QString, int>> get_devs() = 0;
    virtual QList<QPair<QString, int>> get_containers() = 0;


    // "container" transport methods
    virtual bool unregister_container(QString &strRFIDCode) = 0;  // then come to out we need to free it
    virtual bool register_container(QString &strNonDestrCode, QString &strRFIDCode) = 0 ; // connect nondestruct code with rfid
    virtual bool append_moving(uint32_t const &iDevID, QString const &strContainerRFIDCode) = 0; // some device tell us - we crossed some area

    virtual bool add_container(QString &strNonDestrCode, int &id) = 0; // if no nondestrcode for container - ask to add


signals:
    void error_connect(QString &str);

    void no_such_dev(QString &strDevName);
    void no_such_container(QString &strCode); // inform higher level

protected:
    bool bConnected;    
};

#endif // CDB_HOLDER_H
