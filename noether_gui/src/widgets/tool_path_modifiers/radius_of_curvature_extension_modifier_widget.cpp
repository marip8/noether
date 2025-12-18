#include <noether_gui/widgets/tool_path_modifiers/radius_of_curvature_extension_modifier_widget.h>
#include "ui_radius_of_curvature_extension_modifier_widget.h"

#include <noether_tpp/serialization.h>

namespace noether
{
RadiusOfCurvatureExtensionToolPathModifierWidget::RadiusOfCurvatureExtensionToolPathModifierWidget(QWidget* parent)
  : BaseWidget(parent), ui_(new Ui::RadiusOfCurvatureExtension())
{
  ui_->setupUi(this);
}

void RadiusOfCurvatureExtensionToolPathModifierWidget::configure(const YAML::Node& config)
{
  ui_->double_spin_box_distance->setValue(YAML::getMember<double>(config, "distance"));
  ui_->double_spin_box_normal_offset_distance->setValue(YAML::getMember<double>(config, "normal_offset_distance"));
  ui_->check_box_extend_front->setChecked(YAML::getMember<bool>(config, "extend_front"));
  ui_->check_box_extend_back->setChecked(YAML::getMember<bool>(config, "extend_back"));
}

void RadiusOfCurvatureExtensionToolPathModifierWidget::save(YAML::Node& config) const
{
  config["name"] = "RadiusOfCurvatureExtension";
  config["distance"] = ui_->double_spin_box_distance->value();
  config["normal_offset_distance"] = ui_->double_spin_box_normal_offset_distance->value();
  config["extend_front"] = ui_->check_box_extend_front->isChecked();
  config["extend_back"] = ui_->check_box_extend_back->isChecked();
}

}  // namespace noether
