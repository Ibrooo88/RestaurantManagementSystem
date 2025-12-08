#include "../../include/utils/PriceCalculator.h"

double PriceCalculator::calculateTotal(const std::map<int, double>& items) {
    double total = 0.0;
    for (const auto& pair : items) {
        total += pair.second;
    }
    return total;
}

double PriceCalculator::calculateSubtotal(double total) {
    return total;
}

double PriceCalculator::calculateTax(double subtotal, double taxRate) {
    return subtotal * taxRate;
}

double PriceCalculator::calculateDiscount(double total, double discountPercent) {
    return total * (discountPercent / 100.0);
}

double PriceCalculator::calculateFinalTotal(double subtotal, double tax, double discount) {
    return subtotal + tax - discount;
}

double PriceCalculator::calculateTip(double total, double tipPercent) {
    return total * (tipPercent / 100.0);
}

