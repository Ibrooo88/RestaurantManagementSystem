#include "../../include/gui/DashboardWindow.h"
#include "../../include/repositories/OrderRepository.h"
#include "../../include/repositories/TableRepository.h"
#include "../../include/repositories/PaymentRepository.h"
#include "../../include/enums/OrderStatus.h"
#include "../../include/enums/TableStatus.h"
#include "../../include/enums/PaymentStatus.h"
#include "../../include/utils/TimeUtils.h"
#include <QHeaderView>
#include <QDateTime>
#include <QMessageBox>
#include <QBrush>
#include <QColor>

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
    connect(newOrderBtn, &QPushButton::clicked, this, &DashboardWindow::onNewOrderClicked);
    
    newReservationBtn = new QPushButton("New Reservation", this);
    newReservationBtn->setStyleSheet("background-color: #2196F3; color: white; padding: 10px; font-size: 14px;");
    connect(newReservationBtn, &QPushButton::clicked, this, &DashboardWindow::onNewReservationClicked);
    
    viewMenuBtn = new QPushButton("View Menu", this);
    viewMenuBtn->setStyleSheet("background-color: #FF9800; color: white; padding: 10px; font-size: 14px;");
    connect(viewMenuBtn, &QPushButton::clicked, this, &DashboardWindow::onViewMenuClicked);
    
    QPushButton* orderQueueBtn = new QPushButton("Order Queue", this);
    orderQueueBtn->setStyleSheet("background-color: #9C27B0; color: white; padding: 10px; font-size: 14px;");
    connect(orderQueueBtn, &QPushButton::clicked, this, &DashboardWindow::openOrderQueueView);
    
    QPushButton* tablesBtn = new QPushButton("Tables", this);
    tablesBtn->setStyleSheet("background-color: #607D8B; color: white; padding: 10px; font-size: 14px;");
    connect(tablesBtn, &QPushButton::clicked, this, &DashboardWindow::openTableView);
    
    QPushButton* paymentsBtn = new QPushButton("Payments", this);
    paymentsBtn->setStyleSheet("background-color: #795548; color: white; padding: 10px; font-size: 14px;");
    connect(paymentsBtn, &QPushButton::clicked, this, &DashboardWindow::openPaymentView);
    
    actionsLayout->addWidget(newOrderBtn);
    actionsLayout->addWidget(newReservationBtn);
    actionsLayout->addWidget(viewMenuBtn);
    actionsLayout->addWidget(orderQueueBtn);
    actionsLayout->addWidget(tablesBtn);
    actionsLayout->addWidget(paymentsBtn);
    actionsLayout->addStretch();
    
    quickActionsGroup->setLayout(actionsLayout);
    mainLayout->addWidget(quickActionsGroup);
    
    // Recent Orders
    recentOrdersGroup = new QGroupBox("Recent Orders", this);
    QVBoxLayout* ordersLayout = new QVBoxLayout();
    
    refreshBtn = new QPushButton("Refresh", this);
    connect(refreshBtn, &QPushButton::clicked, this, &DashboardWindow::onRefreshClicked);
    
    recentOrdersTable = new QTableWidget(this);
    recentOrdersTable->setColumnCount(6);
    recentOrdersTable->setHorizontalHeaderLabels(QStringList() << "Order #" << "Table" << "Customer" << "Total" << "Status" << "Payment");
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
    
    // Load recent orders (last 10) - do this BEFORE deleting orders
    recentOrdersTable->setRowCount(0);
    PaymentRepository paymentRepo;
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
        
        // Check payment status
        auto payments = paymentRepo.getByOrderId(order->getId());
        QString paymentStr = "Not Paid";
        bool hasCompletedPayment = false;
        for (auto* payment : payments) {
            if (payment->getStatus() == PaymentStatus::COMPLETED) {
                paymentStr = "Paid";
                hasCompletedPayment = true;
            }
            delete payment;
        }
        QTableWidgetItem* paymentItem = new QTableWidgetItem(paymentStr);
        if (hasCompletedPayment) {
            paymentItem->setForeground(QBrush(QColor(0, 150, 0))); // Green color
        }
        recentOrdersTable->setItem(row, 5, paymentItem);
        
        count++;
    }
    
    // Clean up orders AFTER using them
    for (auto* order : allOrders) {
        delete order;
    }
}

void DashboardWindow::onRefreshClicked() {
    loadStatistics();
}

void DashboardWindow::onNewOrderClicked() {
    emit openOrderView();
}

void DashboardWindow::onNewReservationClicked() {
    emit openReservationView();
}

void DashboardWindow::onViewMenuClicked() {
    emit openMenuView();
}

void DashboardWindow::updateStatistics() {
    loadStatistics();
}

