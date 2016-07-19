#include "instatools.h"
#include "ui_instatools.h"

void InstaTools::on_bAuthSend_clicked()
{
    insta_api::account acc;
    acc.username = ui->eAuthLogin->text();
    acc.password = ui->eAuthPassword->text();
    acc.proxy_type = getProxyType( ui->eAuthProxy->text() );
    acc.proxy_ip = getProxyIp( ui->eAuthProxy->text() );
    acc.proxy_port = getProxyPort( ui->eAuthProxy->text() );
    acc.app = getAppId();

    NetThread * th = new NetThread();
    th->addWork( NetThread::AUTH, acc, QVector<QString>() );

    connect(th, SIGNAL(finishAuth(insta_api::account)), this, SLOT(saveSingleAuthAccount(insta_api::account)) );
    connect(th, SIGNAL(finished()), th, SLOT(deleteLater()));

    th->start();
}


void InstaTools::saveSingleAuthAccount(insta_api::account acc)
{
    if( acc.token == "error")
    {
        ui->lAuthStatus1->setText("Вам не удалось авторизоваться");
        ui->lAuthStatus2->setText("Проверьте логин/пароль на корректность");
        return;
    }

    accounts.push_back( acc );

    ui->lAuthStatus1->setText("Вы успешно авторизовались");
    ui->lAuthStatus2->setText( acc.token );
}

void InstaTools::on_bAuthMassSendAuth_clicked()
{
    QVector<QString> logins = vectorFromPTE( ui->pteAuthLogins );
    QVector<QString> passwords = vectorFromPTE( ui->pteAuthPasswords );
    QVector<QString> proxies = vectorFromPTE( ui->pteAuthProxy );

    QVector<insta_api::account> accs;
    for( int i = 0; i < logins.size() && i < passwords.size(); i++ )
    {
        insta_api::account acc;

        acc.username = logins.at(i);
        acc.password = passwords.at(i);
        acc.app = getAppId();

        if( proxies.size() > i )
        {
            acc.proxy_type = getProxyType( proxies.at(i) );
            acc.proxy_ip = getProxyIp( proxies.at(i) );
            acc.proxy_port = getProxyPort( proxies.at(i) );
        }

        accs.push_back( acc );
    }


    NetThread * th = new NetThread();

    for( int i = 0; i < accs.size(); i++ )
    {
        th->addWork( NetThread::AUTH, accs.at(i), QVector<QString>() );
    }

    connect(th, SIGNAL(finishAuth(insta_api::account)), this, SLOT( saveMassAuthAccount(insta_api::account)) );
    connect(th, SIGNAL(finished()), th, SLOT(deleteLater()));

    th->start();
}

void InstaTools::saveMassAuthAccount(insta_api::account acc)
{
    if( acc.token == "error")
    {
        qDebug() << "ERROR" << acc.username;
        return;
    }

    ui->lAuthCount->setText( QString::number( ui->lAuthCount->text().toInt() + 1 ) );
    qDebug() << "DONE" << acc.username << acc.token;

    accounts.push_back( acc );
}


QVector<QString> InstaTools::vectorFromPTE(QPlainTextEdit *pte)
{
    QVector<QString> result;

    for(int i = 0; i < pte->document()->lineCount(); i++)
    {
        QString current_row = pte->document()->findBlockByLineNumber(i).text();
        result.append( current_row );
    }

    return result;
}



