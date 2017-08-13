#ifndef CURRENCY_H
#define CURRENCY_H

#include <QObject>

class Currency : public QObject
{
    Q_OBJECT
public:
    explicit Currency(QObject *parent = 0, QString CurrencyResult = " ");

    QString API_results() const;
    void setAPI_results(const QString &API_results);


    double currency() const;
    void setCurrency(double currency);

    void ParseCurrency(QString aTob);
signals:

public slots:

private:
    QString  m_API_results;

    double  m_currency;
};

#endif // CURRENCY_H
