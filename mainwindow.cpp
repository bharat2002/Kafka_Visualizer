#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tabWidget = new QTabWidget(this);

    // Add tabs to the QTabWidget
    tabWidget->addTab(new QWidget(), "Dashboard");
    tabWidget->addTab(new QWidget(), "Topic Monitoring");
    tabWidget->addTab(new QWidget(), "Consumer Groups");
    tabWidget->addTab(new QWidget(), "Message Visualization");
    tabWidget->addTab(new QWidget(), "Metrics & Performance");

    // Set the QTabWidget as the central widget of the main window
    this->setCentralWidget(tabWidget);
    setupMenu();
    this->setWindowTitle("Kafka Visualizer");
    this->setWindowState(Qt::WindowMaximized);
    m_Config = new IniReader("../../config.ini");
    if(0 != m_Config->ParseFile())
    {
        QMessageBox::critical(this, "Error Opening Config File","Config Loading Failed. Please check config file present or not.");
        m_Config = nullptr;
    }

}

MainWindow::~MainWindow()
{
    delete m_Config;
    delete ui;
}

void MainWindow::setupMenu()
{
    qDebug() << "Setting up menu bar...";

    QIcon ImgSaveIcon(QPixmap(":/icons/assests/Icons/icons8-save-48.png"));
    QIcon ImgAboutIcon(QPixmap(":/icons/assests/Icons/icons8-about-48.png"));
    QIcon ImgLoadIcon (QPixmap(":/icons/assests/Icons/icons8-load-from-file-48.png"));
    QIcon ImgExitIcon(QPixmap(":/icons/assests/Icons/icons8-exit-48.png"));
    QIcon ImgAlertIcon(QPixmap(":/icons/assests/Icons/icons8-alert-48.png"));
    QIcon ImgKafkaIcon(QPixmap(":/icons/assests/Icons/icons8-apache-kafka-64.png"));
    QIcon ImgconnectIcon(QPixmap(":/icons/assests/Icons/icons8-connect-48 (1).png"));
    QIcon ImgDisconnectIcon(QPixmap(":/icons/assests/Icons/icons8-disconnect-48.png"));
    QIcon ImgDarkModeIcon(QPixmap(":/icons/assests/Icons/icons8-dark-mode-48.png"));
    QIcon ImgDashboardIcon(QPixmap(":/icons/assests/Icons/icons8-dashboard-48.png"));
    QIcon ImgDeleteTopicIcon(QPixmap(":/icons/assests/Icons/icons8-delete-48.png"));
    QIcon ImgCreateIcon(QPixmap(":/icons/assests/Icons/icons8-create-48.png"));
    QIcon ImgGraphIcon(QPixmap(":/icons/assests/Icons/icons8-graph-48.png"));
    QIcon ImgGuideIcon(QPixmap(":/icons/assests/Icons/icons8-guide-48.png"));
    QIcon ImgModifyIcon(QPixmap(":/icons/assests/Icons/icons8-modify-48.png"));
    QIcon ImgMonitoringIcon(QPixmap(":/icons/assests/Icons/icons8-monitoring-48.png"));
    QIcon ImgNotificationIcon(QPixmap(":/icons/assests/Icons/icons8-notification-48.png"));
    QIcon ImgPerformanceIcon(QPixmap(":/icons/assests/Icons/icons8-performance-48.png"));
    QIcon ImgPingIcon(QPixmap(":/icons/assests/Icons/icons8-ping-48.png"));
    QIcon ImgRefreshIcon(QPixmap(":/icons/assests/Icons/icons8-refresh-48.png"));
    QIcon ImgSendIcon(QPixmap(":/icons/assests/Icons/icons8-send-48.png"));
    QIcon ImgGroupIcon(QPixmap(":/icons/assests/Icons/icons8-staff-skin-type-7-48.png"));
    QIcon ImgStatisticsIcon(QPixmap(":/icons/assests/Icons/icons8-statistics-48.png"));
    QIcon ImgVisualizationIcon(QPixmap(":/icons/assests/Icons/icons8-tree-structure-48.png"));
    m_MenuBar = new QMenuBar(this);
    // File Menu
    QMenu* fileMenu = new QMenu("File", this);
    QAction* saveConfigAction = new QAction("Save Configuration", this);
    saveConfigAction->setIcon(ImgSaveIcon);
    QAction* loadConfigAction = new QAction("Load Configuration", this);
    loadConfigAction->setIcon(ImgLoadIcon);
    QAction* exitAction = new QAction("Exit", this);
    exitAction->setIcon(ImgExitIcon);

    fileMenu->addAction(saveConfigAction);
    fileMenu->addAction(loadConfigAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    m_MenuBar->addMenu(fileMenu);

    // Kafka Menu
    QMenu* kafkaMenu = new QMenu("Kafka", this);
    QAction* connectAction = new QAction("Connect to Kafka", this);
    QAction* disconnectAction = new QAction("Disconnect from Kafka", this);
    QAction* refreshMetadataAction = new QAction("Refresh Metadata", this);
    QAction* createTopicAction = new QAction("Create Topic", this);
    QAction* deleteTopicAction = new QAction("Delete Topic", this);
    connectAction->setIcon(ImgKafkaIcon);
    disconnectAction->setIcon(ImgDisconnectIcon);
    refreshMetadataAction->setIcon(ImgRefreshIcon);
    createTopicAction->setIcon(ImgCreateIcon);
    deleteTopicAction->setIcon(ImgDeleteTopicIcon);

    kafkaMenu->addAction(connectAction);
    kafkaMenu->addAction(disconnectAction);
    kafkaMenu->addSeparator();
    kafkaMenu->addAction(refreshMetadataAction);
    kafkaMenu->addSeparator();
    kafkaMenu->addAction(createTopicAction);
    kafkaMenu->addAction(deleteTopicAction);
    m_MenuBar->addMenu(kafkaMenu);

    // View Menu
    QMenu* viewMenu = new QMenu("View", this);
    QAction* dashboardAction = new QAction("Dashboard", this);
    QAction* topicMonitoringAction = new QAction("Topic Monitoring", this);
    QAction* consumerGroupsAction = new QAction("Consumer Groups", this);
    QAction* messageVisualizationAction = new QAction("Message Visualization", this);
    QAction* metricsAction = new QAction("Metrics & Performance", this);
    QAction* darkModeAction = new QAction("Dark Mode", this);

    dashboardAction->setIcon(ImgDashboardIcon);
    topicMonitoringAction->setIcon(ImgMonitoringIcon);
    consumerGroupsAction->setIcon(ImgGroupIcon);
    messageVisualizationAction->setIcon(ImgVisualizationIcon);
    metricsAction->setIcon(ImgStatisticsIcon);
    darkModeAction->setIcon(ImgDarkModeIcon);
    darkModeAction->setCheckable(true); // Allow toggling dark mode
    viewMenu->addAction(dashboardAction);
    viewMenu->addAction(topicMonitoringAction);
    viewMenu->addAction(consumerGroupsAction);
    viewMenu->addAction(messageVisualizationAction);
    viewMenu->addAction(metricsAction);
    viewMenu->addSeparator();
    viewMenu->addAction(darkModeAction);
    m_MenuBar->addMenu(viewMenu);

    // Tools Menu
    QMenu* toolsMenu = new QMenu("Tools", this);
    QAction* produceMessageAction = new QAction("Produce Test Message", this);
    QAction* modifyTopicConfigAction = new QAction("Modify Topic Configuration", this);
    QAction* consumerLagGraphAction = new QAction("Consumer Lag Graph", this);
    QAction* throughputGraphAction = new QAction("Throughput Graph", this);
    produceMessageAction->setIcon(ImgSendIcon);
    modifyTopicConfigAction->setIcon(ImgModifyIcon);
    throughputGraphAction->setIcon(ImgGraphIcon);
    consumerLagGraphAction->setIcon(ImgPingIcon);

    toolsMenu->addAction(produceMessageAction);
    toolsMenu->addAction(modifyTopicConfigAction);
    toolsMenu->addSeparator();
    toolsMenu->addAction(consumerLagGraphAction);
    toolsMenu->addAction(throughputGraphAction);
    m_MenuBar->addMenu(toolsMenu);

    // Notifications Menu
    QMenu* notificationsMenu = new QMenu("Notifications", this);
    QAction* viewNotificationsAction = new QAction("View Notifications", this);
    QAction* configureAlertsAction = new QAction("Configure Alerts", this);

    viewNotificationsAction->setIcon(ImgNotificationIcon);
    configureAlertsAction->setIcon(ImgAlertIcon);

    notificationsMenu->addAction(viewNotificationsAction);
    notificationsMenu->addAction(configureAlertsAction);
    m_MenuBar->addMenu(notificationsMenu);

    // Help Menu
    QMenu* helpMenu = new QMenu("Help", this);
    QAction* userGuideAction = new QAction("User Guide", this);
    QAction* aboutAction = new QAction("About", this);

    userGuideAction->setIcon(ImgGuideIcon);
    aboutAction->setIcon(ImgAboutIcon);

    helpMenu->addAction(userGuideAction);
    helpMenu->addAction(aboutAction);
    m_MenuBar->addMenu(helpMenu);

    // Set the menu bar as the main menu bar of the window
    this->setMenuBar(m_MenuBar);

    connect(saveConfigAction, &QAction::triggered, this, &MainWindow::saveConfiguration);
    connect(loadConfigAction, &QAction::triggered, this, &MainWindow::loadConfiguration);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);
    connect(connectAction, &QAction::triggered, this, &MainWindow::connectToKafka);
    connect(disconnectAction, &QAction::triggered, this, &MainWindow::disconnectFromKafka);
    connect(refreshMetadataAction, &QAction::triggered, this, &MainWindow::refreshMetadata);
    connect(createTopicAction, &QAction::triggered, this, &MainWindow::createTopic);
    connect(deleteTopicAction, &QAction::triggered, this, &MainWindow::deleteTopic);
    connect(dashboardAction, &QAction::triggered, this, &MainWindow::switchToDashboard);
    connect(topicMonitoringAction, &QAction::triggered, this, &MainWindow::switchToTopicMonitoring);
    connect(consumerGroupsAction, &QAction::triggered, this, &MainWindow::switchToConsumerGroups);
    connect(messageVisualizationAction, &QAction::triggered, this, &MainWindow::switchToMessageVisualization);
    connect(metricsAction, &QAction::triggered, this, &MainWindow::switchToMetrics);
    connect(darkModeAction, &QAction::toggled, this, &MainWindow::toggleDarkMode);
    connect(produceMessageAction, &QAction::triggered, this, &MainWindow::produceTestMessage);
    connect(modifyTopicConfigAction, &QAction::triggered, this, &MainWindow::modifyTopicConfiguration);
    connect(consumerLagGraphAction, &QAction::triggered, this, &MainWindow::showConsumerLagGraph);
    connect(throughputGraphAction, &QAction::triggered, this, &MainWindow::showThroughputGraph);
    connect(viewNotificationsAction, &QAction::triggered, this, &MainWindow::viewNotifications);
    connect(configureAlertsAction, &QAction::triggered, this, &MainWindow::configureAlerts);
    connect(userGuideAction, &QAction::triggered, this, &MainWindow::openUserGuide);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAboutDialog);
}


void MainWindow::saveConfiguration()
{
    // Save Kafka broker/topic configurations to a file
    QString filePath = QFileDialog::getSaveFileName(this, "Save Configuration", "", "Config Files (*.ini)");
    if (!filePath.isEmpty() ||
        nullptr != m_Config)
    {
        QFile FileToSave(filePath,this);
        std::ostringstream ssDataToWrite("");
        ssDataToWrite<<"[Kafka]\nIP=";
        ssDataToWrite<<m_Config->GetValue("Kafka","IP","")<<"\nPORT="<<m_Config->GetValue("Kafka","PORT","")<<'\n'<<'\n';
        ssDataToWrite<<"[ZooKeeper]\nIP=";
        ssDataToWrite<<m_Config->GetValue("ZooKeeper","IP","")<<"\nPORT="<<m_Config->GetValue("ZooKeeper","PORT","");
        FileToSave.open(QFile::WriteOnly);
        FileToSave.resize(filePath,0);
        FileToSave.write(ssDataToWrite.str().c_str());
        qDebug() << "Configuration saved to:" << filePath;
    }
    else
    {
        QMessageBox::critical(this, "Config Error","Either No Config File Loaded or No File Selected.");
    }
}

void MainWindow::loadConfiguration()
{
    // Load Kafka broker/topic configurations from a file
    QString filePath = QFileDialog::getOpenFileName(this, "Load Configuration", "", "Config Files (*.ini)");
    IniReader* newConfig = new IniReader(filePath.toStdString().c_str());
    if (!filePath.isEmpty()) {
        if(0 != newConfig->ParseFile())
        {
            delete newConfig;
            newConfig = nullptr;
            QMessageBox::critical(this,"Wrong File Passed","Error Parsing File.Check the file again.");
        }
        else
        {
            delete m_Config;
            m_Config = newConfig;
            QMessageBox::information(this, "File Load Success","Config Loading Success.");
        }
        qDebug() << "Configuration loaded from:" << filePath;
    }
}

void MainWindow::connectToKafka()
{
    // Connect to a Kafka cluster
    QString brokerAddress = QInputDialog::getText(this, "Connect to Kafka", "Enter Kafka Broker Address:");
    if (!brokerAddress.isEmpty()) {
        // Logic to connect to Kafka using librdkafka
        qDebug() << "Connecting to Kafka broker:" << brokerAddress;
    }
}

void MainWindow::disconnectFromKafka()
{
    // Disconnect from the current Kafka cluster
    // Logic to disconnect from Kafka
    qDebug() << "Disconnected from Kafka.";
}

void MainWindow::refreshMetadata()
{
    // Refresh Kafka metadata (topics, partitions, brokers)
    // Logic to fetch and display metadata
    qDebug() << "Refreshing Kafka metadata...";
}

void MainWindow::createTopic()
{
    // Open a dialog to create a new Kafka topic
    QString topicName = QInputDialog::getText(this, "Create Topic", "Enter Topic Name:");
    if (!topicName.isEmpty()) {
        // Logic to create a new Kafka topic
        qDebug() << "Creating topic:" << topicName;
    }
}

void MainWindow::deleteTopic()
{
    // Open a dialog to delete an existing Kafka topic
    QString topicName = QInputDialog::getText(this, "Delete Topic", "Enter Topic Name:");
    if (!topicName.isEmpty()) {
        // Logic to delete the Kafka topic
        qDebug() << "Deleting topic:" << topicName;
    }
}



void MainWindow::switchToDashboard()
{
    // Switch to the dashboard view
    this->tabWidget->setCurrentIndex(0); // Assuming the dashboard is the first tab
    qDebug() << "Switched to Dashboard view.";
}

void MainWindow::switchToTopicMonitoring()
{
    // Switch to the topic monitoring view
    this->tabWidget->setCurrentIndex(1); // Assuming topic monitoring is the second tab
    qDebug() << "Switched to Topic Monitoring view.";
}

void MainWindow::switchToConsumerGroups()
{
    // Switch to the consumer group monitoring view
    this->tabWidget->setCurrentIndex(2); // Assuming consumer groups is the third tab
    qDebug() << "Switched to Consumer Groups view.";
}

void MainWindow::switchToMessageVisualization()
{
    // Switch to the message visualization view
    this->tabWidget->setCurrentIndex(3); // Assuming message visualization is the fourth tab
    qDebug() << "Switched to Message Visualization view.";
}

void MainWindow::switchToMetrics()
{
    // Switch to the metrics and performance view
    this->tabWidget->setCurrentIndex(4); // Assuming metrics is the fifth tab
    qDebug() << "Switched to Metrics & Performance view.";
}

void MainWindow::toggleDarkMode(bool enabled)
{
    // Toggle dark mode
    if (enabled) {
        // Apply dark mode stylesheet
        qApp->setStyleSheet("QWidget { background-color: #2E3440; color: #D8DEE9; }");
        qDebug() << "Dark mode enabled.";
    } else {
        // Revert to light mode
        qApp->setStyleSheet(""); // Reset stylesheet
        qDebug() << "Dark mode disabled.";
    }
}


void MainWindow::produceTestMessage()
{
    // Open a dialog to produce a test message
    QString topicName = QInputDialog::getText(this, "Produce Test Message", "Enter Topic Name:");
    if (!topicName.isEmpty()) {
        QString message = QInputDialog::getText(this, "Produce Test Message", "Enter Message:");
        if (!message.isEmpty()) {
            // Logic to produce the message to the specified topic
            qDebug() << "Produced message to topic" << topicName << ":" << message;
        }
    }
}

void MainWindow::modifyTopicConfiguration()
{
    // Open a dialog to modify topic configurations
    QString topicName = QInputDialog::getText(this, "Modify Topic Configuration", "Enter Topic Name:");
    if (!topicName.isEmpty()) {
        // Logic to modify topic configurations (e.g., replication factor, partitions)
        qDebug() << "Modifying configuration for topic:" << topicName;
    }
}

void MainWindow::showConsumerLagGraph()
{
    // Open a graph showing consumer lag over time
    // Logic to display the graph
    qDebug() << "Displaying Consumer Lag Graph.";
}

void MainWindow::showThroughputGraph()
{
    // Open a graph showing topic throughput
    // Logic to display the graph
    qDebug() << "Displaying Throughput Graph.";
}


void MainWindow::viewNotifications()
{
    // Open a panel to view recent notifications/alerts
    // Logic to display notifications
    qDebug() << "Viewing notifications.";
}

void MainWindow::configureAlerts()
{
    // Open a dialog to configure alert thresholds
    // Logic to configure alerts (e.g., consumer lag, message rate)
    qDebug() << "Configuring alerts.";
}

void MainWindow::openUserGuide()
{
    // Open a user guide or documentation
    QDesktopServices::openUrl(QUrl("https://your-documentation-url.com"));
    qDebug() << "Opening user guide.";
}

void MainWindow::showAboutDialog()
{
    // Display information about the application
    QMessageBox::about(this, "About Kafka Visualizer",
                       "Kafka Visualizer\nVersion 1.0\n\nA tool for visualizing and monitoring Kafka clusters.");
    qDebug() << "Displayed About dialog.";
}
