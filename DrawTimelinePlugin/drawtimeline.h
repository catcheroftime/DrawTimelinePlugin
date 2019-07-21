#ifndef DRAWTIMELINE_H
#define DRAWTIMELINE_H

#include <QtUiPlugin/QDesignerExportWidget>

#include <QWidget>
#include <QTime>
#include <QLabel>
#include <QString>
#include <QDateTime>

namespace Ui {
class DrawTimeline;
}

class QDESIGNER_WIDGET_EXPORT DrawTimeline : public QWidget
{
    Q_OBJECT

public:
    struct TimeInfo {
        QTime starttime;
        QTime endtime;
    };

    explicit DrawTimeline(QWidget *parent = 0);
    ~DrawTimeline();

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

private:
    Ui::DrawTimeline *ui;

    QDateTime m_dateTime;

    QLabel *m_displayLabel;
    QLabel *m_fixeDisplayLable;
    QString m_strVisibleValue;

    float m_step;
    int m_stepTimevalue;
    float m_distance;
    int m_hisDistance;
    bool m_buttonIsPressed;
    bool m_isOnce;

private:
    void calcDistance();
    void setFixeDisplayNum();
};

#endif // DRAWTIMELINE_H
