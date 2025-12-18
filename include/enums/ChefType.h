#ifndef CHEFTYPE_H
#define CHEFTYPE_H

enum class ChefType {
    NORMAL_CHEF,    // Standard chef for normal orders
    VEGAN_CHEF,     // Specialized in plant-based food - serves only vegan orders
    VIP_CHEF        // Highly skilled - can prepare any order type, but primarily VIP
};

#endif // CHEFTYPE_H
