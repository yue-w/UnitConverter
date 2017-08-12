#include "mainwindow.h"
#include <QApplication>

//#include <QDeclarativeView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("单位转换器");
    w.show();

    return a.exec();



//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    QDeclarativeView *qmlView = new QDeclarativeView;
//    qmlView->setSource(QUrl::fromLocalFile("myqml.qml"));

//    QWidget *widget = myExistingWidget();
//    QVBoxLayout *layout = new QVBoxLayout(widget);
//    layout->addWidget(qmlView);

//    return a.exec();
}
