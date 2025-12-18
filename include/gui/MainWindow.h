#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(int userId, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDashboardView();
    void onChefView();
    void onMenuView();
    void onOrderView();
    void onOrderQueueView();
    void onReservationView();
    void onTableView();
    void onPaymentView();
    void onStatisticsView();
    void onAdminLogView();
    void onLogout();

private:
    void setupUI();
    void setupMenuBar();
    void setupStatusBar();
    int findTabIndex(const QString& tabText);
    
    int currentUserId;
    QTabWidget* tabWidget;
    QMenuBar* mainMenuBar;
    QMenu* fileMenu;
    QMenu* viewMenu;
    QMenu* helpMenu;
    QAction* logoutAction;
    QAction* exitAction;
    QAction* dashboardAction;
    QAction* chefAction;
    QAction* menuAction;
    QAction* orderAction;
    QAction* orderQueueAction;
    QAction* reservationAction;
    QAction* tableAction;
    QAction* paymentAction;
    QAction* statisticsAction;
    QAction* adminLogAction;
};

#endif // MAINWINDOW_H

