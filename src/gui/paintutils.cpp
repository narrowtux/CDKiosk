#include "paintutils.h"

PaintUtils::PaintUtils(QObject *parent) :
    QObject(parent)
{
}

void PaintUtils::drawRoundedText(QPainter *p, int x, int y, QString text, int radius)
{
    p->save();
    p->translate(x, y);
    
    QFontMetrics fm(p->font());
    QRect bounding = fm.boundingRect(text);
    
    qreal angleRAD = (qreal) bounding.width() / (qreal) radius;
    qreal angleDEG = angleRAD * 180.0 / M_PI;
    
    qreal angleStart = -angleDEG / 2;
    
    foreach(QChar chr, text) {
	p->save();
	p->rotate(angleStart);
	
	int width = fm.width(chr);
	qreal chrRAD = (qreal) width / (qreal) radius;
	qreal chrDEG = chrRAD * 180.0 / M_PI;
	
	p->drawText(0, -radius, QString(chr));
	
	angleStart += chrDEG;
	
	p->restore();
    }
    
    p->restore();
}

QPixmap PaintUtils::generateCoverForJob(QList<Speech *> speeches, Job::DiscType discType)
{
    int size = 2048;
    int radius = size / 2;
    
    QPixmap cover(size, size);
    QPainter p(&cover);
    
    p.setRenderHint(QPainter::Antialiasing);
    
    setFontSize(&p, 100);
    
    QSet<QString> authors;
    QStringList titles;
    QString title = "";
    
    foreach(Speech *speech, speeches) {
	authors << speech->author();
	titles << QObject::tr("%0 on %1 by %2").arg(speech->name()).arg(speech->date().toString(Qt::DefaultLocaleShortDate)).arg(speech->author());
	title = speech->author();
    }
    
    if (authors.size() != 1) {
	title = QObject::tr("Compilation on %0").arg(QDate::currentDate().toString(Qt::DefaultLocaleShortDate));
    }
    
    drawRoundedText(&p, radius, radius, title, radius - 120);
    
    if (speeches.size() == 1) {
	drawRoundedText(&p, radius, radius, speeches.first()->name(), radius - 240);
	
	drawRoundedText(&p, radius, radius, speeches.first()->date().toString(Qt::DefaultLocaleShortDate), -300);
    } else {
	setFontSize(&p, 50);
	int y = 350;
	foreach (QString t, titles) {
	    QRectF rect(0, y, size, 55);
	    
	    p.drawText(rect, t, QTextOption(Qt::AlignCenter));
	    y += 55;
	    
	    if (y >= radius * 0.875 - 55 && y <= radius * 1.125 + 20) {
		y = radius * 1.130 + 20;
	    }
	}
    }
    
    setFontSize(&p, 50);
    
    drawRoundedText(&p, radius, radius, tr("Not for resale or redistribution without written permission of the referent."), -(radius - 60));
    
    //draw logo
    
    QImage typeLogo;
    switch(discType) {
    case Job::AUDIO:
	typeLogo = QImage(":/gui/icons/AudioCDLogo.png");
	break;
    case Job::FILES:
	typeLogo = QImage(":/gui/icons/MP3AudioLogo.png");
	break;
    }
    p.drawImage(QRect(size - 100 - 200, radius - 50, 200, 100), typeLogo);
    return cover;
}

void PaintUtils::setFontSize(QPainter *p, qreal size)
{
    QFont f = p->font();
    f.setPointSizeF(size);
    p->setFont(f);
}
