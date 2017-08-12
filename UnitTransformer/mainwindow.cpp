#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtMath>
#include <QDebug>
#include <QDateTime>
#include <QTimeZone>
#include "weather.h"
#include "checkweather.h"

#include <QtWidgets>
#include <QtNetwork>
#include <QFile>
#include <QString>
#include <QStringRef>
#include <QDebug>
#include <QTextStream>
#include <QPixmap>

#define DOUBLE_PRECISION 0.0000001

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_value_us = 14624.8669;
    m_value_cn = 3215.4989;

    m_rmbToUSD_ratio = 6.77;
    ui->setupUi(this);

    ////Time
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    m_timer->start(1000);

    ////Weather
     //Weather* weather = checkWeather();
    checkWeather();
    //CheckWeather weather;
    //weather.Start();





    ///Temperature CN to US
    connect(ui->lineEdit_temperature_CN, SIGNAL(textEdited()), this, SLOT(on_lineEdit_temperature_CN_textChanged()));

    ///Temperature US to CN
    connect(ui->lineEdit_temperature_US, SIGNAL(textEdited()), this, SLOT(on_lineEdit_temperature_US_textChanged()));

    ////Currency CN to US
    connect(ui->lineEdit_currency_CN, SIGNAL(textEdited()),this, SLOT(on_lineEdit_currency_CN_textChanged()));

    ////Length CN to US
    connect(ui->lineEdit_length_CN, SIGNAL(textEdited()), this, SLOT(on_lineEdit_length_CN_textChanged()));
    connect(ui->comboBox_length_CN, SIGNAL(currentIndexChanged()), this, SLOT(on_comboBox_length_CN_currentIndexChanged()));


    ////Length US　to CN
    connect(ui->lineEdit_length_US, SIGNAL(textEdited()), this, SLOT(on_lineEdit_length_US_textChanged()));
    connect(ui->comboBox_length_US, SIGNAL(currentIndexChanged()),this, SLOT(on_comboBox_length_US_currentIndexChanged()));

    ////Weight CN to US
    connect(ui->lineEdit_weight_CN, SIGNAL(textEdited()), this, SLOT(on_lineEdit_weight_CN_textChanged()));
    connect(ui->comboBox_weight_CN, SIGNAL(currentIndexChanged()), this, SLOT(on_comboBox_weight_CN_currentIndexChanged()));

    ////Weight US to CN
    connect(ui->lineEdit_weight_US, SIGNAL(textEdited()), this, SLOT(on_lineEdit_weight_US_textChanged()));
    connect(ui->comboBox_weight_US, SIGNAL(currentIndexChanged()), this, SLOT(on_comboBox_weight_US_currentIndexChanged()));

}

void MainWindow::checkWeather()
{
//    Weather weather;
//    weather.Start();
 //   Weather* weather = new Weather();

    ////This is the entrance
    //const QString urlSpec = "http://api.openweathermap.org/data/2.5/weather?q=Xiangyang,cn&APPID=87019607e752cb275e0f6bf825202a85";
    const QString urlSpec = "http://api.openweathermap.org/data/2.5/group?id=1790587,4928096&units=metric&appid=87019607e752cb275e0f6bf825202a85";
    // const QString urlSpec = "http://www.google.com";
    if (urlSpec.isEmpty())
        return ;

    const QUrl newUrl = QUrl::fromUserInput(urlSpec);
    if (!newUrl.isValid()) {
        QMessageBox::information(this, tr("Error"),
                                 tr("Invalid URL: %1: %2").arg(urlSpec, newUrl.errorString()));
        return ;
    }

    // schedule the request
    startRequest(newUrl);

    //QString a = weather();
   // return weather();




}

void MainWindow::startRequest(const QUrl &requestedUrl)
{
     url = requestedUrl;
     httpRequestAborted = false;
     reply = qnam.get(QNetworkRequest(url));


     connect(reply, &QNetworkReply::finished, this, &MainWindow::httpFinished);
     connect(reply, &QIODevice::readyRead, this, &MainWindow::httpReadyRead);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_lineEdit_temperature_CN_textChanged(const QString &temperature_CN)
{

    bool  validate = true;
    double lableNumber_CN = temperature_CN.toDouble(&validate);
    m_temperature_CN = lableNumber_CN;
    double lableNumber_US = 0;
    QString labelString_US = "";

    ////if the input is number
    if(validate)
    {
        lableNumber_US = (lableNumber_CN + 40) * 1.8 -40;

        labelString_US = QString::number(lableNumber_US,'g',15);

        //// prevent infinite looping in the case of cyclic connections
        if( qFabs(lableNumber_US-m_temperature_US)>DOUBLE_PRECISION)
        {
            ui->lineEdit_temperature_US->setText(labelString_US);
        }
        // ui->lineEdit_temperature_US->setText(labelString_US);


    }
    else {
         qDebug()<<"it is not number";

    }



}

void MainWindow::on_lineEdit_temperature_US_textChanged(const QString &temperature_US)
{

    bool  validate = true;
    double lableNumber_US = temperature_US.toDouble(&validate);
    m_temperature_US = lableNumber_US;

    double lableNumber_CN = 0;
    QString labelString_CN = "";

    ////if the input is number
    if(validate)
    {
        lableNumber_CN = (lableNumber_US + 40) / 1.8 -40;

        labelString_CN = QString::number(lableNumber_CN,'g',15);

        //// prevent infinite looping in the case of cyclic connections
        if(qFabs(lableNumber_CN-m_temperature_CN)>DOUBLE_PRECISION )
        {
            ui->lineEdit_temperature_CN->setText(labelString_CN);
        }
       // ui->lineEdit_temperature_CN->setText(labelString_CN);

    }
    else {
         qDebug()<<"it is not number";

    }

}

void MainWindow::on_lineEdit_currency_CN_textChanged(const QString &currency_CN)
{
    //double rmbToUSD = 6.77;
    bool  validate = true;
    double lableNumber_CN = currency_CN.toDouble(&validate);
    m_currency_CN = lableNumber_CN;
    double lableNumber_US = 0;
    QString labelString_US = "";

    ////if the input is number
    if(validate)
    {
        lableNumber_US = lableNumber_CN/m_rmbToUSD_ratio;

        labelString_US = QString::number(lableNumber_US,'g',15);

        //// prevent infinite looping in the case of cyclic connections
        if( qFabs(lableNumber_US-m_currency_US)>DOUBLE_PRECISION)
        {
            ui->lineEdit_currency_US->setText(labelString_US);
        }
        // ui->lineEdit_temperature_US->setText(labelString_US);


    }
    else {
         qDebug()<<"it is not number";

    }
}

void MainWindow::on_lineEdit_currency_US_textChanged(const QString &currency_US)
{

    bool  validate = true;
    double lableNumber_US = currency_US.toDouble(&validate);
    m_currency_US = lableNumber_US;

    double lableNumber_CN = 0;
    QString labelString_CN = "";

    ////if the input is number
    if(validate)
    {
        lableNumber_CN = lableNumber_US * m_rmbToUSD_ratio;

        labelString_CN = QString::number(lableNumber_CN,'g',15);

        //// prevent infinite looping in the case of cyclic connections
        if(qFabs(lableNumber_CN-m_currency_CN)>DOUBLE_PRECISION )
        {
            ui->lineEdit_currency_CN->setText(labelString_CN);
        }
       // ui->lineEdit_temperature_CN->setText(labelString_CN);

    }
    else {
         qDebug()<<"it is not number";

    }

}

void MainWindow::on_lineEdit_length_CN_textChanged(const QString & length_CN)
{
   int index_CN = ui->comboBox_length_CN->currentIndex();
   int index_US = ui->comboBox_length_US->currentIndex();


   double outV = lenUnitMatch(length_CN,index_CN,index_US, true);
   QString outStr = QString::number(outV,'g',15);

   //// prevent infinite looping in the case of cyclic connections
   if( qFabs(outV-m_value_us)>DOUBLE_PRECISION)
   {
       ui->lineEdit_length_US->setText(outStr);
   }



}

void MainWindow::on_lineEdit_length_US_textChanged(const QString &length_US)
{

    int index_CN = ui->comboBox_length_CN->currentIndex();
    int index_US = ui->comboBox_length_US->currentIndex();


    double outV = lenUnitMatch(length_US,index_CN,index_US, false);
    QString outStr = QString::number(outV,'g',15);

    //// prevent infinite looping in the case of cyclic connections
    if( qFabs(outV-m_value_cn)>DOUBLE_PRECISION)
    {
        ui->lineEdit_length_CN->setText(outStr);
    }

}

double MainWindow::lenUnitMatch( const QString inputValue, int cn_Unit, int us_Unit, bool CNToUS)
{

    QString outPutValue;
    if(0==cn_Unit)////Km
    {
        if(0==us_Unit)////Km to Mile
        {
            //func(const QString cn_in, const QString us_in, QString cn_out, QString& us_out, double& ratio);

            double ratio = 0.621371;
            CNToUSOrUSToCN( ratio,  CNToUS,   inputValue,  outPutValue);
        }
        else if (1==us_Unit) {////Km to foot
            double ratio = 3280.84;
            CNToUSOrUSToCN( ratio,  CNToUS,   inputValue,  outPutValue);

        }
        else if (2==us_Unit) {////Km to inch
            double ratio = 39370.1;
            CNToUSOrUSToCN( ratio,  CNToUS,   inputValue,  outPutValue);
        }
    }
    else if (1==cn_Unit)////m
    {

        if(0==us_Unit)////m to Mile
        {
            double ratio = 0.000621371;
            CNToUSOrUSToCN( ratio,  CNToUS,   inputValue,  outPutValue);
        }
        else if (1==us_Unit) {////m to foot
            double ratio = 3.28084;
            CNToUSOrUSToCN( ratio,  CNToUS,   inputValue,  outPutValue);
        }
        else if (2==us_Unit) {
            double ratio =39.3701;
            CNToUSOrUSToCN( ratio,  CNToUS,   inputValue,  outPutValue);
        }
    }
    else if (2==cn_Unit)////cm
    {

        if(0==us_Unit)////cm to Mile
        {
            //func(const QString cn_in, const QString us_in, QString cn_out, QString& us_out, double& ratio);

            double ratio =6.2137e-6;
            CNToUSOrUSToCN( ratio,  CNToUS,   inputValue,  outPutValue);
        }
        else if (1==us_Unit) {////cm to foot
            double ratio = 0.032808335990814;
            CNToUSOrUSToCN( ratio,  CNToUS,   inputValue,  outPutValue);

        }
        else if (2==us_Unit) {////cm to inch
            double ratio = 0.393701;
            CNToUSOrUSToCN( ratio,  CNToUS,   inputValue,  outPutValue);
        }

    }
    else if(3==cn_Unit)////mm
    {

        if(0==us_Unit)////mm to Mile
        {
            //func(const QString cn_in, const QString us_in, QString cn_out, QString& us_out, double& ratio);

            double ratio =6.2137e-7;
            CNToUSOrUSToCN( ratio,  CNToUS,   inputValue,  outPutValue);
        }
        else if (1==us_Unit) {////mm to foot
            double ratio = 0.00328084;
            CNToUSOrUSToCN( ratio,  CNToUS,   inputValue,  outPutValue);

        }
        else if (2==us_Unit) {////mm to inch
            double ratio = 0.0393701;
            CNToUSOrUSToCN( ratio,  CNToUS,   inputValue,  outPutValue);
        }


    }
    else
    {
        ////
    }





    return outPutValue.toDouble();
}
double MainWindow::weightUnitMatch(const QString inputValue, int cn_Unit, int us_Unit, bool CNToUS)
{
    QString outPutValue;
    if(0==cn_Unit)////Kg
    {
        if(0==us_Unit)////Kg to lb
        {
            //func(const QString cn_in, const QString us_in, QString cn_out, QString& us_out, double& ratio);

            double ratio = 2.20462;
            CNToUSOrUSToCN( ratio,  CNToUS,   inputValue,  outPutValue);
        }
        else
        {

        }

    }
    else if (1==cn_Unit)////Jin
    {

        if(0==us_Unit)////Kg to lb
        {
            //func(const QString cn_in, const QString us_in, QString cn_out, QString& us_out, double& ratio);

            double ratio = 1.10231;
            CNToUSOrUSToCN( ratio,  CNToUS,   inputValue,  outPutValue);
        }
        else
        {

        }
    }

    return outPutValue.toDouble();
}
void MainWindow::CNToUSOrUSToCN(double ratio, bool CNToUS, const QString inputValue, QString& outPutValue)
{
    if(!CNToUS)
    {
        ratio = 1/ratio;
        execuChange(inputValue,outPutValue,ratio);
        m_value_us = inputValue.toDouble();
    }
    else {
        execuChange(inputValue,outPutValue,ratio);
        m_value_cn = inputValue.toDouble();
    }
}

void MainWindow::execuChange(const QString originV_in, QString& changed_out, const double ratio )
{

    bool  validate = true;
    ////A copy of input
    QString originV = originV_in;
    double lableIn = originV.toDouble(&validate);
    //m_value = lableIn;
    double lableNumber_out = 0;

    ////if the input is number
    if(validate)
    {

        lableNumber_out = lableIn * ratio;
        changed_out = QString::number(lableNumber_out,'g',15);

    }
    else {
         qDebug()<<"it is not number";

    }

}

void MainWindow::writeFile(QByteArray array)
{
    QString filePath = "W:/Programming/Qt/Test_Qt_Qml/TestHttp/test.txt";

    QFile mFile(filePath  );
    if(!mFile.open(QFile::WriteOnly | QFile::Text))
    {

        qDebug()<<"Cannot open the file";
        return;
    }

    QTextStream out(&mFile);
    out<<array;
    mFile.flush();
    mFile.close();
}

QString MainWindow::weather() const
{
    return m_weather;
}

void MainWindow::setWeather(const QString &weather)
{
    m_weather = weather;
}

//void MainWindow::MachWeather(const int id)
//{

//}






void MainWindow::on_comboBox_length_CN_currentIndexChanged(const QString &length_CN)
{

    int index_CN = ui->comboBox_length_CN->currentIndex();
    int index_US = ui->comboBox_length_US->currentIndex();


    double outV = lenUnitMatch(ui->lineEdit_length_CN->text(),index_CN,index_US, true);
    QString outStr = QString::number(outV,'g',15);

    //// prevent infinite looping in the case of cyclic connections
    if( qFabs(outV-m_value_us)>DOUBLE_PRECISION)
    {
        ui->lineEdit_length_US->setText(outStr);
    }

}

void MainWindow::on_comboBox_length_US_currentIndexChanged(const QString &arg1)
{
    int index_CN = ui->comboBox_length_CN->currentIndex();
    int index_US = ui->comboBox_length_US->currentIndex();


    double outV = lenUnitMatch(ui->lineEdit_length_US->text(),index_CN,index_US, true);
    QString outStr = QString::number(outV,'g',15);

    //// prevent infinite looping in the case of cyclic connections
    if( qFabs(outV-m_value_us)>DOUBLE_PRECISION)
    {
        ui->lineEdit_length_US->setText(outStr);
    }
}

void MainWindow::on_lineEdit_weight_CN_textChanged(const QString &weight_CN)
{
    int index_CN = ui->comboBox_weight_CN->currentIndex();
    int index_US = ui->comboBox_weight_US->currentIndex();

    double outV = weightUnitMatch(weight_CN,index_CN,index_US, true);
    QString outStr = QString::number(outV,'g',15);

    //// prevent infinite looping in the case of cyclic connections
    if( qFabs(outV-m_value_us)>DOUBLE_PRECISION)
    {
        ui->lineEdit_weight_US->setText(outStr);
    }
}

void MainWindow::on_comboBox_weight_CN_currentIndexChanged(const QString &weight_CN)
{

    int index_CN = ui->comboBox_weight_CN->currentIndex();
    int index_US = ui->comboBox_weight_US->currentIndex();


    double outV = weightUnitMatch(ui->lineEdit_weight_CN->text(),index_CN,index_US, true);
    QString outStr = QString::number(outV,'g',15);

    //// prevent infinite looping in the case of cyclic connections
    if( qFabs(outV-m_value_us)>DOUBLE_PRECISION)
    {
        ui->lineEdit_weight_US->setText(outStr);
    }
}

void MainWindow::on_lineEdit_weight_US_textChanged(const QString &weight_US)
{
    int index_CN = ui->comboBox_weight_CN->currentIndex();
    int index_US = ui->comboBox_weight_US->currentIndex();


    double outV = weightUnitMatch(weight_US,index_CN,index_US, false);
    QString outStr = QString::number(outV,'g',15);

    //// prevent infinite looping in the case of cyclic connections
    if( qFabs(outV-m_value_cn)>DOUBLE_PRECISION)
    {
        ui->lineEdit_weight_CN->setText(outStr);
    }
}

void MainWindow::on_comboBox_weight_US_currentIndexChanged(const QString &weight_US)
{
    int index_CN = ui->comboBox_weight_CN->currentIndex();
    int index_US = ui->comboBox_weight_US->currentIndex();


    double outV = weightUnitMatch(ui->lineEdit_weight_US->text(),index_CN,index_US, true);
    QString outStr = QString::number(outV,'g',15);

    //// prevent infinite looping in the case of cyclic connections
    if( qFabs(outV-m_value_us)>DOUBLE_PRECISION)
    {
        ui->lineEdit_weight_CN->setText(outStr);
    }

}

void MainWindow::timeUpdate()
{

    //qDebug()<<"update";
//    QTime time = QTime::currentTime();
//    QString time_text = time.toString("hh : mm ::  ss");
//    ui->label_date_time->setText(time_text);




     QDateTime time = QDateTime::currentDateTime();
     QDateTime time_UTC = time.toUTC();     
     QDateTime time_CN = time_UTC.toOffsetFromUtc(8*3600);
     QString time_text_CN = time_CN.toString("hh : mm ::  ss");
     ui->label_date_time_CN->setText(time_text_CN);


//     QDateTime time_US =  time_UTC.toOffsetFromUtc(-4*3600);;



//     QDateTime currentTime = QDateTime::currentDateTime();
//     QDateTime currentTimeUTC = currentTime.toUTC();
//     //int offset = (currentTime-currentTimeUTC)/3600;
//     QString currentTimeS = currentTime.toString("hh : mm ::  ss");
//     QString currentTimeUTCS = currentTimeUTC.toString("hh : mm ::  ss");

      QByteArray qbyte = "America/Indianapolis";
      QTimeZone timeZone_US = QTimeZone(qbyte);

     // ui->label_date_time_US->setText(timeZone_US.time());

      //bool hasDaylightTime = timeZone_US.hasDaylightTime();
      //bool isDaylightTime = timeZone_US.isDaylightTime(QDateTime::currentDateTime());
      //QDateTime timeUS = QDateTime(QDate::currentDate(), QTime::currentTime(), timeZone_US).toLocalTime();


     QDateTime zoneTime = QDateTime(QDate::currentDate(), QTime::currentTime(), timeZone_US).toLocalTime();
     QString time_text_US = zoneTime.time().toString("hh : mm ::  ss");
     ui->label_date_time_US->setText(time_text_US);


}

void MainWindow::httpFinished()
{

}

void MainWindow::httpReadyRead()
{
    QByteArray allContent = reply->readAll();
    //const QString valueFromOpenWeather = QString(allContent);

    m_weather = QString(allContent);

    QString API_Result = weather();

    Weather* weather = new Weather(this, API_Result);

    ////Parse the result from openweathermap.org
    weather->ParseWeather();
    weather->ParseTemperature();

    QString iconId_cn = weather->MatchWeatheIdToIconId(weather->weatherId_cn());
    QString iconId_us = weather->MatchWeatheIdToIconId(weather->weatherId_us());

    QString folderPath = "W:/Programming/Qt/UnitTransformer/Fig/";
    QString fileNameExtension = ".png";

    QString iconPath_cn = folderPath + iconId_cn + fileNameExtension;
    QString iconPath_us = folderPath + iconId_us + fileNameExtension;

    QPixmap pixCN(iconPath_cn);
    ui->label_weather_cn->setPixmap(pixCN);

    QPixmap pixUS(iconPath_us);
    ui->label_weather_us->setPixmap(pixUS);


    QString temp_cn = weather->temperature_cn();
    temp_cn += " °C";
    QString temp_us = weather->temperature_us();
    temp_us += " °C";
    ui->label_temp_cn->setText(temp_cn);
    ui->label_temp_us->setText(temp_us);


//   writeFile(allContent);

}

