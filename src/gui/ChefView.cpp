#include "../../include/gui/ChefView.h"
#include "../../include/repositories/ChefRepository.h"
#include "../../include/repositories/UserRepository.h"
#include "../../include/models/Chef.h"
#include "../../include/models/User.h"
#include "../../include/enums/ChefType.h"
#include "../../include/enums/ChefStatus.h"
#include "../../include/utils/Logger.h"
#include <QHeaderView>

ChefView::ChefView(QWidget *parent)
    : QWidget(parent), currentChefId(-1) {
    setupUI();
    loadChefs();
}

ChefView::~ChefView() {
}

void ChefView::setupUI() {
    mainLayout = new QVBoxLayout(this);
    
    // Form Group
    formGroup = new QGroupBox("Add/Edit Chef", this);
    formLayout = new QVBoxLayout();
    
    QHBoxLayout* nameLayout = new QHBoxLayout();
    nameLayout->addWidget(new QLabel("Chef Name:", this));
    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Enter chef name");
    nameLayout->addWidget(nameEdit);
    formLayout->addLayout(nameLayout);
    
    QHBoxLayout* typeLayout = new QHBoxLayout();
    typeLayout->addWidget(new QLabel("Chef Type:", this));
    chefTypeCombo = new QComboBox(this);
    chefTypeCombo->addItem("Normal Chef", static_cast<int>(ChefType::NORMAL_CHEF));
    chefTypeCombo->addItem("Vegan Chef", static_cast<int>(ChefType::VEGAN_CHEF));
    chefTypeCombo->addItem("VIP Chef", static_cast<int>(ChefType::VIP_CHEF));
    typeLayout->addWidget(chefTypeCombo);
    formLayout->addLayout(typeLayout);
    
    QHBoxLayout* statusLayout = new QHBoxLayout();
    statusLayout->addWidget(new QLabel("Status:", this));
    statusCombo = new QComboBox(this);
    statusCombo->addItem("Available", static_cast<int>(ChefStatus::AVAILABLE));
    statusCombo->addItem("Busy", static_cast<int>(ChefStatus::BUSY));
    statusCombo->addItem("On Break", static_cast<int>(ChefStatus::ON_BREAK));
    statusCombo->addItem("Off Duty", static_cast<int>(ChefStatus::OFF_DUTY));
    connect(statusCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ChefView::onStatusChanged);
    statusLayout->addWidget(statusCombo);
    formLayout->addLayout(statusLayout);
    
    QHBoxLayout* skillLayout = new QHBoxLayout();
    skillLayout->addWidget(new QLabel("Skill Level (1-10):", this));
    skillLevelSpin = new QSpinBox(this);
    skillLevelSpin->setMinimum(1);
    skillLevelSpin->setMaximum(10);
    skillLevelSpin->setValue(5);
    skillLayout->addWidget(skillLevelSpin);
    formLayout->addLayout(skillLayout);
    
    QHBoxLayout* specLayout = new QHBoxLayout();
    specLayout->addWidget(new QLabel("Specialization:", this));
    specializationEdit = new QLineEdit(this);
    specializationEdit->setPlaceholderText("e.g., Italian, Asian, Desserts");
    specLayout->addWidget(specializationEdit);
    formLayout->addLayout(specLayout);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    addBtn = new QPushButton("Add Chef", this);
    addBtn->setStyleSheet("background-color: #4CAF50; color: white; padding: 8px;");
    connect(addBtn, &QPushButton::clicked, this, &ChefView::onAddChefClicked);
    
    updateBtn = new QPushButton("Update Chef", this);
    updateBtn->setStyleSheet("background-color: #2196F3; color: white; padding: 8px;");
    updateBtn->setEnabled(false);
    connect(updateBtn, &QPushButton::clicked, this, &ChefView::onUpdateChefClicked);
    
    deleteBtn = new QPushButton("Delete Chef", this);
    deleteBtn->setStyleSheet("background-color: #f44336; color: white; padding: 8px;");
    deleteBtn->setEnabled(false);
    connect(deleteBtn, &QPushButton::clicked, this, &ChefView::onDeleteChefClicked);
    
    clearBtn = new QPushButton("Clear", this);
    connect(clearBtn, &QPushButton::clicked, this, &ChefView::clearForm);
    
    buttonLayout->addWidget(addBtn);
    buttonLayout->addWidget(updateBtn);
    buttonLayout->addWidget(deleteBtn);
    buttonLayout->addWidget(clearBtn);
    buttonLayout->addStretch();
    formLayout->addLayout(buttonLayout);
    
    formGroup->setLayout(formLayout);
    mainLayout->addWidget(formGroup);
    
    // Table Group
    tableGroup = new QGroupBox("Chefs", this);
    QVBoxLayout* tableLayout = new QVBoxLayout();
    
    refreshBtn = new QPushButton("Refresh", this);
    connect(refreshBtn, &QPushButton::clicked, this, &ChefView::onRefreshClicked);
    
    chefsTable = new QTableWidget(this);
    chefsTable->setColumnCount(6);
    chefsTable->setHorizontalHeaderLabels(QStringList() << "ID" << "Name" << "Type" << "Status" << "Skill Level" << "Specialization");
    chefsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    chefsTable->horizontalHeader()->setStretchLastSection(true);
    connect(chefsTable, &QTableWidget::itemSelectionChanged, this, &ChefView::onChefSelectionChanged);
    
    tableLayout->addWidget(refreshBtn);
    tableLayout->addWidget(chefsTable);
    tableGroup->setLayout(tableLayout);
    mainLayout->addWidget(tableGroup);
}

void ChefView::loadChefs() {
    ChefRepository chefRepo;
    UserRepository userRepo;
    auto chefs = chefRepo.getAll();
    
    chefsTable->setRowCount(0);
    
    for (auto* chef : chefs) {
        User* user = userRepo.getById(chef->getUserId());
        QString userName = user ? user->getFullName().c_str() : "Unknown";
        if (user) delete user;
        
        int row = chefsTable->rowCount();
        chefsTable->insertRow(row);
        
        chefsTable->setItem(row, 0, new QTableWidgetItem(QString::number(chef->getId())));
        chefsTable->setItem(row, 1, new QTableWidgetItem(userName));
        
        QString typeStr = "Normal Chef";
        switch (chef->getChefType()) {
            case ChefType::NORMAL_CHEF: typeStr = "Normal Chef"; break;
            case ChefType::VEGAN_CHEF: typeStr = "Vegan Chef"; break;
            case ChefType::VIP_CHEF: typeStr = "VIP Chef"; break;
        }
        chefsTable->setItem(row, 2, new QTableWidgetItem(typeStr));
        
        QString statusStr = "Available";
        switch (chef->getStatus()) {
            case ChefStatus::BUSY: statusStr = "Busy"; break;
            case ChefStatus::ON_BREAK: statusStr = "On Break"; break;
            case ChefStatus::OFF_DUTY: statusStr = "Off Duty"; break;
        }
        chefsTable->setItem(row, 3, new QTableWidgetItem(statusStr));
        chefsTable->setItem(row, 4, new QTableWidgetItem(QString::number(chef->getSkillLevel())));
        chefsTable->setItem(row, 5, new QTableWidgetItem(chef->getSpecialization().c_str()));
        
        chefsTable->item(row, 0)->setData(Qt::UserRole, chef->getId());
        
        delete chef;
    }
}

void ChefView::onAddChefClicked() {
    QString name = nameEdit->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter chef name.");
        return;
    }
    
    // Create user first
    User* user = new User();
    user->setUsername(name.toLower().replace(" ", "_").toStdString());
    user->setPassword("chef123");
    user->setFullName(name.toStdString());
    user->setRoleId(2); // Chef role
    
    UserRepository userRepo;
    if (!userRepo.insert(user)) {
        QMessageBox::critical(this, "Error", "Failed to create user for chef.");
        delete user;
        return;
    }
    
    // Create chef
    Chef* chef = new Chef();
    chef->setUserId(user->getId());
    chef->setChefType(static_cast<ChefType>(chefTypeCombo->currentData().toInt()));
    chef->setStatus(static_cast<ChefStatus>(statusCombo->currentData().toInt()));
    chef->setSkillLevel(skillLevelSpin->value());
    chef->setSpecialization(specializationEdit->text().toStdString());
    
    ChefRepository chefRepo;
    if (chefRepo.insert(chef)) {
        QMessageBox::information(this, "Success", "Chef added successfully!");
        clearForm();
        loadChefs();
    } else {
        QMessageBox::critical(this, "Error", "Failed to add chef.");
    }
    
    delete user;
    delete chef;
}

void ChefView::onUpdateChefClicked() {
    if (currentChefId == -1) return;
    
    ChefRepository chefRepo;
    Chef* chef = chefRepo.getById(currentChefId);
    if (!chef) {
        QMessageBox::critical(this, "Error", "Chef not found.");
        return;
    }
    
    chef->setChefType(static_cast<ChefType>(chefTypeCombo->currentData().toInt()));
    chef->setStatus(static_cast<ChefStatus>(statusCombo->currentData().toInt()));
    chef->setSkillLevel(skillLevelSpin->value());
    chef->setSpecialization(specializationEdit->text().toStdString());
    
    if (chefRepo.update(chef)) {
        QMessageBox::information(this, "Success", "Chef updated successfully!");
        clearForm();
        loadChefs();
    } else {
        QMessageBox::critical(this, "Error", "Failed to update chef.");
    }
    
    delete chef;
}

void ChefView::onDeleteChefClicked() {
    if (currentChefId == -1) return;
    
    int ret = QMessageBox::question(this, "Confirm Delete", 
        "Are you sure you want to delete this chef?",
        QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        ChefRepository chefRepo;
        if (chefRepo.deleteById(currentChefId)) {
            QMessageBox::information(this, "Success", "Chef deleted successfully!");
            clearForm();
            loadChefs();
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete chef.");
        }
    }
}

void ChefView::onChefSelectionChanged() {
    int currentRow = chefsTable->currentRow();
    if (currentRow < 0) {
        clearForm();
        return;
    }
    
    int chefId = chefsTable->item(currentRow, 0)->data(Qt::UserRole).toInt();
    populateForm(chefId);
}

void ChefView::onRefreshClicked() {
    loadChefs();
}

void ChefView::onStatusChanged() {
    // Can add logic here if needed
}

void ChefView::clearForm() {
    nameEdit->clear();
    chefTypeCombo->setCurrentIndex(0);
    statusCombo->setCurrentIndex(0);
    skillLevelSpin->setValue(5);
    specializationEdit->clear();
    currentChefId = -1;
    updateBtn->setEnabled(false);
    deleteBtn->setEnabled(false);
}

void ChefView::populateForm(int chefId) {
    ChefRepository chefRepo;
    Chef* chef = chefRepo.getById(chefId);
    if (!chef) return;
    
    UserRepository userRepo;
    User* user = userRepo.getById(chef->getUserId());
    if (user) {
        nameEdit->setText(user->getFullName().c_str());
        delete user;
    }
    
    currentChefId = chefId;
    
    // Set chef type
    for (int i = 0; i < chefTypeCombo->count(); ++i) {
        if (chefTypeCombo->itemData(i).toInt() == static_cast<int>(chef->getChefType())) {
            chefTypeCombo->setCurrentIndex(i);
            break;
        }
    }
    
    // Set status
    for (int i = 0; i < statusCombo->count(); ++i) {
        if (statusCombo->itemData(i).toInt() == static_cast<int>(chef->getStatus())) {
            statusCombo->setCurrentIndex(i);
            break;
        }
    }
    
    skillLevelSpin->setValue(chef->getSkillLevel());
    specializationEdit->setText(chef->getSpecialization().c_str());
    
    updateBtn->setEnabled(true);
    deleteBtn->setEnabled(true);
    
    delete chef;
}

