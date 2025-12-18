#include <QApplication>
#include <QCommandLineParser>
#include "../include/gui/LoginWindow.h"
#include "../include/gui/MainWindow.h"
#include "../include/database/DatabaseConnection.h"
#include "../include/database/DatabaseMigration.h"
#include "../include/database/DatabaseSeeder.h"
#include "../include/utils/Logger.h"
#include "../include/utils/SimulationMode.h"
#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Parse command line arguments
    QCommandLineParser parser;
    parser.setApplicationDescription("Restaurant Management System");
    parser.addHelpOption();
    QCommandLineOption simOption("sim", "Run in simulation mode (no database)");
    parser.addOption(simOption);
    parser.process(app);
    
    bool simulationMode = parser.isSet(simOption);
    
    // Initialize database or simulation mode
    Logger::getInstance().info("Initializing Restaurant Management System...");
    
    if (simulationMode) {
        SimulationMode::setEnabled(true);
        Logger::getInstance().info("Running in SIMULATION MODE (no database)");
    } else {
        if (!DatabaseConnection::getInstance().connect()) {
            Logger::getInstance().error("Failed to connect to database!");
            Logger::getInstance().info("Tip: Use --sim flag to run in simulation mode");
            return -1;
        }
        
        // Run migrations
        if (!DatabaseMigration::migrate()) {
            Logger::getInstance().error("Database migration failed!");
            return -1;
        }
        
        // Seed default data
        DatabaseSeeder::seed();
    }
    
    // Show login window
    LoginWindow loginWindow;
    loginWindow.show();
    
    // Connect login signal to main window
    MainWindow* mainWindow = nullptr;
    QObject::connect(&loginWindow, &LoginWindow::loginSuccessful, [&](int userId) {
        if (mainWindow) {
            mainWindow->close();
            delete mainWindow;
        }
        mainWindow = new MainWindow(userId);
        mainWindow->show();
    });
    
    int result = app.exec();
    
    // Cleanup
    if (mainWindow) {
        delete mainWindow;
    }
    
    DatabaseConnection::getInstance().disconnect();
    Logger::getInstance().info("Application closed");
    
    return result;
}

