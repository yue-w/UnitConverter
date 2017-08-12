#include "checkweather.h"
#include <QtWidgets>
#include <QtNetwork>

#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>

CheckWeather::CheckWeather(QWidget *parent) : QMainWindow(parent)
{

    m_url_Xiangyang = "http://www.google.com";
}

void CheckWeather::Start()
{
    ////This is the entrance
    QString urlSpec = getUrl_Xiangyang();
    if (urlSpec.isEmpty())
        return;

    const QUrl newUrl = QUrl::fromUserInput(urlSpec);
    if (!newUrl.isValid()) {
//        QMessageBox::information(this, tr("Error"),
//                                 tr("Invalid URL: %1: %2").arg(urlSpec, newUrl.errorString()));
        return;
    }

    // schedule the request
    startRequest(newUrl);
}

void CheckWeather::startRequest(const QUrl &requestedUrl)
{
    url = requestedUrl;
    httpRequestAborted = false;
    reply = qnam.get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::finished, this, &CheckWeather::httpFinished);
    connect(reply, &QIODevice::readyRead, this, &CheckWeather::httpReadyRead);


}

QString CheckWeather::getUrl_Xiangyang() const
{
    return m_url_Xiangyang;
}

void CheckWeather::setUrl_Xiangyang(const QString &value)
{
    m_url_Xiangyang = value;
}

void CheckWeather::httpFinished()
{
    if (httpRequestAborted) {
        reply->deleteLater();
        reply = Q_NULLPTR;
        return;
    }

    if (reply->error()) {
        reply = Q_NULLPTR;
        return;
    }

    const QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    reply->deleteLater();
    reply = Q_NULLPTR;
    if (!redirectionTarget.isNull()) {
        const QUrl redirectedUrl = url.resolved(redirectionTarget.toUrl());
//        if (QMessageBox::question(this, tr("Redirect"),
//                                  tr("Redirect to %1 ?").arg(redirectedUrl.toString()),
//                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {

//            return;
//        }

        startRequest(redirectedUrl);
        return;
    }
}

void CheckWeather::httpReadyRead()
{
    QByteArray allContent = reply->readAll();

    writeFile(allContent);
}

void CheckWeather::writeFile(QByteArray array)
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
