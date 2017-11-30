#ifndef JNP1_ZAD4_BAKERY_H
#define JNP1_ZAD4_BAKERY_H


#include "pie.h"
#include "cake.h"

template<typename ...>
struct AreUnique : std::false_type {
};

template<typename T>
struct AreUnique<T> : std::true_type {
};

template<typename HeadType, typename... TailTypes>
struct AreUnique<HeadType, TailTypes...>
        : std::conjunction<std::negation<std::is_same<HeadType, TailTypes> >...,
                AreUnique<TailTypes...>> {
};

template<typename T, typename... Ts>
struct Contains : std::disjunction<std::is_same<T, Ts> ... >  {
};

template<class C, class A, A shelfArea, class... P>
class Bakery {
    static_assert(std::is_floating_point<C>::value,
                  "C has to be floating point");
    static_assert(std::is_integral<A>::value, "A has to be integral");

    static_assert(AreUnique<P ...>::value, "Products have to be unique");

    static_assert(std::conjunction<std::disjunction<
                          std::negation<typename P::Sellable>,
                          std::is_same<C, typename P::PriceType> >...>::value,
                          "Price types are not the same");

    std::tuple<P...> products;
    static_assert(
            std::conjunction<std::is_same<A, typename P::SizeType>...>::value,
            "Size types are not the same");

    template<class... Products>
    static constexpr A sumArea = (... + Products::getArea());

    static_assert( sumArea<P...> <= shelfArea,
                   "Not enough space on bakery shelfes for products");

    C profits = 0;

public:

    Bakery(P... products_) : products(products_...) {}

    C getProfits() {
        return profits;
    }


    template<class Product>
    void sell() {
        static_assert(Product::Sellable::value,
                      "Attempt to sell not-sellable product");
        static_assert(Contains<Product, P ...>::value,
                      "Attempt to sell non-stocked product");

        Product& product = std::get<Product>(products);
        if (product.getStock() > 0) {
            product.sell();
            profits += product.getPrice();
        }
    }

    template<class Product>
    int getProductStock(){
        static_assert(Contains<Product, P ...>::value,
                      "Product is not stocked");

        const Product& product = std::get<Product>(products);
        return product.getStock();
    }

    template <class Product>
    void restock(int additionalStock){
        static_assert(Product::IsApplePie::value,
                      "It is only possible to restock apple pies");
        static_assert(Contains<Product, P ...>::value,
                      "Product is not stocked");

        Product& product = std::get<Product>(products);
        product.restock(additionalStock);
    }
};

#endif //JNP1_ZAD4_BAKERY_H
