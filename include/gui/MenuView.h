#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QTextEdit>
#include <QLabel>
#include <QGroupBox>
#include <QMessageBox>
#include <QComboBox>

class MenuView : public QWidget {
    Q_OBJECT

public:
    explicit MenuView(QWidget *parent = nullptr);
    ~MenuView();

private slots:
    void onAddItemClicked();
    void onUpdateItemClicked();
    void onDeleteItemClicked();
    void onItemSelectionChanged();
    void onRefreshClicked();

private:
    void setupUI();
    void loadMenuItems();
    void clearForm();
    void populateForm(int itemId);
    
    QVBoxLayout* mainLayout;
    
    // Form Group
    QGroupBox* formGroup;
    QVBoxLayout* formLayout;
    QLineEdit* nameEdit;
    QTextEdit* descriptionEdit;
    QDoubleSpinBox* priceSpin;
    QLineEdit* categoryEdit;
    QSpinBox* prepTimeSpin;
    QComboBox* availabilityCombo;
    QPushButton* addBtn;
    QPushButton* updateBtn;
    QPushButton* deleteBtn;
    QPushButton* clearBtn;
    
    // Menu Items Table
    QGroupBox* tableGroup;
    QTableWidget* menuTable;
    QPushButton* refreshBtn;
    
    int currentItemId;
};

#endif // MENUVIEW_H

