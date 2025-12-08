#include "../../include/gui/LoginWindow.h"
#include "../../include/services/AuthService.h"
#include "../../include/dto/LoginRequestDTO.h"
#include "../../include/models/User.h"
#include "../../include/utils/Logger.h"
#include <QApplication>
#include <Qt>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupUI();
    setWindowTitle("Restaurant Management System - Login");
    setFixedSize(400, 250);
}

LoginWindow::~LoginWindow() {
    delete centralWidget;
}

void LoginWindow::setupUI() {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    mainLayout = new QVBoxLayout(centralWidget);
    
    titleLabel = new QLabel("Restaurant Management System", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin: 10px;");
    mainLayout->addWidget(titleLabel);
    
    usernameLabel = new QLabel("Username:", this);
    mainLayout->addWidget(usernameLabel);
    
    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("Enter username");
    mainLayout->addWidget(usernameEdit);
    
    passwordLabel = new QLabel("Password:", this);
    mainLayout->addWidget(passwordLabel);
    
    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Enter password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    mainLayout->addWidget(passwordEdit);
    
    buttonLayout = new QHBoxLayout();
    
    loginButton = new QPushButton("Login", this);
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    buttonLayout->addWidget(loginButton);
    
    cancelButton = new QPushButton("Cancel", this);
    connect(cancelButton, &QPushButton::clicked, this, &LoginWindow::onCancelClicked);
    buttonLayout->addWidget(cancelButton);
    
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
}

void LoginWindow::onLoginClicked() {
    std::string username = usernameEdit->text().toStdString();
    std::string password = passwordEdit->text().toStdString();
    
    if (username.empty() || password.empty()) {
        QMessageBox::warning(this, "Login Failed", "Please enter both username and password.");
        return;
    }
    
    LoginRequestDTO loginRequest(username, password);
    User* user = AuthService::login(loginRequest);
    
    if (user) {
        Logger::getInstance().info("Login successful for user: " + username);
        emit loginSuccessful(user->getId());
        delete user;
        close();
    } else {
        QMessageBox::critical(this, "Login Failed", "Invalid username or password.");
        passwordEdit->clear();
    }
}

void LoginWindow::onCancelClicked() {
    QApplication::quit();
}

