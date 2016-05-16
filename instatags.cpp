#include "instatools.h"
#include "ui_instatools.h"

void InstaTools::on_bReloadHot_clicked()
{
    ui->pteIdsHot->clear();
    ui->pteMediaIdsHot->clear();
    ui->pteUsernamesHot->clear();

    QVector<QString> tags;
    for(int i = 0; i < ui->pteTagsForSearch->document()->lineCount(); i++)
    {
        QString current_tag = ui->pteTagsForSearch->document()->findBlockByLineNumber(i).text();
        tags.append( current_tag );
    }

    ui->lCountTags->setText("Считано: " + QString::number(tags.size()));

    int count_results = 0;
    for(int i = 0; i < tags.size(); i++)
    {
        QVector<insta_api::media> list = insta_api::getHotList(tags.at(i), access_token, 200);
        for(int i = 0; i < list.size(); i++)
        {
            ui->pteMediaIdsHot->appendPlainText(list.at(i).id);
            ui->pteUsernamesHot->appendPlainText(list.at(i).owner_username);
            ui->pteIdsHot->appendPlainText(list.at(i).owner_id);
        }
        count_results += list.size();
    }

    ui->lCountMedia->setText("Загружено: " + QString::number(count_results));
}
