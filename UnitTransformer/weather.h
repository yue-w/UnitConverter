#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>

class Weather :public QObject
{
    Q_OBJECT
public:
    explicit Weather(QObject *parent = 0, QString weatherResult = " ");




    int weatherId_cn() const;
    void setWeatherId_cn(int weatherId_cn);

    int weatherId_us() const;
    void setWeatherId_us(int weatherId_us);

    QString API_results() const;
    void setAPI_results(const QString &API_results);

    void ParseWeather();
    void ParseTemperature();

    QString MatchWeatheIdToIconId(const int weatherID);

    QString iconId_cn() const;
    void setIconId_cn(const QString &iconId_cn);

    QString iconId_us() const;
    void setIconId_us(const QString &iconId_us);

    QString temperature_cn() const;
    void setTemperature_cn(const QString &temperature_cn);

    QString temperature_us() const;
    void setTemperature_us(const QString &temperature_us);

signals:


private slots:


private:




private:

    ////Weather result from Openweathermap.org
    QString m_API_results;

    int m_weatherId_cn;
    int m_weatherId_us;

    QString m_iconId_cn;
    QString m_iconId_us;

    QString m_temperature_cn;
    QString m_temperature_us;



};

#endif // WEATHER_H
