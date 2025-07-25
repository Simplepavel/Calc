#include <QApplication>
#include "Calc.h"
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Calc clc;
    return app.exec();
}