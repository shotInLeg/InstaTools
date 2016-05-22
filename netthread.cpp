#include "instatools.h"
#include "ui_instatools.h"

void NetThread::setFlag(QVector< QPair<method, QVector<QString> > > mth )
{
    api_methods = mth;
}

void NetThread::run()
{
    for(int i = 0; i < api_methods.size(); i++)
    {
        if( api_methods.at(i).first == AUTH )
        {
            QString login = api_methods.at(i).second.at(0);
            QString password = api_methods.at(i).second.at(1);

            QString token = insta_api::authentiacation( login, password );

            emit finishAuth(token);
            continue;
        }

        QString access_token = api_methods.at(i).second.at(0);

        if( api_methods.at(i).first == GET_FOLLOWS )
        {
            QVector<insta_api::user> follows = insta_api::getFollows( access_token );

            emit finishGetFollows(follows);
        }
        else if( api_methods.at(i).first == GET_FOLLOWERS )
        {
            QVector<insta_api::user> followers = insta_api::getFollowers( access_token );

            emit finishGetFollowers(followers);
        }
        else if( api_methods.at(i).first == GET_USER_FOLLOWS )
        {
            QString user_id = insta_api::getIdFromUsername( api_methods.at(i).second.at(1), access_token);

            QVector<insta_api::user> follows = insta_api::getUserFollows(user_id, access_token );

            emit finishGetFollows(follows);
        }
        else if( api_methods.at(i).first == GET_USER_FOLLOWERS )
        {
            QString user_id = insta_api::getIdFromUsername( api_methods.at(i).second.at(1), access_token);

            QVector<insta_api::user> followers = insta_api::getUserFollowers(user_id, access_token );

            emit finishGetFollowers(followers);
        }
        else if( api_methods.at(i).first == GET_TAGS )
        {
            QString tag = api_methods.at(i).second.at(1);

            QVector<insta_api::media> media = insta_api::getHotList( tag, access_token, 100);

            emit finishGetTags(media);
        }
        else if( api_methods.at(i).first == SET_LIKE )
        {
            QString media_id = api_methods.at(i).second.at(1);

            insta_api::setLike( media_id, access_token );

            emit finishSetLike("");
        }
        else if( api_methods.at(i).first == SET_FOLLOW )
        {
            QString user_id = api_methods.at(i).second.at(1);

            insta_api::setFollow( user_id, access_token );

            emit finishSetFollow("");
        }
        else if( api_methods.at(i).first == GET_USER_MEDIA )
        {
            QString user_id = insta_api::getIdFromUsername( api_methods.at(i).second.at(1), access_token);

            QVector<insta_api::media> media = insta_api::getMediaList( user_id, access_token );

            emit finishGetUserMedia(media);
        }
        else if( api_methods.at(i).first == GET_MEDIA_LIKERS )
        {
            QString media_id = api_methods.at(i).second.at(1);

            QVector<insta_api::user> users = insta_api::getMediaLikersList(media_id, access_token );

            emit finishGetMediaLikers(users);
        }
    }

     emit finished();
}
