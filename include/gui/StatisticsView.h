#ifndef STATISTICSVIEW_H
#define STATISTICSVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QDateEdit>
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>

class StatisticsView : public QWidget {
    Q_OBJECT

public:
    explicit StatisticsView(QWidget *parent = nullptr);
    ~StatisticsView();

private slots:
    void onRefreshClicked();
    void onDateChanged();

private:
    void setupUI();
    void loadStatistics();
    void updateStatistics();
    
    QVBoxLayout* mainLayout;
    
    // Date Filter
    QGroupBox* filterGroup;
    QHBoxLayout* filterLayout;
    QLabel* dateLabel;
    QDateEdit* dateEdit;
    QPushButton* refreshBtn;
    
    // Statistics Cards
    QGroupBox* statsGroup;
    QGridLayout* statsLayout;
    QLabel* totalOrdersLabel;
    QLabel* totalOrdersValue;
    QLabel* totalRevenueLabel;
    QLabel* totalRevenueValue;
    QLabel* avgOrderValueLabel;
    QLabel* avgOrderValue;
    QLabel* completedOrdersLabel;
    QLabel* completedOrdersValue;
    
    // Statistics Table
    QGroupBox* tableGroup;
    QTableWidget* statsTable;
};

#endif // STATISTICSVIEW_H

