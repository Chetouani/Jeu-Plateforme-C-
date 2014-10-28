#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QBitmap>
#include <QCursor>
#include <QPixmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool quit;

private slots:
    void on_quitter_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
