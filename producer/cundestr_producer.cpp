#include "cundestr_producer.h"


CUndestr_Producer::CUndestr_Producer(uint16_t icode, QString strPlace):CCODEs_Producer(icode, strPlace),strCurCode(""),strPrevCode("")
{
    iPos    = 0;
    iDelay  = 0;

    for(auto i = 0; i < 10; ++i)
        m_lstTestCodes.push_back(QString(i+30));
}

CUndestr_Producer::~CUndestr_Producer()
{

}

void CUndestr_Producer::process()
{
    QString str = "";
    if(iDelay > 10 ){
        iDelay = 0;
        receive_query(str);
        if(str.compare(strCurCode) != 0){
            strPrevCode = strCurCode;
            strCurCode = str;
            emit received_new_code(strCurCode, m_strPlace, m_devCode);
        }
    }else ++iDelay;
}

QString CUndestr_Producer::getNewCode()
{
    return  strCurCode;
}

void CUndestr_Producer::receive_query(QString &str)
{
    if(iPos >= m_lstTestCodes.length()) str = m_lstTestCodes.last();
    str = m_lstTestCodes.at(iPos++);
}
