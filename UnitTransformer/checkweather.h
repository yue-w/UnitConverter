#ifndef CHECKWEATHER_H
#define CHECKWEATHER_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QUrl>

class CheckWeather : public QMainWindow
{
    Q_OBJECT
public:
    explicit CheckWeather(QWidget *parent = 0);

    void Start();
    void startRequest(const QUrl &requestedUrl);

    QString getUrl_Xiangyang() const;
    void setUrl_Xiangyang(const QString &value);



signals:
    void testSignal();

private slots:
    void httpFinished();
    void httpReadyRead();

private:
    void writeFile(QByteArray array);


private:
    QString m_url_Xiangyang;

    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    bool httpRequestAborted;
};

#endif // CHECKWEATHER_H
