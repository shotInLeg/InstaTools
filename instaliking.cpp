#include "instatools.h"
#include "ui_instatools.h"

void InstaTools::on_bStartLiking_clicked()
{
    QVector<QString> id_media = getVectorFromPlainText(ui->pteListMediaToLIke);

    for(int i = 0; i < id_media.size(); i++)
    {
        insta_api::setLike( id_media.at(i), access_token );
    }
}
