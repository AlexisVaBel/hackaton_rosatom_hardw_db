#ifndef CUNDESTR_PRODUCER_H
#define CUNDESTR_PRODUCER_H

#include "ccodes_producer.h"


class CUndestr_Producer:public CCODEs_Producer
{
public:
    CUndestr_Producer(uint16_t icode, QString strPlace);
    ~CUndestr_Producer();

public slots:
    void process(); // for future uses

public:
    QString getNewCode();


private:
    void receive_query(QString &str);

    QString strCurCode;
    QString strPrevCode;

    QList<QString> m_lstTestCodes;

    int iPos;
    int iDelay;
    int noAnswer;
};

#endif // CUNDESTR_PRODUCER_H
