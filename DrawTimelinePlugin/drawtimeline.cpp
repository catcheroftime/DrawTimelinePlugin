#include "drawtimeline.h"
#include "ui_drawtimeline.h"

DrawTimeline::DrawTimeline(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawTimeline)
{
    ui->setupUi(this);
}

DrawTimeline::~DrawTimeline()
{
    delete ui;
}
