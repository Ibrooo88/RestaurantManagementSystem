#ifndef ORDERQUEUEVIEW_H
#define ORDERQUEUEVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QGroupBox>
#include <QMessageBox>

class OrderQueueView : public QWidget {
    Q_OBJECT

public:
    explicit OrderQueueView(QWidget *parent = nullptr);
    ~OrderQueueView();

private slots:
    void onRefreshClicked();
    void onAssignChefClicked();
    void onUpdateStatusClicked();
    void onQueueSelectionChanged();

private:
    void setupUI();
    void loadQueue();
    void updateQueue();
    
    QVBoxLayout* mainLayout;
    
    // Queue Table
    QGroupBox* queueGroup;
    QTableWidget* queueTable;
    QPushButton* refreshBtn;
    
    // Actions
    QGroupBox* actionsGroup;
    QHBoxLayout* actionsLayout;
    QLabel* chefLabel;
    QComboBox* chefCombo;
    QPushButton* assignChefBtn;
    QLabel* statusLabel;
    QComboBox* statusCombo;
    QPushButton* updateStatusBtn;
    
    int currentOrderId;
};

#endif // ORDERQUEUEVIEW_H

