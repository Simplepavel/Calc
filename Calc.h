#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QList>
#include <QString>
#include <QChar>
#include <QDebug>
#include <QSizePolicy>
#include <QTimer>
#include <stack>
#include "MyLineEdit.h"
#include <iostream>

class Calc: public QWidget
{

    Q_OBJECT  
    private:
    int SECONDS = 0;

    static QChar simvols[16];
    static int table_action[6][8];


    // QString _value;


    int HEIGHT = 600;
    int WIDTH = 400;

    QTimer* timer;

    QWidget* window;
    MyLineEdit* field;
    QGridLayout* grid;

    QList<QPushButton*> actions;


    QPushButton* del;
    QPushButton* equal;

    private slots:
    
    void on_action(QChar& bttn);
    void delete_pressed();
    void on_timeout();
    void delete_released();
    QString to_polish();
    void calculated();
    int convert(const QChar& vl) const;
    
    public:
    Calc();
};