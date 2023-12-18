#include "keycombobox.h"
#include "namekey.h"

KeyComboBox::KeyComboBox(QWidget *parent)
    : QComboBox(parent)
{
    populate();
    setEditable(true);
}

KeyComboBox::~KeyComboBox()
{
}

void KeyComboBox::populate()
{
    for (const NameKey &key : NameKey::keyMap())
    {
        addItem(key.name(), key.code());
    }
}

void KeyComboBox::setCurrentKey(int code)
{
    int index = -1;
    for (int i = 0; i < count(); i++)
    {
        if (itemData(i).toInt() == code)
        {
            index = i;
            break;
        }
    }
    setCurrentIndex(index);
}
