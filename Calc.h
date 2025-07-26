#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QList>
#include <QString>
#include <QChar>
#include <QDebug>
#include <QSizePolicy>
#include <QTimer>

class Calc: public QWidget
{

    Q_OBJECT  
    private:
    int SECONDS = 0;

    static QChar simvols[16];


    // QString _value;


    int HEIGHT = 600;
    int WIDTH = 400;

    QTimer* timer;

    QWidget* window;
    QLineEdit* field;
    QGridLayout* grid;

    QList<QPushButton*> actions;


    QPushButton* del;
    QPushButton* equal;

    private slots:
    void on_action(QChar& bttn);
    // void on_delete();

    
    void delete_pressed();
    void on_timeout();
    void delete_released();

    public:
    Calc();
};