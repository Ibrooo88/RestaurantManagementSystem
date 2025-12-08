#include "../../include/gui/OrderView.h"
#include "../../include/services/OrderService.h"
#include "../../include/repositories/MenuItemRepository.h"
#include "../../include/repositories/TableRepository.h"
#include "../../include/repositories/OrderRepository.h"
#include "../../include/utils/Logger.h"
#include "../../include/enums/OrderType.h"
#include "../../include/enums/OrderStatus.h"
#include <QHeaderView>
#include <QAbstractItemView>
#include <map>

OrderView::OrderView(QWidget *parent)
    : QWidget(parent), currentTotal(0.0) {
    setupUI();
    loadMenuItems();
    loadTables();
    refreshOrdersTable();
}

OrderView::~OrderView() {
}

void OrderView::setupUI() {
    mainLayout = new QVBoxLayout(this);
    
    // Order Creation Group
    orderGroup = new QGroupBox("Create New Order", this);
    orderLayout = new QHBoxLayout();
    
    tableLabel = new QLabel("Table:", this);
    tableCombo = new QComboBox(this);
    tableCombo->addItem("Select Table", -1);
    
    customerLabel = new QLabel("Customer Name:", this);
    customerEdit = new QLineEdit(this);
    customerEdit->setPlaceholderText("Enter customer name");
    
    createOrderBtn = new QPushButton("Create Order", this);
    createOrderBtn->setStyleSheet("background-color: #4CAF50; color: white; padding: 8px;");
    connect(createOrderBtn, &QPushButton::clicked, this, &OrderView::onCreateOrderClicked);
    
    orderLayout->addWidget(tableLabel);
    orderLayout->addWidget(tableCombo);
    orderLayout->addWidget(customerLabel);
    orderLayout->addWidget(customerEdit);
    orderLayout->addWidget(createOrderBtn);
    orderGroup->setLayout(orderLayout);
    mainLayout->addWidget(orderGroup);
    
    // Menu Items Group
    menuGroup = new QGroupBox("Add Menu Item", this);
    menuLayout = new QHBoxLayout();
    
    menuItemCombo = new QComboBox(this);
    menuItemCombo->addItem("Select Menu Item", -1);
    
    quantityLabel = new QLabel("Quantity:", this);
    quantitySpin = new QSpinBox(this);
    quantitySpin->setMinimum(1);
    quantitySpin->setMaximum(10);
    quantitySpin->setValue(1);
    
    addItemBtn = new QPushButton("Add Item", this);
    connect(addItemBtn, &QPushButton::clicked, this, &OrderView::onAddItemClicked);
    
    removeItemBtn = new QPushButton("Remove Selected", this);
    connect(removeItemBtn, &QPushButton::clicked, this, &OrderView::onRemoveItemClicked);
    
    menuLayout->addWidget(new QLabel("Menu Item:", this));
    menuLayout->addWidget(menuItemCombo);
    menuLayout->addWidget(quantityLabel);
    menuLayout->addWidget(quantitySpin);
    menuLayout->addWidget(addItemBtn);
    menuLayout->addWidget(removeItemBtn);
    menuGroup->setLayout(menuLayout);
    mainLayout->addWidget(menuGroup);
    
    // Order Items Table
    orderItemsTable = new QTableWidget(this);
    orderItemsTable->setColumnCount(4);
    orderItemsTable->setHorizontalHeaderLabels(QStringList() << "Menu Item" << "Price" << "Quantity" << "Subtotal");
    orderItemsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    orderItemsTable->horizontalHeader()->setStretchLastSection(true);
    mainLayout->addWidget(orderItemsTable);
    
    // Total
    QHBoxLayout* totalLayout = new QHBoxLayout();
    totalLabel = new QLabel("Total:", this);
    totalLabel->setStyleSheet("font-size: 16px; font-weight: bold;");
    totalValueLabel = new QLabel("0.00", this);
    totalValueLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2196F3;");
    totalLayout->addStretch();
    totalLayout->addWidget(totalLabel);
    totalLayout->addWidget(totalValueLabel);
    mainLayout->addLayout(totalLayout);
    
    // Orders List
    ordersGroup = new QGroupBox("Existing Orders", this);
    QVBoxLayout* ordersLayout = new QVBoxLayout();
    
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    refreshBtn = new QPushButton("Refresh", this);
    connect(refreshBtn, &QPushButton::clicked, this, &OrderView::refreshOrdersTable);
    clearBtn = new QPushButton("Clear Order", this);
    connect(clearBtn, &QPushButton::clicked, this, &OrderView::onClearClicked);
    buttonsLayout->addWidget(refreshBtn);
    buttonsLayout->addWidget(clearBtn);
    buttonsLayout->addStretch();
    
    ordersTable = new QTableWidget(this);
    ordersTable->setColumnCount(5);
    ordersTable->setHorizontalHeaderLabels(QStringList() << "Order #" << "Table" << "Customer" << "Total" << "Status");
    ordersTable->horizontalHeader()->setStretchLastSection(true);
    
    ordersLayout->addLayout(buttonsLayout);
    ordersLayout->addWidget(ordersTable);
    ordersGroup->setLayout(ordersLayout);
    mainLayout->addWidget(ordersGroup);
}

void OrderView::loadMenuItems() {
    MenuItemRepository menuRepo;
    auto items = menuRepo.getAvailable();
    
    menuItemCombo->clear();
    menuItemCombo->addItem("Select Menu Item", -1);
    
    for (auto* item : items) {
        QString displayText = QString("%1 - $%2").arg(item->getName().c_str()).arg(item->getPrice(), 0, 'f', 2);
        menuItemCombo->addItem(displayText, item->getId());
        delete item;
    }
}

void OrderView::loadTables() {
    TableRepository tableRepo;
    auto tables = tableRepo.getAll();
    
    tableCombo->clear();
    tableCombo->addItem("Select Table", -1);
    
    for (auto* table : tables) {
        QString displayText = QString("Table %1 (Capacity: %2)").arg(table->getTableNumber()).arg(table->getCapacity());
        tableCombo->addItem(displayText, table->getId());
        delete table;
    }
}

void OrderView::onAddItemClicked() {
    int menuItemId = menuItemCombo->currentData().toInt();
    if (menuItemId == -1) {
        QMessageBox::warning(this, "Warning", "Please select a menu item.");
        return;
    }
    
    int quantity = quantitySpin->value();
    
    MenuItemRepository menuRepo;
    MenuItem* item = menuRepo.getById(menuItemId);
    if (!item) {
        QMessageBox::critical(this, "Error", "Menu item not found.");
        return;
    }
    
    // Add to table
    int row = orderItemsTable->rowCount();
    orderItemsTable->insertRow(row);
    
    double price = item->getPrice();
    double subtotal = price * quantity;
    
    orderItemsTable->setItem(row, 0, new QTableWidgetItem(item->getName().c_str()));
    orderItemsTable->setItem(row, 1, new QTableWidgetItem(QString::number(price, 'f', 2)));
    orderItemsTable->setItem(row, 2, new QTableWidgetItem(QString::number(quantity)));
    orderItemsTable->setItem(row, 3, new QTableWidgetItem(QString::number(subtotal, 'f', 2)));
    
    // Store menu item ID in first column
    orderItemsTable->item(row, 0)->setData(Qt::UserRole, menuItemId);
    
    currentTotal += subtotal;
    updateOrderTotal();
    
    delete item;
}

void OrderView::onRemoveItemClicked() {
    int currentRow = orderItemsTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Warning", "Please select an item to remove.");
        return;
    }
    
    double subtotal = orderItemsTable->item(currentRow, 3)->text().toDouble();
    currentTotal -= subtotal;
    
    orderItemsTable->removeRow(currentRow);
    updateOrderTotal();
}

void OrderView::onCreateOrderClicked() {
    int tableId = tableCombo->currentData().toInt();
    if (tableId == -1) {
        QMessageBox::warning(this, "Warning", "Please select a table.");
        return;
    }
    
    QString customerName = customerEdit->text().trimmed();
    if (customerName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter customer name.");
        return;
    }
    
    if (orderItemsTable->rowCount() == 0) {
        QMessageBox::warning(this, "Warning", "Please add at least one menu item.");
        return;
    }
    
    // Build menu items map
    std::map<int, int> menuItems;
    for (int row = 0; row < orderItemsTable->rowCount(); ++row) {
        int menuItemId = orderItemsTable->item(row, 0)->data(Qt::UserRole).toInt();
        int quantity = orderItemsTable->item(row, 2)->text().toInt();
        menuItems[menuItemId] = quantity;
    }
    
    // Create order
    Order* order = OrderService::createOrder(tableId, customerName.toStdString(), menuItems);
    
    if (order) {
        QMessageBox::information(this, "Success", 
            QString("Order created successfully!\nOrder Number: %1").arg(order->getOrderNumber().c_str()));
        
        // Clear form
        onClearClicked();
        refreshOrdersTable();
        
        delete order;
    } else {
        QMessageBox::critical(this, "Error", "Failed to create order.");
    }
}

void OrderView::onClearClicked() {
    orderItemsTable->setRowCount(0);
    customerEdit->clear();
    tableCombo->setCurrentIndex(0);
    quantitySpin->setValue(1);
    currentTotal = 0.0;
    updateOrderTotal();
}

void OrderView::updateOrderTotal() {
    totalValueLabel->setText(QString::number(currentTotal, 'f', 2));
}

void OrderView::refreshOrdersTable() {
    OrderRepository orderRepo;
    auto orders = orderRepo.getAll();
    
    ordersTable->setRowCount(0);
    
    for (auto* order : orders) {
        int row = ordersTable->rowCount();
        ordersTable->insertRow(row);
        
        ordersTable->setItem(row, 0, new QTableWidgetItem(order->getOrderNumber().c_str()));
        ordersTable->setItem(row, 1, new QTableWidgetItem(QString::number(order->getTableId())));
        ordersTable->setItem(row, 2, new QTableWidgetItem(order->getCustomerName().c_str()));
        ordersTable->setItem(row, 3, new QTableWidgetItem(QString::number(order->getTotalAmount(), 'f', 2)));
        
        QString statusStr = "PENDING";
        switch (order->getStatus()) {
            case OrderStatus::IN_PROGRESS: statusStr = "IN_PROGRESS"; break;
            case OrderStatus::READY: statusStr = "READY"; break;
            case OrderStatus::SERVED: statusStr = "SERVED"; break;
            case OrderStatus::COMPLETED: statusStr = "COMPLETED"; break;
            case OrderStatus::CANCELLED: statusStr = "CANCELLED"; break;
        }
        ordersTable->setItem(row, 4, new QTableWidgetItem(statusStr));
        
        delete order;
    }
}

void OrderView::onTableSelectionChanged() {
    // Can be used to show order details
}

