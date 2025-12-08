#include "../../include/gui/MenuView.h"
#include "../../include/repositories/MenuItemRepository.h"
#include "../../include/models/MenuItem.h"
#include "../../include/utils/Logger.h"
#include <QHeaderView>

MenuView::MenuView(QWidget *parent)
    : QWidget(parent), currentItemId(-1) {
    setupUI();
    loadMenuItems();
}

MenuView::~MenuView() {
}

void MenuView::setupUI() {
    mainLayout = new QVBoxLayout(this);
    
    // Form Group
    formGroup = new QGroupBox("Add/Edit Menu Item", this);
    formLayout = new QVBoxLayout();
    
    QHBoxLayout* nameLayout = new QHBoxLayout();
    nameLayout->addWidget(new QLabel("Name:", this));
    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Enter item name");
    nameLayout->addWidget(nameEdit);
    formLayout->addLayout(nameLayout);
    
    QHBoxLayout* descLayout = new QHBoxLayout();
    descLayout->addWidget(new QLabel("Description:", this));
    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setMaximumHeight(80);
    descLayout->addWidget(descriptionEdit);
    formLayout->addLayout(descLayout);
    
    QHBoxLayout* priceLayout = new QHBoxLayout();
    priceLayout->addWidget(new QLabel("Price:", this));
    priceSpin = new QDoubleSpinBox(this);
    priceSpin->setMinimum(0.0);
    priceSpin->setMaximum(10000.0);
    priceSpin->setDecimals(2);
    priceSpin->setPrefix("$ ");
    priceLayout->addWidget(priceSpin);
    formLayout->addLayout(priceLayout);
    
    QHBoxLayout* categoryLayout = new QHBoxLayout();
    categoryLayout->addWidget(new QLabel("Category:", this));
    categoryEdit = new QLineEdit(this);
    categoryEdit->setPlaceholderText("e.g., Appetizer, Main Course, Dessert");
    categoryLayout->addWidget(categoryEdit);
    formLayout->addLayout(categoryLayout);
    
    QHBoxLayout* prepTimeLayout = new QHBoxLayout();
    prepTimeLayout->addWidget(new QLabel("Preparation Time (minutes):", this));
    prepTimeSpin = new QSpinBox(this);
    prepTimeSpin->setMinimum(1);
    prepTimeSpin->setMaximum(300);
    prepTimeLayout->addWidget(prepTimeSpin);
    formLayout->addLayout(prepTimeLayout);
    
    QHBoxLayout* availabilityLayout = new QHBoxLayout();
    availabilityLayout->addWidget(new QLabel("Availability:", this));
    availabilityCombo = new QComboBox(this);
    availabilityCombo->addItem("Available", true);
    availabilityCombo->addItem("Not Available", false);
    availabilityLayout->addWidget(availabilityCombo);
    formLayout->addLayout(availabilityLayout);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    addBtn = new QPushButton("Add Item", this);
    addBtn->setStyleSheet("background-color: #4CAF50; color: white; padding: 8px;");
    connect(addBtn, &QPushButton::clicked, this, &MenuView::onAddItemClicked);
    
    updateBtn = new QPushButton("Update Item", this);
    updateBtn->setStyleSheet("background-color: #2196F3; color: white; padding: 8px;");
    updateBtn->setEnabled(false);
    connect(updateBtn, &QPushButton::clicked, this, &MenuView::onUpdateItemClicked);
    
    deleteBtn = new QPushButton("Delete Item", this);
    deleteBtn->setStyleSheet("background-color: #f44336; color: white; padding: 8px;");
    deleteBtn->setEnabled(false);
    connect(deleteBtn, &QPushButton::clicked, this, &MenuView::onDeleteItemClicked);
    
    clearBtn = new QPushButton("Clear", this);
    connect(clearBtn, &QPushButton::clicked, this, &MenuView::clearForm);
    
    buttonLayout->addWidget(addBtn);
    buttonLayout->addWidget(updateBtn);
    buttonLayout->addWidget(deleteBtn);
    buttonLayout->addWidget(clearBtn);
    buttonLayout->addStretch();
    formLayout->addLayout(buttonLayout);
    
    formGroup->setLayout(formLayout);
    mainLayout->addWidget(formGroup);
    
    // Table Group
    tableGroup = new QGroupBox("Menu Items", this);
    QVBoxLayout* tableLayout = new QVBoxLayout();
    
    refreshBtn = new QPushButton("Refresh", this);
    connect(refreshBtn, &QPushButton::clicked, this, &MenuView::onRefreshClicked);
    
    menuTable = new QTableWidget(this);
    menuTable->setColumnCount(6);
    menuTable->setHorizontalHeaderLabels(QStringList() << "ID" << "Name" << "Price" << "Category" << "Prep Time" << "Available");
    menuTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    menuTable->horizontalHeader()->setStretchLastSection(true);
    connect(menuTable, &QTableWidget::itemSelectionChanged, this, &MenuView::onItemSelectionChanged);
    
    tableLayout->addWidget(refreshBtn);
    tableLayout->addWidget(menuTable);
    tableGroup->setLayout(tableLayout);
    mainLayout->addWidget(tableGroup);
}

void MenuView::loadMenuItems() {
    MenuItemRepository menuRepo;
    auto items = menuRepo.getAll();
    
    menuTable->setRowCount(0);
    
    for (auto* item : items) {
        int row = menuTable->rowCount();
        menuTable->insertRow(row);
        
        menuTable->setItem(row, 0, new QTableWidgetItem(QString::number(item->getId())));
        menuTable->setItem(row, 1, new QTableWidgetItem(item->getName().c_str()));
        menuTable->setItem(row, 2, new QTableWidgetItem(QString::number(item->getPrice(), 'f', 2)));
        menuTable->setItem(row, 3, new QTableWidgetItem(item->getCategory().c_str()));
        menuTable->setItem(row, 4, new QTableWidgetItem(QString::number(item->getPreparationTime())));
        menuTable->setItem(row, 5, new QTableWidgetItem(item->getIsAvailable() ? "Yes" : "No"));
        
        menuTable->item(row, 0)->setData(Qt::UserRole, item->getId());
        
        delete item;
    }
}

void MenuView::onAddItemClicked() {
    QString name = nameEdit->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter item name.");
        return;
    }
    
    MenuItem* item = new MenuItem();
    item->setName(name.toStdString());
    item->setDescription(descriptionEdit->toPlainText().toStdString());
    item->setPrice(priceSpin->value());
    item->setCategory(categoryEdit->text().toStdString());
    item->setPreparationTime(prepTimeSpin->value());
    item->setIsAvailable(availabilityCombo->currentData().toBool());
    
    MenuItemRepository menuRepo;
    if (menuRepo.insert(item)) {
        QMessageBox::information(this, "Success", "Menu item added successfully!");
        clearForm();
        loadMenuItems();
    } else {
        QMessageBox::critical(this, "Error", "Failed to add menu item.");
    }
    
    delete item;
}

void MenuView::onUpdateItemClicked() {
    if (currentItemId == -1) return;
    
    QString name = nameEdit->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter item name.");
        return;
    }
    
    MenuItemRepository menuRepo;
    MenuItem* item = menuRepo.getById(currentItemId);
    if (!item) {
        QMessageBox::critical(this, "Error", "Item not found.");
        return;
    }
    
    item->setName(name.toStdString());
    item->setDescription(descriptionEdit->toPlainText().toStdString());
    item->setPrice(priceSpin->value());
    item->setCategory(categoryEdit->text().toStdString());
    item->setPreparationTime(prepTimeSpin->value());
    item->setIsAvailable(availabilityCombo->currentData().toBool());
    
    if (menuRepo.update(item)) {
        QMessageBox::information(this, "Success", "Menu item updated successfully!");
        clearForm();
        loadMenuItems();
    } else {
        QMessageBox::critical(this, "Error", "Failed to update menu item.");
    }
    
    delete item;
}

void MenuView::onDeleteItemClicked() {
    if (currentItemId == -1) return;
    
    int ret = QMessageBox::question(this, "Confirm Delete", 
        "Are you sure you want to delete this menu item?",
        QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        MenuItemRepository menuRepo;
        if (menuRepo.deleteById(currentItemId)) {
            QMessageBox::information(this, "Success", "Menu item deleted successfully!");
            clearForm();
            loadMenuItems();
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete menu item.");
        }
    }
}

void MenuView::onItemSelectionChanged() {
    int currentRow = menuTable->currentRow();
    if (currentRow < 0) {
        clearForm();
        return;
    }
    
    int itemId = menuTable->item(currentRow, 0)->data(Qt::UserRole).toInt();
    populateForm(itemId);
}

void MenuView::onRefreshClicked() {
    loadMenuItems();
}

void MenuView::clearForm() {
    nameEdit->clear();
    descriptionEdit->clear();
    priceSpin->setValue(0.0);
    categoryEdit->clear();
    prepTimeSpin->setValue(1);
    availabilityCombo->setCurrentIndex(0);
    currentItemId = -1;
    updateBtn->setEnabled(false);
    deleteBtn->setEnabled(false);
}

void MenuView::populateForm(int itemId) {
    MenuItemRepository menuRepo;
    MenuItem* item = menuRepo.getById(itemId);
    if (!item) return;
    
    currentItemId = itemId;
    nameEdit->setText(item->getName().c_str());
    descriptionEdit->setPlainText(item->getDescription().c_str());
    priceSpin->setValue(item->getPrice());
    categoryEdit->setText(item->getCategory().c_str());
    prepTimeSpin->setValue(item->getPreparationTime());
    availabilityCombo->setCurrentIndex(item->getIsAvailable() ? 0 : 1);
    
    updateBtn->setEnabled(true);
    deleteBtn->setEnabled(true);
    
    delete item;
}

