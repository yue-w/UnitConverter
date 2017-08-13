#include "currency.h"

Currency::Currency(QObject *parent, QString weatherResult) : QObject(parent), m_API_results(weatherResult)
{

}

QString Currency::API_results() const
{
    return m_API_results;
}

void Currency::setAPI_results(const QString &API_results)
{
    m_API_results = API_results;
}

double Currency::currency() const
{
    return m_currency;
}

void Currency::setCurrency(double currency)
{
    m_currency = currency;
}

void Currency::ParseCurrency(QString aTob)
{
    //The position of the word "weather" for the first City (Xiangyang)
    QString test = m_API_results;
    int flagPosition= m_API_results.indexOf(aTob);
    int stepForward = 8;
    int endFlag = m_API_results.indexOf(",", flagPosition+1);
    int startFlag = flagPosition + stepForward;

    int idLength = endFlag - startFlag;
    QStringRef currency_ref(&m_API_results,startFlag , idLength);

    QString currency = currency_ref.toString();

    int dotIndex = currency.indexOf(".");
    int precision = 4;
    dotIndex = dotIndex + precision;
    currency.truncate(dotIndex);

    m_currency = currency.toDouble();

}
