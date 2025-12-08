#ifndef DATABASESEEDER_H
#define DATABASESEEDER_H

class DatabaseSeeder {
public:
    static bool seed();
    static bool seedRoles();
    static bool seedPermissions();
    static bool seedAccessScopes();
    static bool seedUsers();
    static bool seedChefs();
    static bool seedMenuItems();
    static bool seedIngredients();
    static bool seedTables();
    static bool clearAll();
};

#endif // DATABASESEEDER_H

