#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>

class LoginWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void onLoginClicked();
    void onCancelClicked();

signals:
    void loginSuccessful(int userId);

private:
    void setupUI();
    
    QWidget* centralWidget;
    QVBoxLayout* mainLayout;
    QLabel* titleLabel;
    QLabel* usernameLabel;
    QLineEdit* usernameEdit;
    QLabel* passwordLabel;
    QLineEdit* passwordEdit;
    QHBoxLayout* buttonLayout;
    QPushButton* loginButton;
    QPushButton* cancelButton;
};

#endif // LOGINWINDOW_H

