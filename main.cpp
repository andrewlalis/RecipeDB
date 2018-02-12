#include "userInterface/mainwindow.h"
#include <QApplication>

#include "model/database/database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Database db("test.db");

    return a.exec();
}
