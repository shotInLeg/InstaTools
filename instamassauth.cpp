#include "instatools.h"
#include "ui_instatools.h"

void InstaTools::on_bMassAuth_clicked()
{
    QVector< QVector<QString> > login_data = getParsedVectorFromPlainText(ui->pteLoginDataList);

    list_access_token.clear();
    for(int i = 0; i < login_data.size(); i++)
    {
        QString cur_access_token = insta_api::authentiacation( login_data[i][0], login_data[i][1] );
        list_access_token.push_back( {login_data[i][0],cur_access_token} );
    }

    ui->lwRelTokenList->clear();
    printVecotrToListWidget(list_access_token, ui->lwRelTokenList);
    printVecotrToPlainText(list_access_token, ui->pteTokenList);
}
