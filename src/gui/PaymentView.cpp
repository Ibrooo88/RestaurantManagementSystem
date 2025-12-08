#include "../../include/gui/PaymentView.h"
#include "../../include/repositories/PaymentRepository.h"
#include "../../include/repositories/OrderRepository.h"
#include "../../include/models/Payment.h"
#include "../../include/enums/PaymentMethod.h"
#include "../../include/enums/PaymentStatus.h"
#include <QHeaderView>

PaymentView::PaymentView(QWidget *parent)
    : QWidget(parent), currentPaymentId(-1) {
    setupUI();
    loadOrders();
    loadPayments();
}

PaymentView::~PaymentView() {
}

void PaymentView::setupUI() {
    mainLayout = new QVBoxLayout(this);
    
    // Form Group
    formGroup = new QGroupBox("Process Payment", this);
    formLayout = new QVBoxLayout();
    
    QHBoxLayout* orderLayout = new QHBoxLayout();
    orderLayout->addWidget(new QLabel("Order:", this));
    orderCombo = new QComboBox(this);
    orderCombo->addItem("Select Order", -1);
    orderLayout->addWidget(orderCombo);
    formLayout->addLayout(orderLayout);
    
    QHBoxLayout* amountLayout = new QHBoxLayout();
    amountLayout->addWidget(new QLabel("Amount:", this));
    amountSpin = new QDoubleSpinBox(this);
    amountSpin->setMinimum(0.0);
    amountSpin->setMaximum(10000.0);
    amountSpin->setDecimals(2);
    amountSpin->setPrefix("$ ");
    amountLayout->addWidget(amountSpin);
    formLayout->addLayout(amountLayout);
    
    QHBoxLayout* methodLayout = new QHBoxLayout();
    methodLayout->addWidget(new QLabel("Payment Method:", this));
    paymentMethodCombo = new QComboBox(this);
    paymentMethodCombo->addItem("Cash", static_cast<int>(PaymentMethod::CASH));
    paymentMethodCombo->addItem("Credit Card", static_cast<int>(PaymentMethod::CREDIT_CARD));
    paymentMethodCombo->addItem("Debit Card", static_cast<int>(PaymentMethod::DEBIT_CARD));
    paymentMethodCombo->addItem("Mobile Payment", static_cast<int>(PaymentMethod::MOBILE_PAYMENT));
    paymentMethodCombo->addItem("Online Payment", static_cast<int>(PaymentMethod::ONLINE_PAYMENT));
    methodLayout->addWidget(paymentMethodCombo);
    formLayout->addLayout(methodLayout);
    
    processBtn = new QPushButton("Process Payment", this);
    processBtn->setStyleSheet("background-color: #4CAF50; color: white; padding: 8px;");
    connect(processBtn, &QPushButton::clicked, this, &PaymentView::onProcessPaymentClicked);
    formLayout->addWidget(processBtn);
    
    formGroup->setLayout(formLayout);
    mainLayout->addWidget(formGroup);
    
    // Table Group
    tableGroup = new QGroupBox("Payment History", this);
    QVBoxLayout* tableLayout = new QVBoxLayout();
    
    refreshBtn = new QPushButton("Refresh", this);
    connect(refreshBtn, &QPushButton::clicked, this, &PaymentView::onRefreshClicked);
    
    paymentsTable = new QTableWidget(this);
    paymentsTable->setColumnCount(6);
    paymentsTable->setHorizontalHeaderLabels(QStringList() << "ID" << "Order #" << "Amount" << "Method" << "Status" << "Date");
    paymentsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    paymentsTable->horizontalHeader()->setStretchLastSection(true);
    connect(paymentsTable, &QTableWidget::itemSelectionChanged, this, &PaymentView::onPaymentSelectionChanged);
    
    tableLayout->addWidget(refreshBtn);
    tableLayout->addWidget(paymentsTable);
    tableGroup->setLayout(tableLayout);
    mainLayout->addWidget(tableGroup);
}

void PaymentView::loadOrders() {
    OrderRepository orderRepo;
    auto orders = orderRepo.getAll();
    
    orderCombo->clear();
    orderCombo->addItem("Select Order", -1);
    
    for (auto* order : orders) {
        QString displayText = QString("Order #%1 - $%2").arg(order->getOrderNumber().c_str()).arg(order->getTotalAmount(), 0, 'f', 2);
        orderCombo->addItem(displayText, order->getId());
        delete order;
    }
}

void PaymentView::loadPayments() {
    PaymentRepository paymentRepo;
    auto payments = paymentRepo.getAll();
    
    paymentsTable->setRowCount(0);
    
    for (auto* payment : payments) {
        OrderRepository orderRepo;
        Order* order = orderRepo.getById(payment->getOrderId());
        QString orderNumber = order ? order->getOrderNumber().c_str() : "N/A";
        if (order) delete order;
        
        int row = paymentsTable->rowCount();
        paymentsTable->insertRow(row);
        
        paymentsTable->setItem(row, 0, new QTableWidgetItem(QString::number(payment->getId())));
        paymentsTable->setItem(row, 1, new QTableWidgetItem(orderNumber));
        paymentsTable->setItem(row, 2, new QTableWidgetItem("$" + QString::number(payment->getAmount(), 'f', 2)));
        
        QString methodStr = "Cash";
        switch (payment->getPaymentMethod()) {
            case PaymentMethod::CREDIT_CARD: methodStr = "Credit Card"; break;
            case PaymentMethod::DEBIT_CARD: methodStr = "Debit Card"; break;
            case PaymentMethod::MOBILE_PAYMENT: methodStr = "Mobile Payment"; break;
            case PaymentMethod::ONLINE_PAYMENT: methodStr = "Online Payment"; break;
        }
        paymentsTable->setItem(row, 3, new QTableWidgetItem(methodStr));
        
        QString statusStr = "Pending";
        switch (payment->getStatus()) {
            case PaymentStatus::COMPLETED: statusStr = "Completed"; break;
            case PaymentStatus::FAILED: statusStr = "Failed"; break;
            case PaymentStatus::REFUNDED: statusStr = "Refunded"; break;
        }
        paymentsTable->setItem(row, 4, new QTableWidgetItem(statusStr));
        paymentsTable->setItem(row, 5, new QTableWidgetItem(payment->getPaymentDate().c_str()));
        
        paymentsTable->item(row, 0)->setData(Qt::UserRole, payment->getId());
        
        delete payment;
    }
}

void PaymentView::onProcessPaymentClicked() {
    int orderId = orderCombo->currentData().toInt();
    if (orderId == -1) {
        QMessageBox::warning(this, "Warning", "Please select an order.");
        return;
    }
    
    double amount = amountSpin->value();
    if (amount <= 0) {
        QMessageBox::warning(this, "Warning", "Please enter a valid amount.");
        return;
    }
    
    Payment* payment = new Payment();
    payment->setOrderId(orderId);
    payment->setAmount(amount);
    payment->setPaymentMethod(static_cast<PaymentMethod>(paymentMethodCombo->currentData().toInt()));
    payment->setStatus(PaymentStatus::COMPLETED);
    
    PaymentRepository paymentRepo;
    if (paymentRepo.insert(payment)) {
        QMessageBox::information(this, "Success", "Payment processed successfully!");
        loadPayments();
        loadOrders();
    } else {
        QMessageBox::critical(this, "Error", "Failed to process payment.");
    }
    
    delete payment;
}

void PaymentView::onPaymentSelectionChanged() {
    int currentRow = paymentsTable->currentRow();
    if (currentRow < 0) {
        currentPaymentId = -1;
        return;
    }
    
    currentPaymentId = paymentsTable->item(currentRow, 0)->data(Qt::UserRole).toInt();
}

void PaymentView::onRefreshClicked() {
    loadPayments();
    loadOrders();
}

