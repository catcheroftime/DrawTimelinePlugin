#ifndef DRAWTIMELINE_H
#define DRAWTIMELINE_H

#include <QWidget>

#include <QtUiPlugin/QDesignerExportWidget>

namespace Ui {
class DrawTimeline;
}

class QDESIGNER_WIDGET_EXPORT DrawTimeline : public QWidget
{
    Q_OBJECT

public:
    explicit DrawTimeline(QWidget *parent = 0);
    ~DrawTimeline();

private:
    Ui::DrawTimeline *ui;
};

#endif // DRAWTIMELINE_H
