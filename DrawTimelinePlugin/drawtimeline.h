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

private slots:
    void on_ptn_levelup_clicked();

    void on_ptn_leveldown_clicked();

private:
    Ui::DrawTimeline *ui;

    QDateTime m_pressDateTime;
    QDateTime m_currentDateTime;

    QLabel *m_displayLabel;
    QLabel *m_fixeDisplayLable;
    QString m_strVisibleValue;


    int m_pressPoint;
    bool m_isPressed;
    bool m_isOnce;

    int m_sizeLevel;
    QVector< TimeForDistance> m_vecStep;
    int m_totleLevel;

private:
    void drawTimescale(QPainter &painter);
};

#endif // DRAWTIMELINE_H
