#include "Calc.h"


QChar Calc::simvols[16] = {'1', '2', '3', '+', '4', '5', '6', '-', '7', '8', '9', '*', '0', '/', '(', ')'};


Calc::Calc()
{
    window = new QWidget;
    window->setFixedSize(WIDTH, HEIGHT);
    window->setWindowTitle("Калькулятор");


    grid = new QGridLayout(window);


    field = new QLineEdit(window);
    field->setAlignment(Qt::AlignRight);
    field->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    grid->addWidget(field, 0, 0, 1, 3);


    del = new QPushButton("<", window);
    del->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // QObject::connect(del, SIGNAL(clicked()), this, SLOT(on_delete()));
    QObject::connect(del, SIGNAL(pressed()), this, SLOT(delete_pressed()));
    QObject::connect(del, SIGNAL(released()), this, SLOT(delete_released()));
    grid->addWidget(del, 0, 3);



    actions.reserve(16);

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            actions.push_back(new QPushButton(simvols[i * 4 + j], window));
            actions[i * 4 + j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            grid->addWidget(actions[i * 4 + j], i + 1, j);
            QObject::connect(actions[i * 4 + j], &QPushButton::clicked, this, [i, j, this](){this->on_action(Calc::simvols[i * 4 + j]);});
        }
    }

    equal = new QPushButton("=", window);
    equal->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    grid->addWidget(equal, 5, 0, 1, 4);


    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    // timer->setSingleShot(true);

    window->show();
}


void Calc::on_action(QChar& bttn)
{
    QString _value = field->text();
    _value.push_back(bttn);
    field->setText(_value);
}




void Calc::delete_pressed()
{
    timer->start(100);
}



void Calc::on_timeout()
{
    ++SECONDS;
    if (SECONDS >= 8)
    {
        field->clear();
        timer->stop();
        SECONDS = 0;
    }
}

void Calc::delete_released()
{
    if (SECONDS < 8){
        timer->stop();
        QString _value = field->text();
        _value.erase(_value.end() - 1);
        field->setText(_value);
        SECONDS = 0;
    }
}
