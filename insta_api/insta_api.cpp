#include "insta_api.h"
#include <QDebug>


QMap<QString, QString> insta_api::getCookieAuth( const insta_api::account& acc  )
{
    QNetworkProxy * proxy = insta_api::proxyFromAccount( acc );

    QUrl request_url("https://www.instagram.com/accounts/login/ajax/");

    QByteArray bytes;
    bytes.append("username="+acc.username+"&password="+acc.password);

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

    if( proxy != NULL )
        manager->setProxy( *proxy );

    QNetworkReply * reply = manager->post( request, bytes );

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


insta_api::account insta_api::getInstToken( QMap<QString, QString> cookie, const insta_api::account& acc )
{
    QNetworkProxy * proxy = insta_api::proxyFromAccount( acc );

    QUrl request_url("https://www.instagram.com/oauth/authorize/?client_id="+acc.app+"&redirect_uri=http://shotinleg.xyz/passcode.php&response_type=token&scope=comments+relationships+likes+public_content");

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
    QString ref = "https://www.instagram.com/oauth/authorize/?client_id="+acc.app+"&redirect_uri=http://shotinleg.xyz/passcode.php&response_type=token&scope=comments+relationships+likes+public_content";
    request.setRawHeader("Referer", QByteArray().append(ref) );
    request.setRawHeader("Cookie", cookie_header);
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded; charset=utf-8" );
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.93 Safari/537.36");
    request.setRawHeader("Content-Length", length );

    QNetworkAccessManager* manager = new QNetworkAccessManager();

    if( proxy != NULL )
        manager->setProxy( *proxy );

    QNetworkReply * reply = manager->post( request, bytes );

    QEventLoop wait;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
    QTimer::singleShot(300000, &wait, SLOT(quit()));

    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    wait.exec();

    QByteArray answer = reply->readAll();
    qDebug() << answer;

    reply->deleteLater();

    QString location = reply->header(QNetworkRequest::LocationHeader).toString();
    //qDebug() << location;

    QString token = tokenFromURL(location);


    account res_acc;

    res_acc.username = acc.username;
    res_acc.password = acc.password;
    res_acc.app = acc.app;
    res_acc.proxy_type = acc.proxy_type;
    res_acc.proxy_ip = acc.proxy_ip;
    res_acc.proxy_port = acc.proxy_type;
    res_acc.token = token;

    return res_acc;
}








//METHODS//

insta_api::account insta_api::authentiacation( const insta_api::account& acc )
{
    QMap<QString, QString> cookie = insta_api::getCookieAuth( acc );

    if(cookie["lastOperStatus"]=="false")
            return acc;

    return insta_api::getInstToken( cookie, acc );
}

QString insta_api::getIdFromUsername( const QString& username, const insta_api::account& acc )
{
    QMap<QString, QString> data;
    data["q"] = username;
    data["access_token"] = acc.token;

    QByteArray answer = insta_api::GET( "https://api.instagram.com/v1/users/search", data, acc );


    qDebug() << answer;

    if( answer.isEmpty() )
    {
        qDebug() << "Пустой ответ в instaAPI::getIdFromUsername()";
    }

    QVariantList usersList = QtJson::parse(answer).toMap().value("data").toList();
    for(int i = 0; i < usersList.size(); i++)
    {
        QVariantMap user = usersList[i].toMap();

        if( usersList[i].toMap().value("username").toString() == username )
        {
            QString id = user.value("id").toString();
            return id;
        }
    }
    return "-1";
}

QVector<insta_api::media> insta_api::getMediaList(  const QString& user_id,  const insta_api::account& acc )
{
    QMap<QString, QString> data;
    data["access_token"] = acc.token;

    QByteArray answer = insta_api::GET( "https://api.instagram.com/v1/users/"+user_id+"/media/recent/", data, acc );

    if( answer.isEmpty() )
    {
        qDebug() << "Пустой ответ в instaAPI::getMediaList()";
    }

    QVector<insta_api::media> medias;

    QVariantList mediaList = QtJson::parse(answer).toMap().value("data").toList();
    for(int i = 0; i < mediaList.size(); i++)
    {
        QVariantMap media = mediaList[i].toMap();
        QVariantMap media_user = mediaList[i].toMap().value("user").toMap();
        QVariantMap media_image = mediaList[i].toMap().value("images").toMap();

        insta_api::media md;

        md.id = media.value("id").toString();
        md.create_time = media.value("created_time").toString();
        md.likes = media.value("likes").toMap().value("count").toInt();

        md.owner_id = media_user.value("id").toString();
        md.owner_username = media_user.value("username").toString();

        md.url = media_image.value("low_resolution").toMap().value("url").toString();

        medias.push_back( md );
    }

    qDebug() << "COUNT PHOTO USER : " << medias.size();
    for(int i = 0; i < medias.size(); i++)
    {
        qDebug() << "PHOTO URL : " << medias.at(i).likes << " : " << medias.at(i).url;
    }

    return medias;
}

QVector<insta_api::media> insta_api::getHotList( const QString& tag, const insta_api::account& acc, int count)
{
    QMap<QString, QString> data;
    data["access_token"] = acc.token;
    data["count"] = QString::number(count);

    QByteArray answer = insta_api::GET( "https://api.instagram.com/v1/tags/"+tag+"/media/recent/", data, acc );

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
        QVariantMap media_image = mediaList[i].toMap().value("images").toMap();

        insta_api::media md;

        md.id = media.value("id").toString();
        md.create_time = media.value("created_time").toString();
        md.likes = media.value("likes").toMap().value("count").toInt();

        md.owner_id = media_user.value("id").toString();
        md.owner_username = media_user.value("username").toString();

        md.url = media_image.value("low_resolution").toMap().value("url").toString();


        medias.push_back( md );
    }

    return medias;
}

QVector<insta_api::user> insta_api::getFollows( const insta_api::account& acc )
{
    QMap<QString, QString> data;
    data["access_token"] = acc.token;

    QByteArray answer = insta_api::GET( "https://api.instagram.com/v1/users/self/follows", data, acc );

    if( answer.isEmpty() )
    {
        qDebug() << "Пустой ответ в insta_api::getFollows";
    }

    QVector<insta_api::user> users;
    QString next_url  = "1"; int c = 0;
    while(c < 1000000 && next_url != "")
    {
        QVariantList followsList = QtJson::parse(answer).toMap().value("data").toList();
        for(int i = 0; i < followsList.size(); i++)
        {
            QVariantMap fllw_map = followsList[i].toMap();
            insta_api::user fllw;

            fllw.id = fllw_map.value("id").toString();
            fllw.username = fllw_map.value("username").toString();;

            users.push_back( fllw );
        }

        next_url = QtJson::parse(answer).toMap().value("pagination").toMap().value("next_url").toString();
        answer = http_request::get( next_url );
        qDebug() << c << "   >    " << next_url;

        c++;
    }

    return users;
}

QVector<insta_api::user> insta_api::getFollowers( const insta_api::account& acc )
{
    QMap<QString, QString> data;
    data["access_token"] = acc.token;

    QByteArray answer = insta_api::GET( "https://api.instagram.com/v1/users/self/followed-by", data, acc );

    if( answer.isEmpty() )
    {
        qDebug() << "Пустой ответ в insta_api::getFollowers";
    }

    QVector<insta_api::user> users;
    QString next_url  = "1"; int c = 0;
    while(c < 1000000 && next_url != "")
    {
        QVariantList followsList = QtJson::parse(answer).toMap().value("data").toList();
        for(int i = 0; i < followsList.size(); i++)
        {
            QVariantMap fllw_map = followsList[i].toMap();
            insta_api::user fllw;

            fllw.id = fllw_map.value("id").toString();
            fllw.username = fllw_map.value("username").toString();;

            users.push_back( fllw );
        }

        next_url = QtJson::parse(answer).toMap().value("pagination").toMap().value("next_url").toString();
        answer = http_request::get( next_url );
        qDebug() << c << "   >    " << next_url;

        c++;
    }

    return users;
}

QVector<insta_api::user> insta_api::getUserFollows( const QString& user_id, const insta_api::account& acc)
{
    QMap<QString, QString> data;
    data["access_token"] = acc.token;

    QByteArray answer = insta_api::GET( "https://api.instagram.com/v1/users/"+user_id+"/follows", data, acc );

    if( answer.isEmpty() )
    {
        qDebug() << "Пустой ответ в insta_api::getUserFollows";
    }

    QVector<insta_api::user> users;
    QString next_url  = "1"; int c = 0;
    while(c < 1000000 && next_url != "")
    {
        QVariantList followsList = QtJson::parse(answer).toMap().value("data").toList();
        for(int i = 0; i < followsList.size(); i++)
        {
            QVariantMap fllw_map = followsList[i].toMap();
            insta_api::user fllw;

            fllw.id = fllw_map.value("id").toString();
            fllw.username = fllw_map.value("username").toString();;

            users.push_back( fllw );
        }

        next_url = QtJson::parse(answer).toMap().value("pagination").toMap().value("next_url").toString();
        answer = http_request::get( next_url );
        qDebug() << c << "   >    " << next_url;

        c++;
    }

    return users;
}

QVector<insta_api::user> insta_api::getUserFollowers( const QString& user_id, const insta_api::account& acc)
{
    QMap<QString, QString> data;
    data["access_token"] = acc.token;

    QByteArray answer = insta_api::GET( "https://api.instagram.com/v1/users/"+user_id+"/followed-by", data, acc );

    if( answer.isEmpty() )
    {
        qDebug() << "Пустой ответ в insta_api::getFollowers";
    }

    QVector<insta_api::user> users;
    QString next_url  = "1"; int c = 0;
    while(c < 1000000 && next_url != "")
    {
        QVariantList followsList = QtJson::parse(answer).toMap().value("data").toList();
        for(int i = 0; i < followsList.size(); i++)
        {
            QVariantMap fllw_map = followsList[i].toMap();
            insta_api::user fllw;

            fllw.id = fllw_map.value("id").toString();
            fllw.username = fllw_map.value("username").toString();;

            users.push_back( fllw );
        }

        next_url = QtJson::parse(answer).toMap().value("pagination").toMap().value("next_url").toString();
        answer = http_request::get( next_url );
        qDebug() << c << "   >    " << next_url;

        c++;
    }

    return users;
}

QVector<insta_api::user> insta_api::getMediaLikersList( const QString& media_id, const insta_api::account& acc)
{
    QMap<QString, QString> data;
    data["access_token"] = acc.token;

    QByteArray answer = insta_api::GET( "https://api.instagram.com/v1/media/"+media_id+"/likes", data, acc );

    if( answer.isEmpty() )
    {
        qDebug() << "Пустой ответ в insta_api::getMediaLikersList";
    }

    //qDebug() << answer;

    QVector<insta_api::user> users;
    QString next_url  = "1"; int c = 0;
    while(c < 100 && next_url != "")
    {
        QVariantList userList = QtJson::parse(answer).toMap().value("data").toList();
        for(int i = 0; i < userList.size(); i++)
        {
            QVariantMap user_map = userList[i].toMap();
            insta_api::user usr;

            usr.id = user_map.value("id").toString();
            usr.username = user_map.value("username").toString();;

            users.push_back( usr );
        }

        next_url = QtJson::parse(answer).toMap().value("pagination").toMap().value("next_url").toString();
        answer = http_request::get( next_url );
        qDebug() << c << "   >    " << next_url;

        c++;
    }

    return users;
}


void insta_api::setLike( const QString& media_id, const insta_api::account& acc)
{
    QMap<QString, QString> data;
    data["access_token"] = acc.token;

    QByteArray answer = insta_api::POST( "https://api.instagram.com/v1/media/"+media_id+"/likes", data, acc );

    if( answer.isEmpty() )
    {
        qDebug() << "Пустой ответ в instaAPI::setLike()";
    }
    if( !answer.contains("meta") )
    {
        qDebug() << "Неверный ответ в instaAPI::setLike()";
    }
}

void insta_api::setFollow( const QString& user_id, const insta_api::account& acc)
{
    QMap<QString, QString> data;
    data["access_token"] = acc.token;
    data["action"] = "follow";

    QByteArray answer = insta_api::POST( "https://api.instagram.com/v1/users/"+user_id+"/relationship", data, acc );

    qDebug() << QtJson::parse(answer).toMap().value("data").toMap().value("outgoing_status").toString();

    if( answer.isEmpty() )
    {
        qDebug() << "Пустой ответ в instaAPI::setFollow()";
    }
    if( !answer.contains("meta") )
    {
        qDebug() << "Неверный ответ в instaAPI::setFollow()";
    }
}









QNetworkProxy::ProxyType insta_api::proxyFromString( const QString& proxy_type )
{
    QNetworkProxy::ProxyType type = QNetworkProxy::DefaultProxy;

    if( proxy_type.size() <= 0 )
        return QNetworkProxy::DefaultProxy;

    if( proxy_type == "http" ||  proxy_type == "HTTP" )
        type = QNetworkProxy::HttpProxy;
    else if(  proxy_type == "socks5" ||  proxy_type == "SOCKS5" )
        type = QNetworkProxy::Socks5Proxy;

    return type;
}

QNetworkProxy* insta_api::proxyFromAccount( const insta_api::account& acc )
{
    QNetworkProxy * proxy = NULL;

    if( insta_api::proxyFromString(acc.proxy_type) != 0 && acc.proxy_ip != "" && acc.proxy_port != "" )
    {
        proxy = new QNetworkProxy();
        proxy->setType( insta_api::proxyFromString(acc.proxy_type) );
        proxy->setHostName( acc.proxy_ip );
        proxy->setPort( acc.proxy_port.toInt() );
    }

    return proxy;
}

QString insta_api::tokenFromURL( const QString& url)
{
    QString token = "";

    bool write = false;
    for(int i = 1; i < url.size(); i++ )
    {
        if( url.at(i-1) == '=' )
            write = true;

        if( url.at(i) == '?' || url.at(i) == '&'  )
            write = false;

        if( write )
            token += url.at(i);
    }

    return token;
}

QByteArray insta_api::GET( const QString& url, QMap<QString, QString> &data, const insta_api::account& acc)
{
    QByteArray answer = "";

    if( acc.proxy_type != "" && acc.proxy_ip != "" && acc.proxy_port != "" )
        answer = http_request::get( insta_api::proxyFromString(acc.proxy_type), acc.proxy_ip, acc.proxy_port, url, data );
    else
        answer = http_request::get( url, data );

    return answer;
}

QByteArray insta_api::POST( const QString& url, QMap<QString, QString> &data, const insta_api::account& acc)
{
    QByteArray answer = "";

    if( acc.proxy_type != "" && acc.proxy_ip != "" && acc.proxy_port != "" )
        answer = http_request::post( insta_api::proxyFromString(acc.proxy_type), acc.proxy_ip, acc.proxy_port, url, data );
    else
        answer = http_request::post( url, data );

    return answer;
}
