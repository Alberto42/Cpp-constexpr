#ifndef JNP1_ZAD4_CAKE_H
#define JNP1_ZAD4_CAKE_H

#include <type_traits>

template <class T, T _length, T _width>
class Cake {
    static_assert(std::is_integral<T>::value, "Wrong cake size type in Cake.");   
    
    private:
    static const int LN2_COMPUTATION_STEPS = 500;
    static constexpr double compute_ln2(int steps, double acc, double power_of_2)
    {
        if (steps == LN2_COMPUTATION_STEPS) {
            return acc;
        } else {
            double denominator = steps * power_of_2;
            return compute_ln2(steps + 1, acc + 1 / denominator, 2 * power_of_2);
        }
    }
    static constexpr double LN2_VALUE = compute_ln2(1, 0, 2); // 15 digits
    
    protected:
    int _stock;
    Cake(int stock): _stock(stock) {}; // Czy powinienem sprawdzać argument? - dopytać się prowadzącego
    
    public:
    static double getArea()
    {
        return _length * _width * LN2_VALUE;
    }
    int getStock()
    {
        return _stock;
    }
};

template <class T, T _length, T _width>
class CheeseCake: public Cake<T, _length, _width> {
    public:
    CheeseCake(int stock): Cake<T, _length, _width>(stock) {};
};

template <class T, T _length, T _width, class P>
class CreamCake: public Cake<T, _length, _width> {
    static_assert(std::is_floating_point<P>::value,
                  "Wrong cake price type in CreamCake.");
    
    private:
    P _price;
    
    public:
    CreamCake(int stock, P price): Cake<T, _length, _width>(stock),
                                   _price(price) {};
    void sell()
    {
        if (Cake<T, _length, _width>::_stock > 0) // Czy funkcja powinna być "cicha" dla 0?
            --Cake<T, _length, _width>::_stock;
    }
    P getPrice()
    {
        return _price;
    }
};

#endif //JNP1_ZAD4_CAKE_H
