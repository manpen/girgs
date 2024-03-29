
#pragma once

#include <cassert>
#include <vector>

#include <hypergirgs/AngleHelper.h>
#include <hypergirgs/Point.h>

#include <hypergirgs/hypergirgs_api.h>


namespace hypergirgs {


class HYPERGIRGS_API RadiusLayer {
public:

	RadiusLayer() = delete;

	RadiusLayer(double r_min, double r_max, unsigned int targetLevel,
				const std::vector<int> &nodes, const std::vector<double> &angles,
				const std::vector<Point> &points);


    int pointsInCell(unsigned int cell, unsigned int level) const {
        auto cellBoundaries = levelledCell(cell, level);
        assert(cellBoundaries.first  + AngleHelper::firstCellOfLevel(level) < AngleHelper::firstCellOfLevel(m_target_level+1));
        assert(cellBoundaries.second + AngleHelper::firstCellOfLevel(level) < AngleHelper::firstCellOfLevel(m_target_level+1));

        return m_prefix_sums[cellBoundaries.second+1] - m_prefix_sums[cellBoundaries.first];
    }

    const Point& kthPoint(unsigned int cell, unsigned int level, int k) const {
        auto cellBoundaries = levelledCell(cell, level);
        return m_points[m_prefix_sums[cellBoundaries.first] + k];
    }

    const Point* firstPointPointer(unsigned int cell, unsigned int level) const {
        auto cellBoundaries = levelledCell(cell, level);
        return m_points.data() + m_prefix_sums[cellBoundaries.first];
    }

    std::pair<const Point*, const Point*> cellIterators(unsigned int cell, unsigned int level) const {
        auto cellBoundaries = levelledCell(cell, level);
        const auto* base = m_points.data();
        return {base + m_prefix_sums[cellBoundaries.first],
                base + m_prefix_sums[cellBoundaries.second+1]};
    }


public:
    const double m_r_min;
    const double m_r_max;
    const unsigned int m_target_level;

protected:
    std::vector<int>   m_prefix_sums;       ///< for each cell c in target level: the sum of points of this layer in all cells <c
    std::vector<Point> m_points; 			///< vector of points in this layer

    std::pair<unsigned int, unsigned int> levelledCell(unsigned int cell, unsigned int level) const {
        assert(level <= m_target_level);
        assert(AngleHelper::firstCellOfLevel(level) <= cell && cell < AngleHelper::firstCellOfLevel(level + 1)); // cell is from fromLevel

        // we want the begin-th and end-th cell in level targetLevel to be the first and last descendant of cell in this level
        // we could apply the firstChild function to find the first descendant but this is in O(1)
        auto descendants = AngleHelper::numCellsInLevel(m_target_level - level);
        auto localIndexCell = cell - AngleHelper::firstCellOfLevel(level);
        auto localIndexDescendant = localIndexCell * descendants; // each cell before the parent splits in 2^D cells in the next layer that are all before our descendant
        auto begin = localIndexDescendant;
        auto end = begin + descendants - 1;

        return {begin, end};
    }

};

} // namespace hypergirgs
