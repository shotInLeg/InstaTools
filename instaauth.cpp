#include "instatools.h"
#include "ui_instatools.h"

void InstaTools::getToken(QUrl url)
{
    if(!url.toString().contains("access_token"))
    {
        return;
    }

    url = url.toString().replace("#", "?");
    access_token = QUrlQuery(url).queryItemValue("access_token");

    ui->centralWidget->setWindowTitle("InstaTools [session: "+access_token+"]");
}


void InstaTools::on_bAuth_clicked()
{
    access_token = insta_api::authentiacation( ui->eLogin->text(), ui->ePassword->text() );


    if(access_token == "error")
    {
        ui->lAuthStatus1->setText("Вам не удалось авторизоваться");
        ui->lAuthStatus2->setText("Проверьте логин/пароль на корректность");
        return;
    }

    ui->lAuthStatus1->setText("Вы успешно авторизовались");
    ui->lAuthStatus2->setText(access_token);
}

