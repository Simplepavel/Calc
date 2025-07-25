#include <QWidget>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QList>
#include <QString>
#include <QChar>
#include <QDebug>


class Calc: public QWidget
{
    private:

    QChar simvols[16] = {'1', '2', '3', '+', '4', '5', '6', '-', '7', '8', '9', '*', '0', '/', '(', ')'};


    int HEIGHT = 600;
    int WIDTH = 400;

    QWidget* window;
    QTextEdit* field;
    QGridLayout* grid;

    QList<QPushButton*> actions;


    QPushButton* del;
    QPushButton* equal;



    public:
    Calc();
};