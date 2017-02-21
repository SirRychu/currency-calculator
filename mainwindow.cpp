#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QLabel *firstLabel = new QLabel("PLN", this);
    firstLabel->setGeometry(15,15,150,30);
    wartoscPLN = new QLineEdit(this);
    wartoscPLN->setGeometry(50, 15, 150, 30);
    connect(wartoscPLN, SIGNAL(editingFinished()), this, SLOT(edycjaPLN()));

    listaWalut = new QComboBox(this);
    listaWalut->setGeometry(15,60,150,30);
    listaWalut->addItem("");
    listaWalut->addItem("AUD");
    listaWalut->addItem("BGN");
    listaWalut->addItem("BRL");
    listaWalut->addItem("CAD");
    listaWalut->addItem("CHF");
    listaWalut->addItem("CNY");
    listaWalut->addItem("CZK");
    listaWalut->addItem("DKK");
    listaWalut->addItem("EUR");
    listaWalut->addItem("GBP");
    listaWalut->addItem("HKD");
    listaWalut->addItem("HRK");
    listaWalut->addItem("ILS");
    listaWalut->addItem("INR");
    listaWalut->addItem("MXN");
    listaWalut->addItem("MYR");
    listaWalut->addItem("NOK");
    listaWalut->addItem("NZD");
    listaWalut->addItem("PHP");
    listaWalut->addItem("RON");
    listaWalut->addItem("RUB");
    listaWalut->addItem("SEK");
    listaWalut->addItem("SGD");
    listaWalut->addItem("THB");
    listaWalut->addItem("TRY");
    listaWalut->addItem("UAH");
    listaWalut->addItem("USD");
    listaWalut->addItem("ZAR");

    connect(listaWalut, SIGNAL(currentIndexChanged(int)), this, SLOT(edycjaPLN()));

    wartoscWaluty = new QLineEdit(this);
    wartoscWaluty->setGeometry(50, 60, 150, 30);

    guzik = new QPushButton("Przelicz",this);
    guzik->setGeometry(50,105,150,30);
    connect(guzik, SIGNAL(clicked()), this, SLOT(ZamianaWaluty()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::edycjaPLN(){
    wartoscWaluty->setText(tr(""));
    uaktualnijPrzelicznik();
}

float MainWindow::PrzeliczPrzelicznik(){
    float pomprzelicznik;
    if (listaWalut->currentText() == "USD")
        pomprzelicznik = 3.8150;
    else if (listaWalut->currentText() == "EUR")
        pomprzelicznik = 4.3334;
    else if (listaWalut->currentText() == "GBP")
        pomprzelicznik = 5.5174;
    else if (listaWalut->currentText() == "CHF")
        pomprzelicznik = 4.0380;
    else if (listaWalut->currentText() == "AUD")
        pomprzelicznik = 2.9067;
    else if (listaWalut->currentText() == "CAD")
        pomprzelicznik = 3.0337;
    else if (listaWalut->currentText() == "NZD")
        pomprzelicznik = 2.7713;
    else if (listaWalut->currentText() == "CZK")
        pomprzelicznik = 0.1623;
    else if (listaWalut->currentText() == "UAH")
        pomprzelicznik = 0.1557;
    else if (listaWalut->currentText() == "DKK")
        pomprzelicznik = 0.5908;
    else if (listaWalut->currentText() == "HRK")
        pomprzelicznik = 0.5845;
    else if (listaWalut->currentText() == "RUB")
        pomprzelicznik = 0.0604;
    else if (listaWalut->currentText() == "THB")
        pomprzelicznik = 0.1105;
    else if (listaWalut->currentText() == "HKD")
        pomprzelicznik = 0.5020;
    else if (listaWalut->currentText() == "SGD")
        pomprzelicznik = 2.9018;
    else if (listaWalut->currentText() == "NOK")
        pomprzelicznik = 0.4691;
    else if (listaWalut->currentText() == "SEK")
        pomprzelicznik = 0.4704;
    else if (listaWalut->currentText() == "RON")
        pomprzelicznik = 0.9681;
    else if (listaWalut->currentText() == "BGN")
        pomprzelicznik = 2.2445;
    else if (listaWalut->currentText() == "TRY")
        pomprzelicznik = 1.3382;
    else if (listaWalut->currentText() == "ILS")
        pomprzelicznik = 1.0087;
    else if (listaWalut->currentText() == "PHP")
        pomprzelicznik = 0.0836;
    else if (listaWalut->currentText() == "MXN")
        pomprzelicznik = 0.2081;
    else if (listaWalut->currentText() == "ZAR")
        pomprzelicznik = 0.2645;
    else if (listaWalut->currentText() == "BRL")
        pomprzelicznik = 1.1405;
    else if (listaWalut->currentText() == "MYR")
        pomprzelicznik = 0.9648;
    else if (listaWalut->currentText() == "INR")
        pomprzelicznik = 5.7634;
    else if (listaWalut->currentText() == "CNY")
        pomprzelicznik = 0.5918;
    else pomprzelicznik = 0;

    return pomprzelicznik;

}

void MainWindow::ZamianaWaluty(){

    float wynik;
    if(wartoscWaluty->text() == ""){
        wynik = wartoscPLN->text().toFloat()*przelicznik;
        wartoscWaluty->setText(QString::number(wynik));
    }
    else if(wartoscPLN->text() == ""){
        wynik = wartoscWaluty->text().toFloat()/przelicznik;
        wartoscPLN->setText(QString::number(wynik));
    }
}

void MainWindow::uaktualnijPrzelicznik(){
    networkManager = new QNetworkAccessManager();

    szukana = listaWalut->currentText();

    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::pobierzPrzelicznik);
    networkManager->get(QNetworkRequest(QUrl("http://api.nbp.pl/api/exchangerates/rates/a/"+szukana+"/?format=json")));


}

void MainWindow::pobierzPrzelicznik(QNetworkReply *replay){

    if(!replay->error()){
        QJsonDocument document = QJsonDocument::fromJson(replay->readAll());

        QJsonObject root = document.object();

        QJsonValue jv = root.value("rates");
        if (jv.isArray()){
            QJsonArray ja = jv.toArray();
            for(int i = 0; i<ja.count(); i++){
                QJsonObject subtree = ja.at(i).toObject();
                przelicznik = subtree.value("mid").toDouble();
                qDebug()<<"przelicznik ="<<przelicznik;
           }


        }

    }
    else przelicznik=PrzeliczPrzelicznik();

}
