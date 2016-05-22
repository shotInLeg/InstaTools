#include "instatools.h"
#include "ui_instatools.h"

void InstaTools::on_bMassAuth_clicked()
{
    QVector< QVector<QString> > login_data = getParsedVectorFromPlainText(ui->pteLoginDataList);

    QVector< QPair<NetThread::method, QVector<QString> > > queue;
    NetThread * th = new NetThread();
    QVector<QString> params;

    for(int i = 0; i < login_data.size(); i++)
    {
        params.push_back( login_data[i][0] );
        params.push_back( login_data[i][1] );
        queue.push_back( {NetThread::AUTH, params} );
        params.clear();
    }
    th->setFlag( queue );

    connect(th, SIGNAL(finishAuth(QString)), this, SLOT(saveAuthToken(QString)) );
    connect(th, SIGNAL(finished()), th, SLOT(deleteLater()));
    th->start();
}
