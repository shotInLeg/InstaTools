#include "instatools.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InstaTools w;
    w.show();

    return a.exec();
}
