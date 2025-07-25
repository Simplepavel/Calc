#include "Calc.h"


Calc::Calc()
{

    
    window = new QWidget;
    window->setFixedSize(WIDTH, HEIGHT);
    window->setWindowTitle("Калькулятор");


    grid = new QGridLayout(window);


    field = new QTextEdit(window);
    field->setAlignment(Qt::AlignRight);

    grid->addWidget(field, 0, 0, 1, 3);


    del = new QPushButton("<", window);
    grid->addWidget(del, 0, 3);



    actions.reserve(16);

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            actions.push_back(new QPushButton(simvols[i * 4 + j], window));
            grid->addWidget(actions[i * 4 + j], i + 1, j + 1);
            // QObject::connect(actions[i * 4 + j], QPushButton::clicked, this, [](){on_action(actions[i * 4 + j]);});
        }
    }

    equal = new QPushButton("=", window);
    grid->addWidget(equal, 5, 0, 1, 4);

    window->show();
}