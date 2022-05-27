#pragma once

#include <QWidget>

class QParallelAnimationGroup;
class QGridLayout;
class QToolButton;
class QFrame;
class QScrollArea;

namespace noether
{
/**
 * @brief The CollapsibleArea class
 * @ref https://stackoverflow.com/questions/32476006/how-to-make-an-expandable-collapsable-section-widget-in-qt
 */
class CollapsibleArea : public QWidget
{
  Q_OBJECT
public:
  CollapsibleArea(QWidget* parent = nullptr);
  CollapsibleArea(const QString& label, QWidget* parent = nullptr);
  virtual ~CollapsibleArea();

  void setContentLayout(QLayout* layout);
  QLayout* getContentLayout() const;

private:
  QGridLayout* layout;
  QToolButton* tool_button;
  QFrame* line;
  QScrollArea* content;
  QParallelAnimationGroup* animation_;
};

}  // namespace noether
