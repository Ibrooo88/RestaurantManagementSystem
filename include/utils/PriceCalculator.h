#ifndef PRICECALCULATOR_H
#define PRICECALCULATOR_H

#include <vector>
#include <map>

class PriceCalculator {
public:
    static double calculateTotal(const std::map<int, double>& items); // itemId -> price
    static double calculateSubtotal(double total);
    static double calculateTax(double subtotal, double taxRate = 0.15);
    static double calculateDiscount(double total, double discountPercent);
    static double calculateFinalTotal(double subtotal, double tax, double discount);
    static double calculateTip(double total, double tipPercent);
};

#endif // PRICECALCULATOR_H

