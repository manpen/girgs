
#pragma once

#include <vector>
#include <cmath>

#include <girgs/Node.h>
#include <girgs/SpatialTreeCoordinateHelper.h>


// TODO does each function need to be passed the level of the cell?
template<unsigned int D>
class WeightLayer {
public:

    WeightLayer() = delete;
    WeightLayer(unsigned int layer, unsigned int targetLevel, const SpatialTreeCoordinateHelper<D>& helper, std::vector<Node*>&& nodes);


    // helper functions from paper:
    // returns the number of points in a cell
    // PRECONDITION: cell must be of lower level than the target level
    //               i.e. cell index > first cell index in target level
    // begin = first descendant of cell in targetLevel
    // end = last child of cell in targetLevel
    // return how many points there are in cells {begin..end} using prefix sums
    int pointsInCell(unsigned int cell, unsigned int level) const; // maybe also give level of cell?

    // returns the k-th point in a cell
    // PRECONDITION: cell must be of lower level than the target level
    //               i.e. cell index > first cell index in target level (see n)
    // find first descendant of cell in target level and use m_A to find the point
    Node* kthPoint(unsigned int cell, unsigned int level, int k) const; // maybe also give level of cell?

protected:

    const unsigned int m_layer;             // the index of the layer
    const unsigned int m_target_level;      // the insertion level for the current weight layer (v(i) = wiw0/W)

    std::vector<Node*> m_nodes;             // all nodes of the current weight layer

    std::vector<int>   m_points_in_cell;    // the number of points in each cell of target_level
    std::vector<int>   m_prefix_sums;       // for each cell c in target level: the sum of points of this layer in all cells <c
    std::vector<Node*> m_A;                 // m_A[m_prefix_sums[i]+k] contains the k-th point in the i-th cell of target level
};


#include <girgs/WeightLayer.inl>