#include "../../include/gui/ReservationView.h"
#include "../../include/repositories/ReservationRepository.h"
#include "../../include/repositories/TableRepository.h"
#include "../../include/repositories/PaymentRepository.h"
#include "../../include/models/Reservation.h"
#include "../../include/models/Payment.h"
#include "../../include/enums/ReservationStatus.h"
#include "../../include/enums/PaymentStatus.h"
#include <QHeaderView>
#include <QDateTime>

ReservationView::ReservationView(QWidget *parent)
    : QWidget(parent), currentReservationId(-1), filterByDate(false) {
    setupUI();
    loadReservations();
}

ReservationView::~ReservationView() {
}

void ReservationView::setupUI() {
    mainLayout = new QVBoxLayout(this);
    
    // Form Group
    formGroup = new QGroupBox("Add/Edit Reservation", this);
    formLayout = new QVBoxLayout();
    
    QHBoxLayout* nameLayout = new QHBoxLayout();
    nameLayout->addWidget(new QLabel("Customer Name:", this));
    customerNameEdit = new QLineEdit(this);
    customerNameEdit->setPlaceholderText("Enter customer name");
    nameLayout->addWidget(customerNameEdit);
    formLayout->addLayout(nameLayout);
    
    QHBoxLayout* phoneLayout = new QHBoxLayout();
    phoneLayout->addWidget(new QLabel("Phone:", this));
    customerPhoneEdit = new QLineEdit(this);
    customerPhoneEdit->setPlaceholderText("Enter phone number");
    phoneLayout->addWidget(customerPhoneEdit);
    formLayout->addLayout(phoneLayout);
    
    QHBoxLayout* emailLayout = new QHBoxLayout();
    emailLayout->addWidget(new QLabel("Email:", this));
    customerEmailEdit = new QLineEdit(this);
    customerEmailEdit->setPlaceholderText("Enter email");
    emailLayout->addWidget(customerEmailEdit);
    formLayout->addLayout(emailLayout);
    
    QHBoxLayout* tableLayout = new QHBoxLayout();
    tableLayout->addWidget(new QLabel("Table:", this));
    tableCombo = new QComboBox(this);
    tableCombo->addItem("Select Table", -1);
    tableLayout->addWidget(tableCombo);
    formLayout->addLayout(tableLayout);
    
    QHBoxLayout* dateLayout = new QHBoxLayout();
    dateLayout->addWidget(new QLabel("Date:", this));
    dateEdit = new QDateEdit(this);
    dateEdit->setDate(QDate::currentDate());
    dateEdit->setCalendarPopup(true);
    dateLayout->addWidget(dateEdit);
    formLayout->addLayout(dateLayout);
    
    QHBoxLayout* timeLayout = new QHBoxLayout();
    timeLayout->addWidget(new QLabel("Time:", this));
    timeEdit = new QTimeEdit(this);
    timeEdit->setTime(QTime::currentTime());
    timeLayout->addWidget(timeEdit);
    formLayout->addLayout(timeLayout);
    
    QHBoxLayout* guestsLayout = new QHBoxLayout();
    guestsLayout->addWidget(new QLabel("Number of Guests:", this));
    guestsSpin = new QSpinBox(this);
    guestsSpin->setMinimum(1);
    guestsSpin->setMaximum(20);
    guestsSpin->setValue(2);
    guestsLayout->addWidget(guestsSpin);
    formLayout->addLayout(guestsLayout);
    
    QHBoxLayout* statusLayout = new QHBoxLayout();
    statusLayout->addWidget(new QLabel("Status:", this));
    statusCombo = new QComboBox(this);
    statusCombo->addItem("Pending", static_cast<int>(ReservationStatus::PENDING));
    statusCombo->addItem("Confirmed", static_cast<int>(ReservationStatus::CONFIRMED));
    statusCombo->addItem("Seated", static_cast<int>(ReservationStatus::SEATED));
    statusCombo->addItem("Cancelled", static_cast<int>(ReservationStatus::CANCELLED));
    statusCombo->addItem("Completed", static_cast<int>(ReservationStatus::COMPLETED));
    statusCombo->addItem("No Show", static_cast<int>(ReservationStatus::NO_SHOW));
    statusLayout->addWidget(statusCombo);
    formLayout->addLayout(statusLayout);
    
    QHBoxLayout* requestsLayout = new QHBoxLayout();
    requestsLayout->addWidget(new QLabel("Special Requests:", this));
    specialRequestsEdit = new QTextEdit(this);
    specialRequestsEdit->setMaximumHeight(60);
    requestsLayout->addWidget(specialRequestsEdit);
    formLayout->addLayout(requestsLayout);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    addBtn = new QPushButton("Add Reservation", this);
    addBtn->setStyleSheet("background-color: #4CAF50; color: white; padding: 8px;");
    connect(addBtn, &QPushButton::clicked, this, &ReservationView::onAddReservationClicked);
    
    updateBtn = new QPushButton("Update Reservation", this);
    updateBtn->setStyleSheet("background-color: #2196F3; color: white; padding: 8px;");
    updateBtn->setEnabled(false);
    connect(updateBtn, &QPushButton::clicked, this, &ReservationView::onUpdateReservationClicked);
    
    deleteBtn = new QPushButton("Delete Reservation", this);
    deleteBtn->setStyleSheet("background-color: #f44336; color: white; padding: 8px;");
    deleteBtn->setEnabled(false);
    connect(deleteBtn, &QPushButton::clicked, this, &ReservationView::onDeleteReservationClicked);
    
    clearBtn = new QPushButton("Clear", this);
    connect(clearBtn, &QPushButton::clicked, this, &ReservationView::clearForm);
    
    buttonLayout->addWidget(addBtn);
    buttonLayout->addWidget(updateBtn);
    buttonLayout->addWidget(deleteBtn);
    buttonLayout->addWidget(clearBtn);
    buttonLayout->addStretch();
    formLayout->addLayout(buttonLayout);
    
    formGroup->setLayout(formLayout);
    mainLayout->addWidget(formGroup);
    
    // Table Group
    tableGroup = new QGroupBox("Reservations", this);
    QVBoxLayout* reservationsLayout = new QVBoxLayout();
    
    QHBoxLayout* filterLayout = new QHBoxLayout();
    filterLayout->addWidget(new QLabel("Filter by Date:", this));
    filterDateEdit = new QDateEdit(this);
    filterDateEdit->setDate(QDate::currentDate());
    filterDateEdit->setCalendarPopup(true);
    filterLayout->addWidget(filterDateEdit);
    
    QPushButton* filterBtn = new QPushButton("Filter", this);
    connect(filterBtn, &QPushButton::clicked, this, &ReservationView::onRefreshClicked);
    filterLayout->addWidget(filterBtn);
    
    QPushButton* clearFilterBtn = new QPushButton("Show All", this);
    connect(clearFilterBtn, &QPushButton::clicked, this, &ReservationView::onClearFilterClicked);
    filterLayout->addWidget(clearFilterBtn);
    
    filterLayout->addStretch();
    
    refreshBtn = new QPushButton("Refresh", this);
    connect(refreshBtn, &QPushButton::clicked, this, &ReservationView::onRefreshClicked);
    filterLayout->addWidget(refreshBtn);
    
    reservationsLayout->addLayout(filterLayout);
    
    reservationsTable = new QTableWidget(this);
    reservationsTable->setColumnCount(9);
    reservationsTable->setHorizontalHeaderLabels(QStringList() << "ID" << "Customer" << "Table" << "Date" << "Time" << "Guests" << "Status" << "Payment" << "Requests");
    reservationsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    reservationsTable->horizontalHeader()->setStretchLastSection(true);
    connect(reservationsTable, &QTableWidget::itemSelectionChanged, this, &ReservationView::onReservationSelectionChanged);
    
    reservationsLayout->addWidget(reservationsTable);
    tableGroup->setLayout(reservationsLayout);
    mainLayout->addWidget(tableGroup);
    
    // Load tables
    TableRepository tableRepo;
    auto tables = tableRepo.getAll();
    for (auto* table : tables) {
        QString displayText = QString("Table %1 (Capacity: %2)").arg(table->getTableNumber()).arg(table->getCapacity());
        tableCombo->addItem(displayText, table->getId());
        delete table;
    }
}

void ReservationView::loadReservations() {
    ReservationRepository reservationRepo;
    std::vector<Reservation*> reservations;
    
    if (filterByDate) {
        QString dateStr = filterDateEdit->date().toString("yyyy-MM-dd");
        reservations = reservationRepo.getByDate(dateStr.toStdString());
    } else {
        reservations = reservationRepo.getAll();
    }
    
    reservationsTable->setRowCount(0);
    
    for (auto* reservation : reservations) {
        int row = reservationsTable->rowCount();
        reservationsTable->insertRow(row);
        
        reservationsTable->setItem(row, 0, new QTableWidgetItem(QString::number(reservation->getId())));
        reservationsTable->setItem(row, 1, new QTableWidgetItem(reservation->getCustomerName().c_str()));
        reservationsTable->setItem(row, 2, new QTableWidgetItem(QString::number(reservation->getTableId())));
        reservationsTable->setItem(row, 3, new QTableWidgetItem(reservation->getReservationDate().c_str()));
        reservationsTable->setItem(row, 4, new QTableWidgetItem(reservation->getReservationTime().c_str()));
        reservationsTable->setItem(row, 5, new QTableWidgetItem(QString::number(reservation->getNumberOfGuests())));
        
        QString statusStr = "PENDING";
        switch (reservation->getStatus()) {
            case ReservationStatus::CONFIRMED: statusStr = "CONFIRMED"; break;
            case ReservationStatus::SEATED: statusStr = "SEATED"; break;
            case ReservationStatus::CANCELLED: statusStr = "CANCELLED"; break;
            case ReservationStatus::COMPLETED: statusStr = "COMPLETED"; break;
            case ReservationStatus::NO_SHOW: statusStr = "NO_SHOW"; break;
        }
        reservationsTable->setItem(row, 6, new QTableWidgetItem(statusStr));
        
        // Get payment info
        QString paymentStr = "N/A";
        if (reservation->getOrderId() > 0) {
            PaymentRepository paymentRepo;
            auto payments = paymentRepo.getByOrderId(reservation->getOrderId());
            if (!payments.empty()) {
                Payment* payment = payments[0];
                paymentStr = QString("$%1 - %2").arg(payment->getAmount(), 0, 'f', 2)
                                                 .arg(payment->getStatus() == PaymentStatus::COMPLETED ? "Paid" : "Pending");
                delete payment;
            }
            for (size_t i = 1; i < payments.size(); ++i) {
                delete payments[i];
            }
        }
        reservationsTable->setItem(row, 7, new QTableWidgetItem(paymentStr));
        reservationsTable->setItem(row, 8, new QTableWidgetItem(reservation->getSpecialRequests().c_str()));
        
        reservationsTable->item(row, 0)->setData(Qt::UserRole, reservation->getId());
        
        delete reservation;
    }
}

void ReservationView::onAddReservationClicked() {
    QString customerName = customerNameEdit->text().trimmed();
    if (customerName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter customer name.");
        return;
    }
    
    int tableId = tableCombo->currentData().toInt();
    if (tableId == -1) {
        QMessageBox::warning(this, "Warning", "Please select a table.");
        return;
    }
    
    Reservation* reservation = new Reservation();
    reservation->setCustomerName(customerName.toStdString());
    reservation->setCustomerPhone(customerPhoneEdit->text().toStdString());
    reservation->setCustomerEmail(customerEmailEdit->text().toStdString());
    reservation->setTableId(tableId);
    reservation->setReservationDate(dateEdit->date().toString("yyyy-MM-dd").toStdString());
    reservation->setReservationTime(timeEdit->time().toString("HH:mm").toStdString());
    reservation->setNumberOfGuests(guestsSpin->value());
    reservation->setStatus(static_cast<ReservationStatus>(statusCombo->currentData().toInt()));
    reservation->setSpecialRequests(specialRequestsEdit->toPlainText().toStdString());
    
    ReservationRepository reservationRepo;
    if (reservationRepo.insert(reservation)) {
        QMessageBox::information(this, "Success", "Reservation added successfully!");
        clearForm();
        loadReservations();
    } else {
        QMessageBox::critical(this, "Error", "Failed to add reservation.");
    }
    
    delete reservation;
}

void ReservationView::onUpdateReservationClicked() {
    if (currentReservationId == -1) return;
    
    ReservationRepository reservationRepo;
    Reservation* reservation = reservationRepo.getById(currentReservationId);
    if (!reservation) {
        QMessageBox::critical(this, "Error", "Reservation not found.");
        return;
    }
    
    reservation->setCustomerName(customerNameEdit->text().toStdString());
    reservation->setCustomerPhone(customerPhoneEdit->text().toStdString());
    reservation->setCustomerEmail(customerEmailEdit->text().toStdString());
    reservation->setTableId(tableCombo->currentData().toInt());
    reservation->setReservationDate(dateEdit->date().toString("yyyy-MM-dd").toStdString());
    reservation->setReservationTime(timeEdit->time().toString("HH:mm").toStdString());
    reservation->setNumberOfGuests(guestsSpin->value());
    reservation->setStatus(static_cast<ReservationStatus>(statusCombo->currentData().toInt()));
    reservation->setSpecialRequests(specialRequestsEdit->toPlainText().toStdString());
    
    if (reservationRepo.update(reservation)) {
        QMessageBox::information(this, "Success", "Reservation updated successfully!");
        clearForm();
        loadReservations();
    } else {
        QMessageBox::critical(this, "Error", "Failed to update reservation.");
    }
    
    delete reservation;
}

void ReservationView::onDeleteReservationClicked() {
    if (currentReservationId == -1) return;
    
    int ret = QMessageBox::question(this, "Confirm Delete", 
        "Are you sure you want to delete this reservation?",
        QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        ReservationRepository reservationRepo;
        if (reservationRepo.deleteById(currentReservationId)) {
            QMessageBox::information(this, "Success", "Reservation deleted successfully!");
            clearForm();
            loadReservations();
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete reservation.");
        }
    }
}

void ReservationView::onReservationSelectionChanged() {
    int currentRow = reservationsTable->currentRow();
    if (currentRow < 0) {
        clearForm();
        return;
    }
    
    int reservationId = reservationsTable->item(currentRow, 0)->data(Qt::UserRole).toInt();
    populateForm(reservationId);
}

void ReservationView::onRefreshClicked() {
    filterByDate = true;
    loadReservations();
}

void ReservationView::onClearFilterClicked() {
    filterByDate = false;
    loadReservations();
}

void ReservationView::clearForm() {
    customerNameEdit->clear();
    customerPhoneEdit->clear();
    customerEmailEdit->clear();
    tableCombo->setCurrentIndex(0);
    dateEdit->setDate(QDate::currentDate());
    timeEdit->setTime(QTime::currentTime());
    guestsSpin->setValue(2);
    statusCombo->setCurrentIndex(0);
    specialRequestsEdit->clear();
    currentReservationId = -1;
    updateBtn->setEnabled(false);
    deleteBtn->setEnabled(false);
}

void ReservationView::populateForm(int reservationId) {
    ReservationRepository reservationRepo;
    Reservation* reservation = reservationRepo.getById(reservationId);
    if (!reservation) return;
    
    currentReservationId = reservationId;
    customerNameEdit->setText(reservation->getCustomerName().c_str());
    customerPhoneEdit->setText(reservation->getCustomerPhone().c_str());
    customerEmailEdit->setText(reservation->getCustomerEmail().c_str());
    
    // Set table
    for (int i = 0; i < tableCombo->count(); ++i) {
        if (tableCombo->itemData(i).toInt() == reservation->getTableId()) {
            tableCombo->setCurrentIndex(i);
            break;
        }
    }
    
    dateEdit->setDate(QDate::fromString(reservation->getReservationDate().c_str(), "yyyy-MM-dd"));
    timeEdit->setTime(QTime::fromString(reservation->getReservationTime().c_str(), "HH:mm"));
    guestsSpin->setValue(reservation->getNumberOfGuests());
    
    // Set status
    for (int i = 0; i < statusCombo->count(); ++i) {
        if (statusCombo->itemData(i).toInt() == static_cast<int>(reservation->getStatus())) {
            statusCombo->setCurrentIndex(i);
            break;
        }
    }
    
    specialRequestsEdit->setPlainText(reservation->getSpecialRequests().c_str());
    
    updateBtn->setEnabled(true);
    deleteBtn->setEnabled(true);
    
    delete reservation;
}

