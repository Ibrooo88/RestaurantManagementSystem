#ifndef ADMINLOGVIEW_H
#define ADMINLOGVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QLabel>
#include <QGroupBox>

class AdminLogView : public QWidget {
    Q_OBJECT

public:
    explicit AdminLogView(QWidget *parent = nullptr);
    ~AdminLogView();

private slots:
    void onRefreshClicked();
    void onFilterClicked();

private:
    void setupUI();
    void loadLogs();
    
    QVBoxLayout* mainLayout;
    
    // Filter Group
    QGroupBox* filterGroup;
    QHBoxLayout* filterLayout;
    QLabel* userLabel;
    QLineEdit* userEdit;
    QLabel* actionLabel;
    QComboBox* actionCombo;
    QLabel* dateLabel;
    QDateEdit* dateEdit;
    QPushButton* filterBtn;
    QPushButton* refreshBtn;
    
    // Logs Table
    QGroupBox* tableGroup;
    QTableWidget* logsTable;
};

#endif // ADMINLOGVIEW_H

