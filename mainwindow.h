#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "inireader.h"
#include <QMessageBox>
#include <QMenuBar>
#include <QFileDialog>
#include <QInputDialog>
#include <QDesktopServices>
#include <QFile>
#include "ckafkainputdialog.h"
#include "kakfaconsumer.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void saveConfiguration();
    void loadConfiguration();
    void connectToKafka();
    void disconnectFromKafka();
    void refreshMetadata();
    void createTopic();
    void deleteTopic();
    void switchToDashboard();
    void switchToTopicMonitoring();
    void switchToConsumerGroups();
    void switchToMessageVisualization();
    void switchToMetrics();
    void toggleDarkMode(bool enabled);
    void produceTestMessage();
    void modifyTopicConfiguration();
    void showConsumerLagGraph();
    void showThroughputGraph();
    void viewNotifications();
    void configureAlerts();
    void openUserGuide();
    void showAboutDialog();
private:
    IniReader* m_Config=nullptr;
    Ui::MainWindow *ui;
    QMenuBar* m_MenuBar= nullptr;
    void setupMenu();
    QTabWidget *tabWidget;
    int m_ConsumerCount = 0;
    int m_ProducerCount = 0;

};
#endif // MAINWINDOW_H
