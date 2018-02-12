#include "userInterface/mainwindow.h"
#include <QApplication>

#include "model/database/database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Database db("test.db");

    vector<RecipeIngredient> ri;
    ri.push_back(RecipeIngredient("flour", "grains", 3.0f, UnitOfMeasure("cup", "cups", "c")));



    Recipe rec("Example", ri, Instruction("Hello world"), QImage(), vector<RecipeTag>(), QDate::currentDate(), QTime(0, 30), QTime(0, 25), 10.0f);

    return a.exec();
}
