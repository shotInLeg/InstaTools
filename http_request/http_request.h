#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <QByteArray>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>
#include <QNetworkCookieJar>
#include <QList>
#include <QNetworkCookie>
#include <QNetworkProxy>

namespace http_request
{
    QByteArray head( QString url, QMap<QString, QString> data );
    QByteArray get(QString url, QMap<QString, QString> data = QMap<QString, QString>() );
    QByteArray post( QString url, QMap<QString, QString> data );
    QMap<QString, QString> cookieFromURL( QString url );

    QByteArray get( QNetworkProxy::ProxyType proxy_type, QString proxy_ip, QString proxy_port, QString url, QMap<QString, QString> data = QMap<QString, QString>() );
    QByteArray post( QNetworkProxy::ProxyType proxy_type, QString proxy_ip, QString proxy_port, QString url, QMap<QString, QString> data );

}
#endif // HTTP_REQUEST_H
