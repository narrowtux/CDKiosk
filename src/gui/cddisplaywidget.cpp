#include "cddisplaywidget.h"
#include <QPainter>
#include <QTransform>
#include "paintutils.h"

CDDisplayWidget::CDDisplayWidget(QWidget *parent) :
    QWidget(parent)
{
    m_currentJob = 0;
}

void CDDisplayWidget::setCurrentJob(Job *job)
{
    m_currentJob = job;
    update();
}

void CDDisplayWidget::onJobDiskProgress(Job *job, int discsDone, int discsTotal, int progress)
{
//    if (job != m_currentJob) {
	setCurrentJob(job);
	//    }
}

void CDDisplayWidget::onManagerStopped()
{
    setCurrentJob(0);
}

Job *CDDisplayWidget::currentJob()
{
    return m_currentJob;
}

void CDDisplayWidget::setJobManager(JobManager *jobManager)
{
    m_jobManager = jobManager;
    
    connect(m_jobManager, SIGNAL(jobDiscProgress(Job*,int,int,int)), this, SLOT(onJobDiskProgress(Job *, int, int, int)));
    connect(m_jobManager, SIGNAL(stopped()), this, SLOT(onManagerStopped()));
}

void CDDisplayWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::HighQualityAntialiasing);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    int width = geometry().width();
    int height = geometry().height();
    
    int diameter = qMin(width, height);
    qreal radius = diameter / 2;
    
    int left = width / 2;
    int top = height / 2;
    
    p.translate(left, top);
//    p.rotate(angle);
    
    p.setBrush(Qt::white);
    
    p.drawEllipse(QPointF(0,0), radius, radius);
    
    p.setPen(Qt::transparent);
    p.setBrush(Qt::red);
    
    p.drawEllipse(QPointF(0, 0), radius*0.125, radius*0.125);
    
    p.setPen(Qt::black);
    
    if (m_currentJob != 0) {
	p.drawPixmap(-radius, -radius, diameter, diameter, m_currentJob->cover());
	
	p.setBrush(QColor(128, 128, 128, 128));
	
	p.drawPie(QRectF(-radius, -radius, diameter, diameter), 90 * 16, -((qreal) m_currentJob->progress() / 100.0) * 360.0 * 16.0);
    } else {
	PaintUtils::drawRoundedText(&p, 0, 0, tr("No Job running"), radius - 20);
    }
}
