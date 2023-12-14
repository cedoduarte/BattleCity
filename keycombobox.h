#ifndef KEYCOMBOBOX_H
#define KEYCOMBOBOX_H

#include <QComboBox>

class KeyComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit KeyComboBox(QWidget *parent = nullptr);
    virtual ~KeyComboBox();
    void setCurrentKey(int code);
    void setCurrentKey(const QString &name);
};

#endif // KEYCOMBOBOX_H
