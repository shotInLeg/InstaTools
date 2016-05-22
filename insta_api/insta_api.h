#ifndef INSTA_API_H
#define INSTA_API_H

#include <http_request/http_request.h>
#include <json/json.h>

namespace insta_api
{
    QMap<QString, QString> getCookieAuth(QString login, QString password );
    QString getInstToken( QMap<QString, QString> cookie );
    QString getTokenFromURL( QString url );

    QString authentiacation( QString login, QString password );


    struct media
    {
        QString id;
        QString create_time;
        QString owner_id;
        QString owner_username;
        QString url;
        int likes;
    };

    struct user
    {
        QString id;
        QString username;
        int count_likes;
        QVector<media> listPhoto;
    };

    struct account
    {
        QString username;
        QString password;
    };

    QVector<user> getFollows(QString access_token);
    QVector<user> getFollowers(QString access_token);
    QVector<user> getUserFollows(QString user_id, QString access_token);
    QVector<user> getUserFollowers(QString user_id, QString access_token);
    QVector<media> getMediaList(QString user_id, QString access_token);
    QVector<user> getMediaLikersList(QString media_id, QString access_token);
    void setLike (QString media_id, QString access_token );
    void setFollow( QString user_id, QString access_token );
    QString getIdFromUsername(QString username , QString access_token);
    QVector<media> getHotList(QString tag, QString access_token, int count);

}

#endif // INSTA_API_H
