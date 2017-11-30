#ifndef JNP1_ZAD4_CAKE_H
#define JNP1_ZAD4_CAKE_H

#include <type_traits>

template<class T, T length, T width, class P, bool forSale>
class Cake {

private:

    static const int LN2_COMPUTATION_STEPS = 500;

    static constexpr double computeLn2(int steps, double acc,
                                       double powerOf2) {
        if (steps == LN2_COMPUTATION_STEPS) {
            return acc;
        } else {
            double denominator = steps * powerOf2;
            return computeLn2(steps + 1, acc + 1 / denominator,
                              2 * powerOf2);
        }
    }

    static constexpr double LN2_VALUE = computeLn2(1, 0, 2); // 15 digits
    int stock;
    P price;

public:

    typedef typename std::conditional<forSale, std::true_type,
            std::false_type>::type Sellable;
    typedef typename std::conditional<forSale, P,
            std::false_type>::type PriceType;
    typedef T SizeType;
    typedef std::false_type IsApplePie;

    template<class U = P, class = class std::enable_if<
            !forSale && std::is_same<U, P>::value, U>::type>
    Cake(int stock): stock(stock) {
        static_assert(std::is_integral<T>::value,
                      "Wrong cake size type in Cake.");
    }

    template<class U = P, class = class std::enable_if<
            forSale && std::is_same<U, P>::value, U>::type>
    Cake(int stock, P price): stock(stock), price(price) {
        static_assert(std::is_integral<T>::value,
                      "Wrong cake size type in Cake.");
        static_assert(std::is_floating_point<P>::value,
                      "Wrong cake price type in CreamCake.");
    }

    static constexpr double getArea() {
        return length * width * LN2_VALUE;
    }

    int getStock() const {
        return stock;
    }

    template<class U = P, class = class std::enable_if<
            forSale && std::is_same<U, P>::value, U>::type>
    void sell() {
        if (stock > 0)
            --stock;
    }

    template<class U = P, class = class std::enable_if<
            forSale && std::is_same<U, P>::value, U>::type>
    P getPrice() const {
        return price;
    }
};

template<class T, T length, T width>
using CheeseCake = Cake<T, length, width, double, false>;

template<class T, T length, T width, class P>
using CreamCake = Cake<T, length, width, P, true>;

#endif //JNP1_ZAD4_CAKE_H
