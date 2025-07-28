#include "Calc.h"

QChar Calc::simvols[16] = {'1', '2', '3', '+', '4', '5', '6', '-', '7', '8', '9', '*', '0', '/', '(', ')'};

int Calc::table_action[6][8] =
    {
        {0, 2, 2, 2, 2, 2, 6, 1},
        {4, 2, 2, 2, 2, 2, 4, 1},
        {4, 2, 2, 2, 2, 2, 4, 1},
        {4, 3, 3, 2, 2, 2, 4, 1},
        {4, 3, 3, 2, 2, 2, 4, 1},
        {6, 2, 2, 2, 2, 2, 5, 1}};

Calc::Calc()
{
    window = new QWidget;
    window->resize(WIDTH, HEIGHT);
    window->setWindowTitle("Калькулятор");

    grid = new QGridLayout(window);

    field = new MyLineEdit(window);
    field->setAlignment(Qt::AlignRight);
    field->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    grid->addWidget(field, 0, 0, 1, 3);

    del = new QPushButton("<", window);
    del->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
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
            QObject::connect(actions[i * 4 + j], &QPushButton::clicked, this, [i, j, this]()
                             { this->on_action(Calc::simvols[i * 4 + j]); });
        }
    }

    equal = new QPushButton("=", window);
    equal->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QObject::connect(equal, SIGNAL(clicked()), this, SLOT(calculated()));

    grid->addWidget(equal, 5, 0, 1, 4);

    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    // timer->setSingleShot(true);

    window->show();
}

void Calc::on_action(QChar &bttn)
{
    field->insert(bttn);
    // QString _value = field->text();
    // _value.push_back(bttn);
    // field->setText(_value);
    field->setFocus();
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
    if (SECONDS < 8)
    {
        timer->stop();
        field->backspace();
        // QString _value = field->text();
        // _value.erase(_value.end() - 1);
        // field->setText(_value);
        SECONDS = 0;
    }
    field->setFocus();
}

QString Calc::to_polish()
{
    std::stack<QChar> storage;
    QString input = field->text();
    QString result;
    QChar top_stack;
    QChar sign;
    result.reserve(input.length() * 2);
    int i = 0;
    while (i < input.length())
    {
        if (input[i].isDigit())
        {
            result.push_back(input[i]);
            ++i;
        }
        else
        {
            result.push_back(' '); // для отделения чисел
            if (storage.empty())
                top_stack = ' ';
            else
                top_stack = storage.top();
            sign = input[i];
            int idx1 = convert(top_stack);
            int idx2 = convert(sign);
            int act = table_action[idx1][idx2];
            std::cout << act << ' ';
            switch (act)
            {
            case (0):
                return result;
            case (1):
                break;
            case (2):
                storage.push(sign);
                ++i;
                break;
            case (3):
                result.push_back(storage.top());
                result.push_back(' ');
                storage.pop();
                storage.push(sign);
                ++i;
                break;
            case (4):
                result.push_back(storage.top());
                result.push_back(' ');
                storage.pop();
                break;
            case (5):
                storage.pop();
                ++i;
                break;
            case (6):
                throw "Error";
            }
        }
    }
    while (!storage.empty()) // конец строки
    {
        result.push_back(' ');
        top_stack = storage.top();
        int idx1 = convert(top_stack);
        int act = table_action[idx1][0];
        if (act == 4)
            result.push_back(top_stack);
        else
            throw "Error"; // 6
        storage.pop();
    }
    return result;
}

int Calc::convert(const QChar &vl) const
{
    switch (vl.toLatin1())
    {
    case (' '):
        return 0;
    case ('\n'):
        return 0;
    case ('+'):
        return 1;
    case ('-'):
        return 2;
    case ('*'):
        return 3;
    case ('/'):
        return 4;
    case ('('):
        return 5;
    case (')'):
        return 6;
    }
    return 0;
}

void Calc::calculated()
{
    QString polish = to_polish(); // польская нотация
    std::stack<int> storage;
    QString num;
    int idx = 0;
    int argv1;
    int argv2;
    int result;
    while (idx < polish.length())
    {
        if (polish[idx].isDigit())
        {
            num.push_back(polish[idx]);
        }
        else if (polish[idx] == ' ')
        {
            if (!num.isEmpty())
            {
                int value = num.toInt();
                storage.push(value);
                num.clear();
            }
        }
        else if (polish[idx] == '+')
        {

            argv1 = storage.top();
            storage.pop();
            argv2 = storage.top();
            storage.pop();
            result = argv1 + argv2;
            storage.push(result);
        }
        else if (polish[idx] == '-')
        {
            argv1 = storage.top();
            storage.pop();
            argv2 = storage.top();
            storage.pop();
            result = argv2 - argv1;
            storage.push(result);
        }
        else if (polish[idx] == '*')
        {
            argv1 = storage.top();
            storage.pop();
            argv2 = storage.top();
            storage.pop();
            result = argv1 * argv2;
            storage.push(result);
        }
        else if (polish[idx] == '/')
        {
            argv1 = storage.top();
            storage.pop();
            argv2 = storage.top();
            storage.pop();
            if (argv2 == 0)
            {
                throw "Error";
            }
            result = argv2 / argv1;
            storage.push(result);
        }
        ++idx;
    }
    QString ans = QString::number(storage.top());
    storage.pop();
    field->setText(ans);
    field->setFocus();
}