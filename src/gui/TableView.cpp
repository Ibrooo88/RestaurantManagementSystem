#include "../../include/gui/TableView.h"
#include "../../include/repositories/TableRepository.h"
#include "../../include/models/Table.h"
#include "../../include/enums/TableStatus.h"
#include <QHeaderView>

TableView::TableView(QWidget *parent)
    : QWidget(parent), currentTableId(-1) {
    setupUI();
    loadTables();
}

TableView::~TableView() {
}

void TableView::setupUI() {
    mainLayout = new QVBoxLayout(this);
    
    // Form Group
    formGroup = new QGroupBox("Add/Edit Table", this);
    formLayout = new QVBoxLayout();
    
    QHBoxLayout* numberLayout = new QHBoxLayout();
    numberLayout->addWidget(new QLabel("Table Number:", this));
    tableNumberSpin = new QSpinBox(this);
    tableNumberSpin->setMinimum(1);
    tableNumberSpin->setMaximum(100);
    numberLayout->addWidget(tableNumberSpin);
    formLayout->addLayout(numberLayout);
    
    QHBoxLayout* capacityLayout = new QHBoxLayout();
    capacityLayout->addWidget(new QLabel("Capacity:", this));
    capacitySpin = new QSpinBox(this);
    capacitySpin->setMinimum(1);
    capacitySpin->setMaximum(20);
    capacitySpin->setValue(4);
    capacityLayout->addWidget(capacitySpin);
    formLayout->addLayout(capacityLayout);
    
    QHBoxLayout* statusLayout = new QHBoxLayout();
    statusLayout->addWidget(new QLabel("Status:", this));
    statusCombo = new QComboBox(this);
    statusCombo->addItem("Available", static_cast<int>(TableStatus::AVAILABLE));
    statusCombo->addItem("Occupied", static_cast<int>(TableStatus::OCCUPIED));
    statusCombo->addItem("Reserved", static_cast<int>(TableStatus::RESERVED));
    statusCombo->addItem("Cleaning", static_cast<int>(TableStatus::CLEANING));
    statusCombo->addItem("Out of Service", static_cast<int>(TableStatus::OUT_OF_SERVICE));
    statusLayout->addWidget(statusCombo);
    formLayout->addLayout(statusLayout);
    
    QHBoxLayout* locationLayout = new QHBoxLayout();
    locationLayout->addWidget(new QLabel("Location:", this));
    locationEdit = new QLineEdit(this);
    locationEdit->setPlaceholderText("e.g., Main Hall, Patio, VIP Room");
    locationLayout->addWidget(locationEdit);
    formLayout->addLayout(locationLayout);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    addBtn = new QPushButton("Add Table", this);
    addBtn->setStyleSheet("background-color: #4CAF50; color: white; padding: 8px;");
    connect(addBtn, &QPushButton::clicked, this, &TableView::onAddTableClicked);
    
    updateBtn = new QPushButton("Update Table", this);
    updateBtn->setStyleSheet("background-color: #2196F3; color: white; padding: 8px;");
    updateBtn->setEnabled(false);
    connect(updateBtn, &QPushButton::clicked, this, &TableView::onUpdateTableClicked);
    
    deleteBtn = new QPushButton("Delete Table", this);
    deleteBtn->setStyleSheet("background-color: #f44336; color: white; padding: 8px;");
    deleteBtn->setEnabled(false);
    connect(deleteBtn, &QPushButton::clicked, this, &TableView::onDeleteTableClicked);
    
    clearBtn = new QPushButton("Clear", this);
    connect(clearBtn, &QPushButton::clicked, this, &TableView::clearForm);
    
    buttonLayout->addWidget(addBtn);
    buttonLayout->addWidget(updateBtn);
    buttonLayout->addWidget(deleteBtn);
    buttonLayout->addWidget(clearBtn);
    buttonLayout->addStretch();
    formLayout->addLayout(buttonLayout);
    
    formGroup->setLayout(formLayout);
    mainLayout->addWidget(formGroup);
    
    // Table Group
    tableGroup = new QGroupBox("Tables", this);
    QVBoxLayout* tableLayout = new QVBoxLayout();
    
    refreshBtn = new QPushButton("Refresh", this);
    connect(refreshBtn, &QPushButton::clicked, this, &TableView::onRefreshClicked);
    
    tablesTable = new QTableWidget(this);
    tablesTable->setColumnCount(5);
    tablesTable->setHorizontalHeaderLabels(QStringList() << "ID" << "Table #" << "Capacity" << "Status" << "Location");
    tablesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    tablesTable->horizontalHeader()->setStretchLastSection(true);
    connect(tablesTable, &QTableWidget::itemSelectionChanged, this, &TableView::onTableSelectionChanged);
    
    tableLayout->addWidget(refreshBtn);
    tableLayout->addWidget(tablesTable);
    tableGroup->setLayout(tableLayout);
    mainLayout->addWidget(tableGroup);
}

void TableView::loadTables() {
    TableRepository tableRepo;
    auto tables = tableRepo.getAll();
    
    tablesTable->setRowCount(0);
    
    for (auto* table : tables) {
        int row = tablesTable->rowCount();
        tablesTable->insertRow(row);
        
        tablesTable->setItem(row, 0, new QTableWidgetItem(QString::number(table->getId())));
        tablesTable->setItem(row, 1, new QTableWidgetItem(QString::number(table->getTableNumber())));
        tablesTable->setItem(row, 2, new QTableWidgetItem(QString::number(table->getCapacity())));
        
        QString statusStr = "Available";
        switch (table->getStatus()) {
            case TableStatus::OCCUPIED: statusStr = "Occupied"; break;
            case TableStatus::RESERVED: statusStr = "Reserved"; break;
            case TableStatus::CLEANING: statusStr = "Cleaning"; break;
            case TableStatus::OUT_OF_SERVICE: statusStr = "Out of Service"; break;
        }
        tablesTable->setItem(row, 3, new QTableWidgetItem(statusStr));
        tablesTable->setItem(row, 4, new QTableWidgetItem(table->getLocation().c_str()));
        
        tablesTable->item(row, 0)->setData(Qt::UserRole, table->getId());
        
        delete table;
    }
}

void TableView::onAddTableClicked() {
    Table* table = new Table();
    table->setTableNumber(tableNumberSpin->value());
    table->setCapacity(capacitySpin->value());
    table->setStatus(static_cast<TableStatus>(statusCombo->currentData().toInt()));
    table->setLocation(locationEdit->text().toStdString());
    
    TableRepository tableRepo;
    if (tableRepo.insert(table)) {
        QMessageBox::information(this, "Success", "Table added successfully!");
        clearForm();
        loadTables();
    } else {
        QMessageBox::critical(this, "Error", "Failed to add table.");
    }
    
    delete table;
}

void TableView::onUpdateTableClicked() {
    if (currentTableId == -1) return;
    
    TableRepository tableRepo;
    Table* table = tableRepo.getById(currentTableId);
    if (!table) {
        QMessageBox::critical(this, "Error", "Table not found.");
        return;
    }
    
    table->setTableNumber(tableNumberSpin->value());
    table->setCapacity(capacitySpin->value());
    table->setStatus(static_cast<TableStatus>(statusCombo->currentData().toInt()));
    table->setLocation(locationEdit->text().toStdString());
    
    if (tableRepo.update(table)) {
        QMessageBox::information(this, "Success", "Table updated successfully!");
        clearForm();
        loadTables();
    } else {
        QMessageBox::critical(this, "Error", "Failed to update table.");
    }
    
    delete table;
}

void TableView::onDeleteTableClicked() {
    if (currentTableId == -1) return;
    
    int ret = QMessageBox::question(this, "Confirm Delete", 
        "Are you sure you want to delete this table?",
        QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        TableRepository tableRepo;
        if (tableRepo.deleteById(currentTableId)) {
            QMessageBox::information(this, "Success", "Table deleted successfully!");
            clearForm();
            loadTables();
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete table.");
        }
    }
}

void TableView::onTableSelectionChanged() {
    int currentRow = tablesTable->currentRow();
    if (currentRow < 0) {
        clearForm();
        return;
    }
    
    int tableId = tablesTable->item(currentRow, 0)->data(Qt::UserRole).toInt();
    populateForm(tableId);
}

void TableView::onRefreshClicked() {
    loadTables();
}

void TableView::clearForm() {
    tableNumberSpin->setValue(1);
    capacitySpin->setValue(4);
    statusCombo->setCurrentIndex(0);
    locationEdit->clear();
    currentTableId = -1;
    updateBtn->setEnabled(false);
    deleteBtn->setEnabled(false);
}

void TableView::populateForm(int tableId) {
    TableRepository tableRepo;
    Table* table = tableRepo.getById(tableId);
    if (!table) return;
    
    currentTableId = tableId;
    tableNumberSpin->setValue(table->getTableNumber());
    capacitySpin->setValue(table->getCapacity());
    
    // Set status
    for (int i = 0; i < statusCombo->count(); ++i) {
        if (statusCombo->itemData(i).toInt() == static_cast<int>(table->getStatus())) {
            statusCombo->setCurrentIndex(i);
            break;
        }
    }
    
    locationEdit->setText(table->getLocation().c_str());
    
    updateBtn->setEnabled(true);
    deleteBtn->setEnabled(true);
    
    delete table;
}

