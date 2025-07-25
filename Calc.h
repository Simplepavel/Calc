#include <QWidget>
#include <QButtonGroup>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QList>


class Calc: public QWidget
{
    private:
    int HEIGHT = 500;
    int WIDTH = 400;

    QWidget* window;
    QTextEdit* field;
    QButtonGroup* box;
    QGridLayout grid;

    QList<QPushButton*> actions;


    QPushButton* del;
    QPushButton* equal;
}