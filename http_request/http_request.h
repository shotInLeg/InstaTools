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

namespace http_request
{
    QByteArray head( QString url, QMap<QString, QString> data );
    QByteArray get(QString url, QMap<QString, QString> data );
    QByteArray post( QString url, QMap<QString, QString> data );
    QMap<QString, QString> cookieFromURL( QString url );

}
#endif // HTTP_REQUEST_H
