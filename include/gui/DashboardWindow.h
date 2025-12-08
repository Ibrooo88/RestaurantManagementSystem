#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QTableWidget>
#include <QPushButton>

class DashboardWindow : public QWidget {
    Q_OBJECT

public:
    explicit DashboardWindow(QWidget *parent = nullptr);
    ~DashboardWindow();

private slots:
    void onRefreshClicked();
    void updateStatistics();

private:
    void setupUI();
    void loadStatistics();
    
    QVBoxLayout* mainLayout;
    
    // Statistics Cards
    QGroupBox* statsGroup;
    QGridLayout* statsLayout;
    QLabel* totalOrdersLabel;
    QLabel* totalOrdersValue;
    QLabel* totalRevenueLabel;
    QLabel* totalRevenueValue;
    QLabel* pendingOrdersLabel;
    QLabel* pendingOrdersValue;
    QLabel* activeTablesLabel;
    QLabel* activeTablesValue;
    
    // Recent Orders
    QGroupBox* recentOrdersGroup;
    QTableWidget* recentOrdersTable;
    QPushButton* refreshBtn;
    
    // Quick Actions
    QGroupBox* quickActionsGroup;
    QHBoxLayout* actionsLayout;
    QPushButton* newOrderBtn;
    QPushButton* newReservationBtn;
    QPushButton* viewMenuBtn;
};

#endif // DASHBOARDWINDOW_H

