#include <noether_gui/widgets/raster_planner_widget.h>
#include "ui_raster_planner_widget.h"
#include <noether_gui/plugin_interface.h>
#include <noether_gui/widgets/collapsible_area_widget.h>
#include <noether_gui/utils.h>

#include <QMessageBox>

namespace noether
{
template <typename T>
static const T* findFirstWidgetOfType(const QWidget* container)
{
  // Attempt to cast the container to a collapsible area widget
  auto collapsible_area = dynamic_cast<const CollapsibleArea*>(container);
  if (!collapsible_area)
    throw std::runtime_error("Unexpected widget in container");

  // Try to find the first child widget of type T
  const T* widget;
  for (const QObject* obj : collapsible_area->getContentLayout()->children())
  {
    widget = dynamic_cast<const T*>(obj);
    if (widget)
      break;
  }

  if (!widget)
    throw std::runtime_error("Failed to find widget");

  return widget;
}

RasterPlannerWidget::RasterPlannerWidget(plugin_loader::PluginLoader&& loader, QWidget* parent)
  : ToolPathPlannerWidget(parent), loader_(std::move(loader)), ui_(new Ui::RasterPlanner())
{
  ui_->setupUi(this);

  // Populate the combo boxes
  ui_->combo_box_dir_gen->addItems(getAllAvailablePlugins<DirectionGeneratorWidgetPlugin>(loader_));
  ui_->combo_box_origin_gen->addItems(getAllAvailablePlugins<OriginGeneratorWidgetPlugin>(loader_));

  connect(ui_->combo_box_dir_gen, &QComboBox::currentTextChanged, [this](const QString& text) {
    if (text.isEmpty())
    {
      overwriteWidget(ui_->group_box_dir_gen->layout(), ui_->widget_dir_gen, new QWidget(this));
    }
    else
    {
      try
      {
        auto plugin = loader_.createInstance<DirectionGeneratorWidgetPlugin>(text.toStdString());

        auto layout = new QVBoxLayout();
        layout->addWidget(plugin->create(this));

        auto collapsible_area = new CollapsibleArea(text, this);
        collapsible_area->setContentLayout(layout);

        overwriteWidget(ui_->group_box_dir_gen->layout(), ui_->widget_dir_gen, collapsible_area);
      }
      catch (const std::exception& ex)
      {
        QMessageBox::warning(this, "Direction Generator Error", QString::fromStdString(ex.what()));
      }
    }
  });

  connect(ui_->combo_box_origin_gen, &QComboBox::currentTextChanged, [this](const QString& text) {
    if (text.isEmpty())
    {
      overwriteWidget(ui_->group_box_origin_gen->layout(), ui_->widget_origin_gen, new QWidget(this));
    }
    else
    {
      try
      {
        auto plugin = loader_.createInstance<OriginGeneratorWidgetPlugin>(text.toStdString());

        auto layout = new QVBoxLayout();
        layout->addWidget(plugin->create(this));

        auto collapsible_area = new CollapsibleArea(text, this);
        collapsible_area->setContentLayout(layout);

        overwriteWidget(ui_->group_box_origin_gen->layout(), ui_->widget_origin_gen, collapsible_area);
      }
      catch (const std::exception& ex)
      {
        QMessageBox::warning(this, "Origin Generator Error", QString::fromStdString(ex.what()));
      }
    }
  });
}

}  // namespace noether
