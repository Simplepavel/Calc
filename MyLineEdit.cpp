#include "MyLineEdit.h"

void MyLineEdit::keyPressEvent(QKeyEvent* event)
{
    if (is_valiable(event->text()))
    {
        QLineEdit::keyPressEvent(event);
    }
    event->ignore();
}

bool MyLineEdit::is_valiable(const QString& vl) const
{
    bool result = false;
    if ((QChar('0') <= vl && vl <= QChar('9')))
    {
        result = true;
    }
    if (vl == '+' || vl == '-' || vl == ')')
    {
        result = true;
    }
    if (vl == '*' || vl == '/' || vl == '(')
    {
        result = true;
    }
    return result;
}