#pragma once

#include <noether_gui/widgets.h>

namespace Ui
{
class RadiusOfCurvatureExtension;
}

namespace noether
{
/**
 * @ingroup gui_widgets_tool_path_modifiers
 */
struct RadiusOfCurvatureExtensionToolPathModifierWidget : public BaseWidget
{
public:
  RadiusOfCurvatureExtensionToolPathModifierWidget(QWidget* parent);

  void configure(const YAML::Node&) override;
  void save(YAML::Node&) const override;

protected:
  Ui::RadiusOfCurvatureExtension* ui_;
};

}  // namespace noether
