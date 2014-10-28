#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    quit = false;
    //Curseur personalisé
    QPixmap curseur("://img/curseur.png");
    QPixmap curseurBouton("://img/curseur_boutton.png");
    curseurBouton.setMask(QBitmap("://img/curseur_boutton.png"));
    curseur.setMask(QBitmap("://img/curseur.png"));

    //Pour la fenetre
    setCursor(QCursor(curseur) );

    //Pour les boutons
    ui->nouvellePartie->setCursor(curseurBouton);
    ui->meilleurScore->setCursor(curseurBouton);
    ui->options->setCursor(curseurBouton);
    ui->quitter->setCursor(curseurBouton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_quitter_clicked()
{
    quit = true;
    QApplication::quit();
}
