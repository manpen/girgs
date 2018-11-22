
#pragma once

#include <vector>
#include <string>
#include <functional>

#include <girgs/girgs_api.h>
#include <girgs/Node.h>


// a generator that samples a GIRG in expected linear time and provides access to the result
// can be used multiple times
// if multiple graphs are generated with the same generator instance, the generation process implies the deletion of the previous graph
// accessors to graph data always refer to the last generated graph
// weightSeed and position seed should not be equal!
class GIRGS_API Generator
{
public:

    // init parameter
    void setWeights(const std::vector<double>& weights);
    void setWeights(int n, double ple, int weightSeed);
    void setPositions(const std::vector<std::vector<double>>& positions);
    void setPositions(int n, int dimension, int positionSeed);

    double scaleWeights(int desiredAvgDegree, int dimension, double alpha);

    // generate
    void generate(double alpha, int samplingSeed);
    void generateThreshold();
    // convenience
    const std::vector<Node>& generate(int n, int dimension, double ple, double alpha, int desiredAvgDegree, int weightSeed, int positionSeed, int samplingSeed);


    // access results
    const std::vector<Node>& graph() const {return m_graph;}
    double avg_degree() const;
    void saveDot(std::string file) const;
    // copy internal data for access
    std::vector<double> weights() const;
    std::vector<std::vector<double>> positions() const;

    // helper
    double estimateWeightScalingThreshold(const std::vector<double>& weights, int desiredAvgDegree, int dimension) const;
    double estimateWeightScaling(const std::vector<double>& weights, int desiredAvgDegree, int dimension, double alpha) const;

    double exponentialSearch(std::function<double(double)> f, double desiredValue, double accuracy = 0.02, double lower = 1.0, double upper = 2.0) const;

protected:

    std::vector<Node> m_graph;
};