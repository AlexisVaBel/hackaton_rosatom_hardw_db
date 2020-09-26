#ifndef CCODES_PRODUCER_H
#define CCODES_PRODUCER_H

#include <QObject>


class CCODEs_Producer: public QObject{
    Q_OBJECT

public:
    CCODEs_Producer(uint16_t icode, QString strPlace):bNewCode(false),bFinished(false), m_codeCnt(0),
        m_devCode(icode), m_strPlace(strPlace){}
    virtual ~CCODEs_Producer(){}

    bool new_code_avl(){return bNewCode;}
    bool is_finished(){return  bFinished;}
    uint32_t get_code_cnt(){return m_codeCnt;}
    uint16_t get_dev_code(){return m_devCode;}
    QString  get_place(){return m_strPlace;}



    virtual QString getNewCode() = 0;

public slots:
    virtual void process() = 0;

signals:
    void received_new_code(QString &strCode, QString &strDev, uint32_t &idDev);
    void err_connection(QString &strDev);      // some physical troubles


protected:

    bool bNewCode;
    bool bFinished;


    uint32_t m_codeCnt;
    uint32_t m_devCode;
    QString  m_strPlace;
};


#endif // CCODES_PRODUCER_H
