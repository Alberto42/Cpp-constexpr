#ifndef JNP1_ZAD4_PIE_H
#define JNP1_ZAD4_PIE_H

#include <type_traits>

template <class R, R _radius>
class Pie {
    static_assert(std::is_integral<R>::value, "Wrong cake size type in Pie.");

    private:
    static const int PI_COMPUTATION_STEPS = 500;
    static constexpr double compute_pi(int steps, double acc)
    {
        if (steps == PI_COMPUTATION_STEPS) {
            return 3 + acc;
        } else {
            double sign = 1, denominator;
            if (steps % 2 == 1) {
                sign = -1;
            }
            double helper = 2 * steps + 3;
            double denominator = (helper - 1) * helper * (helper + 1);
            return compute_pi(steps + 1, acc + sign * 4 / denominator);
        }
    }
    static constexpr double PI_VALUE = compute_pi(0, 0); // 8 digits
    
    protected:
    int _stock;
    Pie (int stock): _stock(stock) {}; // Czy powinienem sprawdzać argument? - dopytać się prowadzącego
    
    public:
    static double getArea()
    {
        return _radius * _radius * PI_VALUE;
    }
    int getStock()
    {
        return _stock;
    }
};

template <class R, R _radius>
class CherryPie: public Pie<R, _radius> {
    public:
    CherryPie(int stock): Pie<R, _radius>(stock) {};
};

template <class R, R _radius, class P>
class ApplePie: public Pie<R, _radius> {
    static_assert(std::is_floating_point<P>::value,
                  "Wrong cake price type in ApplePie.");
    
    private:
    P _price;
    
    public:
    ApplePie(int stock, P price): Pie<R, _radius>(stock), _price(price) {};
    void sell()
    {
        if (Pie<R, _radius>::_stock > 0) // Czy funkcja powinna być "cicha" dla 0?
            --Pie<R, _radius>::_stock;
    }
    P getPrice()
    {
        return _price;
    }
};

#endif //JNP1_ZAD4_PIE_H
