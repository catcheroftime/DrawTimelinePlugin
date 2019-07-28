#include "drawtimeline.h"
#include "ui_drawtimeline.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QFont>

#define RECTY 60
#define CURSORHEIGTH 50
#define RECTHEIGH 10

DrawTimeline::DrawTimeline(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawTimeline)
  , m_currentDateTime(QDateTime::currentDateTime())
  , m_sizeLevel(0)
{
    ui->setupUi(this);
    this->setMouseTracking(true);

    // 设置时间轴时间单位和像素的步长关系
    setStepLevel();

    // 设置中间显示时间的Label和放缩等级按键的样式
    m_midDisplayLabel = new QLabel(this);
    m_midDisplayLabel->setFixedSize(QSize(150,22));
    m_midDisplayLabel->setAlignment(Qt::AlignCenter);
    m_midDisplayLabel->setStyleSheet("background:rgba(255,255,255,0);color:rgb(255,255,255);font:12px \"Microsoft YaHei\"");

    ui->ptn_levelup->setStyleSheet("QPushButton{background:rgba(255,255,255,0); color:rgb(255,255,255); font-size:12px}"
                                   "QPushButton:hover{font-size:14px}"
                                   "QPushButton:pressed{font-size:10px}");

    ui->ptn_leveldown->setStyleSheet("QPushButton{background:rgba(255,255,255,0); color:rgb(255,255,255); font-size:12px}"
                                     "QPushButton:hover{font-size:14px}"
                                     "QPushButton:pressed{font-size:10px}");
}

DrawTimeline::~DrawTimeline()
{
    delete ui;
}

void DrawTimeline::setSizeLevel(int level)
{
    if (level>=0 && level<=m_totleLevel-1) {
        m_sizeLevel = level;
        update();
    }  else {
        qDebug() << "设置显示的系数有误";
    }
}

void DrawTimeline::setTimeRangeInfo(QVector<DrawTimeline::TimeRange> timeRangeInfo)
{
    m_vecTimeRangeInfo = timeRangeInfo;
    if (!timeRangeInfo.isEmpty()) {
        m_currentDateTime = m_vecTimeRangeInfo.at(0).starttime;
    }
    update();
}

void DrawTimeline::setStepLevel()
{
    m_vecStep.append({12*60*60,50.0});
    m_vecStep.append({6*60*60,60.0});
    m_vecStep.append({2*60*60,70.0});
    m_vecStep.append({1*60*60,80.0});
    m_vecStep.append({30*60,90.0});
    m_vecStep.append({10*60,100.0});
    m_vecStep.append({5*60,110.0});
    m_vecStep.append({1*60,120.0});
    m_totleLevel = m_vecStep.size();
}


void DrawTimeline::paintEvent(QPaintEvent *)
{
    // 绘制黑色的背景
    QPainter painter(this);
    painter.setBrush(QColor{50,50,50});
    painter.drawRect(rect());

    // 绘制时间刻度
    drawTimescale(painter);

    // 绘制中间的游标
    drawTimeCursor(painter);

    // 显示中间位置时间
    m_midDisplayLabel->setText(m_currentDateTime.toString("yyyy-MM-dd hh:mm:ss"));
    m_midDisplayLabel->move(this->size().width()/2-m_midDisplayLabel->width()/2-5,10);

    // 绘制具体的时间数据
    drawTimeRangeInfo();
}

void DrawTimeline::mousePressEvent(QMouseEvent *event)
{
    m_isPressed = true;
    m_pressDateTime = m_currentDateTime;
    m_pressPointX = event->pos().x();
    QWidget::mousePressEvent(event);
}

void DrawTimeline::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
    QWidget::mouseReleaseEvent(event);
}

void DrawTimeline::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPressed) {
        int move_length = event->pos().x() - m_pressPointX;
        float secs = m_vecStep.at(m_sizeLevel).timestep/m_vecStep.at(m_sizeLevel).pixelstep;
        m_currentDateTime = m_pressDateTime.addSecs(-secs*move_length);
    }
    update();
}

void DrawTimeline::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
        on_ptn_levelup_clicked();
    else
        on_ptn_leveldown_clicked();

    QWidget::wheelEvent(event);
}

void DrawTimeline::drawTimescale(QPainter &painter)
{
    // 绘制容纳时间的矩形
    painter.setPen( QColor{150,150,150});
    painter.drawRect(-1,RECTY,this->width()+40,RECTHEIGH);

    float pixelstep = m_vecStep.at(m_sizeLevel).pixelstep;
    int timestep = m_vecStep.at(m_sizeLevel).timestep;
    float secsper = timestep/pixelstep;

    QDateTime timeline_starttime =  m_currentDateTime.addSecs(-( this->width()/2)*secsper);
    int timeH = timeline_starttime.time().hour();
    int timeM = timeline_starttime.time().minute();
    int timeS = timeline_starttime.time().second();
    int second = timeH*3600+timeM*60+timeS;

    int drawstarttime = (second/timestep+1)*timestep - second;
    int startPosition = drawstarttime / secsper;

    QDateTime show_starttime = timeline_starttime.addSecs(drawstarttime);
    QFont font{"\"Microsoft YaHei\"",8,57};
    int count  = this->size().width() / pixelstep;
    for (int i = 0; i <= count; ++i) {
        float timeX = pixelstep*i+startPosition -10;
        painter.setFont(font);
        painter.drawText(timeX, RECTY-5, show_starttime.toString("hh:mm"));
        painter.drawLine(pixelstep*i+startPosition, RECTY-1, pixelstep*i+startPosition, RECTY+25);
        show_starttime = show_starttime.addSecs(timestep);
    }
}

void DrawTimeline::drawTimeCursor(QPainter &painter)
{
    painter.setPen( QPen{QColor{255,0,0,200},2});
    painter.drawLine(this->width()/2+1, CURSORHEIGTH, this->width()/2+1, 105);
    QPolygonF cursorPolygon;
    cursorPolygon << QPointF(this->size().width()/2,   CURSORHEIGTH)
                  << QPointF(this->size().width()/2+4, CURSORHEIGTH-4)
                  << QPointF(this->size().width()/2+4, CURSORHEIGTH-12)
                  << QPointF(this->size().width()/2-4, CURSORHEIGTH-12)
                  << QPointF(this->size().width()/2-4, CURSORHEIGTH-4) ;
    painter.setBrush(QColor{200,200,200});
    painter.setPen(QColor{200,200,200});
    painter.drawPolygon(cursorPolygon);
}


void DrawTimeline::drawTimeRangeInfo()
{
    for (int i=0; i<m_vecTimeRangeInfo.count(); ++i) {
        QDateTime stime = m_vecTimeRangeInfo.at(i).starttime;
        QDateTime etime = m_vecTimeRangeInfo.at(i).endtime;

        float pixelstep = m_vecStep.at(m_sizeLevel).pixelstep;
        int timestep = m_vecStep.at(m_sizeLevel).timestep;
        float secsper = timestep/pixelstep;
        float sToCurrent = m_currentDateTime.secsTo(stime);
        float eToCurrent = m_currentDateTime.secsTo(etime);
        float length = eToCurrent - sToCurrent;

        int timeX = sToCurrent/secsper + this->width()/2;
        int timeLen = length/secsper;

        QPainter paint;
        paint.begin(this);
        paint.setPen(QPen(Qt::darkYellow,1,Qt::NoPen));
        paint.setBrush(QBrush(Qt::cyan,Qt::SolidPattern));
        paint.drawRect(timeX,RECTY+1,timeLen,RECTHEIGH-1);
        paint.end();
    }
}

void DrawTimeline::on_ptn_levelup_clicked()
{
    if (m_sizeLevel < m_totleLevel-1)
        m_sizeLevel += 1;

    update();
}

void DrawTimeline::on_ptn_leveldown_clicked()
{
    if (m_sizeLevel >0)
        m_sizeLevel -= 1;

    update();
}

