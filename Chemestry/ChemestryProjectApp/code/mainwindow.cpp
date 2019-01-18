#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QErrorMessage"
#include "QFile"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reaction_1()
{
    QString x_str, control = ui->comboBox->currentText(), mass_str;
    QRegExp re("^[0-9]+(\\.[0-9]+)?$");
    x_str = ui->lineEdit->text();
    mass_str = ui->lineEdit_2->text();

    if(x_str == "")
    {
        if(ui->comboBox_2->currentText() == "ENG")
            (new QErrorMessage(this))->showMessage("Not all information is available");
        else (new QErrorMessage(this))->showMessage("Заполнены не все поля");
        return;
    }

    if(!re.exactMatch(x_str))
    {
        if(ui->comboBox_2->currentText() == "ENG")
            (new QErrorMessage(this))->showMessage("Invalid X value");
        else (new QErrorMessage(this))->showMessage("Неверное значение X");
        return;
    }

    double x = x_str.toDouble(), mass = mass_str.toDouble();

    if(x > 6 || 0 >= x)
    {
        if(ui->comboBox_2->currentText() == "ENG")
            (new QErrorMessage(this))->showMessage("X must be (0;6]");
        else (new QErrorMessage(this))->showMessage("X должен принимать значение в промежутке (0;6]");
        return;
    }

    double coef_1 = (6 - x/2), coef_2 = (x/2), coef_4 = (x), coef_3 = (12 - x);
    double M_BaCO3 = 197.337, M_Fe2O3 = 159.687, M_EL2O3 = 0, M_El = 0;

    if(control == "Al") {M_EL2O3 = 2 * 26.98 + 47.997; M_El = 26.98;}
    if(control == "Ga") {M_EL2O3 = 2 * 69.723 + 47.997; M_El = 69.723;}
    if(control == "In") {M_EL2O3 = 2 * 114.818 + 47.997; M_El = 114.818;}
    if(control == "Sc") {M_EL2O3 = 2 * 44.956 + 47.997; M_El = 44.956;}

    double M2_Fe2O3 = (coef_1 * M_Fe2O3), M2_El2O3 = (coef_2 * M_EL2O3);
    double BaFeElO = 137.33 + coef_3 * 55.845 + coef_4 * M_El + 303.981;

    ui->label->setText("BaCO3 + " + QString::number(coef_1) + " Fe2O3 + " +
                       QString::number(coef_2) + " " + control +
                       "2O3  -->  BaFe" + " (" + QString::number(coef_3) + ") " + control + " (" +
                       QString::number(coef_4) + ") " +"O19 + CO2");

    double mass_BaCO3 = M_BaCO3 * mass / BaFeElO;
    double mass_Fe2O3 = M2_Fe2O3 * mass / BaFeElO;
    double mass_El2O3 = M2_El2O3 * mass / BaFeElO;

    if(ui->comboBox_2->currentText() == "ENG")
    {
        Final = "m(BaCO3) = " + QString::number(mass_BaCO3) + "\r\n\n" +
                "m(Fe2O3) = " + QString::number(mass_Fe2O3) + "\r\n\n" +
                "m(" + control + "2O3) = " + QString::number(mass_El2O3) + "\r\n\n" +
                "Total mass = " + QString::number(mass_BaCO3 + mass_Fe2O3 + mass_El2O3);
    }
    else
    {
        Final = "m(BaCO3) = " + QString::number(mass_BaCO3) + "\r\n\n" +
                "m(Fe2O3) = " + QString::number(mass_Fe2O3) + "\r\n\n" +
                "m(" + control + "2O3) = " + QString::number(mass_El2O3) + "\r\n\n" +
                "Итоговая масса = " + QString::number(mass_BaCO3 + mass_Fe2O3 + mass_El2O3);
    }
    ui->textEdit->setText(Final);
}

void MainWindow::reaction_2()
{
    QString x_str, mass_str;
    QRegExp re("^[0-9]+(\\.[0-9]+)?$");
    x_str = ui->lineEdit->text();
    mass_str = ui->lineEdit_2->text();

    if(x_str == "")
    {
        if(ui->comboBox_2->currentText() == "ENG")
            (new QErrorMessage(this))->showMessage("Not all information is available");
        else (new QErrorMessage(this))->showMessage("Заполнены не все поля");
        return;
    }

    if(!re.exactMatch(x_str))
    {
        if(ui->comboBox_2->currentText() == "ENG")
            (new QErrorMessage(this))->showMessage("Invalid X value");
        else (new QErrorMessage(this))->showMessage("Неверное значение X");
        return;
    }

    double x = x_str.toDouble(), mass = mass_str.toDouble();

    if(x >= 6 || 0 >= x)
    {
        if(ui->comboBox_2->currentText() == "ENG")
            (new QErrorMessage(this))->showMessage("X must be (0;6)");
        else (new QErrorMessage(this))->showMessage("X должен принимать значение в промежутке (0;6)");
        return;
    }

    double coef_1 = (6-x/2), coef_2 = x, coef_3 = (12-x);
    double M_BaCO3 = 197.336, M_Zn = 65.38, M2_Zn = coef_2 * M_Zn, M_Fe2O3 = 159.687, M2_Fe2O3 = M_Fe2O3*coef_1;

    double BaFeZnO = 137.33 + coef_3*55.845 + coef_2*M_Zn + 19*15.999;

    ui->label->setText("BaCO3 + " + QString::number(coef_1) + "Fe2O3 + " +
                       QString::number(coef_2) + "Zn  ->  BaFe (" + QString::number(coef_3) +
                       ") Zn (" + QString::number(coef_2) + ") O19 + CO2");

    double mass_BaCO3 = M_BaCO3 * mass / BaFeZnO;
    double mass_Zn = M2_Zn * mass / BaFeZnO;
    double mass_Fe2O3 = M2_Fe2O3 * mass / BaFeZnO;

    if(ui->comboBox_2->currentText() == "ENG")
    {
        Final = "m(BaCO3) = " + QString::number(mass_BaCO3) + "\r\n\n" +
                "m(Zn) = " + QString::number(mass_Zn) + "\r\n\n" +
                "m(Fe2O3) = " + QString::number(mass_Fe2O3) + "\r\n\n" +
                "Total mass = " + QString::number(mass_BaCO3 + mass_Fe2O3 + mass_Zn);
    }
    else
    {
        Final = "m(BaCO3) = " + QString::number(mass_BaCO3) + "\r\n\n" +
                "m(Zn) = " + QString::number(mass_Zn) + "\r\n\n" +
                "m(Fe2O3) = " + QString::number(mass_Fe2O3) + "\r\n\n" +
                "Итоговая масса = " + QString::number(mass_BaCO3 + mass_Fe2O3 + mass_Zn);
    }
    ui->textEdit->setText(Final);
}

void MainWindow::reaction_4()
{
    QString mass_str;
    mass_str = ui->lineEdit_2->text();

    double mass = mass_str.toDouble();

    double M_BaCO3 = 197.338, M_6Fe2O3 = 958.122, M_BaFe12O19 = 1111.451;

    double mass_BaCO3 = M_BaCO3 * mass / M_BaFe12O19;
    double mass_Fe2O3 = M_6Fe2O3 * mass / M_BaFe12O19;

    if(ui->comboBox_2->currentText() == "ENG")
    {
        Final = "m(BaCO3) = " + QString::number(mass_BaCO3) + "\r\n\n" +
                "m(Fe2O3) = " + QString::number(mass_Fe2O3) + "\r\n\n" +
                "Total mass = " + QString::number(mass_BaCO3 + mass_Fe2O3);
    }
    else
    {
        Final = "m(BaCO3) = " + QString::number(mass_BaCO3) + "\r\n\n" +
                "m(Fe2O3) = " + QString::number(mass_Fe2O3) + "\r\n\n" +
                "Итоговая масса = " + QString::number(mass_BaCO3 + mass_Fe2O3);
    }
    ui->textEdit->setText(Final);
}

void MainWindow::reaction_5()
{
    QString mass_str;
    mass_str = ui->lineEdit_2->text();

    double mass = mass_str.toDouble();

    double M_NiO = 74.692, M_Fe2O3 = 159.687, M_NiFe2O4 = 234.379;

    double mass_NiO = M_NiO * mass / M_NiFe2O4;
    double mass_Fe2O3 = M_Fe2O3 * mass / M_NiFe2O4;

    if(ui->comboBox_2->currentText() == "ENG")
    {
        Final = "m(NiO) = " + QString::number(mass_NiO) + "\r\n\n" +
                "m(Fe2O3) = " + QString::number(mass_Fe2O3) + "\r\n\n" +
                "Total mass = " + QString::number(mass_NiO + mass_Fe2O3);
    }
    else
    {
        Final = "m(NiO) = " + QString::number(mass_NiO) + "\r\n\n" +
                "m(Fe2O3) = " + QString::number(mass_Fe2O3) + "\r\n\n" +
                "Итоговая масса = " + QString::number(mass_NiO + mass_Fe2O3);
    }
    ui->textEdit->setText(Final);

}

void MainWindow::reaction_6()
{
    QString x_str, mass_str;
    QRegExp re("^[0-9]+(\\.[0-9]+)?$");
    x_str = ui->lineEdit->text();
    mass_str = ui->lineEdit_2->text();

    if(x_str == "")
    {
        if(ui->comboBox_2->currentText() == "ENG")
            (new QErrorMessage(this))->showMessage("Not all information is available");
        else (new QErrorMessage(this))->showMessage("Заполнены не все поля");
        return;
    }

    if(!re.exactMatch(x_str))
    {
        if(ui->comboBox_2->currentText() == "ENG")
            (new QErrorMessage(this))->showMessage("Invalid X value");
        else (new QErrorMessage(this))->showMessage("Неверное значение X");
        return;
    }

    double x = x_str.toDouble(), mass = mass_str.toDouble();

    if(x >= 1 || 0 >= x)
    {
        if(ui->comboBox_2->currentText() == "ENG")
            (new QErrorMessage(this))->showMessage("X must be (0;1)");
        else (new QErrorMessage(this))->showMessage("X должен принимать значение в промежутке (0;1)");
        return;
    }

    double coef_1 = (1-x), coef_2 = x;
    double M_NiO = 74.692, M_ZnO = 81.379, M2_NiO = M_NiO*coef_1, M2_ZnO = M_ZnO*coef_2, M_Fe2O3 = 159.687;

    double NiZnFeO = coef_1 * 58.693 + coef_2 * 65.38 + 2 * 55.845 + 4*15.999;

    ui->label->setText(QString::number(coef_1) + "NiO + " +
                       QString::number(coef_2) + "ZnO + Fe2O3  ->  Ni (" + QString::number(coef_1) +
                       ") Zn (" + QString::number(coef_2) + ") Fe2O4");

    double mass_NiO = M2_NiO * mass / NiZnFeO;
    double mass_ZnO = M2_ZnO * mass / NiZnFeO;
    double mass_Fe2O3 = M_Fe2O3 * mass / NiZnFeO;

    if(ui->comboBox_2->currentText() == "ENG")
    {
        Final = "m(NiO) = " + QString::number(mass_NiO) + "\r\n\n" +
                "m(ZnO) = " + QString::number(mass_ZnO) + "\r\n\n" +
                "m(Fe2O3) = " + QString::number(mass_Fe2O3) + "\r\n\n" +
                "Total mass = " + QString::number(mass_NiO + mass_Fe2O3 + mass_ZnO);
    }
    else
    {
        Final = "m(NiO) = " + QString::number(mass_NiO) + "\r\n\n" +
                "m(ZnO) = " + QString::number(mass_ZnO) + "\r\n\n" +
                "m(Fe2O3) = " + QString::number(mass_Fe2O3) + "\r\n\n" +
                "Итоговая масса = " + QString::number(mass_NiO + mass_Fe2O3 + mass_ZnO);
    }
    ui->textEdit->setText(Final);
}

void MainWindow::reaction_7()
{
    QString mass_str;
    mass_str = ui->lineEdit_2->text();

    double mass = mass_str.toDouble();

    double M_Bi2O3 = 465.957, M_Fe2O3 = 159.687, M_2BiFeO3 = 625.644;

    double mass_Bi2O3 = M_Bi2O3 * mass / M_2BiFeO3;
    double mass_Fe2O3 = M_Fe2O3 * mass / M_2BiFeO3;

    if(ui->comboBox_2->currentText() == "ENG")
    {
        Final = "m(Bi2O3) = " + QString::number(mass_Bi2O3) + "\r\n\n" +
                "m(Fe2O3) = " + QString::number(mass_Fe2O3) + "\r\n\n" +
                "Total mass = " + QString::number(mass_Bi2O3 + mass_Fe2O3);
    }
    else
    {
        Final = "m(Bi2O3) = " + QString::number(mass_Bi2O3) + "\r\n\n" +
                "m(Fe2O3) = " + QString::number(mass_Fe2O3) + "\r\n\n" +
                "Итоговая масса = " + QString::number(mass_Bi2O3 + mass_Fe2O3);
    }
    ui->textEdit->setText(Final);
}

void MainWindow::on_pushButton_clicked()
{
    QString  mass_str;
    QRegExp re("^[0-9]+(\\.[0-9]+)?$");
    mass_str = ui->lineEdit_2->text();

    if(mass_str == "")
    {
        if(ui->comboBox_2->currentText() == "ENG")
            (new QErrorMessage(this))->showMessage("Not all information is available");
        else (new QErrorMessage(this))->showMessage("Заполнены не все поля");
        return;
    }

    if(!re.exactMatch(mass_str))
    {
        if(ui->comboBox_2->currentText() == "ENG")
            (new QErrorMessage(this))->showMessage("Invalid mass value");
        else (new QErrorMessage(this))->showMessage("Неверное значение массы");
        return;
    }

    if(ui->comboBox_3->currentText() == "BaFe(y)el(x)O19")
        reaction_1();
    if(ui->comboBox_3->currentText() == "BaFe(y)Zn(x)O19")
        reaction_2();
    if(ui->comboBox_3->currentText() == "BaFe12O19")
        reaction_4();
    if(ui->comboBox_3->currentText() == "NiFe2O4")
        reaction_5();
    if(ui->comboBox_3->currentText() == "Ni(y)Zn(x)Fe2O4")
        reaction_6();
    if(ui->comboBox_3->currentText() == "BiFeO3")
        reaction_7();
}

void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    if(arg1 == "RU")
    {
        ui->label_8->setText("Масса = ");
        ui->label_9->setText("Элемент");
        ui->label_2->setText("Вещество");
        ui->pushButton->setText("Установить параметры");
        ui->pushButton_2->setText("Сохранить в файл");
    }
    else
    {
        ui->label_8->setText("Mass = ");
        ui->label_9->setText("Element");
        ui->label_2->setText("Substance");
        ui->pushButton->setText("Set parameters");
        ui->pushButton_2->setText("Save in file");
    }
}

void MainWindow::on_comboBox_3_currentTextChanged(const QString &arg1)
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->textEdit->clear();

    if(arg1 == "BaFe(y)el(x)O19")
    {
        ui->label->setText("BaCO3 +  _Fe2O3 + _ _2O3  ->  BaFe_ _ _O19 + CO2");
        ui->lineEdit->setDisabled(false);
        ui->comboBox->setDisabled(false);
    }
    if(arg1 == "BaFe(y)Zn(x)O19")
    {
        ui->label->setText("BaCO3 +  _Fe2O3 + _Zn  ->  BaFe_Zn_O19 + CO2");
        ui->lineEdit->setDisabled(false);
        ui->comboBox->setDisabled(true);
    }
    if(arg1 == "BaFe12O19")
    {
        ui->label->setText("BaCO3 + 6Fe2O3  ->  BaFe12O19 + CO2");
        ui->lineEdit->setDisabled(true);
        ui->comboBox->setDisabled(true);
    }
    if(arg1 == "NiFe2O4")
    {
        ui->label->setText("NiO + Fe2O3  ->  NiFe2O4");
        ui->lineEdit->setDisabled(true);
        ui->comboBox->setDisabled(true);
    }
    if(arg1 == "Ni(y)Zn(x)Fe2O4")
    {
        ui->label->setText("_NiO + _ZnO + Fe2O3  ->  Ni_Zn_Fe2O4");
        ui->lineEdit->setDisabled(false);
        ui->comboBox->setDisabled(true);
    }
    if(arg1 == "BiFeO3")
    {
        ui->label->setText("Bi2O3 + Fe2O3  ->  2BiFeO3");
        ui->lineEdit->setDisabled(true);
        ui->comboBox->setDisabled(true);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
     int i = 1;
     for(i;;i++)
     {
         QString num = QString::number(i);
         QString str = "Reactions/Reaction" + num + ".txt";
         QFile filetest(str);
              if(!filetest.exists())
              break;
     }

     QString num = QString::number(i);
     QString name = "Reactions/Reaction" + num + ".txt";
     QFile file(name);
     if (!file.open(QIODevice::ReadWrite))
         return;

     file.write(filePrint());
}

QByteArray MainWindow::filePrint()
{
    QString reaction = ui->label->text();
    QString config = "X  = ";
    QString result= "";

    if(ui->lineEdit->text() == "")
        config += "---";
    else
        config +=  " " + ui->lineEdit->text();

    if(ui->comboBox_2->currentText() == "RU")
    {
        config += "     Масса  =  " + ui->lineEdit_2->text();
        result += "РЕАКЦИЯ: \r\n" + reaction + "\r\n\r\nПАРАМЕТРЫ: \r\n" + config + "\r\n\r\nРЕЗУЛЬТАТ: \r\n" + Final;
    }
    else
    {
        config += "     Mass  =  " + ui->lineEdit_2->text();
        result += "REACTION: \r\n" + reaction + "\r\n\r\nPARAMETERS: \r\n" + config + "\r\n\r\nRESULTS: \r\n" + Final;
    }

    QByteArray toBack = result.toUtf8();
    return toBack;
}
