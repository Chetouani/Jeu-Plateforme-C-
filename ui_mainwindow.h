/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *titre;
    QPushButton *nouvellePartie;
    QPushButton *options;
    QPushButton *quitter;
    QLabel *perso;
    QPushButton *meilleurScore;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(735, 474);
        MainWindow->setMinimumSize(QSize(735, 474));
        MainWindow->setMaximumSize(QSize(735, 474));
        MainWindow->setStyleSheet(QLatin1String("#centralWidget{border-image: url(://img/SuperMarioBrosWallpaper.png) 0 0 0 0 stretch stretch;}\n"
"#titre {border-image: url(://img/titre.png) 0 0 0 0 stretch stretch;}\n"
"#perso {border-image: url(://img/Hero.png) 0 0 0 0 stretch stretch;}\n"
"\n"
"QPushButton {\n"
"border:  2px solid  rgb(0, 0, 127);\n"
"font: 15pt \"MV Boli\";\n"
"color:white;\n"
"border-radius:10px;\n"
"background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0 rgba(0, 74, 255, 255), stop:1 rgba(255, 255, 255, 255));\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0 rgba(255, 255, 255, 255), stop:1 rgba(0, 74, 255, 255));\n"
"}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        titre = new QLabel(centralWidget);
        titre->setObjectName(QStringLiteral("titre"));
        titre->setGeometry(QRect(-11, -21, 751, 391));
        titre->setMinimumSize(QSize(711, 361));
        titre->setStyleSheet(QStringLiteral(""));
        nouvellePartie = new QPushButton(centralWidget);
        nouvellePartie->setObjectName(QStringLiteral("nouvellePartie"));
        nouvellePartie->setGeometry(QRect(240, 410, 281, 41));
        nouvellePartie->setMinimumSize(QSize(150, 0));
        nouvellePartie->setCursor(QCursor(Qt::PointingHandCursor));
        nouvellePartie->setFlat(false);
        options = new QPushButton(centralWidget);
        options->setObjectName(QStringLiteral("options"));
        options->setGeometry(QRect(300, 350, 161, 41));
        options->setMinimumSize(QSize(150, 0));
        options->setCursor(QCursor(Qt::PointingHandCursor));
        options->setFlat(false);
        quitter = new QPushButton(centralWidget);
        quitter->setObjectName(QStringLiteral("quitter"));
        quitter->setGeometry(QRect(480, 350, 171, 41));
        quitter->setMinimumSize(QSize(150, 0));
        quitter->setCursor(QCursor(Qt::PointingHandCursor));
        quitter->setFlat(false);
        perso = new QLabel(centralWidget);
        perso->setObjectName(QStringLiteral("perso"));
        perso->setGeometry(QRect(-80, 190, 291, 261));
        perso->setMinimumSize(QSize(291, 261));
        meilleurScore = new QPushButton(centralWidget);
        meilleurScore->setObjectName(QStringLiteral("meilleurScore"));
        meilleurScore->setGeometry(QRect(120, 350, 161, 41));
        meilleurScore->setCursor(QCursor(Qt::PointingHandCursor));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        titre->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><br/></p></body></html>", 0));
        nouvellePartie->setText(QApplication::translate("MainWindow", "Nouvelle partie", 0));
        options->setText(QApplication::translate("MainWindow", "Options", 0));
        quitter->setText(QApplication::translate("MainWindow", "Quitter", 0));
        perso->setText(QString());
        meilleurScore->setText(QApplication::translate("MainWindow", "Meilleur score", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
