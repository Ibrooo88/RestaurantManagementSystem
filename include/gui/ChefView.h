#ifndef CHEFVIEW_H
#define CHEFVIEW_H

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

class ChefView : public QWidget {
    Q_OBJECT

public:
    explicit ChefView(QWidget *parent = nullptr);
    ~ChefView();

private slots:
    void onAddChefClicked();
    void onUpdateChefClicked();
    void onDeleteChefClicked();
    void onChefSelectionChanged();
    void onRefreshClicked();
    void onStatusChanged();

private:
    void setupUI();
    void loadChefs();
    void clearForm();
    void populateForm(int chefId);
    
    QVBoxLayout* mainLayout;
    
    // Form Group
    QGroupBox* formGroup;
    QVBoxLayout* formLayout;
    QLineEdit* nameEdit;
    QComboBox* chefTypeCombo;
    QComboBox* statusCombo;
    QSpinBox* skillLevelSpin;
    QLineEdit* specializationEdit;
    QPushButton* addBtn;
    QPushButton* updateBtn;
    QPushButton* deleteBtn;
    QPushButton* clearBtn;
    
    // Chefs Table
    QGroupBox* tableGroup;
    QTableWidget* chefsTable;
    QPushButton* refreshBtn;
    
    int currentChefId;
};

#endif // CHEFVIEW_H

