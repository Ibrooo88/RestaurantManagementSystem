#include "../../include/gui/MainWindow.h"
#include "../../include/gui/DashboardWindow.h"
#include "../../include/gui/OrderView.h"
#include "../../include/gui/MenuView.h"
#include "../../include/gui/ChefView.h"
#include "../../include/gui/OrderQueueView.h"
#include "../../include/gui/ReservationView.h"
#include "../../include/gui/TableView.h"
#include "../../include/gui/PaymentView.h"
#include "../../include/gui/StatisticsView.h"
#include "../../include/gui/AdminLogView.h"
#include "../../include/utils/Logger.h"
#include <QApplication>
#include <Qt>

MainWindow::MainWindow(int userId, QWidget *parent)
    : QMainWindow(parent), currentUserId(userId) {
    setupUI();
    setWindowTitle("Restaurant Management System");
    setMinimumSize(1200, 800);
}

MainWindow::~MainWindow() {
}

void MainWindow::setupUI() {
    setupMenuBar();
    setupStatusBar();
    
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);
    
    // Add Dashboard as default tab
    DashboardWindow* dashboardWidget = new DashboardWindow();
    tabWidget->addTab(dashboardWidget, "Dashboard");
}

void MainWindow::setupMenuBar() {
    menuBar = this->menuBar();
    
    fileMenu = menuBar->addMenu("File");
    logoutAction = new QAction("Logout", this);
    connect(logoutAction, &QAction::triggered, this, &MainWindow::onLogout);
    fileMenu->addAction(logoutAction);
    
    exitAction = new QAction("Exit", this);
    connect(exitAction, &QAction::triggered, QApplication::instance(), &QApplication::quit);
    fileMenu->addAction(exitAction);
    
    viewMenu = menuBar->addMenu("View");
    dashboardAction = new QAction("Dashboard", this);
    connect(dashboardAction, &QAction::triggered, this, &MainWindow::onDashboardView);
    viewMenu->addAction(dashboardAction);
    
    viewMenu->addSeparator();
    
    chefAction = new QAction("Chefs", this);
    connect(chefAction, &QAction::triggered, this, &MainWindow::onChefView);
    viewMenu->addAction(chefAction);
    
    menuAction = new QAction("Menu", this);
    connect(menuAction, &QAction::triggered, this, &MainWindow::onMenuView);
    viewMenu->addAction(menuAction);
    
    orderAction = new QAction("Orders", this);
    connect(orderAction, &QAction::triggered, this, &MainWindow::onOrderView);
    viewMenu->addAction(orderAction);
    
    orderQueueAction = new QAction("Order Queue", this);
    connect(orderQueueAction, &QAction::triggered, this, &MainWindow::onOrderQueueView);
    viewMenu->addAction(orderQueueAction);
    
    reservationAction = new QAction("Reservations", this);
    connect(reservationAction, &QAction::triggered, this, &MainWindow::onReservationView);
    viewMenu->addAction(reservationAction);
    
    tableAction = new QAction("Tables", this);
    connect(tableAction, &QAction::triggered, this, &MainWindow::onTableView);
    viewMenu->addAction(tableAction);
    
    paymentAction = new QAction("Payments", this);
    connect(paymentAction, &QAction::triggered, this, &MainWindow::onPaymentView);
    viewMenu->addAction(paymentAction);
    
    statisticsAction = new QAction("Statistics", this);
    connect(statisticsAction, &QAction::triggered, this, &MainWindow::onStatisticsView);
    viewMenu->addAction(statisticsAction);
    
    adminLogAction = new QAction("Admin Logs", this);
    connect(adminLogAction, &QAction::triggered, this, &MainWindow::onAdminLogView);
    viewMenu->addAction(adminLogAction);
    
    helpMenu = menuBar->addMenu("Help");
}

void MainWindow::setupStatusBar() {
    statusBar()->showMessage("Ready");
}

void MainWindow::onChefView() {
    statusBar()->showMessage("Chef View", 2000);
    ChefView* chefView = new ChefView();
    int index = tabWidget->addTab(chefView, "Chefs");
    tabWidget->setCurrentIndex(index);
}

void MainWindow::onMenuView() {
    statusBar()->showMessage("Menu View", 2000);
    MenuView* menuView = new MenuView();
    int index = tabWidget->addTab(menuView, "Menu Management");
    tabWidget->setCurrentIndex(index);
}

void MainWindow::onOrderView() {
    statusBar()->showMessage("Order View", 2000);
    OrderView* orderView = new OrderView();
    int index = tabWidget->addTab(orderView, "Order Management");
    tabWidget->setCurrentIndex(index);
}

void MainWindow::onReservationView() {
    statusBar()->showMessage("Reservation View", 2000);
    ReservationView* reservationView = new ReservationView();
    int index = tabWidget->addTab(reservationView, "Reservations");
    tabWidget->setCurrentIndex(index);
}

void MainWindow::onPaymentView() {
    statusBar()->showMessage("Payment View", 2000);
    PaymentView* paymentView = new PaymentView();
    int index = tabWidget->addTab(paymentView, "Payments");
    tabWidget->setCurrentIndex(index);
}

void MainWindow::onDashboardView() {
    statusBar()->showMessage("Dashboard", 2000);
    DashboardWindow* dashboardView = new DashboardWindow();
    int index = tabWidget->addTab(dashboardView, "Dashboard");
    tabWidget->setCurrentIndex(index);
}

void MainWindow::onOrderQueueView() {
    statusBar()->showMessage("Order Queue View", 2000);
    OrderQueueView* orderQueueView = new OrderQueueView();
    int index = tabWidget->addTab(orderQueueView, "Order Queue");
    tabWidget->setCurrentIndex(index);
}

void MainWindow::onTableView() {
    statusBar()->showMessage("Table View", 2000);
    TableView* tableView = new TableView();
    int index = tabWidget->addTab(tableView, "Tables");
    tabWidget->setCurrentIndex(index);
}

void MainWindow::onStatisticsView() {
    statusBar()->showMessage("Statistics View", 2000);
    StatisticsView* statisticsView = new StatisticsView();
    int index = tabWidget->addTab(statisticsView, "Statistics");
    tabWidget->setCurrentIndex(index);
}

void MainWindow::onAdminLogView() {
    statusBar()->showMessage("Admin Log View", 2000);
    AdminLogView* adminLogView = new AdminLogView();
    int index = tabWidget->addTab(adminLogView, "Admin Logs");
    tabWidget->setCurrentIndex(index);
}

void MainWindow::onLogout() {
    Logger::getInstance().info("User logged out: " + std::to_string(currentUserId));
    close();
    // Emit signal to show login window again
}

