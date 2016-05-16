#include "instatools.h"
#include "ui_instatools.h"

void InstaTools::on_bAddNameToLName_clicked()
{
    ui->pteNamesAndLNames->clear();

    QVector<QString> names = getVectorFromPlainText(ui->pteListNames);
    QVector<QString> lnames = getVectorFromPlainText(ui->pteListLNames);

    QVector<QString> result;
    for(int i = 0; i < names.size(); i++)
    {
        for(int j = 0; j < lnames.size(); j++)
        {
            QString name_lname = lnames.at(j) + names.at(i);
            result.push_back(name_lname);
        }
    }

    printVecotrToPlainText(result, ui->pteNamesAndLNames);
}

void InstaTools::on_bShuffle_clicked()
{
    ui->pteNamesAndLNames->clear();

    QVector<QString> names_lnames = getVectorFromPlainText(ui->pteNamesAndLNames);
    QVector<QString> result;

}

void InstaTools::on_bAddNumeric_clicked()
{
    ui->pteNamesAndLNames->clear();

    int count = ui->eCountNumeric->text().toInt();
    QVector<QString> names = getVectorFromPlainText(ui->pteListLNames);

    QVector<QString> result;
    for(int i = 0; i < names.size(); i++)
    {
        for(int j = 0; j < count; j++)
        {
            result.push_back( names.at(i) + QString::number(j+1) );
        }
    }

    printVecotrToPlainText(result, ui->pteNamesAndLNames);
}
