#include "statistics.hpp"

namespace miptlib
{

double sum(const std::vector<double>& data)
{
    double total = 0.0;

    for (double value : data)
    {
        total += value;
    }

    return total;
}

double mean(const std::vector<double>& data)
{
    if (data.empty())
    {
        return 0.0;
    }

    return sum(data) / data.size();
}

double variance(const std::vector<double>& data)
{
    if (data.empty())
    {
        return 0.0;
    }

    double m = mean(data);
    double var = 0.0;

    for (double value : data)
    {
        double diff = value - m;
        var += diff * diff;
    }

    return var / data.size();
}

}
