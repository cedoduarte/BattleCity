#ifndef KEYHUD_H
#define KEYHUD_H

#include <QWidget>

namespace Ui
{
class KeyHUD;
}

class KeyHUD : public QWidget
{
    Q_OBJECT
public:
    explicit KeyHUD(QWidget *parent = nullptr);
    virtual ~KeyHUD();
    void loadData();
private slots:
    void on_up_comboBox_currentIndexChanged(int index);
    void on_down_comboBox_currentIndexChanged(int index);
    void on_left_comboBox_currentIndexChanged(int index);
    void on_right_comboBox_currentIndexChanged(int index);
    void on_shoot_comboBox_currentIndexChanged(int index);
private:
    Ui::KeyHUD *ui;
};

#endif // KEYHUD_H
