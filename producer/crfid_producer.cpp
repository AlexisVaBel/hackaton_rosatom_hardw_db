#include "crfid_producer.h"


#include <QThread>
#include <iostream>

CRFID_Producer::CRFID_Producer(uint16_t icode, QString strPlace):CCODEs_Producer(icode, strPlace),strCurCode(""),strPrevCode("")
{
}

CRFID_Producer::~CRFID_Producer()
{

}

QString CRFID_Producer::getNewCode()
{
    return strCurCode;
}

void CRFID_Producer::process()
{
    QString strQry = "01 03 01 00 00 0A A8";
    QString strAns = "";

    send_query(strQry);
    strPrevCode = strCurCode;
    QThread::usleep(20);
    receive_query(strAns);

    if(!strAns.isEmpty() && strAns.compare(strPrevCode) != 0) {
        noAnswer = 0;
        strCurCode = strAns;
        emit received_new_code(strCurCode, m_strPlace, m_devCode);
    }else{
        ++noAnswer;
    }

    if(noAnswer > 10){ // magic 10 need to replace
        emit err_connection(m_strPlace);
    }


}

void CRFID_Producer::send_query(QString &str)
{
//    std::cout << m_strPlace.toStdString() << __PRETTY_FUNCTION__ << " sending packet "<< std::endl;
}

void CRFID_Producer::receive_query(QString &str)
{
//    std::cout << m_strPlace.toStdString() << __PRETTY_FUNCTION__ << "receiving packet "<< std::endl;
    qint64 value = qrand();

    str = QString::number(value);
}
