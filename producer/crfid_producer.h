#ifndef CRFID_PRODUCER_H
#define CRFID_PRODUCER_H

#include "ccodes_producer.h"



class CRFID_Producer:public CCODEs_Producer
{
public:
    CRFID_Producer(uint16_t icode, QString strPlace);
    ~CRFID_Producer();

    // CCODEs_Producer interface
public slots:
    void process(); // for future uses

public:
    QString getNewCode();


private:
    void send_query(QString &str);
    void receive_query(QString &str);

    QString strCurCode;
    QString strPrevCode;

    int noAnswer;
};

#endif // CRFID_PRODUCER_H
