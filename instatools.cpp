#include "instatools.h"
#include "ui_instatools.h"

InstaTools::InstaTools(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InstaTools)
{
    ui->setupUi(this);

    qRegisterMetaType< QVector<insta_api::user> >();
    qRegisterMetaType< QVector<insta_api::media> >();
    qRegisterMetaType< insta_api::account >();

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

void InstaTools::printMapToPlainText(const QMap<QString, int> &map, QPlainTextEdit *pte)
{
    QMap<QString, int>::const_iterator itr = map.begin();
    for( ; itr != map.end(); itr++)
    {
        pte->appendPlainText(itr.key() + " | " + QString::number(itr.value()));
    }
}

QString InstaTools::getProxyType( const QString& proxy_line )
{
    if( proxy_line == "" )
        return "";

    QStringList list = proxy_line.split(" ");

    if( list.size() <= 0 )
        return "";

    return list.at(0);
}

QString InstaTools::getProxyIp(const QString &proxy_line)
{
    if( proxy_line == "" )
        return "";

    QStringList list = proxy_line.split(" ");

    if( list.size() <= 0 )
        return "";

    QString ip_port = list.at(1);

    return ip_port.split(":").at(0);
}

QString InstaTools::getProxyPort(const QString &proxy_line)
{
    if( proxy_line == "" )
        return "";

    QStringList list = proxy_line.split(" ");

    if( list.size() <= 0 )
        return "";

    QString ip_port = list.at(1);

    return ip_port.split(":").at(1);
}

QString InstaTools::getAppId()
{
    return "99e5da2ffc694c1db55491d47fb82377";
}

void InstaTools::printVectorFollows(const QVector<insta_api::user> &vector)
{
    QVector<QString> id;
    QVector<QString> username;
    for(int i = 0; i < vector.size(); i++)
    {
        id.push_back( vector.at(i).id );
        username.push_back( vector.at(i).username );
    }

    printVecotrToPlainText(id, ui->pteFollowsId);
    printVecotrToPlainText(username, ui->pteFollowsUsername );
}

void InstaTools::printVectorFollowers(const QVector<insta_api::user> &vector)
{
    QVector<QString> id;
    QVector<QString> username;
    for(int i = 0; i < vector.size(); i++)
    {
        id.push_back( vector.at(i).id );
        username.push_back( vector.at(i).username );
    }

    printVecotrToPlainText(id, ui->pteFollowersId);
    printVecotrToPlainText(username, ui->pteFollowersUsername );
}

void InstaTools::printVectorTags(const QVector<insta_api::media> &vector)
{
//    QVector<QString> id;
//    QVector<QString> username;
//    QVector<QString> id_ow;

//    for(int i = 0; i < vector.size(); i++)
//    {
//        id.push_back( vector.at(i).id );
//        username.push_back( vector.at(i).owner_username );
//        id_ow.push_back( vector.at(i).owner_id );
//    }

//    ui->lCountMedia->setText( QString::number( ui->lCountMedia->text().toInt() + vector.size() ) );

//    printVecotrToPlainText(id, ui->pteMediaIdsHot);
//    printVecotrToPlainText(username, ui->pteUsernamesHot );
//    printVecotrToPlainText(id_ow, ui->pteIdsHot );
}




void InstaTools::on_lMenu_activated(const QModelIndex &index)
{
    ui->swScreens->setCurrentIndex( index.row() );
}

void InstaTools::on_lMenu_currentRowChanged(int currentRow)
{
    ui->swScreens->setCurrentIndex( currentRow );
}









void InstaTools::on_pteAuthLogins_textChanged()
{
    int count = ui->pteAuthLogins->document()->lineCount();

    if( count > 0 )
    {
     if( ui->pteAuthLogins->document()->findBlockByLineNumber( count-1 ).text() == "" )
        ui->lAuthLoginsCount->setText( "Логины ("+QString::number( count-1 )+"):");
     else
        ui->lAuthLoginsCount->setText( "Логины ("+QString::number( count )+"):");
    }
    else
       ui->lAuthLoginsCount->setText( "Логины (0):");
}

void InstaTools::on_pteAuthPasswords_textChanged()
{
    int count = ui->pteAuthPasswords->document()->lineCount();

    if( count > 0 )
    {
     if( ui->pteAuthPasswords->document()->findBlockByLineNumber( count-1 ).text() == "" )
        ui->lAuthPasswordsCount->setText( "Пароли ("+QString::number( count-1 )+"):");
     else
        ui->lAuthPasswordsCount->setText( "Пароли ("+QString::number( count )+"):");
    }
    else
       ui->lAuthPasswordsCount->setText( "Пароли (0):");
}

void InstaTools::on_pteAuthProxy_textChanged()
{
    int count = ui->pteAuthProxy->document()->lineCount();

    if( count > 0 )
    {
     if( ui->pteAuthProxy->document()->findBlockByLineNumber( count-1 ).text() == "" )
        ui->lAuthProxyCount->setText( "Прокси ("+QString::number( count-1 )+"):");
     else
        ui->lAuthProxyCount->setText( "Прокси ("+QString::number( count )+"):");
    }
    else
       ui->lAuthProxyCount->setText( "Прокси (0):");
}
