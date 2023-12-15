#include "util.h"

#include <QRandomGenerator>
#include <limits>

bool Util::randomBool()
{
    return QRandomGenerator::global()->bounded(std::numeric_limits<int>::max()) % 2;
}

int Util::randomItem(const std::vector<int> &collection)
{
    const int index = QRandomGenerator::global()->bounded(collection.size());
    return collection[index];
}