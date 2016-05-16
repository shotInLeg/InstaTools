#include "instatools.h"
#include "ui_instatools.h"

InstaTools::InstaTools(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InstaTools)
{
    ui->setupUi(this);



    QString client_id = "99e5da2ffc694c1db55491d47fb82377";
    QString redirect_uri = "shotinleg.xyz/passcode.php";
}

InstaTools::~InstaTools()
{
    delete ui;
}

QVector<QString> InstaTools::getVectorFromPlainText(QPlainTextEdit *pte)
{
    QVector<QString> result;

    for(int i = 0; i < pte->document()->lineCount(); i++)
    {
        QString current_row = pte->document()->findBlockByLineNumber(i).text();
        result.append( current_row );
    }

    return result;
}

QVector<QVector<QString> > InstaTools::getParsedVectorFromPlainText(QPlainTextEdit *pte)
{
    QVector<QVector<QString> > result;

    for(int i = 0; i < pte->document()->lineCount(); i++)
    {
        QString current_row = pte->document()->findBlockByLineNumber(i).text();
        QStringList list_row = current_row.split(";");

        QVector<QString> row;
        for(int j = 0; j < list_row.size(); j++)
        {
            qDebug() << list_row.at(j);
            row.push_back(list_row.at(j));
        }

        result.push_back( row );
    }

    return result;
}

void InstaTools::printVecotrToPlainText(const QVector<QString>& vector, QPlainTextEdit *pte)
{
    for(int i = 0; i < vector.size(); i++)
    {
        pte->appendPlainText( vector.at(i) );
    }
}
void InstaTools::printVecotrToPlainText(const QVector< QPair<QString,QString> >& vector, QPlainTextEdit *pte)
{
    for(int i = 0; i < vector.size(); i++)
    {
        pte->appendPlainText( vector.at(i).first+": "+vector.at(i).second );
    }
}
void InstaTools::printVecotrToListWidget(const QVector< QPair<QString,QString> >& vector, QListWidget *lw)
{
    for(int i = 0; i < vector.size(); i++)
    {
        lw->addItem(vector.at(i).first);
    }
}
void InstaTools::on_lMenu_activated(const QModelIndex &index)
{
    ui->swScreens->setCurrentIndex( index.row() );
}

void InstaTools::on_lMenu_currentRowChanged(int currentRow)
{
    ui->swScreens->setCurrentIndex( currentRow );
}













