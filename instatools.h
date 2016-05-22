#ifndef INSTATOOLS_H
#define INSTATOOLS_H

#include <QMainWindow>
#include <QUrl>
#include <QUrlQuery>
#include <QTextBlock>
#include <QPlainTextEdit>
#include <QListWidget>
#include <QThread>
#include <insta_api/insta_api.h>

Q_DECLARE_METATYPE( QVector<insta_api::user> )
Q_DECLARE_METATYPE( QVector<insta_api::media> )

namespace Ui {
class InstaTools;
}

class NetThread : public QThread
{
    Q_OBJECT

public:
    explicit NetThread(){}
    ~NetThread(){}

    enum method {SET_LIKE, SET_FOLLOW, GET_FOLLOWS, GET_FOLLOWERS, GET_USER_FOLLOWS, GET_USER_FOLLOWERS, GET_TAGS, GET_USER_MEDIA, GET_MEDIA_LIKERS, AUTH };

    void setFlag( QVector< QPair<method, QVector<QString> > > mth );
    void run();

signals:
    void finished();
    void finishGetFollows(QVector<insta_api::user>);
    void finishGetFollowers(QVector<insta_api::user>);
    void finishGetTags(QVector<insta_api::media>);
    void finishGetUserMedia(QVector<insta_api::media>);
    void finishGetMediaLikers(QVector<insta_api::user>);
    void finishSetLike(QString);
    void finishSetFollow(QString);
    void finishAuth(QString);

private:
    QVector< QPair<method, QVector<QString> > > api_methods;
    QString access_token;
};

class InstaTools : public QMainWindow
{
    Q_OBJECT

public:
    explicit InstaTools(QWidget *parent = 0);
    ~InstaTools();

private slots:
    void on_bReloadHot_clicked();

    void on_lMenu_activated(const QModelIndex &index);

    void on_lMenu_currentRowChanged(int currentRow);

    void on_bAuth_clicked();

    void on_bLoadFollowList_clicked();

    void on_bConts_clicked();

    void on_bOthersFollows_clicked();

    void on_bOthersFollowers_clicked();

    void on_bAddNameToLName_clicked();

    void on_bShuffle_clicked();

    void on_bAddNumeric_clicked();

    void on_bMassAuth_clicked();

    void on_bStartLiking_clicked();

    void on_bRatingFollowers_clicked();

    void on_bActiveFollowers_clicked();

public slots:
    void getToken(QUrl url);
    void printVectorFollows( const QVector<insta_api::user> &vector );
    void printVectorFollowers(const QVector<insta_api::user> &vector );
    void printVectorTags(const QVector<insta_api::media> &vector );
    void saveAuthToken(QString);
    void saveSignleAuthToken(QString token);
    void loadMediaLikers( const QVector<insta_api::media> &vector );
    void loadMediaLikersActive( const QVector<insta_api::media> &vector );
    void countRatingLikers(QVector<insta_api::user> vector );
    void printActiveLikers(QVector<insta_api::user> vector );
private:
    QVector<QString> getVectorFromPlainText(QPlainTextEdit* pte);
    QVector< QVector<QString> > getParsedVectorFromPlainText(QPlainTextEdit* pte);
    void printVecotrToPlainText(const QVector<QString> &vector, QPlainTextEdit* pte);
    void printVecotrToPlainText(const QVector<QPair<QString,QString> > &vector, QPlainTextEdit* pte);
    void printVecotrToListWidget(const QVector<QPair<QString,QString> > &vector, QListWidget* pte);
    void printMapToPlainText(const QMap<QString,int>& map, QPlainTextEdit * pte);



private:
    Ui::InstaTools *ui;

    QString access_token;
    QVector< QPair<QString, QString> > list_access_token;

    int count_lists;
    QMap<QString, int> lists_likers_username;
    QMap<QString, int> lists_likers_id;

};

#endif // INSTATOOLS_H
