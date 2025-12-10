cmake_minimum_required(VERSION 3.10)
project(RestaurantManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Find Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

# Find SQLite3 (optional - not needed in simulation mode)
find_package(SQLite3)
if(NOT SQLite3_FOUND)
    message(WARNING "SQLite3 not found. Simulation mode will work, but database mode requires SQLite3.")
endif()

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/models
    ${CMAKE_SOURCE_DIR}/include/repositories
    ${CMAKE_SOURCE_DIR}/include/services
    ${CMAKE_SOURCE_DIR}/include/controllers
    ${CMAKE_SOURCE_DIR}/include/database
    ${CMAKE_SOURCE_DIR}/include/utils
    ${CMAKE_SOURCE_DIR}/include/enums
    ${CMAKE_SOURCE_DIR}/include/dto
    ${CMAKE_SOURCE_DIR}/include/gui
)

# Source files
set(SOURCES
    src/main.cpp
    
    # Models
    src/models/User.cpp
    src/models/Role.cpp
    src/models/Chef.cpp
    src/models/MenuItem.cpp
    src/models/Order.cpp
    src/models/OrderItem.cpp
    src/models/Table.cpp
    src/models/Reservation.cpp
    src/models/Payment.cpp
    src/models/AdminActionLog.cpp
    
    # Repositories
    src/repositories/UserRepository.cpp
    src/repositories/OrderRepository.cpp
    src/repositories/OrderItemRepository.cpp
    src/repositories/MenuItemRepository.cpp
    src/repositories/TableRepository.cpp
    src/repositories/ChefRepository.cpp
    src/repositories/ReservationRepository.cpp
    src/repositories/PaymentRepository.cpp
    src/repositories/AdminActionLogRepository.cpp
    
    # Services
    src/services/AuthService.cpp
    src/services/OrderService.cpp
    src/services/MenuService.cpp
    src/services/ReservationService.cpp
    src/services/PaymentService.cpp
    src/services/TableService.cpp
    src/services/ChefService.cpp
    src/services/StatisticsService.cpp
    
    # Controllers
    src/controllers/OrderController.cpp
    src/controllers/UserController.cpp
    src/controllers/RoleController.cpp
    src/controllers/ChefController.cpp
    src/controllers/MenuController.cpp
    src/controllers/QueueController.cpp
    src/controllers/PaymentController.cpp
    src/controllers/ReservationController.cpp
    src/controllers/StatisticsController.cpp
    
    # Database
    src/database/DatabaseConnection.cpp
    src/database/DatabaseMigration.cpp
    
    # Utils
    src/utils/Logger.cpp
    src/utils/TimeUtils.cpp
    src/utils/PriceCalculator.cpp
    src/utils/PriorityCalculator.cpp
    src/utils/SimulationMode.cpp
    
    # GUI
    src/gui/LoginWindow.cpp
    src/gui/MainWindow.cpp
    src/gui/DashboardWindow.cpp
    src/gui/OrderView.cpp
    src/gui/MenuView.cpp
    src/gui/ChefView.cpp
    src/gui/OrderQueueView.cpp
    src/gui/ReservationView.cpp
    src/gui/TableView.cpp
    src/gui/PaymentView.cpp
    src/gui/StatisticsView.cpp
    src/gui/AdminLogView.cpp
)

# Header files
set(HEADERS
    include/models/User.h
    include/models/Role.h
    include/models/Chef.h
    include/models/MenuItem.h
    include/models/Order.h
    include/models/OrderItem.h
    include/models/Table.h
    include/models/Reservation.h
    include/models/Payment.h
    include/models/AdminActionLog.h
    
    include/repositories/UserRepository.h
    include/repositories/OrderRepository.h
    include/repositories/OrderItemRepository.h
    include/repositories/MenuItemRepository.h
    include/repositories/TableRepository.h
    include/repositories/ChefRepository.h
    include/repositories/ReservationRepository.h
    include/repositories/PaymentRepository.h
    include/repositories/AdminActionLogRepository.h
    
    include/services/AuthService.h
    include/services/OrderService.h
    include/services/MenuService.h
    include/services/ReservationService.h
    include/services/PaymentService.h
    include/services/TableService.h
    include/services/ChefService.h
    include/services/StatisticsService.h
    
    include/controllers/OrderController.h
    include/controllers/UserController.h
    include/controllers/RoleController.h
    include/controllers/ChefController.h
    include/controllers/MenuController.h
    include/controllers/QueueController.h
    include/controllers/PaymentController.h
    include/controllers/ReservationController.h
    include/controllers/StatisticsController.h
    
    include/database/DatabaseConnection.h
    include/database/DatabaseMigration.h
    
    include/utils/Logger.h
    include/utils/TimeUtils.h
    include/utils/PriceCalculator.h
    include/utils/PriorityCalculator.h
    include/utils/SimulationMode.h
    
    include/gui/LoginWindow.h
    include/gui/MainWindow.h
    include/gui/DashboardWindow.h
    include/gui/OrderView.h
    include/gui/MenuView.h
    include/gui/ChefView.h
    include/gui/OrderQueueView.h
    include/gui/ReservationView.h
    include/gui/TableView.h
    include/gui/PaymentView.h
    include/gui/StatisticsView.h
    include/gui/AdminLogView.h
)

# Create executable
# Only wrap GUI headers that contain Q_OBJECT
set(GUI_HEADERS
    include/gui/LoginWindow.h
    include/gui/MainWindow.h
    include/gui/DashboardWindow.h
    include/gui/OrderView.h
    include/gui/MenuView.h
    include/gui/ChefView.h
    include/gui/OrderQueueView.h
    include/gui/ReservationView.h
    include/gui/TableView.h
    include/gui/PaymentView.h
    include/gui/StatisticsView.h
    include/gui/AdminLogView.h
)

qt5_wrap_cpp(MOC_SOURCES ${GUI_HEADERS})
add_executable(${PROJECT_NAME} ${SOURCES} ${MOC_SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
)


# Link SQLite3 if found
if(SQLite3_FOUND)
    target_link_libraries(${PROJECT_NAME} ${SQLite3_LIBRARIES})
    target_include_directories(${PROJECT_NAME} PRIVATE ${SQLite3_INCLUDE_DIRS})
endif()

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

