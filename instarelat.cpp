#include "instatools.h"
#include "ui_instatools.h"


void InstaTools::on_bLoadFollowList_clicked()
{
    ui->pteFollowersUsername->clear();
    ui->pteFollowersId->clear();
    ui->pteFollowsUsername->clear();
    ui->pteFollowsId->clear();

    QString c_access_token = "";
    if( ui->lwRelTokenList->currentRow() >= 0 && ui->lwRelTokenList->currentRow() <= ui->lwRelTokenList->count() )
        c_access_token = list_access_token.at(ui->lwRelTokenList->currentRow()).second;
    else
        c_access_token = access_token;

    QVector<insta_api::user> followers = insta_api::getFollowers(c_access_token);
    for(int i = 0; i < followers.size(); i++)
    {
        ui->pteFollowersUsername->appendPlainText( followers.at(i).username );
        ui->pteFollowersId->appendPlainText( followers.at(i).id );
    }
    ui->lFollowers->setText("Подписчики: " + QString::number(followers.size()));

    QVector<insta_api::user> follows = insta_api::getFollows(c_access_token);
    for(int i = 0; i < follows.size(); i++)
    {
        ui->pteFollowsUsername->appendPlainText( follows.at(i).username );
        ui->pteFollowsId->appendPlainText( follows.at(i).id );
    }
    ui->lFollows->setText("Подписки: " + QString::number(follows.size()));
}

void InstaTools::on_bConts_clicked()
{
    ui->pteResultUsername->clear();
    ui->pteResultId->clear();

    QVector<QString> followers_uname = getVectorFromPlainText(ui->pteFollowersUsername);
    QVector<QString> followers_id = getVectorFromPlainText(ui->pteFollowersId);
    QVector<QString> follows_uname = getVectorFromPlainText(ui->pteFollowsUsername);
    QVector<QString> follows_id = getVectorFromPlainText(ui->pteFollowsId);

    QVector<QString> result_uname;
    for(int i = 0; i < followers_uname.size() && i < follows_uname.size(); i++)
    {
        if(follows_uname.size() < followers_uname.size())
        {
            if( followers_uname.indexOf( follows_uname.at(i) ) != -1 )
                result_uname.push_back( follows_uname.at(i) );
        }
        else
        {
            if( follows_uname.indexOf( followers_uname.at(i) ) != -1 )
                result_uname.push_back( followers_uname.at(i) );
        }
    }

    QVector<QString> result_id;
    for(int i = 0; i < followers_id.size() && i < follows_id.size(); i++)
    {
        if(follows_uname.size() < followers_id.size())
        {
            if( followers_id.indexOf( follows_id.at(i) ) != -1 )
                result_id.push_back( follows_id.at(i) );
        }
        else
        {
            if( follows_id.indexOf( followers_id.at(i) ) != -1 )
                result_id.push_back( followers_id.at(i) );
        }
    }

    printVecotrToPlainText(result_uname, ui->pteResultUsername);
    printVecotrToPlainText(result_id, ui->pteResultId);
}

void InstaTools::on_bOthersFollows_clicked()
{
    ui->pteResultUsername->clear();
    ui->pteResultId->clear();

    QVector<QString> followers_uname = getVectorFromPlainText(ui->pteFollowersUsername);
    QVector<QString> followers_id = getVectorFromPlainText(ui->pteFollowersId);
    QVector<QString> follows_uname = getVectorFromPlainText(ui->pteFollowsUsername);
    QVector<QString> follows_id = getVectorFromPlainText(ui->pteFollowsId);

    QVector<QString> result_uname;
    for(int i = 0; i < followers_uname.size(); i++)
    {
        if( follows_uname.indexOf( followers_uname.at(i) ) == -1 )
            result_uname.push_back( followers_uname.at(i) );
    }

    QVector<QString> result_id;
    for(int i = 0; i < followers_id.size(); i++)
    {
        if( follows_id.indexOf( followers_id.at(i) ) == -1 )
            result_id.push_back( followers_id.at(i) );
    }

    printVecotrToPlainText(result_uname, ui->pteResultUsername);
    printVecotrToPlainText(result_id, ui->pteResultId);
}

void InstaTools::on_bOthersFollowers_clicked()
{
    ui->pteResultUsername->clear();
    ui->pteResultId->clear();

    QVector<QString> followers_uname = getVectorFromPlainText(ui->pteFollowersUsername);
    QVector<QString> followers_id = getVectorFromPlainText(ui->pteFollowersId);
    QVector<QString> follows_uname = getVectorFromPlainText(ui->pteFollowsUsername);
    QVector<QString> follows_id = getVectorFromPlainText(ui->pteFollowsId);

    QVector<QString> result_uname;
    for(int i = 0; i < follows_uname.size(); i++)
    {
        if( followers_uname.indexOf( follows_uname.at(i) ) == -1 )
            result_uname.push_back( follows_uname.at(i) );
    }

    QVector<QString> result_id;
    for(int i = 0; i < follows_id.size(); i++)
    {
        if( followers_id.indexOf( follows_id.at(i) ) == -1 )
            result_id.push_back( follows_id.at(i) );
    }

    printVecotrToPlainText(result_uname, ui->pteResultUsername);
    printVecotrToPlainText(result_id, ui->pteResultId);
}

