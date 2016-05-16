#ifndef INSTATOOLS_H
#define INSTATOOLS_H

#include <QMainWindow>
#include <QUrl>
#include <QUrlQuery>
#include <QTextBlock>
#include <QPlainTextEdit>
#include <QListWidget>
#include <insta_api/insta_api.h>

namespace Ui {
class InstaTools;
}

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

public slots:
    void getToken(QUrl url);

private:
    QVector<QString> getVectorFromPlainText(QPlainTextEdit* pte);
    QVector< QVector<QString> > getParsedVectorFromPlainText(QPlainTextEdit* pte);
    void printVecotrToPlainText(const QVector<QString> &vector, QPlainTextEdit* pte);
    void printVecotrToPlainText(const QVector<QPair<QString,QString> > &vector, QPlainTextEdit* pte);
    void printVecotrToListWidget(const QVector<QPair<QString,QString> > &vector, QListWidget* pte);



private:
    Ui::InstaTools *ui;

    QString access_token;
    QVector< QPair<QString, QString> > list_access_token;

};

#endif // INSTATOOLS_H
