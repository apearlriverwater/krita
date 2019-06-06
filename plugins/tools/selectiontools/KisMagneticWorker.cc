/*
 *  Copyright (c) 2019 Kuntal Majumder <hellozee@disroot.org>
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; version 2.1 of the License.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "KisMagneticWorker.h"

#include "kis_gaussian_kernel.h"

#include <QtCore>
#include <boost/graph/astar_search.hpp>
#include <boost/functional/hash.hpp>
#include <boost/unordered_map.hpp>
#include "KisMagneticGraph.h"

struct VertexHash : std::unary_function<VertexDescriptor, std::size_t> {
  std::size_t operator()(VertexDescriptor const& u) const {
    std::size_t seed = 0;
    boost::hash_combine(seed, u.x);
    boost::hash_combine(seed, u.y);
    return seed;
  }
};

typedef boost::unordered_map<VertexDescriptor, VertexDescriptor, VertexHash> PredMap;
typedef boost::associative_property_map<PredMap> APredMap;

class AstarHeuristic : public boost::astar_heuristic<KisMagneticGraph, double> {
    private:
        APredMap m_pmap;
        VertexDescriptor m_goal;
        double coeff_a, coeff_b;

    public:
        AstarHeuristic(VertexDescriptor goal, APredMap pmap, double a, double b):
            m_pmap(pmap), m_goal(goal), coeff_a(a), coeff_b(b)
        { }

        AstarHeuristic(VertexDescriptor goal, APredMap pmap):
            m_pmap(pmap), m_goal(goal), coeff_a(0.5), coeff_b(0.5)
        { }

        double operator()(VertexDescriptor v){
            auto prev = m_pmap[v];
            double di = (m_goal.y - prev.y) * v.x + (m_goal.x - prev.x) * v.y;
            di = std::abs(di + prev.x * m_goal.y + prev.y * m_goal.x);
            auto dist = [](VertexDescriptor p1, VertexDescriptor p2){
                return std::sqrt(std::pow(p1.y-p2.y, 2) + std::pow(p1.x-p2.x, 2));
            };
            double dz = dist(prev, m_goal);
            di = di/dz;
            double dm = dist(v, m_goal);
            return coeff_a * di + coeff_b * (dm - dz);
        }
};

KisMagneticWorker::KisMagneticWorker():
    m_dev(0), m_rect(QRect())
{ }

KisMagneticWorker::KisMagneticWorker(KisPaintDeviceSP dev, const QRect &rect):
    m_dev(dev), m_rect(rect)
{ }

void KisMagneticWorker::run(KisPaintDeviceSP dev, const QRect &rect)
{
    KisGaussianKernel::applyLoG(dev, rect, 2, -1.0, QBitArray(), 0);
}

void KisMagneticWorker::computeEdge(QPoint start, QPoint end)
{
    Q_UNUSED(start)
    Q_UNUSED(end)
    KisGaussianKernel::applyLoG(m_dev, m_rect, 2, -1.0, QBitArray(), 0);
}