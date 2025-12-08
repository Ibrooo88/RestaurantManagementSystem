#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QGroupBox>
#include <QMessageBox>

class TableView : public QWidget {
    Q_OBJECT

public:
    explicit TableView(QWidget *parent = nullptr);
    ~TableView();

private slots:
    void onAddTableClicked();
    void onUpdateTableClicked();
    void onDeleteTableClicked();
    void onTableSelectionChanged();
    void onRefreshClicked();

private:
    void setupUI();
    void loadTables();
    void clearForm();
    void populateForm(int tableId);
    
    QVBoxLayout* mainLayout;
    
    // Form Group
    QGroupBox* formGroup;
    QVBoxLayout* formLayout;
    QSpinBox* tableNumberSpin;
    QSpinBox* capacitySpin;
    QComboBox* statusCombo;
    QLineEdit* locationEdit;
    QPushButton* addBtn;
    QPushButton* updateBtn;
    QPushButton* deleteBtn;
    QPushButton* clearBtn;
    
    // Tables Table
    QGroupBox* tableGroup;
    QTableWidget* tablesTable;
    QPushButton* refreshBtn;
    
    int currentTableId;
};

#endif // TABLEVIEW_H

