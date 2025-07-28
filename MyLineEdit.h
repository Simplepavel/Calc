#include <QWidget>
#include <QLineEdit>
#include <QKeyEvent>

class MyLineEdit: public QLineEdit
{
    Q_OBJECT
    private:
    bool is_valiable(const QString& value) const;
    public:
    MyLineEdit(QWidget* parent = nullptr):QLineEdit(parent)
    {}
    ~MyLineEdit()
    {}
    void keyPressEvent(QKeyEvent*) override;
};
