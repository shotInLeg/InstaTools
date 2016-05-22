#include "instatools.h"
#include "ui_instatools.h"

void InstaTools::getToken(QUrl url)
{
    if(!url.toString().contains("access_token"))
    {
        return;
    }

    url = url.toString().replace("#", "?");
    access_token = QUrlQuery(url).queryItemValue("access_token");

    ui->centralWidget->setWindowTitle("InstaTools [session: "+access_token+"]");
}




void InstaTools::on_bAuth_clicked()
{
    QVector< QPair<NetThread::method, QVector<QString> > > queue;
    NetThread * th = new NetThread();
    QVector<QString> params;


    params.push_back( ui->eLogin->text() );
    params.push_back( ui->ePassword->text() );
    queue.push_back( {NetThread::AUTH, params} );

    th->setFlag( queue );

    connect(th, SIGNAL(finishAuth(QString)), this, SLOT(saveSignleAuthToken(QString)) );
    connect(th, SIGNAL(finished()), th, SLOT(deleteLater()));
    th->start();
}

