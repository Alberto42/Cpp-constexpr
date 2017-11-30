#ifndef JNP1_ZAD4_PIE_H
#define JNP1_ZAD4_PIE_H

#include <type_traits>

template<class R, R radius, class P, bool ForSale>
class Pie {

private:

    static const int PI_COMPUTATION_STEPS = 500;

    static constexpr double computePi(int steps, double acc) {
        if (steps == PI_COMPUTATION_STEPS) {
            return 3 + acc;
        } else {
            double sign = 1;
            if (steps % 2 == 1) {
                sign = -1;
            }
            double helper = 2 * steps + 3;
            double denominator = (helper - 1) * helper * (helper + 1);
            return computePi(steps + 1, acc + sign * 4 / denominator);
        }
    }

    static constexpr double PI_VALUE = computePi(0, 0); // 8 digits

    int stock;
    P price;

public:

    typedef typename std::conditional<ForSale, std::true_type,
            std::false_type>::type Sellable;
    typedef typename std::conditional<ForSale, P,
            std::false_type>::type PriceType;
    typedef R SizeType;
    typedef typename std::conditional<ForSale, std::true_type,
            std::false_type>::type IsApplePie;

    template<class U = P, class = class std::enable_if<
            !ForSale && std::is_same<U, P>::value, U>::type>
    Pie(int stock): stock(stock) {
        static_assert(std::is_integral<R>::value,
                      "Wrong cake size type in Pie.");
    };

    template<class U = P, class = class std::enable_if<
            ForSale && std::is_same<U, P>::value, U>::type>
    Pie(int stock, P price): stock(stock), price(price) {
        static_assert(std::is_integral<R>::value,
                      "Wrong cake size type in Pie.");
        static_assert(std::is_floating_point<P>::value,
                      "Wrong cake price type in ApplePie.");
    };

    static constexpr double getArea() {
        return radius * radius * PI_VALUE;
    }

    int getStock() const {
        return stock;
    }

    template<class U = P, class = class std::enable_if<
            ForSale && std::is_same<U, P>::value, U>::type>
    void sell() {
        if (stock > 0)
            --stock;
    }

    template<class U = P, class = class std::enable_if<
            ForSale && std::is_same<U, P>::value, U>::type>
    P getPrice() const {
        return price;
    }

    template<class U = P, class = class std::enable_if<
            ForSale && std::is_same<U, P>::value, U>::type>
    void restock(int additionalStock) {
        stock += additionalStock;
    }
};

template<class R, R radius>
using CherryPie = Pie<R, radius, double, false>;

template<class R, R radius, class P>
using ApplePie = Pie<R, radius, P, true>;

#endif //JNP1_ZAD4_PIE_H
