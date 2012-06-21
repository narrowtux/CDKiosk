#include <QtGui/QApplication>
#include "src/gui/mainwindow.h"
#include <QSplashScreen>
#include <QDesktopServices>
#include <QPixmap>
#include <QDir>
#include <QDebug>
#include "src/jobmanager/jobmanagersimulator.h"
#include <QTranslator>
#include <QSqlDatabase>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    qDebug()<<""; //Make sure that a newline is printed before printing other stuff...
    
    QApplication a(argc, argv);
    
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
		      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);
    
    QTranslator myappTranslator;
    myappTranslator.load("cdkiosk-" + QLocale::system().name());
    a.installTranslator(&myappTranslator);
    
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
    
    QSettings settings;
    
    splash->showMessage("Starting the print Job Manager ...", align, color);
    a.processEvents();
    JobManager *jobManager = new JobManagerSimulator(QDir(QDesktopServices::storageLocation(QDesktopServices::DataLocation)));
    
    splash->showMessage("Connecting to the SQL-Database ...", align, color);
    a.processEvents();
    QSqlDatabase db = QSqlDatabase::addDatabase(settings.value("sql.driver", "QMYSQL").toString());
    db.setHostName(settings.value("sql.hostname", "localhost").toString());
    db.setUserName(settings.value("sql.username", "root").toString());
    db.setPassword(settings.value("sql.password", "").toString());
    db.setPort(settings.value("sql.port", db.port()).toInt());
    db.setDatabaseName(settings.value("sql.databasename", "cdkiosk").toString());
    db.setConnectOptions(settings.value("sql.connectoptions", "UNIX_SOCKET=/Applications/XAMPP/xamppfiles/var/mysql/mysql.sock").toString());
    
    if (!db.open()) {
	QMessageBox::critical(splash, QObject::tr("Database error!"), QObject::tr("Could not connect to the database!\nPlease check the settings screen. Error:\n%0 - %1").arg(db.lastError().driverText()).arg(db.lastError().databaseText()));
    }
    
    splash->showMessage("Done!", align, color);
    a.processEvents();
    
    MainWindow w(db);
    w.setJobManager(jobManager);
    
    splash->finish(&w);
    w.show();
    splash->deleteLater();
    
    return a.exec();
}
