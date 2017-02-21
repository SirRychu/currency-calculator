#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>


#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QtNetwork/QNetworkReply>
#include <QUrl>

#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QLineEdit *wartoscPLN;
    QLineEdit *wartoscWaluty;
    QComboBox *listaWalut;
    QPushButton *guzik;
    QLabel *label;

    QString szukana;
    double przelicznik;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    float PrzeliczPrzelicznik();
    QNetworkAccessManager *networkManager;
    void uaktualnijPrzelicznik();


public slots:
    void edycjaPLN();
    void ZamianaWaluty();
    void pobierzPrzelicznik(QNetworkReply *replay);


};

#endif // MAINWINDOW_H
