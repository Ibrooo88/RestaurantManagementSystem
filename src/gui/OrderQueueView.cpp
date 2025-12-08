#include "../../include/gui/OrderQueueView.h"
#include "../../include/repositories/OrderRepository.h"
#include "../../include/repositories/ChefRepository.h"
#include "../../include/services/OrderService.h"
#include "../../include/enums/OrderStatus.h"
#include <QHeaderView>

OrderQueueView::OrderQueueView(QWidget *parent)
    : QWidget(parent), currentOrderId(-1) {
    setupUI();
    loadQueue();
}

OrderQueueView::~OrderQueueView() {
}

void OrderQueueView::setupUI() {
    mainLayout = new QVBoxLayout(this);
    
    // Queue Table
    queueGroup = new QGroupBox("Order Queue", this);
    QVBoxLayout* queueLayout = new QVBoxLayout();
    
    refreshBtn = new QPushButton("Refresh", this);
    connect(refreshBtn, &QPushButton::clicked, this, &OrderQueueView::onRefreshClicked);
    
    queueTable = new QTableWidget(this);
    queueTable->setColumnCount(7);
    queueTable->setHorizontalHeaderLabels(QStringList() << "Order #" << "Table" << "Customer" << "Items" << "Total" << "Status" << "Chef");
    queueTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    queueTable->horizontalHeader()->setStretchLastSection(true);
    connect(queueTable, &QTableWidget::itemSelectionChanged, this, &OrderQueueView::onQueueSelectionChanged);
    
    queueLayout->addWidget(refreshBtn);
    queueLayout->addWidget(queueTable);
    queueGroup->setLayout(queueLayout);
    mainLayout->addWidget(queueGroup);
    
    // Actions Group
    actionsGroup = new QGroupBox("Actions", this);
    actionsLayout = new QHBoxLayout();
    
    chefLabel = new QLabel("Assign Chef:", this);
    chefCombo = new QComboBox(this);
    chefCombo->addItem("Select Chef", -1);
    
    assignChefBtn = new QPushButton("Assign Chef", this);
    assignChefBtn->setStyleSheet("background-color: #2196F3; color: white; padding: 8px;");
    assignChefBtn->setEnabled(false);
    connect(assignChefBtn, &QPushButton::clicked, this, &OrderQueueView::onAssignChefClicked);
    
    statusLabel = new QLabel("Update Status:", this);
    statusCombo = new QComboBox(this);
    statusCombo->addItem("Pending", static_cast<int>(OrderStatus::PENDING));
    statusCombo->addItem("In Progress", static_cast<int>(OrderStatus::IN_PROGRESS));
    statusCombo->addItem("Ready", static_cast<int>(OrderStatus::READY));
    statusCombo->addItem("Served", static_cast<int>(OrderStatus::SERVED));
    statusCombo->addItem("Completed", static_cast<int>(OrderStatus::COMPLETED));
    statusCombo->addItem("Cancelled", static_cast<int>(OrderStatus::CANCELLED));
    
    updateStatusBtn = new QPushButton("Update Status", this);
    updateStatusBtn->setStyleSheet("background-color: #4CAF50; color: white; padding: 8px;");
    updateStatusBtn->setEnabled(false);
    connect(updateStatusBtn, &QPushButton::clicked, this, &OrderQueueView::onUpdateStatusClicked);
    
    actionsLayout->addWidget(chefLabel);
    actionsLayout->addWidget(chefCombo);
    actionsLayout->addWidget(assignChefBtn);
    actionsLayout->addWidget(statusLabel);
    actionsLayout->addWidget(statusCombo);
    actionsLayout->addWidget(updateStatusBtn);
    actionsLayout->addStretch();
    
    actionsGroup->setLayout(actionsLayout);
    mainLayout->addWidget(actionsGroup);
    
    // Load chefs
    ChefRepository chefRepo;
    auto chefs = chefRepo.getAvailable();
    for (auto* chef : chefs) {
        chefCombo->addItem(QString("Chef #%1").arg(chef->getId()), chef->getId());
        delete chef;
    }
}

void OrderQueueView::loadQueue() {
    OrderRepository orderRepo;
    auto orders = orderRepo.getAll();
    
    queueTable->setRowCount(0);
    
    for (auto* order : orders) {
        int row = queueTable->rowCount();
        queueTable->insertRow(row);
        
        queueTable->setItem(row, 0, new QTableWidgetItem(order->getOrderNumber().c_str()));
        queueTable->setItem(row, 1, new QTableWidgetItem(QString::number(order->getTableId())));
        queueTable->setItem(row, 2, new QTableWidgetItem(order->getCustomerName().c_str()));
        queueTable->setItem(row, 3, new QTableWidgetItem("N/A")); // Items count - can be enhanced
        queueTable->setItem(row, 4, new QTableWidgetItem("$" + QString::number(order->getTotalAmount(), 'f', 2)));
        
        QString statusStr = "PENDING";
        switch (order->getStatus()) {
            case OrderStatus::IN_PROGRESS: statusStr = "IN_PROGRESS"; break;
            case OrderStatus::READY: statusStr = "READY"; break;
            case OrderStatus::SERVED: statusStr = "SERVED"; break;
            case OrderStatus::COMPLETED: statusStr = "COMPLETED"; break;
            case OrderStatus::CANCELLED: statusStr = "CANCELLED"; break;
        }
        queueTable->setItem(row, 5, new QTableWidgetItem(statusStr));
        queueTable->setItem(row, 6, new QTableWidgetItem(QString::number(order->getChefId())));
        
        queueTable->item(row, 0)->setData(Qt::UserRole, order->getId());
        
        delete order;
    }
}

void OrderQueueView::onRefreshClicked() {
    loadQueue();
}

void OrderQueueView::onAssignChefClicked() {
    if (currentOrderId == -1) {
        QMessageBox::warning(this, "Warning", "Please select an order.");
        return;
    }
    
    int chefId = chefCombo->currentData().toInt();
    if (chefId == -1) {
        QMessageBox::warning(this, "Warning", "Please select a chef.");
        return;
    }
    
    if (OrderService::assignChefToOrder(currentOrderId, chefId)) {
        QMessageBox::information(this, "Success", "Chef assigned successfully!");
        loadQueue();
    } else {
        QMessageBox::critical(this, "Error", "Failed to assign chef.");
    }
}

void OrderQueueView::onUpdateStatusClicked() {
    if (currentOrderId == -1) {
        QMessageBox::warning(this, "Warning", "Please select an order.");
        return;
    }
    
    OrderStatus status = static_cast<OrderStatus>(statusCombo->currentData().toInt());
    if (OrderService::updateOrderStatus(currentOrderId, status)) {
        QMessageBox::information(this, "Success", "Status updated successfully!");
        loadQueue();
    } else {
        QMessageBox::critical(this, "Error", "Failed to update status.");
    }
}

void OrderQueueView::onQueueSelectionChanged() {
    int currentRow = queueTable->currentRow();
    if (currentRow < 0) {
        currentOrderId = -1;
        assignChefBtn->setEnabled(false);
        updateStatusBtn->setEnabled(false);
        return;
    }
    
    currentOrderId = queueTable->item(currentRow, 0)->data(Qt::UserRole).toInt();
    assignChefBtn->setEnabled(true);
    updateStatusBtn->setEnabled(true);
}

void OrderQueueView::updateQueue() {
    loadQueue();
}

