#include "instatools.h"
#include "ui_instatools.h"

void InstaTools::on_bReloadHot_clicked()
{
//    ui->pteIdsHot->clear();
//    ui->pteMediaIdsHot->clear();
//    ui->pteUsernamesHot->clear();
//    ui->lCountMedia->setText("0");

//    QVector<QString> tags;
//    for(int i = 0; i < ui->pteTagsForSearch->document()->lineCount(); i++)
//    {
//        QString current_tag = ui->pteTagsForSearch->document()->findBlockByLineNumber(i).text();
//        tags.append( current_tag );
//    }

//    ui->lCountTags->setText("Считано: " + QString::number(tags.size()));

//    QVector< QPair<NetThread::method, QVector<QString> > > queue;
//    NetThread * th = new NetThread();
//    for(int i = 0; i < tags.size(); i++)
//    {
//        QVector<QString> params;
//        params.push_back( access_token );
//        params.push_back( tags.at(i) );

//        queue.push_back( { NetThread::GET_TAGS, params } );
//    }
//    th->setFlag( queue );

//    connect(th, SIGNAL(finishGetTags(QVector<insta_api::media>)), this, SLOT(printVectorTags(QVector<insta_api::media>)) );
//    connect(th, SIGNAL(finished()), th, SLOT(deleteLater()));
//    th->start();
}
