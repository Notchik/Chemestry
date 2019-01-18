#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_comboBox_3_currentTextChanged(const QString &arg1);

    void reaction_1();

    void reaction_2();

    void reaction_4();

    void reaction_5();

    void reaction_6();

    void reaction_7();

    void on_pushButton_2_clicked();

    QByteArray filePrint();

private:
    Ui::MainWindow *ui;
    QString Final;
};

#endif // MAINWINDOW_H
