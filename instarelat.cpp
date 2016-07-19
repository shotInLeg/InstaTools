#include "instatools.h"
#include "ui_instatools.h"


void InstaTools::on_bLoadFollowList_clicked()
{
//    ui->pteFollowersUsername->clear();
//    ui->pteFollowersId->clear();
//    ui->pteFollowsUsername->clear();
//    ui->pteFollowsId->clear();

//    QString username = ui->eRelUsername->text();

//    QString c_access_token = "";
//    if( ui->lwRelTokenList->currentRow() >= 0 && ui->lwRelTokenList->currentRow() <= ui->lwRelTokenList->count() )
//        c_access_token = list_access_token.at(ui->lwRelTokenList->currentRow()).second;
//    else
//        c_access_token = access_token;



//    QVector< QPair<NetThread::method, QVector<QString> > > queue;
//    NetThread * th = new NetThread();
//    QVector<QString> params;

//    params.push_back( c_access_token );
//    if( username != "" )
//    {
//        params.push_back( username );
//        queue.push_back( { NetThread::GET_USER_FOLLOWS, params } );
//    }
//    else
//    {
//        queue.push_back( { NetThread::GET_FOLLOWS, params } );
//    }

//    params.clear();
//    params.push_back( c_access_token );
//    if( username != "" )
//    {
//        params.push_back( username );
//        queue.push_back( { NetThread::GET_USER_FOLLOWERS, params } );
//    }
//    else
//    {
//        queue.push_back( { NetThread::GET_FOLLOWERS, params } );
//    }

//    th->setFlag( queue );

//    connect(th, SIGNAL(finishGetFollows(QVector<insta_api::user>)), this, SLOT(printVectorFollows(QVector<insta_api::user>)) );
//    connect(th, SIGNAL(finishGetFollowers(QVector<insta_api::user>)), this, SLOT(printVectorFollowers(QVector<insta_api::user>)) );
//    connect(th, SIGNAL(finished()), th, SLOT(deleteLater()));
//    th->start();
}

void InstaTools::on_bActiveFollowers_clicked()
{
//    count_lists = 0;
//    lists_likers_username.clear();
//    lists_likers_id.clear();
//    ui->pteResultUsername->clear();
//    ui->pteResultId->clear();

//    QString username = ui->eRelUsername->text();

//    QString c_access_token = "";
//    if( ui->lwRelTokenList->currentRow() >= 0 && ui->lwRelTokenList->currentRow() <= ui->lwRelTokenList->count() )
//        c_access_token = list_access_token.at(ui->lwRelTokenList->currentRow()).second;
//    else
//        c_access_token = access_token;

//    QVector< QPair<NetThread::method, QVector<QString> > > queue;
//    NetThread * th = new NetThread();
//    QVector<QString> params;

//    params.push_back( c_access_token );
//    if( username != "" )
//    {
//        params.push_back( username );
//        queue.push_back( { NetThread::GET_USER_MEDIA, params } );
//    }
//    else
//    {
//        return;
//    }
//    th->setFlag( queue );

//    connect(th, SIGNAL(finishGetUserMedia(QVector<insta_api::media>)), this, SLOT(loadMediaLikersActive(QVector<insta_api::media>)) );
//    connect(th, SIGNAL(finished()), th, SLOT(deleteLater()));
//    th->start();
}

void InstaTools::on_bRatingFollowers_clicked()
{
//    count_lists = 0;
//    lists_likers_username.clear();
//    lists_likers_id.clear();
//    ui->pteResultUsername->clear();
//    ui->pteResultId->clear();

//    QString username = ui->eRelUsername->text();

//    QString c_access_token = "";
//    if( ui->lwRelTokenList->currentRow() >= 0 && ui->lwRelTokenList->currentRow() <= ui->lwRelTokenList->count() )
//        c_access_token = list_access_token.at(ui->lwRelTokenList->currentRow()).second;
//    else
//        c_access_token = access_token;

//    QVector< QPair<NetThread::method, QVector<QString> > > queue;
//    NetThread * th = new NetThread();
//    QVector<QString> params;

//    params.push_back( c_access_token );
//    if( username != "" )
//    {
//        params.push_back( username );
//        queue.push_back( { NetThread::GET_USER_MEDIA, params } );
//    }
//    else
//    {
//        return;
//    }
//    th->setFlag( queue );

//    connect(th, SIGNAL(finishGetUserMedia(QVector<insta_api::media>)), this, SLOT(loadMediaLikers(QVector<insta_api::media>)) );
//    connect(th, SIGNAL(finished()), th, SLOT(deleteLater()));
//    th->start();
}

void InstaTools::loadMediaLikers(const QVector<insta_api::media> &vector)
{
//    QString c_access_token = "";
//    if( ui->lwRelTokenList->currentRow() >= 0 && ui->lwRelTokenList->currentRow() <= ui->lwRelTokenList->count() )
//        c_access_token = list_access_token.at(ui->lwRelTokenList->currentRow()).second;
//    else
//        c_access_token = access_token;

//    QVector< QPair<NetThread::method, QVector<QString> > > queue;
//    NetThread * th = new NetThread();
//    QVector<QString> params;


//    for(int i = 0; i < vector.size(); i++)
//    {
//        params.push_back( c_access_token );
//        params.push_back( vector.at(i).id );
//        queue.push_back( { NetThread::GET_MEDIA_LIKERS, params } );
//        params.clear();
//    }
//    th->setFlag( queue );

//    connect(th, SIGNAL(finishGetMediaLikers(QVector<insta_api::user>)), this, SLOT(countRatingLikers( QVector<insta_api::user>)) );
//    connect(th, SIGNAL(finished()), th, SLOT(deleteLater()));
//    th->start();
}

void InstaTools::loadMediaLikersActive(const QVector<insta_api::media> &vector)
{
//    QString c_access_token = "";
//    if( ui->lwRelTokenList->currentRow() >= 0 && ui->lwRelTokenList->currentRow() <= ui->lwRelTokenList->count() )
//        c_access_token = list_access_token.at(ui->lwRelTokenList->currentRow()).second;
//    else
//        c_access_token = access_token;

//    QVector< QPair<NetThread::method, QVector<QString> > > queue;
//    NetThread * th = new NetThread();
//    QVector<QString> params;


//    for(int i = 0; i < vector.size(); i++)
//    {
//        params.push_back( c_access_token );
//        params.push_back( vector.at(i).id );
//        queue.push_back( { NetThread::GET_MEDIA_LIKERS, params } );
//        params.clear();
//    }
//    th->setFlag( queue );

//    connect(th, SIGNAL(finishGetMediaLikers(QVector<insta_api::user>)), this, SLOT(printActiveLikers( QVector<insta_api::user>)) );
//    connect(th, SIGNAL(finished()), th, SLOT(deleteLater()));
//    th->start();
}

void InstaTools::countRatingLikers( QVector<insta_api::user> vector)
{
//    count_lists++;

//    for(int i = 0; i < vector.size(); i++)
//    {
//        QMap<QString, int>::iterator itr = lists_likers_username.find(vector.at(i).username);
//        if( itr.key() == vector.at(i).username )
//        {
//            itr.value()++;
//        }
//        else
//        {
//            lists_likers_username[vector.at(i).username] = 1;
//        }

//        itr = lists_likers_id.find(vector.at(i).id);
//        if( itr.key() == vector.at(i).id )
//        {
//            itr.value()++;
//        }
//        else
//        {
//            lists_likers_id[vector.at(i).id] = 1;
//        }

//    }

//    ui->pteResultUsername->clear();
//    ui->pteResultId->clear();

//    printMapToPlainText(lists_likers_username, ui->pteResultUsername );
//    printMapToPlainText(lists_likers_id, ui->pteResultId );
}

void InstaTools::printActiveLikers(QVector<insta_api::user> vector)
{
//    count_lists++;

//    for(int i = 0; i < vector.size(); i++)
//    {
//        QMap<QString, int>::iterator itr = lists_likers_username.find(vector.at(i).username);
//        if( itr.key() == vector.at(i).username )
//        {
//            itr.value()++;
//        }
//        else
//        {
//            lists_likers_username[vector.at(i).username] = 1;
//        }

//        itr = lists_likers_id.find(vector.at(i).id);
//        if( itr.key() == vector.at(i).id )
//        {
//            itr.value()++;
//        }
//        else
//        {
//            lists_likers_id[vector.at(i).id] = 1;
//        }

//    }

//    //Поиск минимального и максимального
//    int max_u = 0;
//    int max_i = 0;
//    QMap<QString, int>::iterator itr_u = lists_likers_username.begin();
//    QMap<QString, int>::iterator itr_i = lists_likers_id.begin();
//    for( ; itr_u != lists_likers_username.end() && itr_i != lists_likers_id.end(); itr_u++, itr_i++)
//    {
//        if(itr_u.value() > max_u )
//            max_u = itr_u.value();

//        if(itr_i.value() > max_i )
//            max_i = itr_i.value();
//    }

//    max_u = (int)(max_u * 0.8);
//    max_i = (int)(max_i * 0.8);

//    QVector<QString> ids;
//    QVector<QString> usernames;

//    itr_u = lists_likers_username.begin();
//    itr_i = lists_likers_id.begin();
//    for( ; itr_u != lists_likers_username.end() && itr_i != lists_likers_id.end(); itr_u++, itr_i++)
//    {
//        if(itr_u.value() >= max_u )
//            usernames.push_back( itr_u.key() );

//        if(itr_i.value() >= max_i )
//            ids.push_back( itr_i.key() );
//    }

//    ui->pteResultUsername->clear();
//    ui->pteResultId->clear();

//    ui->lRelResultUsername->setText( QString::number(count_lists) );
//    printVecotrToPlainText(usernames, ui->pteResultUsername );
//    printVecotrToPlainText(ids, ui->pteResultId );
}





void InstaTools::on_bConts_clicked()
{
//    ui->pteResultUsername->clear();
//    ui->pteResultId->clear();

//    QVector<QString> followers_uname = getVectorFromPlainText(ui->pteFollowersUsername);
//    QVector<QString> followers_id = getVectorFromPlainText(ui->pteFollowersId);
//    QVector<QString> follows_uname = getVectorFromPlainText(ui->pteFollowsUsername);
//    QVector<QString> follows_id = getVectorFromPlainText(ui->pteFollowsId);

//    QVector<QString> result_uname;
//    for(int i = 0; i < followers_uname.size() && i < follows_uname.size(); i++)
//    {
//        if(follows_uname.size() < followers_uname.size())
//        {
//            if( followers_uname.indexOf( follows_uname.at(i) ) != -1 )
//                result_uname.push_back( follows_uname.at(i) );
//        }
//        else
//        {
//            if( follows_uname.indexOf( followers_uname.at(i) ) != -1 )
//                result_uname.push_back( followers_uname.at(i) );
//        }
//    }

//    QVector<QString> result_id;
//    for(int i = 0; i < followers_id.size() && i < follows_id.size(); i++)
//    {
//        if(follows_uname.size() < followers_id.size())
//        {
//            if( followers_id.indexOf( follows_id.at(i) ) != -1 )
//                result_id.push_back( follows_id.at(i) );
//        }
//        else
//        {
//            if( follows_id.indexOf( followers_id.at(i) ) != -1 )
//                result_id.push_back( followers_id.at(i) );
//        }
//    }

//    printVecotrToPlainText(result_uname, ui->pteResultUsername);
//    printVecotrToPlainText(result_id, ui->pteResultId);
}

void InstaTools::on_bOthersFollows_clicked()
{
//    ui->pteResultUsername->clear();
//    ui->pteResultId->clear();

//    QVector<QString> followers_uname = getVectorFromPlainText(ui->pteFollowersUsername);
//    QVector<QString> followers_id = getVectorFromPlainText(ui->pteFollowersId);
//    QVector<QString> follows_uname = getVectorFromPlainText(ui->pteFollowsUsername);
//    QVector<QString> follows_id = getVectorFromPlainText(ui->pteFollowsId);

//    QVector<QString> result_uname;
//    for(int i = 0; i < followers_uname.size(); i++)
//    {
//        if( follows_uname.indexOf( followers_uname.at(i) ) == -1 )
//            result_uname.push_back( followers_uname.at(i) );
//    }

//    QVector<QString> result_id;
//    for(int i = 0; i < followers_id.size(); i++)
//    {
//        if( follows_id.indexOf( followers_id.at(i) ) == -1 )
//            result_id.push_back( followers_id.at(i) );
//    }

//    printVecotrToPlainText(result_uname, ui->pteResultUsername);
//    printVecotrToPlainText(result_id, ui->pteResultId);
}

void InstaTools::on_bOthersFollowers_clicked()
{
//    ui->pteResultUsername->clear();
//    ui->pteResultId->clear();

//    QVector<QString> followers_uname = getVectorFromPlainText(ui->pteFollowersUsername);
//    QVector<QString> followers_id = getVectorFromPlainText(ui->pteFollowersId);
//    QVector<QString> follows_uname = getVectorFromPlainText(ui->pteFollowsUsername);
//    QVector<QString> follows_id = getVectorFromPlainText(ui->pteFollowsId);

//    QVector<QString> result_uname;
//    for(int i = 0; i < follows_uname.size(); i++)
//    {
//        if( followers_uname.indexOf( follows_uname.at(i) ) == -1 )
//            result_uname.push_back( follows_uname.at(i) );
//    }

//    QVector<QString> result_id;
//    for(int i = 0; i < follows_id.size(); i++)
//    {
//        if( followers_id.indexOf( follows_id.at(i) ) == -1 )
//            result_id.push_back( follows_id.at(i) );
//    }

//    printVecotrToPlainText(result_uname, ui->pteResultUsername);
//    printVecotrToPlainText(result_id, ui->pteResultId);
}




