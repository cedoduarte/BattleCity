#include "namekey.h"

std::vector<NameKey> NameKey::s_keyMap;

NameKey::NameKey(const QString &name, int code)
{
    m_name = name;
    m_code = code;
    m_enabled = true;
}

NameKey::NameKey(const NameKey &other)
{
    m_name = other.m_name;
    m_code = other.m_code;
    m_enabled = other.m_enabled;
}

NameKey::NameKey()
{
    m_name = "";
    m_code = -1;
    m_enabled = true;
}

NameKey::~NameKey()
{
}

bool NameKey::match(int keyCode) const
{
    return m_enabled && m_code == keyCode;
}

int NameKey::code(const QString &name)
{
    for (const NameKey &nameKey : s_keyMap)
    {
        if (nameKey.m_name == name)
        {
            return nameKey.m_code;
        }
    }
    return -1;
}

QString NameKey::name(int code)
{
    for (const NameKey &nameKey : s_keyMap)
    {
        if (nameKey.m_code == code)
        {
            return nameKey.m_name;
        }
    }
    return "";
}

void NameKey::initializeKeyMap()
{
    s_keyMap.push_back(NameKey("A", Qt::Key_A));
    s_keyMap.push_back(NameKey("B", Qt::Key_B));
    s_keyMap.push_back(NameKey("C", Qt::Key_C));
    s_keyMap.push_back(NameKey("D", Qt::Key_D));
    s_keyMap.push_back(NameKey("E", Qt::Key_E));
    s_keyMap.push_back(NameKey("F", Qt::Key_F));
    s_keyMap.push_back(NameKey("G", Qt::Key_G));
    s_keyMap.push_back(NameKey("H", Qt::Key_H));
    s_keyMap.push_back(NameKey("I", Qt::Key_I));
    s_keyMap.push_back(NameKey("J", Qt::Key_J));
    s_keyMap.push_back(NameKey("K", Qt::Key_K));
    s_keyMap.push_back(NameKey("L", Qt::Key_L));
    s_keyMap.push_back(NameKey("M", Qt::Key_M));
    s_keyMap.push_back(NameKey("N", Qt::Key_N));
    s_keyMap.push_back(NameKey("O", Qt::Key_O));
    s_keyMap.push_back(NameKey("P", Qt::Key_P));
    s_keyMap.push_back(NameKey("Q", Qt::Key_Q));
    s_keyMap.push_back(NameKey("R", Qt::Key_R));
    s_keyMap.push_back(NameKey("S", Qt::Key_S));
    s_keyMap.push_back(NameKey("T", Qt::Key_T));
    s_keyMap.push_back(NameKey("U", Qt::Key_U));
    s_keyMap.push_back(NameKey("V", Qt::Key_V));
    s_keyMap.push_back(NameKey("W", Qt::Key_W));
    s_keyMap.push_back(NameKey("X", Qt::Key_X));
    s_keyMap.push_back(NameKey("Y", Qt::Key_Y));
    s_keyMap.push_back(NameKey("Z", Qt::Key_Z));
    s_keyMap.push_back(NameKey("UP", Qt::Key_Up));
    s_keyMap.push_back(NameKey("DOWN", Qt::Key_Down));
    s_keyMap.push_back(NameKey("LEFT", Qt::Key_Left));
    s_keyMap.push_back(NameKey("RIGHT", Qt::Key_Right));
    s_keyMap.push_back(NameKey("SPACE", Qt::Key_Space));
}

NameKey NameKey::getNameKey(int code)
{
    for (const NameKey &nameKey : s_keyMap)
    {
        if (nameKey.m_code == code)
        {
            return nameKey;
        }
    }
    return NameKey("", -1);
}

NameKey NameKey::getNameKey(const QString &name)
{
    for (const NameKey &nameKey : s_keyMap)
    {
        if (nameKey.m_name == name)
        {
            return nameKey;
        }
    }
    return NameKey("", -1);
}
