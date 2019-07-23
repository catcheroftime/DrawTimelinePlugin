#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ptn_add_clicked()
{
    QVector<DrawTimeline::TimeRange> timeRangeInfo;

    QStringList timerangelist = ui->textEdit_timerange->toPlainText().split("\n");
    for (int i=0; i<timerangelist.count(); ++i) {
        QString timerangeinfo = timerangelist.at(i);
        timerangeinfo = timerangeinfo.trimmed();
        QStringList info = timerangeinfo.split(",");
        QString starttime = info.at(0).trimmed();
        QString endtime = info.at(1).trimmed();

        QDateTime startdatetime = QDateTime::fromString(starttime,"yyyy-MM-dd hh:mm:ss");
        QDateTime enddatetime = QDateTime::fromString(endtime,"yyyy-MM-dd hh:mm:ss");
        timeRangeInfo.append({startdatetime,enddatetime});
    }
    ui->drawTimeline->setTimeRangeInfo(timeRangeInfo);
}
