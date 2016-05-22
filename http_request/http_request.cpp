#include "http_request.h"

QByteArray http_request::head(QString url, QMap<QString, QString> data)
{
    QString url_params = url;

    QMap<QString, QString>::iterator i = data.begin();
    for(; i != data.end(); i++)
    {
        if( !url_params.contains("?") )
        {
            url_params += "?";
        }
        else
        {
            url_params += "&";
        }
        url_params += i.key() + "=" + i.value();
    }

    qDebug() << url_params;


    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkReply* reply = manager->head( QNetworkRequest( QUrl(url_params) ) );

    QEventLoop wait;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
    QTimer::singleShot(300000, &wait, SLOT(quit()));

    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    wait.exec();
    QByteArray answer;
    //    /answer.append( reply->header(QNetworkRequest::CookieHeader) );
    reply->deleteLater();

    qDebug() << "      Cookie: " << reply->header(QNetworkRequest::CookieHeader);

    return answer;
}


QByteArray http_request::get(QString url, QMap<QString, QString> data )
{
    QString url_params = url;

    QMap<QString, QString>::iterator i = data.begin();
    for(; i != data.end(); i++)
    {
        if( !url_params.contains("?") )
        {
            url_params += "?";
        }
        else
        {
            url_params += "&";
        }
        url_params += i.key() + "=" + i.value();
    }

    //qDebug() << url_params;


    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkReply* reply = manager->get( QNetworkRequest( QUrl(url_params) ) );

    QEventLoop wait;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
    QTimer::singleShot(300000, &wait, SLOT(quit()));

    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    wait.exec();



    QByteArray answer = reply->readAll();
    reply->deleteLater();

    QNetworkCookieJar * cookie = manager->cookieJar();
    QList<QNetworkCookie> listCookie = cookie->cookiesForUrl( QUrl(url_params) );


    for( int i = 0; i < listCookie.size(); i++ )
    {
        //qDebug() << "Cookie " << i << ":" << listCookie.at(0).value();
    }

    //qDebug() << "  >" << answer;

    return answer;
}


QMap<QString, QString> http_request::cookieFromURL( QString url )
{
    QString url_params = url;

    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkReply* reply = manager->get( QNetworkRequest( QUrl(url_params) ) );

    QEventLoop wait;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
    QTimer::singleShot(300000, &wait, SLOT(quit()));

    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    wait.exec();
    reply->deleteLater();

    QNetworkCookieJar * cookie = manager->cookieJar();
    QList<QNetworkCookie> listCookie = cookie->cookiesForUrl( QUrl(url_params) );


    QMap<QString, QString> result;

    for( int i = 0; i < listCookie.size(); i++ )
    {
        result[ listCookie.at(i).name() ] = listCookie.at(i).value();
    }

    return result;
}

QByteArray http_request::post(QString url, QMap<QString, QString> data)
{
    QUrl request_url(url);
    QString boundary = "1BEF0A57BE110FD467A";
    QByteArray bytes;

    qDebug() << request_url;

    bytes.append("\r\n");
    QMap<QString, QString>::iterator i = data.begin();
    for(; i != data.end(); i++)
    {
        bytes.append("--" + boundary + "\r\n");
        bytes.append("Content-Disposition: form-data; name=\""+i.key()+"\"\r\n");
        bytes.append("\r\n");
        bytes.append(i.value()+"\r\n");
    }
    bytes.append("--" + boundary + "--" + "\r\n");


    QByteArray host;
    host.append( request_url.host() );

    QByteArray type;
    type.append( "multipart/form-data; boundary="+boundary+"" );

    QByteArray length;
    length.append( QString::number( bytes.length() ) );

    QNetworkRequest request;
    request.setUrl( request_url );
    request.setRawHeader("Host", host );
    request.setRawHeader("Referer", host );
    request.setRawHeader("Cookie", "income=1");
    request.setRawHeader("Content-Type", type );
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0");
    request.setRawHeader("Content-Length", length );

    request.setRawHeader("X-CSRFToken", "a4a221222d496385ffe044d1f572bb7e");
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

    qDebug() << answer;

    return answer;
}


