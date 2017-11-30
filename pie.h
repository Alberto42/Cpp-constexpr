#ifndef JNP1_ZAD4_PIE_H
#define JNP1_ZAD4_PIE_H

#include <type_traits>

template<class R, R _radius, class P, bool forSale>
class Pie {

    private:
    
    static const int PI_COMPUTATION_STEPS = 500;
    static constexpr double compute_pi(int steps, double acc)
    {
        if (steps == PI_COMPUTATION_STEPS) {
            return 3 + acc;
        } else {
            double sign = 1;
            if (steps % 2 == 1) {
                sign = -1;
            }
            double helper = 2 * steps + 3;
            double denominator = (helper - 1) * helper * (helper + 1);
            return compute_pi(steps + 1, acc + sign * 4 / denominator);
        }
    }
    static constexpr double PI_VALUE = compute_pi(0, 0); // 8 digits
    int _stock;
    P _price;
    
    public:
    
    typedef std::conditional<forsale, std::true_type, std::false_type> Sellable;
    typedef std::conditional<forsale, P, std::false_type> PriceType;
    typedef T SizeType;
    typedef std::conditional<forsale, std::true_type, std::false_type> IsApplePie;
    
    template<class U = P, class = class std::enable_if<!forSale && std::is_same<U,P>::value, U>::type>
    Pie(int stock): _stock(stock)
    {
        static_assert(std::is_integral<R>::value,
                      "Wrong cake size type in Pie.");
    };
    
    template<class U = P, class = class std::enable_if<forSale && std::is_same<U,P>::value, U>::type>
    Pie(int stock, P price): _stock(stock), _price(price)
    {
        static_assert(std::is_integral<R>::value,
                      "Wrong cake size type in Pie.");
        static_assert(std::is_floating_point<P>::value,
                      "Wrong cake price type in ApplePie.");
    };
    
    static double getArea()
    {
        return _radius * _radius * PI_VALUE;
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

template<class R, R _radius>
using CherryPie = Pie<R, _radius, double, false>;

template<class R, R _radius, class P>
using ApplePie = Pie<R, _radius, P, true>;

#endif //JNP1_ZAD4_PIE_H
