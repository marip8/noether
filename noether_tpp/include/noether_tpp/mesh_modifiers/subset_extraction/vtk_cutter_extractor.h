#pragma once

#include <noether_tpp/mesh_modifiers/subset_extraction/subset_extractor.h>

namespace noether
{
class VtkCutterExtractor : public SubMeshExtractor
{
public:
  pcl::PolygonMesh extract(const pcl::PolygonMesh& mesh, const Eigen::MatrixX3d& boundary) const override;
};

}  // namespace noether
