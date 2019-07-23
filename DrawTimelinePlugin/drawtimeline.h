#ifndef DRAWTIMELINE_H
#define DRAWTIMELINE_H

#include <QtUiPlugin/QDesignerExportWidget>

#include <QWidget>
#include <QTime>
#include <QLabel>
#include <QString>
#include <QDateTime>
#include <QMap>

namespace Ui {
class DrawTimeline;
}

class QDESIGNER_WIDGET_EXPORT DrawTimeline : public QWidget
{
    Q_OBJECT

    struct TimeForDistance
    {
        int timestep;
        float pixelstep;
    };

public:
    struct TimeRange
    {
        QDateTime starttime;
        QDateTime endtime;
    };

    explicit DrawTimeline(QWidget *parent = 0);
    ~DrawTimeline();

    void setSizeLevel(int level);
    QDateTime getCurrentTime() {return m_currentDateTime;}
    void setTimeRangeInfo(QVector<TimeRange> timeRangeInfo);

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

private slots:
    void on_ptn_levelup_clicked();
    void on_ptn_leveldown_clicked();

private:
    Ui::DrawTimeline *ui;

    QDateTime m_pressDateTime;
    QDateTime m_currentDateTime;
    QLabel *m_midDisplayLabel;

    int m_pressPointX;
    bool m_isPressed;

    QVector< TimeForDistance> m_vecStep;
    int m_totleLevel;
    int m_sizeLevel;

    QVector<TimeRange> m_vecTimeRangeInfo;

private:
    void setStepLevel();
    void drawTimescale(QPainter &painter);
    void drawTimeRangeInfo();
};

#endif // DRAWTIMELINE_H
