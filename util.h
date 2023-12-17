#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <limits>
#include <QRandomGenerator>

namespace Util
{
inline bool randomBool()
{
    return QRandomGenerator::global()->bounded(std::numeric_limits<int>::max()) % 2;
}

inline int randomItem(const std::vector<int> &collection)
{
    return collection[QRandomGenerator::global()->bounded(collection.size())];
}
} // end namespace Util

#endif // UTIL_H
