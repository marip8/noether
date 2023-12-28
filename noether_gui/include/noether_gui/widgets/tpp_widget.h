#pragma once

#include <noether_tpp/core/types.h>
#include <QWidget>
#include <vtkSmartPointer.h>

class QVTKWidget;
class vtkActor;
class vtkPolyDataMapper;
class vtkProp;
class vtkRenderer;
class vtkAxes;
class vtkTubeFilter;
class vtkAssembly;
class vtkPolyData;

namespace boost_plugin_loader
{
class PluginLoader;
}

namespace Ui
{
class TPP;
}

namespace noether
{
class ConfigurableTPPPipelineWidget;

/**
 * @brief Basic tool path planning widget
 * @details Allows the user to laod a mesh from file, configure a tool path planning pipeline, and generate tool paths
 * from the input mesh
 */
class TPPWidget : public QWidget
{
  Q_OBJECT
public:
  TPPWidget(boost_plugin_loader::PluginLoader loader, QWidget* parent = nullptr);

  /**
   * @brief Get the planned tool paths
   * @details The highest level vector represents the tool paths generated for each mesh "fragment" generated by the
   * mesh modifier in the tool path planning pipeline
   */
  std::vector<ToolPaths> getToolPaths();

  void setMeshFile(const QString& file);
  void setConfigurationFile(const QString& file);

private:
  void onLoadMesh(const bool /*checked*/);
  void onPlan(const bool /*checked*/);
  void onShowOriginalMesh(const bool);
  void onShowModifiedMesh(const bool);
  void onShowUnmodifiedToolPath(const bool);
  void onShowModifiedToolPath(const bool);

  Ui::TPP* ui_;
  ConfigurableTPPPipelineWidget* pipeline_widget_;

  // Viewer rendering
  QVTKWidget* render_widget_;
  vtkSmartPointer<vtkRenderer> renderer_;
  vtkSmartPointer<vtkPolyDataMapper> mesh_mapper_;
  vtkSmartPointer<vtkActor> mesh_actor_;

  vtkSmartPointer<vtkAssembly> tool_path_actor_;
  vtkSmartPointer<vtkAssembly> unmodified_tool_path_actor_;
  vtkSmartPointer<vtkAssembly> mesh_fragment_actor_;

  vtkSmartPointer<vtkAxes> axes_;
  vtkSmartPointer<vtkTubeFilter> tube_filter_;

  std::vector<ToolPaths> tool_paths_;
};

}  // namespace noether
