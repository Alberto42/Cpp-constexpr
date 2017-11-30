#ifndef JNP1_ZAD4_CAKE_H
#define JNP1_ZAD4_CAKE_H

#include <type_traits>

template<class T, T _length, T _width, class P, bool forSale>
class Cake {
     
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
    int _stock;
    P _price;
    
    public:
    
    template<class U = P, class = class std::enable_if<!forSale && std::is_same<U,P>::value, U>::type>
    Cake(int stock): _stock(stock)
    {
        static_assert(std::is_integral<T>::value,
                      "Wrong cake size type in Cake.");
    }
    
    template<class U = P, class = class std::enable_if<forSale && std::is_same<U,P>::value, U>::type>
    Cake(int stock, P price): _stock(stock), _price(price)
    {
        static_assert(std::is_integral<T>::value,
                      "Wrong cake size type in Cake.");
        static_assert(std::is_floating_point<P>::value,
                      "Wrong cake price type in CreamCake."); 
    }
    
    static double getArea()
    {
        return _length * _width * LN2_VALUE;
    }
    
    int getStock()
    {
        return _stock;
    }
    
    template<class U = P, class = class std::enable_if<forSale && std::is_same<U,P>::value, U>::type>
    void sell()
    {
        if (_stock > 0)
            --_stock;
    }
    
    template<class U = P, class = class std::enable_if<forSale && std::is_same<U,P>::value, U>::type>
    P getPrice()
    {
        return _price;
    }
};

template<class T, T _length, T _width>
using CheeseCake = Cake<T, _length, _width, double, false>;

template<class T, T _length, T _width, class P>
using CreamCake = Cake<T, _length, _width, P, true>;

#endif //JNP1_ZAD4_CAKE_H
