#include "../../include/gui/DashboardWindow.h"
#include "../../include/repositories/OrderRepository.h"
#include "../../include/repositories/TableRepository.h"
#include "../../include/enums/OrderStatus.h"
#include "../../include/enums/TableStatus.h"
#include <QHeaderView>

DashboardWindow::DashboardWindow(QWidget *parent)
    : QWidget(parent) {
    setupUI();
    loadStatistics();
}

DashboardWindow::~DashboardWindow() {
}

void DashboardWindow::setupUI() {
    mainLayout = new QVBoxLayout(this);
    
    // Statistics Cards
    statsGroup = new QGroupBox("Statistics", this);
    statsLayout = new QGridLayout();
    
    totalOrdersLabel = new QLabel("Total Orders Today:", this);
    totalOrdersValue = new QLabel("0", this);
    totalOrdersValue->setStyleSheet("font-size: 24px; font-weight: bold; color: #2196F3;");
    
    totalRevenueLabel = new QLabel("Total Revenue Today:", this);
    totalRevenueValue = new QLabel("$0.00", this);
    totalRevenueValue->setStyleSheet("font-size: 24px; font-weight: bold; color: #4CAF50;");
    
    pendingOrdersLabel = new QLabel("Pending Orders:", this);
    pendingOrdersValue = new QLabel("0", this);
    pendingOrdersValue->setStyleSheet("font-size: 24px; font-weight: bold; color: #FF9800;");
    
    activeTablesLabel = new QLabel("Active Tables:", this);
    activeTablesValue = new QLabel("0", this);
    activeTablesValue->setStyleSheet("font-size: 24px; font-weight: bold; color: #9C27B0;");
    
    statsLayout->addWidget(totalOrdersLabel, 0, 0);
    statsLayout->addWidget(totalOrdersValue, 0, 1);
    statsLayout->addWidget(totalRevenueLabel, 0, 2);
    statsLayout->addWidget(totalRevenueValue, 0, 3);
    statsLayout->addWidget(pendingOrdersLabel, 1, 0);
    statsLayout->addWidget(pendingOrdersValue, 1, 1);
    statsLayout->addWidget(activeTablesLabel, 1, 2);
    statsLayout->addWidget(activeTablesValue, 1, 3);
    
    statsGroup->setLayout(statsLayout);
    mainLayout->addWidget(statsGroup);
    
    // Quick Actions
    quickActionsGroup = new QGroupBox("Quick Actions", this);
    actionsLayout = new QHBoxLayout();
    
    newOrderBtn = new QPushButton("New Order", this);
    newOrderBtn->setStyleSheet("background-color: #4CAF50; color: white; padding: 10px; font-size: 14px;");
    
    newReservationBtn = new QPushButton("New Reservation", this);
    newReservationBtn->setStyleSheet("background-color: #2196F3; color: white; padding: 10px; font-size: 14px;");
    
    viewMenuBtn = new QPushButton("View Menu", this);
    viewMenuBtn->setStyleSheet("background-color: #FF9800; color: white; padding: 10px; font-size: 14px;");
    
    actionsLayout->addWidget(newOrderBtn);
    actionsLayout->addWidget(newReservationBtn);
    actionsLayout->addWidget(viewMenuBtn);
    actionsLayout->addStretch();
    
    quickActionsGroup->setLayout(actionsLayout);
    mainLayout->addWidget(quickActionsGroup);
    
    // Recent Orders
    recentOrdersGroup = new QGroupBox("Recent Orders", this);
    QVBoxLayout* ordersLayout = new QVBoxLayout();
    
    refreshBtn = new QPushButton("Refresh", this);
    connect(refreshBtn, &QPushButton::clicked, this, &DashboardWindow::onRefreshClicked);
    
    recentOrdersTable = new QTableWidget(this);
    recentOrdersTable->setColumnCount(5);
    recentOrdersTable->setHorizontalHeaderLabels(QStringList() << "Order #" << "Table" << "Customer" << "Total" << "Status");
    recentOrdersTable->horizontalHeader()->setStretchLastSection(true);
    recentOrdersTable->setMaximumHeight(300);
    
    ordersLayout->addWidget(refreshBtn);
    ordersLayout->addWidget(recentOrdersTable);
    recentOrdersGroup->setLayout(ordersLayout);
    mainLayout->addWidget(recentOrdersGroup);
}

void DashboardWindow::loadStatistics() {
    OrderRepository orderRepo;
    TableRepository tableRepo;
    
    auto allOrders = orderRepo.getAll();
    auto allTables = tableRepo.getAll();
    
    // Calculate statistics
    int totalOrders = allOrders.size();
    double totalRevenue = 0.0;
    int pendingOrders = 0;
    int activeTables = 0;
    
    for (auto* order : allOrders) {
        totalRevenue += order->getTotalAmount();
        if (order->getStatus() == OrderStatus::PENDING || order->getStatus() == OrderStatus::IN_PROGRESS) {
            pendingOrders++;
        }
        delete order;
    }
    
    for (auto* table : allTables) {
        if (table->getStatus() == TableStatus::OCCUPIED || table->getStatus() == TableStatus::RESERVED) {
            activeTables++;
        }
        delete table;
    }
    
    // Update labels
    totalOrdersValue->setText(QString::number(totalOrders));
    totalRevenueValue->setText("$" + QString::number(totalRevenue, 'f', 2));
    pendingOrdersValue->setText(QString::number(pendingOrders));
    activeTablesValue->setText(QString::number(activeTables));
    
    // Load recent orders (last 10)
    recentOrdersTable->setRowCount(0);
    int count = 0;
    for (int i = allOrders.size() - 1; i >= 0 && count < 10; --i) {
        Order* order = allOrders[i];
        int row = recentOrdersTable->rowCount();
        recentOrdersTable->insertRow(row);
        
        recentOrdersTable->setItem(row, 0, new QTableWidgetItem(order->getOrderNumber().c_str()));
        recentOrdersTable->setItem(row, 1, new QTableWidgetItem(QString::number(order->getTableId())));
        recentOrdersTable->setItem(row, 2, new QTableWidgetItem(order->getCustomerName().c_str()));
        recentOrdersTable->setItem(row, 3, new QTableWidgetItem("$" + QString::number(order->getTotalAmount(), 'f', 2)));
        
        QString statusStr = "PENDING";
        switch (order->getStatus()) {
            case OrderStatus::IN_PROGRESS: statusStr = "IN_PROGRESS"; break;
            case OrderStatus::READY: statusStr = "READY"; break;
            case OrderStatus::SERVED: statusStr = "SERVED"; break;
            case OrderStatus::COMPLETED: statusStr = "COMPLETED"; break;
            case OrderStatus::CANCELLED: statusStr = "CANCELLED"; break;
        }
        recentOrdersTable->setItem(row, 4, new QTableWidgetItem(statusStr));
        count++;
    }
}

void DashboardWindow::onRefreshClicked() {
    loadStatistics();
}

void DashboardWindow::updateStatistics() {
    loadStatistics();
}

