#include <Calc.h>


Calc::Calc()
{
    window = new QWidget;
    window->resize(WIDTH, HEIGHT);
    window->setWindowTitle("Калькулятор");

    grid = new QGridLayout(window);
    
}