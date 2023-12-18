#ifndef NAMEKEY_H
#define NAMEKEY_H

#include <QString>
#include <vector>

class NameKey
{
public:
    NameKey(const QString &name, int code);
    NameKey(const NameKey &other);
    NameKey();
    virtual ~NameKey();
    void setName(const QString &name) { m_name = name; }
    QString name() const { return m_name; }
    void setCode(int code) { m_code = code; }
    int code() const { return m_code; }
    void setEnabled(bool enabled) { m_enabled = enabled; }
    void setDisabled(bool disabled) { m_enabled = !disabled; }
    bool isEnabled() { return m_enabled; }
    bool match(int keyCode) const { return m_enabled && m_code == keyCode; }
    static int code(const QString &name);
    static QString name(int code);
    static void initializeKeyMap();
    static const std::vector<NameKey>& keyMap() { return s_keyMap; }
    static NameKey getNameKey(int code);
    static NameKey getNameKey(const QString &name);
private:
    QString m_name;
    int m_code;
    bool m_enabled;
    static std::vector<NameKey> s_keyMap;
};

#endif // NAMEKEY_H
