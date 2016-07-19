#ifndef INSTA_API_H
#define INSTA_API_H

#include <http_request/http_request.h>
#include <json/json.h>

namespace insta_api
{
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
        QString app;
        QString proxy_type;
        QString proxy_ip;
        QString proxy_port;
        QString token;
    };



    account             authentiacation         ( const account& acc );
    QVector<user>       getFollows              ( const account& acc);
    QVector<user>       getFollowers            ( const account& acc);
    QVector<user>       getUserFollows          (  const QString& user_id,  const account& acc );
    QVector<user>       getUserFollowers        (  const QString& user_id,  const account& acc );
    QVector<media>      getMediaList            (  const QString& user_id,  const account& acc );
    QVector<user>       getMediaLikersList      (  const QString& media_id,  const account& acc );
    void                setLike                 (  const QString& media_id,  const account& acc );
    void                setFollow               (  const QString& user_id,  const account& acc );
    QString             getIdFromUsername       (  const QString& username, const account& acc);
    QVector<media>      getHotList              (  const QString& tag,  const account& acc, int count);


    //Модифицированные функции HTTP запросов
    QByteArray                          GET(  const QString& url,  QMap<QString, QString>& data,  const account& acc );
    QByteArray                          POST(  const QString& url,  QMap<QString, QString>& data,  const account& acc );

    //Вспомогательные функции

    QNetworkProxy*                      proxyFromAccount        ( const account& acc );
    QNetworkProxy::ProxyType            proxyFromString         ( const QString& proxy_type );
    QString                             tokenFromURL            (  const QString& url );


    QMap<QString, QString>              getCookieAuth( const account& acc  );
    account                             getInstToken(QMap<QString, QString> cookie , const account& acc);


}

#endif // INSTA_API_H
