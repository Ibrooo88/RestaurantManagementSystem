#include "../../include/gui/StatisticsView.h"
#include "../../include/repositories/OrderRepository.h"
#include "../../include/repositories/PaymentRepository.h"
#include "../../include/enums/OrderStatus.h"
#include "../../include/enums/PaymentStatus.h"
#include <QHeaderView>

StatisticsView::StatisticsView(QWidget *parent)
    : QWidget(parent) {
    setupUI();
    loadStatistics();
}

StatisticsView::~StatisticsView() {
}

void StatisticsView::setupUI() {
    mainLayout = new QVBoxLayout(this);
    
    // Filter Group
    filterGroup = new QGroupBox("Filter", this);
    filterLayout = new QHBoxLayout();
    
    dateLabel = new QLabel("Date:", this);
    dateEdit = new QDateEdit(this);
    dateEdit->setDate(QDate::currentDate());
    dateEdit->setCalendarPopup(true);
    connect(dateEdit, &QDateEdit::dateChanged, this, &StatisticsView::onDateChanged);
    
    refreshBtn = new QPushButton("Refresh", this);
    connect(refreshBtn, &QPushButton::clicked, this, &StatisticsView::onRefreshClicked);
    
    filterLayout->addWidget(dateLabel);
    filterLayout->addWidget(dateEdit);
    filterLayout->addWidget(refreshBtn);
    filterLayout->addStretch();
    
    filterGroup->setLayout(filterLayout);
    mainLayout->addWidget(filterGroup);
    
    // Statistics Cards
    statsGroup = new QGroupBox("Statistics", this);
    statsLayout = new QGridLayout();
    
    totalOrdersLabel = new QLabel("Total Orders:", this);
    totalOrdersValue = new QLabel("0", this);
    totalOrdersValue->setStyleSheet("font-size: 20px; font-weight: bold; color: #2196F3;");
    
    totalRevenueLabel = new QLabel("Total Revenue:", this);
    totalRevenueValue = new QLabel("$0.00", this);
    totalRevenueValue->setStyleSheet("font-size: 20px; font-weight: bold; color: #4CAF50;");
    
    avgOrderValueLabel = new QLabel("Average Order Value:", this);
    avgOrderValue = new QLabel("$0.00", this);
    avgOrderValue->setStyleSheet("font-size: 20px; font-weight: bold; color: #FF9800;");
    
    completedOrdersLabel = new QLabel("Completed Orders:", this);
    completedOrdersValue = new QLabel("0", this);
    completedOrdersValue->setStyleSheet("font-size: 20px; font-weight: bold; color: #9C27B0;");
    
    statsLayout->addWidget(totalOrdersLabel, 0, 0);
    statsLayout->addWidget(totalOrdersValue, 0, 1);
    statsLayout->addWidget(totalRevenueLabel, 0, 2);
    statsLayout->addWidget(totalRevenueValue, 0, 3);
    statsLayout->addWidget(avgOrderValueLabel, 1, 0);
    statsLayout->addWidget(avgOrderValue, 1, 1);
    statsLayout->addWidget(completedOrdersLabel, 1, 2);
    statsLayout->addWidget(completedOrdersValue, 1, 3);
    
    statsGroup->setLayout(statsLayout);
    mainLayout->addWidget(statsGroup);
    
    // Statistics Table
    tableGroup = new QGroupBox("Detailed Statistics", this);
    QVBoxLayout* tableLayout = new QVBoxLayout();
    
    statsTable = new QTableWidget(this);
    statsTable->setColumnCount(4);
    statsTable->setHorizontalHeaderLabels(QStringList() << "Date" << "Orders" << "Revenue" << "Avg Order");
    statsTable->horizontalHeader()->setStretchLastSection(true);
    
    tableLayout->addWidget(statsTable);
    tableGroup->setLayout(tableLayout);
    mainLayout->addWidget(tableGroup);
}

void StatisticsView::loadStatistics() {
    updateStatistics();
}

void StatisticsView::updateStatistics() {
    OrderRepository orderRepo;
    PaymentRepository paymentRepo;
    
    auto allOrders = orderRepo.getAll();
    auto allPayments = paymentRepo.getAll();
    
    // Calculate statistics
    int totalOrders = allOrders.size();
    double totalRevenue = 0.0;
    int completedOrders = 0;
    
    for (auto* order : allOrders) {
        if (order->getStatus() == OrderStatus::COMPLETED) {
            completedOrders++;
        }
        delete order;
    }
    
    for (auto* payment : allPayments) {
        if (payment->getStatus() == PaymentStatus::COMPLETED) {
            totalRevenue += payment->getAmount();
        }
        delete payment;
    }
    
    double avgOrder = totalOrders > 0 ? totalRevenue / totalOrders : 0.0;
    
    // Update labels
    totalOrdersValue->setText(QString::number(totalOrders));
    totalRevenueValue->setText("$" + QString::number(totalRevenue, 'f', 2));
    avgOrderValue->setText("$" + QString::number(avgOrder, 'f', 2));
    completedOrdersValue->setText(QString::number(completedOrders));
    
    // Update table (simplified - can be enhanced with date filtering)
    statsTable->setRowCount(1);
    statsTable->setItem(0, 0, new QTableWidgetItem(dateEdit->date().toString("yyyy-MM-dd")));
    statsTable->setItem(0, 1, new QTableWidgetItem(QString::number(totalOrders)));
    statsTable->setItem(0, 2, new QTableWidgetItem("$" + QString::number(totalRevenue, 'f', 2)));
    statsTable->setItem(0, 3, new QTableWidgetItem("$" + QString::number(avgOrder, 'f', 2)));
}

void StatisticsView::onRefreshClicked() {
    updateStatistics();
}

void StatisticsView::onDateChanged() {
    updateStatistics();
}

