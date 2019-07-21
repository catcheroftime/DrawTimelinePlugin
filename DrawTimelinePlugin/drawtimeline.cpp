#include "drawtimeline.h"
#include "ui_drawtimeline.h"

#include <QPainter>

#define RECTY 50
#define RECTHEIGH 10

DrawTimeline::DrawTimeline(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawTimeline)
  , m_dateTime(QDateTime(QDate::currentDate(),QTime(0,0,0)))
  , m_step(79.0)
  , m_stepTimevalue(2*60*60)
{
    ui->setupUi(this);

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

    // 绘制容纳时间的举行
    painter.setPen( Qt::yellow );
    painter.drawRect(-1,RECTY,this->width()+40,RECTHEIGH);

    calcDistance();
    int width = this->size().width() ;
    int count  = width / m_step;

    QDateTime dateTime =  m_dateTime;
    int timeH = dateTime.time().hour();
    int timeM = dateTime.time().minute();
    int timeS = dateTime.time().second();

    if(m_stepTimevalue==60*60*2) // 时间间隔为2小时
    {
        if(timeH%2==0 )
        {
            dateTime = dateTime.addSecs(-(timeM*60+timeS));
        }
        else
        {
            dateTime = dateTime.addSecs(-(timeM*60+timeS+3600));
        }
    }
    else
    {
        if(timeM>m_stepTimevalue/60)
        {
            int min = timeM%(m_stepTimevalue/60);
            dateTime = dateTime.addSecs(-(min*60+timeS));
        }
        else
        {
            dateTime = dateTime.addSecs(-(timeM*60+timeS));
        }
    }

    for (int i = 0; i <= count; ++i)
    {
        dateTime = dateTime.addSecs(m_stepTimevalue);
        float timeX = m_step * (i)+ m_distance - 10;
        painter.setPen( Qt::white );
        painter.drawText(timeX, RECTY-10, dateTime.toString("hh:mm"));
        painter.setPen( Qt::yellow );
        painter.drawLine(m_distance + m_step * i, 49, m_distance + m_step * i, 75);
    }
    setFixeDisplayNum();
    m_fixeDisplayLable->setText(m_strVisibleValue);
    painter.drawLine(this->width()/2, 5, this->width()/2, 105);
}

void DrawTimeline::mousePressEvent(QMouseEvent *event)
{

}

void DrawTimeline::mouseReleaseEvent(QMouseEvent *event)
{

}

void DrawTimeline::mouseMoveEvent(QMouseEvent *event)
{

}

void DrawTimeline::wheelEvent(QWheelEvent *event)
{

}

void DrawTimeline::calcDistance()
{
    int timeH = m_dateTime.time().hour();
    int timeM = m_dateTime.time().minute();
    int timeS = m_dateTime.time().second();
    int tmp;
    if (m_stepTimevalue == 2*60*60) {
        tmp = timeH%2==0? m_stepTimevalue - (timeM*60+timeS):tmp = m_stepTimevalue - (3600+timeM*60+timeS);
    } else {
        if (timeM > m_stepTimevalue/60) {
            int min = timeM % (m_stepTimevalue/60);
            tmp = m_stepTimevalue - (min*60+timeS);
        } else {
            tmp = m_stepTimevalue - (timeM*60+timeS);
        }
    }
    m_distance = tmp*m_step/m_stepTimevalue;
}


void DrawTimeline::setFixeDisplayNum()
{
    if (true) {
        QDateTime dateTime = m_dateTime;
        float secs = m_stepTimevalue/m_step;
        float width = this->size().width();
        dateTime = dateTime.addSecs((width/2)*secs);
        m_strVisibleValue = dateTime.toString("yyyy-MM-dd hh:mm:ss");
    } else {

    }
}
