#include "drawtimeline.h"
#include "ui_drawtimeline.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#define RECTY 50
#define RECTHEIGH 10

DrawTimeline::DrawTimeline(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawTimeline)
  , m_currentDateTime(QDateTime::currentDateTime())
  , m_sizeLevel(4)
{
    ui->setupUi(this);

    m_vecStep.append({2*60*60,80.0});
    m_vecStep.append({1*60*60,90.0});
    m_vecStep.append({30*60,100.0});
    m_vecStep.append({10*60,110.0});
    m_vecStep.append({5*60,120.0});
    m_totleLevel = m_vecStep.size();

    m_fixeDisplayLable = new QLabel(this);
    m_fixeDisplayLable->setFixedSize(QSize(150,18));
    //设置游标背景为白色
    m_fixeDisplayLable->setAutoFillBackground(true);
    QPalette palette1;
    palette1.setColor(QPalette::Background, Qt::white);
    m_fixeDisplayLable->setPalette(palette1);
    m_fixeDisplayLable->setAlignment(Qt::AlignCenter);
    m_fixeDisplayLable->setStyleSheet("color:rgb(248,248,255);background:transparent");
    m_fixeDisplayLable->setVisible(true);

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

void DrawTimeline::paintEvent(QPaintEvent *)
{
    // 绘制黑色的背景
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawRect(rect());

    // 绘制时间刻度
    drawTimescale(painter);

    // 显示中间位置时间
    painter.drawLine(this->width()/2, 5, this->width()/2, 105);
    m_fixeDisplayLable->setText(m_currentDateTime.toString("yyyy-MM-dd hh:mm:ss"));
    m_fixeDisplayLable->move(this->size().width()/2-m_fixeDisplayLable->width()/2,15);
}

void DrawTimeline::mousePressEvent(QMouseEvent *event)
{
    m_isPressed = true;
    m_pressDateTime = m_currentDateTime;
    m_pressPoint = event->pos().x();
    QWidget::mousePressEvent(event);
}

void DrawTimeline::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
    QWidget::mouseReleaseEvent(event);
}

void DrawTimeline::mouseMoveEvent(QMouseEvent *event)
{
    if (m_pressPoint) {
        int move_length = event->pos().x() - m_pressPoint;
        float secs = m_vecStep.at(m_sizeLevel).timestep/m_vecStep.at(m_sizeLevel).pixelstep;
        m_currentDateTime = m_pressDateTime.addSecs(-secs*move_length);
    } else {
        // 显示鼠标停留位置的时间
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
    painter.setPen( Qt::yellow );
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
    int count  = this->size().width() / pixelstep;
    for (int i = 0; i <= count; ++i) {
        float timeX = pixelstep*i+startPosition -10;
        painter.setPen( Qt::white );
        painter.drawText(timeX, RECTY-5, show_starttime.toString("hh:mm"));
        painter.setPen( Qt::yellow );
        painter.drawLine(pixelstep*i+startPosition, RECTY-1, pixelstep*i+startPosition, RECTY+25);
        show_starttime = show_starttime.addSecs(timestep);
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
