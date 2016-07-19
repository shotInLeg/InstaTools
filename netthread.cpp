#include "instatools.h"
#include "ui_instatools.h"

void NetThread::addWork(method mthd, insta_api::account acc, QVector<QString> mth )
{
    api_methods.push_back( createItem( mthd, acc, mth ) );
}

void NetThread::run()
{
    for(int i = 0; i < api_methods.size(); i++)
    {
        method mthd = api_methods.at(i).mthd;
        insta_api::account acc = api_methods.at(i).acc;
        QVector<QString> params = api_methods.at(i).params;


        if( mthd == AUTH )
        {
            insta_api::account accn = insta_api::authentiacation( acc );

            emit finishAuth( accn );
            continue;
        }

        if( mthd == GET_FOLLOWS )
        {
            QVector<insta_api::user> follows = insta_api::getFollows( acc );

            emit finishGetFollows( follows );
        }
        else if( mthd == GET_FOLLOWERS )
        {
            QVector<insta_api::user> followers = insta_api::getFollowers( acc );

            emit finishGetFollowers( followers );
        }
        else if( mthd == GET_USER_FOLLOWS )
        {
            QString user_id = insta_api::getIdFromUsername( params.at(0), acc );

            QVector<insta_api::user> follows = insta_api::getUserFollows( user_id, acc );

            emit finishGetFollows( follows );
        }
        else if( mthd == GET_USER_FOLLOWERS )
        {
            QString user_id = insta_api::getIdFromUsername( params.at(0), acc );

            QVector<insta_api::user> followers = insta_api::getUserFollowers( user_id, acc );

            emit finishGetFollowers( followers );
        }
        else if( mthd == GET_TAGS )
        {
            QString tag = params.at(0);

            QVector<insta_api::media> media = insta_api::getHotList( tag, acc, 100);

            emit finishGetTags( media );
        }
        else if( mthd == SET_LIKE )
        {
            QString media_id = params.at(0);

            insta_api::setLike( media_id, acc );

            emit finishSetLike("");
        }
        else if( mthd == SET_FOLLOW )
        {
            QString user_id = params.at(0);

            insta_api::setFollow( user_id, acc );

            emit finishSetFollow("");
        }
        else if( mthd == GET_USER_MEDIA )
        {
            QString user_id = insta_api::getIdFromUsername( params.at(0), acc );

            QVector<insta_api::media> media = insta_api::getMediaList( user_id, acc );

            emit finishGetUserMedia( media );
        }
        else if( mthd == GET_MEDIA_LIKERS )
        {
            QString media_id = params.at(0);

            QVector<insta_api::user> users = insta_api::getMediaLikersList( media_id, acc );

            emit finishGetMediaLikers(users);
        }
    }
}

NetThread::queueItem NetThread::createItem(NetThread::method _mthd, insta_api::account _acc, const QVector<QString> &_params)
{
    queueItem qItem;

    qItem.mthd = _mthd;
    qItem.acc = _acc;
    qItem.params = _params;

    return qItem;
}
