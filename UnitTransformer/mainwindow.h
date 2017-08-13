#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <QNetworkAccessManager>
#include <QUrl>

namespace Ui {
class MainWindow;
}
class Weather;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //Weather* checkWeather();
    void  checkWeather();

    void CheckCurrency();

    void startRequest_Weather(const QUrl &requestedUrl);

    void StartRequest_Currency(const QUrl &requestedUrl);

    QString weather() const;
    void setWeather(const QString &weather);

private slots:
    void on_lineEdit_temperature_CN_textChanged(const QString &temperature_CN);

    void on_lineEdit_temperature_US_textChanged(const QString &temperature_US);

    void on_lineEdit_currency_CN_textChanged(const QString &currency_CN);

    void on_lineEdit_currency_US_textChanged(const QString &currency_US);

    void on_lineEdit_length_CN_textChanged(const QString &length_CN);
    void on_lineEdit_length_US_textChanged(const QString &length_US);


    void on_comboBox_length_CN_currentIndexChanged(const QString &arg1);
    void on_comboBox_length_US_currentIndexChanged(const QString &arg1);

    void on_lineEdit_weight_CN_textChanged(const QString& weight_CN);
    void on_comboBox_weight_CN_currentIndexChanged(const QString& weight_CN);

    void on_lineEdit_weight_US_textChanged(const QString& weight_US);
    void on_comboBox_weight_US_currentIndexChanged(const QString& weight_US);
    void timeUpdate();


private slots:
    void httpFinished_weather();
    void httpFinished_currency();
    void httpReadyRead_Weather();
    void httpReadyRead_Currency();


private:
    Ui::MainWindow *ui;

    ////The following four variable will be replaced by m_value in Code refactoring
    double m_temperature_CN;
    double m_temperature_US;
    double m_currency_CN;
    double m_currency_US;

    ////The following value is used to avoid infinite loop
    double m_value_cn;
    double m_value_us;

    double m_rmbToUSD_ratio;

    QTimer* m_timer;

signals:
    //void valueChanged(int newValue);

private:
    double lenUnitMatchlenUnitMatch( const QString inputValue, int cn_Unit, int us_Unit);
    double weightUnitMatch( const QString inputValue, int cn_Unit, int us_Unit, bool CNToUS);
    double MainWindow::lenUnitMatch( const QString inputValue, int cn_Unit, int us_Unit, bool CNToUS);
    void CNToUSOrUSToCN(double ratio, bool CNToUS, const QString inputValue,QString& outPutValue);
    ////changed_out = ratio* originV_in
    void execuChange(const QString originV_in, QString& changed_out, const double ratio );

    void writeFile(QByteArray array);

private:
    QString m_url_Xiangyang;

    QUrl url_weather;
    QUrl url_currency;
    QNetworkAccessManager qnam_weather;
    QNetworkAccessManager qnam_currency;

    QNetworkReply *reply_weather;
     QNetworkReply *reply_currency;

    bool httpRequestAborted;

    QString m_weather;

    //realtime currency from the web
    QString m_RealtimeCurrency_All;

    //Currency between USD and CNY
    int m_RealtimeCurrency_USDCNY;
    //void MachWeather(const int id);

};

#endif // MAINWINDOW_H
