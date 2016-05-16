#include "insta_api.h"
#include <QDebug>

QString insta_api::authentiacation(QString login, QString password)
{
    QMap<QString, QString> cookie = insta_api::getCookieAuth( login, password );

    if(cookie["lastOperStatus"]=="false")
            return "error";

    return insta_api::getInstToken( cookie );
}


QMap<QString, QString> insta_api::getCookieAuth(QString login, QString password)
{
    QUrl request_url("https://www.instagram.com/accounts/login/ajax/");

    QByteArray bytes;
    bytes.append("username="+login+"&password="+password);

    QByteArray host;
    host.append( request_url.host() );

    QByteArray type;
    type.append( "application/x-www-form-urlencoded; charset=utf-8" );

    QByteArray length;
    length.append( QString::number( bytes.length() ) );

    QMap<QString, QString> instCookie = http_request::cookieFromURL("https://www.instagram.com/");
    QByteArray csrftoken;
    csrftoken.append( instCookie["csrftoken"] );

    QByteArray mid;
    mid.append("mid="+instCookie["mid"]+"; csrftoken="+instCookie["csrftoken"] );


    QNetworkRequest request;
    request.setUrl( request_url );
    request.setRawHeader("Host", "www.instagram.com" );
    request.setRawHeader("Referer", "https://www.instagram.com/" );
    request.setRawHeader("Cookie", mid);
    request.setRawHeader("Content-Type", type );
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.93 Safari/537.36");
    request.setRawHeader("Content-Length", length );

    request.setRawHeader("X-CSRFToken", csrftoken );
    request.setRawHeader("X-Instagram-AJAX", "1");
    request.setRawHeader("X-Requested-With", "XMLHttpRequest");



    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkReply* reply = manager->post( request, bytes );

    QEventLoop wait;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
    QTimer::singleShot(300000, &wait, SLOT(quit()));

    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    wait.exec();
    QByteArray answer = reply->readAll();
    reply->deleteLater();

    QString ans_str( answer );
    qDebug() << ans_str;

    QNetworkCookieJar * cookie = manager->cookieJar();
    QList<QNetworkCookie> listCookie = cookie->cookiesForUrl( request_url );


    QMap<QString, QString> result;

    if( !ans_str.contains("authenticated\": true") )
        result[ "lastOperStatus" ] = "false";
    else
        result[ "lastOperStatus" ] = "true";

    result[ "mid" ] = instCookie["mid"];
    for( int i = 0; i < listCookie.size(); i++ )
    {
        result[ listCookie.at(i).name() ] = listCookie.at(i).value();
    }

    return result;
}

QString insta_api::getInstToken(QMap<QString, QString> cookie)
{
    QUrl request_url("https://www.instagram.com/oauth/authorize/?client_id=471f9c538ce545649c9272a5d9a6492f&redirect_uri=http://instabot.ru/get_token.php&response_type=token&scope=comments+relationships+likes");

    QByteArray bytes;
    bytes.append("csrfmiddlewaretoken="+cookie["csrftoken"]+"&allow=Authorize");


    QByteArray length;
    length.append( QString::number( bytes.length() ) );

    QByteArray cookie_header;
    cookie_header.append("mid="+cookie["mid"]+"; csrftoken="+cookie["csrftoken"] + "; ds_user_id=" + cookie["ds_user_id"] + "; sessionid=" + cookie["sessionid"] );
    //qDebug() << "\nCookie: " << cookie_header;


    QNetworkRequest request;
    request.setUrl( request_url );
    request.setRawHeader("Host", "www.instagram.com" );
    request.setRawHeader("Referer", "https://www.instagram.com/oauth/authorize/?client_id=471f9c538ce545649c9272a5d9a6492f&redirect_uri=http://instabot.ru/get_token.php&response_type=token&scope=comments+relationships+likes" );
    request.setRawHeader("Cookie", cookie_header);
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded; charset=utf-8" );
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.93 Safari/537.36");
    request.setRawHeader("Content-Length", length );

    //request.setRawHeader("X-CSRFToken", csrftoken );
    //request.setRawHeader("X-Instagram-AJAX", "1");
    //request.setRawHeader("X-Requested-With", "XMLHttpRequest");



    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkReply* reply = manager->post( request, bytes );

    QEventLoop wait;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
    QTimer::singleShot(300000, &wait, SLOT(quit()));

    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    wait.exec();

    QByteArray answer = reply->readAll();
    //qDebug() << answer;

    reply->deleteLater();

    QString location = reply->header(QNetworkRequest::LocationHeader).toString();
    //qDebug() << location;

    QString token = getTokenFromURL(location);

    return token;
}

QString insta_api::getTokenFromURL(QString url)
{
    QString token = "";
    bool write = false;
    for(int i = 1; i < url.size(); i++ )
    {
        if( url.at(i-1) == '=' )
        {
            write = true;
        }
        if( url.at(i) == '?' || url.at(i) == '&'  )
        {
            write = false;
        }
        if( write )
        {
            token += url.at(i);
        }
    }

    return token;
}










void insta_api::setLike(insta_api::media ph, QString access_token)
{
    QMap<QString, QString> data;
    data["access_token"] = access_token;

    QByteArray answer = http_request::post("https://api.instagram.com/v1/media/"+ph.id+"/likes", data);

    if( answer.isEmpty() )
    {
        qDebug() << "Пустой ответ в instaAPI::setLike()";
    }
    if( !answer.contains("meta") )
    {
        qDebug() << "Неверный ответ в instaAPI::setLike()";
    }
}



QString insta_api::getIdFromUsername(QString username, QString access_token)
{
    QMap<QString, QString> data;
    data["q"] = username;
    data["access_token"] = access_token;
    QByteArray answer = http_request::get( "https://api.instagram.com/v1/users/search", data );

    //qDebug() << answer;

    if( answer.isEmpty() )
    {
        qDebug() << "Пустой ответ в instaAPI::getIdFromUsername()";
    }

    QVariantList usersList = QtJson::parse(answer).toMap().value("data").toList();
    for(int i = 0; i < usersList.size(); i++)
    {
        QVariantMap user = usersList[i].toMap();

        QString id = user.value("id").toString();

        return id;
    }

    return "-1";
}

QVector<insta_api::media> insta_api::getMediaList( insta_api::user user, QString access_token )
{
    QMap<QString, QString> data;
    data["access_token"] = access_token;

    QByteArray answer = http_request::get( "https://api.instagram.com/v1/users/"+user.id+"/media/recent/", data );

    if( answer.isEmpty() )
    {
        qDebug() << "Пустой ответ в instaAPI::getMediaList()";
    }

    QVector<insta_api::media> medias;

    QVariantList mediaList = QtJson::parse(answer).toMap().value("data").toList();
    for(int i = 0; i < mediaList.size(); i++)
    {
        QVariantMap media = mediaList[i].toMap();
        insta_api::media md;

        md.id = media.value("id").toString();
        md.create_time = media.value("created_time").toString();
        md.likes = 0;


        //check time need here
        medias.push_back( md );
    }

    for( int i = 0; i < medias.size(); ++i )
    {
        qDebug() << "{ id:" << medias.at(i).id;
        qDebug() << "  time:" << medias.at(i).create_time << " }";
    }

    return medias;
}

QVector<insta_api::media> insta_api::getHotList(QString tag, QString access_token, int count)
{
    QMap<QString, QString> data;
    data["access_token"] = access_token;
    data["count"] = QString::number(count);
    QByteArray answer = http_request::get( "https://api.instagram.com/v1/tags/"+tag+"/media/recent/", data );

    if( answer.isEmpty() )
    {
        qDebug() << "Пустой ответ в instaAPI::getHotList()";
    }

    qDebug() << answer;

    QVector<insta_api::media> medias;

    QVariantList mediaList = QtJson::parse(answer).toMap().value("data").toList();
    for(int i = 0; i < mediaList.size(); i++)
    {
        QVariantMap media = mediaList[i].toMap();
        QVariantMap media_user = mediaList[i].toMap().value("user").toMap();

        insta_api::media md;

        md.id = media.value("id").toString();
        md.create_time = media.value("created_time").toString();

        md.owner_id = media_user.value("id").toString();
        md.owner_username = media_user.value("username").toString();


        medias.push_back( md );
    }

    return medias;
}

QVector<insta_api::user> insta_api::getFollows(QString access_token)
{
    QMap<QString, QString> data;
    data["access_token"] = access_token;

    QByteArray answer = http_request::get( "https://api.instagram.com/v1/users/self/follows", data );

    if( answer.isEmpty() )
    {
        qDebug() << "Пустой ответ в insta_api::getFollows";
    }

    QVector<insta_api::user> users;

    QVariantList followsList = QtJson::parse(answer).toMap().value("data").toList();
    for(int i = 0; i < followsList.size(); i++)
    {
        QVariantMap fllw_map = followsList[i].toMap();
        insta_api::user fllw;

        fllw.id = fllw_map.value("id").toString();
        fllw.username = fllw_map.value("username").toString();;

        users.push_back( fllw );
    }

    return users;
}

QVector<insta_api::user> insta_api::getFollowers(QString access_token)
{
    QMap<QString, QString> data;
    data["access_token"] = access_token;

    QByteArray answer = http_request::get( "https://api.instagram.com/v1/users/self/followed-by", data );

    if( answer.isEmpty() )
    {
        qDebug() << "Пустой ответ в insta_api::getFollowers";
    }

    QVector<insta_api::user> users;

    QVariantList followsList = QtJson::parse(answer).toMap().value("data").toList();
    for(int i = 0; i < followsList.size(); i++)
    {
        QVariantMap fllw_map = followsList[i].toMap();
        insta_api::user fllw;

        fllw.id = fllw_map.value("id").toString();
        fllw.username = fllw_map.value("username").toString();;

        users.push_back( fllw );
    }

    return users;
}
