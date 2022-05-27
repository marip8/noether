#include <noether_tpp/core/mesh_modifier.h>
#include <noether_tpp/core/tool_path_modifier.h>
#include <noether_tpp/core/tool_path_planner.h>
#include <noether_tpp/tool_path_planners/edge/edge_planner.h>
#include <noether_tpp/tool_path_planners/raster/raster_planner.h>
#include <noether_tpp/tool_path_planners/raster/direction_generators.h>
#include <noether_tpp/tool_path_planners/raster/origin_generators.h>
#include <noether_tpp/tool_path_planners/raster/plane_slicer_raster_planner.h>

#include <yaml-cpp/yaml.h>

namespace noether
{
struct FixedDirectionGeneratorPlugin : public DirectionGeneratorPlugin
{
  void initialize(const YAML::Node& config) override
  {
    double x = config["x"].as<double>();
    double y = config["y"].as<double>();
    double z = config["z"].as<double>();
    Eigen::Vector3d dir(x, y, z);
    dir.normalize();

    generator_ = std::make_unique<FixedDirectionGenerator>(dir);
  }
};

struct PrincipalAxisDirectionGeneratorPlugin : public DirectionGeneratorPlugin
{
  void initialize(const YAML::Node& config) override
  {
    generator_ = std::make_unique<PrincipalAxisDirectionGenerator>(config["rotation_offset"].as<double>());
  }
};

struct FixedOriginGeneratorPlugin : public OriginGeneratorPlugin
{
public:
  void initialize(const YAML::Node& config) override final
  {
    double x = config["x"].as<double>();
    double y = config["y"].as<double>();
    double z = config["z"].as<double>();
    generator_ = std::make_unique<FixedOriginGenerator>(Eigen::Vector3d(x, y, z));
  }
};

struct CentroidOriginGeneratorPlugin : public OriginGeneratorPlugin
{
public:
  void initialize(const YAML::Node&) override final { generator_ = std::make_unique<CentroidOriginGenerator>(); }
};

struct AABBCenterOriginGeneratorPlugin : public OriginGeneratorPlugin
{
public:
  void initialize(const YAML::Node&) override final { generator_ = std::make_unique<AABBCenterOriginGenerator>(); }
};

class OffsetOriginGeneratorPlugin : public OriginGeneratorPlugin
{
public:
  void initialize(const YAML::Node& config) override final
  {
    const YAML::Node offset_config = config["offset"];
    double x = offset_config["x"].as<double>();
    double y = offset_config["y"].as<double>();
    double z = offset_config["z"].as<double>();

    // Load the origin generator plugin
    OriginGenerator::ConstPtr origin_gen;

    generator_ = std::make_unique<OffsetOriginGenerator>(std::move(origin_gen), Eigen::Vector3d(x, y, z));
  }

  // private:
  //  plugin_loader::PluginLoader loader;
};

class RasterPlannerPlugin : public ToolPathPlannerPlugin
{
  void initialize(const YAML::Node& config) override final
  {
    const YAML::Node tpp_config = config["params"];

    // Load the direction generator plugin
    DirectionGeneratorPlugin::ConstPtr dir_gen;

    // Load the origin generator plugin
    OriginGeneratorPlugin::ConstPtr origin_gen;

    initializeImpl(tpp_config, std::move(dir_gen), std::move(origin_gen));

    auto raster_tpp = dynamic_cast<RasterPlanner*>(tpp_.get());
    if (!raster_tpp)
      throw std::runtime_error("Initialized planner does not inherit from raster planner");

    raster_tpp->setPointSpacing(tpp_config["point_spacing"].as<double>());
    raster_tpp->setLineSpacing(tpp_config["line_spacing"].as<double>());
    raster_tpp->setMinHoleSize(tpp_config["min_hole_size"].as<double>());
  }

  virtual void initializeImpl(const YAML::Node& config,
                              DirectionGenerator::ConstPtr&& dir_gen,
                              OriginGenerator::ConstPtr&& origin_gen) = 0;

  // protected:
  //  plugin_loader::PluginLoader loader;
};

class EdgePlannerPlugin : public ToolPathPlannerPlugin
{
public:
  void initialize(const YAML::Node& config) override final
  {
    initializeImpl(config);
    auto edge_planner = dynamic_cast<EdgePlanner*>(tpp_.get());
    if (!edge_planner)
      throw std::runtime_error("Planner does not inherit from edge planner");

    //    edge_planner->setPointSpacing(config["point_spacing"].as<double>());
  }

  virtual void initializeImpl(const YAML::Node& config) = 0;
};

struct PlaneSlicerRasterPlannerPlugin : public RasterPlannerPlugin
{
  void initializeImpl(const YAML::Node& config,
                      DirectionGenerator::ConstPtr&& dir_gen,
                      OriginGenerator::ConstPtr&& origin_gen) override final
  {
    tpp_ = std::make_unique<PlaneSlicerRasterPlanner>(std::move(dir_gen), std::move(origin_gen));
    auto ps = static_cast<PlaneSlicerRasterPlanner*>(tpp_.get());
    ps->setSearchRadius(config["search_radius"].as<double>());
    ps->setMinSegmentSize(config["min_segment_size"].as<double>());
  }
};

}  // namespace noether
