#include "weather.h"
#include <QtWidgets>
#include <QtNetwork>

#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>

Weather::Weather(QObject *parent, QString weatherResult) : QObject(parent), m_API_results(weatherResult)
{


}

int Weather::weatherId_cn() const
{
    return m_weatherId_cn;
}

void Weather::setWeatherId_cn(int weatherId_cn)
{
    m_weatherId_cn = weatherId_cn;
}

int Weather::weatherId_us() const
{
    return m_weatherId_us;
}

void Weather::setWeatherId_us(int weatherId_us)
{
    m_weatherId_us = weatherId_us;
}

QString Weather::API_results() const
{
    return m_API_results;
}

void Weather::setAPI_results(const QString &API_results)
{
    m_API_results = API_results;
}

void Weather::ParseWeather()
{

        //The position of the word "weather" for the first City (Xiangyang)
        int flagPosition_weather_CN= m_API_results.indexOf("weather");

        //The position of the word "weather" for the second City (West Lafayette)
        int flagPosition_weather_US =m_API_results.indexOf("weather", flagPosition_weather_CN+1);

        ////The position of the \" after the weather. This means the end of the weather====CN
        int flagPosition_idOfWeather_CN= m_API_results.indexOf("id", flagPosition_weather_CN);

        ////The position of the \" after the weather. This means the end of the weather====US
        int flagPosition_idOfWeather_US= m_API_results.indexOf("id", flagPosition_weather_US);

        ////assert that id is a 3 digit number ====CN
        int flagPosition_begin_CN = flagPosition_idOfWeather_CN +4;

        ////assert that id is a 3 digit number ===US
        int flagPosition_begin_US = flagPosition_idOfWeather_US +4;
        int idLength = 3;


       QStringRef weather_IdRef_CN(&m_API_results,flagPosition_begin_CN , idLength);
       QString weather_id_str_CN = weather_IdRef_CN.toString();

       m_weatherId_cn = weather_id_str_CN.toInt();


       QStringRef weather_IdRef_US(&m_API_results,flagPosition_begin_US , idLength);
       QString weather_id_str_US = weather_IdRef_US.toString();

       m_weatherId_us = weather_id_str_US.toInt();

}

void Weather::ParseTemperature()
{

    //The position of the word "temp" for the first City (Xiangyang)
    int flagPosition_temperature_CN= m_API_results.indexOf("\"temp\"");

    //// Example: "temp":26.99,"pressure":1004.47 ==== we need to increase the index for 6 to get 26.99
    int step = 7;
    int temp_start_cn = flagPosition_temperature_CN+step;



    //The position of the word "temp" for the second City (West Lafayette)
    int flagPosition_temperature_US =m_API_results.indexOf("\"temp\"", flagPosition_temperature_CN +1);
    int temp_start_us = flagPosition_temperature_US+step;

    ////The position of the \, after the temperature. This means the end of the weather====CN
    int flagPosition_end_CN= m_API_results.indexOf(",", flagPosition_temperature_CN);

    ////The position of the \, after the temperature. This means the end of the weather====US
    int flagPosition_end_US= m_API_results.indexOf(",", flagPosition_temperature_US);

    ////length of the temperature ===CN
    int length_cn = flagPosition_end_CN - temp_start_cn;

    ////length of the temperature ===US
    int length_us = flagPosition_end_US - temp_start_us;



   QStringRef weather_IdRef_CN(&m_API_results,temp_start_cn , length_cn);
   QString weather_id_str_CN = weather_IdRef_CN.toString();
   m_temperature_cn = weather_id_str_CN;




   QStringRef weather_IdRef_US(&m_API_results,temp_start_us , length_us);
   QString weather_id_str_US = weather_IdRef_US.toString();
   m_temperature_us = weather_id_str_US;


}

QString Weather::MatchWeatheIdToIconId(const int weatherID)
{

    if(weatherID<300)
    {
        return "11d";
    }
    else if (300<=weatherID & weatherID<400) {
        return "09d";
    }
    else if (500<=weatherID & weatherID<600) {
        return "10d";
    }
    else if (600<=weatherID & weatherID<700) {
        return "13d";
    }
    else if (700<=weatherID & weatherID<800) {
        return "50d";
    }
    else if (800==weatherID) {
        return "01d" ;
    }
    else if (801==weatherID) {
        return "02d";
    }
    else if (802==weatherID) {
        return "03d";
    }
    else if (803<=weatherID & weatherID<=804) {
        return "04d";
    }
    else {
        return "others";
    }
}

QString Weather::iconId_cn() const
{
    return m_iconId_cn;
}

void Weather::setIconId_cn(const QString &iconId_cn)
{
    m_iconId_cn = iconId_cn;
}

QString Weather::iconId_us() const
{
    return m_iconId_us;
}

void Weather::setIconId_us(const QString &iconId_us)
{
    m_iconId_us = iconId_us;
}

QString Weather::temperature_cn() const
{
    return m_temperature_cn;
}

void Weather::setTemperature_cn(const QString &temperature_cn)
{
    m_temperature_cn = temperature_cn;
}

QString Weather::temperature_us() const
{
    return m_temperature_us;
}

void Weather::setTemperature_us(const QString &temperature_us)
{
    m_temperature_us = temperature_us;
}



