#ifndef PAYMENTVIEW_H
#define PAYMENTVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QGroupBox>
#include <QMessageBox>

class PaymentView : public QWidget {
    Q_OBJECT

public:
    explicit PaymentView(QWidget *parent = nullptr);
    ~PaymentView();

private slots:
    void onProcessPaymentClicked();
    void onPaymentSelectionChanged();
    void onRefreshClicked();

private:
    void setupUI();
    void loadPayments();
    void loadOrders();
    
    QVBoxLayout* mainLayout;
    
    // Payment Form
    QGroupBox* formGroup;
    QVBoxLayout* formLayout;
    QComboBox* orderCombo;
    QDoubleSpinBox* amountSpin;
    QComboBox* paymentMethodCombo;
    QPushButton* processBtn;
    
    // Payments Table
    QGroupBox* tableGroup;
    QTableWidget* paymentsTable;
    QPushButton* refreshBtn;
    
    int currentPaymentId;
};

#endif // PAYMENTVIEW_H

