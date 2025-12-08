#include "../../include/gui/AdminLogView.h"
#include "../../include/repositories/AdminActionLogRepository.h"
#include "../../include/repositories/UserRepository.h"
#include <QHeaderView>

AdminLogView::AdminLogView(QWidget *parent)
    : QWidget(parent) {
    setupUI();
    loadLogs();
}

AdminLogView::~AdminLogView() {
}

void AdminLogView::setupUI() {
    mainLayout = new QVBoxLayout(this);
    
    // Filter Group
    filterGroup = new QGroupBox("Filter Logs", this);
    filterLayout = new QHBoxLayout();
    
    userLabel = new QLabel("User:", this);
    userEdit = new QLineEdit(this);
    userEdit->setPlaceholderText("Enter username");
    
    actionLabel = new QLabel("Action:", this);
    actionCombo = new QComboBox(this);
    actionCombo->addItem("All Actions", "");
    actionCombo->addItem("Create", "CREATE");
    actionCombo->addItem("Update", "UPDATE");
    actionCombo->addItem("Delete", "DELETE");
    actionCombo->addItem("Login", "LOGIN");
    actionCombo->addItem("Logout", "LOGOUT");
    
    dateLabel = new QLabel("Date:", this);
    dateEdit = new QDateEdit(this);
    dateEdit->setDate(QDate::currentDate());
    dateEdit->setCalendarPopup(true);
    
    filterBtn = new QPushButton("Filter", this);
    connect(filterBtn, &QPushButton::clicked, this, &AdminLogView::onFilterClicked);
    
    refreshBtn = new QPushButton("Refresh", this);
    connect(refreshBtn, &QPushButton::clicked, this, &AdminLogView::onRefreshClicked);
    
    filterLayout->addWidget(userLabel);
    filterLayout->addWidget(userEdit);
    filterLayout->addWidget(actionLabel);
    filterLayout->addWidget(actionCombo);
    filterLayout->addWidget(dateLabel);
    filterLayout->addWidget(dateEdit);
    filterLayout->addWidget(filterBtn);
    filterLayout->addWidget(refreshBtn);
    filterLayout->addStretch();
    
    filterGroup->setLayout(filterLayout);
    mainLayout->addWidget(filterGroup);
    
    // Logs Table
    tableGroup = new QGroupBox("Admin Action Logs", this);
    QVBoxLayout* tableLayout = new QVBoxLayout();
    
    logsTable = new QTableWidget(this);
    logsTable->setColumnCount(6);
    logsTable->setHorizontalHeaderLabels(QStringList() << "ID" << "User" << "Action" << "Entity" << "Description" << "Date");
    logsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    logsTable->horizontalHeader()->setStretchLastSection(true);
    
    tableLayout->addWidget(logsTable);
    tableGroup->setLayout(tableLayout);
    mainLayout->addWidget(tableGroup);
}

void AdminLogView::loadLogs() {
    AdminActionLogRepository logRepo;
    auto logs = logRepo.getAll();
    
    logsTable->setRowCount(0);
    
    for (auto* log : logs) {
        UserRepository userRepo;
        User* user = userRepo.getById(log->getUserId());
        QString userName = user ? user->getUsername().c_str() : "Unknown";
        if (user) delete user;
        
        int row = logsTable->rowCount();
        logsTable->insertRow(row);
        
        logsTable->setItem(row, 0, new QTableWidgetItem(QString::number(log->getId())));
        logsTable->setItem(row, 1, new QTableWidgetItem(userName));
        logsTable->setItem(row, 2, new QTableWidgetItem(log->getActionType().c_str()));
        logsTable->setItem(row, 3, new QTableWidgetItem(log->getEntityType().c_str()));
        logsTable->setItem(row, 4, new QTableWidgetItem(log->getDescription().c_str()));
        logsTable->setItem(row, 5, new QTableWidgetItem(log->getCreatedAt().c_str()));
        
        delete log;
    }
}

void AdminLogView::onRefreshClicked() {
    loadLogs();
}

void AdminLogView::onFilterClicked() {
    // Filter implementation can be added here
    loadLogs();
}

