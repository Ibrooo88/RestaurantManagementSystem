#ifndef RESERVATIONVIEW_H
#define RESERVATIONVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QComboBox>
#include <QLabel>
#include <QGroupBox>
#include <QMessageBox>

class ReservationView : public QWidget {
    Q_OBJECT

public:
    explicit ReservationView(QWidget *parent = nullptr);
    ~ReservationView();

private slots:
    void onAddReservationClicked();
    void onUpdateReservationClicked();
    void onDeleteReservationClicked();
    void onReservationSelectionChanged();
    void onRefreshClicked();

private:
    void setupUI();
    void loadReservations();
    void clearForm();
    void populateForm(int reservationId);
    
    QVBoxLayout* mainLayout;
    
    // Form Group
    QGroupBox* formGroup;
    QVBoxLayout* formLayout;
    QLineEdit* customerNameEdit;
    QLineEdit* customerPhoneEdit;
    QLineEdit* customerEmailEdit;
    QComboBox* tableCombo;
    QDateEdit* dateEdit;
    QTimeEdit* timeEdit;
    QSpinBox* guestsSpin;
    QComboBox* statusCombo;
    QTextEdit* specialRequestsEdit;
    QPushButton* addBtn;
    QPushButton* updateBtn;
    QPushButton* deleteBtn;
    QPushButton* clearBtn;
    
    // Reservations Table
    QGroupBox* tableGroup;
    QTableWidget* reservationsTable;
    QPushButton* refreshBtn;
    
    int currentReservationId;
};

#endif // RESERVATIONVIEW_H

