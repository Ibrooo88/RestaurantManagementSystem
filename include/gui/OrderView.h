#ifndef ORDERVIEW_H
#define ORDERVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QLabel>
#include <QGroupBox>
#include <QMessageBox>

class OrderView : public QWidget {
    Q_OBJECT

public:
    explicit OrderView(QWidget *parent = nullptr);
    ~OrderView();

private slots:
    void onAddItemClicked();
    void onRemoveItemClicked();
    void onCreateOrderClicked();
    void onClearClicked();
    void onTableSelectionChanged();

private:
    void setupUI();
    void loadMenuItems();
    void loadTables();
    void updateOrderTotal();
    void refreshOrdersTable();
    
    QVBoxLayout* mainLayout;
    
    // Order Creation Section
    QGroupBox* orderGroup;
    QHBoxLayout* orderLayout;
    QLabel* tableLabel;
    QComboBox* tableCombo;
    QLabel* customerLabel;
    QLineEdit* customerEdit;
    QPushButton* createOrderBtn;
    
    // Menu Items Section
    QGroupBox* menuGroup;
    QHBoxLayout* menuLayout;
    QComboBox* menuItemCombo;
    QLabel* quantityLabel;
    QSpinBox* quantitySpin;
    QPushButton* addItemBtn;
    QPushButton* removeItemBtn;
    
    // Order Items Table
    QTableWidget* orderItemsTable;
    
    // Total
    QLabel* totalLabel;
    QLabel* totalValueLabel;
    
    // Orders List
    QGroupBox* ordersGroup;
    QTableWidget* ordersTable;
    QPushButton* refreshBtn;
    QPushButton* clearBtn;
    
    double currentTotal;
};

#endif // ORDERVIEW_H

