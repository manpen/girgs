
#pragma once

#include <vector>
#include <cmath>
#include <random>

#include <hypergirgs/hypergirgs_api.h>


namespace hypergirgs {

constexpr double PI = 3.14159265358979323846;

using default_random_engine = std::mt19937_64;

HYPERGIRGS_API double calculateRadius(int n, double alpha, double T, int deg);
HYPERGIRGS_API double hyperbolicDistance(double r1, double phi1, double r2, double phi2);

HYPERGIRGS_API std::vector<double> sampleRadii(int n, double alpha, double R, int seed);
HYPERGIRGS_API std::vector<double> sampleAngles(int n, int seed);
HYPERGIRGS_API std::vector<std::pair<int, int> > generateEdges(std::vector<double>& radii, std::vector<double>& angles, double T, double R, int seed = 0);

} // namespace hypergirgs
