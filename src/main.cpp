#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QSplashScreen>
#include <QDesktopServices>
#include <QPixmap>
#include <QDir>
#include <QDebug>
#include "jobmanager/jobmanagersimulator.h"

int main(int argc, char *argv[])
{
    qDebug()<<""; //Make sure that a newline is printed before printing other stuff...
    
    QApplication a(argc, argv);
    
    QPixmap pixmap(":/gui/icons/splash.png");
    QSplashScreen *splash = new QSplashScreen(pixmap);
    int align = Qt::AlignBottom | Qt::AlignHCenter;
    QColor color = Qt::white;
    splash->show();
    splash->showMessage("Starting up ...", align, color);
    a.processEvents();
    
    a.setOrganizationDomain("narrowtux.com");
    a.setOrganizationName("narrowtux");
    a.setApplicationName("CD-Kiosk");
    a.setApplicationVersion("0.1a1");
    
    splash->showMessage("Starting the print Job Manager ...", align, color);
    a.processEvents();
    JobManager *jobManager = new JobManagerSimulator(QDir(QDesktopServices::storageLocation(QDesktopServices::DataLocation)));
    
    splash->showMessage("Done!", align, color);
    a.processEvents();
    
    MainWindow w;
    w.setJobManager(jobManager);
    
    splash->finish(&w);
    w.show();
    splash->deleteLater();

    return a.exec();
}
