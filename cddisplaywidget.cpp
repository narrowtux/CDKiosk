#include "cddisplaywidget.h"
#include <QPainter>
#include <QTransform>

CDDisplayWidget::CDDisplayWidget(QWidget *parent) :
    QWidget(parent)
{
    m_currentJob = 0;
}

void CDDisplayWidget::setCurrentJob(Job *job)
{
    this->m_currentJob = job;
    update();
}

void CDDisplayWidget::onJobDiskProgress(Job *job, int discsDone, int discsTotal, int progress)
{
    setCurrentJob(m_currentJob);
}

Job *CDDisplayWidget::currentJob()
{
    return m_currentJob;
}

void CDDisplayWidget::setJobManager(JobManager *jobManager)
{
    m_jobManager = jobManager;
    
    connect(m_jobManager, SIGNAL(jobDiscProgress(Job*,int,int,int)), this, SLOT(onJobDiskProgress(Job *, int, int, int)));
}

void CDDisplayWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.setRenderHint(QPainter::Antialiasing, true);
    int width = geometry().width();
    int height = geometry().height();
    
    int diameter = qMin(width, height);
    qreal radius = diameter / 2;
    
    p.translate(radius, radius);
//    p.rotate(angle);
    
    p.setBrush(Qt::white);
    
    p.drawEllipse(QPointF(0,0), radius, radius);
    
    p.setPen(Qt::transparent);
    p.setBrush(Qt::red);
    
    p.drawEllipse(QPointF(0, 0), radius*0.125, radius*0.125);
    
    p.setPen(Qt::black);
    
    if (m_currentJob != 0) {
	p.drawPixmap(-radius, -radius, diameter, diameter, m_currentJob->cover());
    } else {
	p.drawText(QPoint(0, -radius/2), tr("No Job running"));
    }
}
