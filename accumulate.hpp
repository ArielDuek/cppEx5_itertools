#pragma once
#include <iostream>
#include <vector>
#include <iterator>

typedef struct {
    template <typename T>
    auto operator()(const T& x , const T& y) const{
        return x+y;
    }
} sum;

namespace itertools{
    template<class C,class F = sum>
    class accumulate{

    protected:
        //Fields
        const C& container;
        const F& function;
    public:
//        accumulate( C& c):container(c),function(sum()){} //Constructor
        accumulate(const C& c, const F& f=sum()):container(c),function(f){} //Constructor

        //inner class
        class iterator {

        private:
            //Fields
            const accumulate& acc;
            decltype(container.begin()) iter; //for pass over the container
            typename std::decay<decltype(*(container.begin()))>::type res;

            /*
             * NOTES:
             * Decltype is sort of an operator that evaluates the type of passed expression
             * -for the iter we needed the same type of iterator of the container and that what the begin function returns
             * and the decltype is recognize it.
             * -How ever in the res we needed the actual type of the element in the container דo that we can put the
             * result of the calculation done with the function. that the reason we do decltype(*(container.begin()))
             * and NOT decltype(container.begin()).
             *
             * The decay type of T is the same type that results from the standard conversions that happen when an lvalue
             * expression is used as an rvalue
             */

        public:
            //Constructor
            iterator(const accumulate& a,decltype(container.begin()) i)
                    : acc(a),iter(i)
            {
                if (i != acc.container.end())
                res=*i;
            }

            auto operator*() const {
                return res;
            }

            //++iter
            iterator& operator++() {
                ++iter;
                if(iter!=acc.container.end())
                {
                    res=acc.function(res,*(iter));
                }
                return *this; //return current iter after ++iter
            }

            //iter++
            const iterator operator++(int) {
                iterator tmp=*this; //save
                iter++;
                if(iter!=acc.container.end())
                {
                    res=acc.function(res,*(iter));
                }
                return *tmp; //return current iter after ++iter
            }

            bool operator==(const iterator& iterator) const {
                return iterator.iter==iter;
            }

            bool operator!=(const iterator& iterator) const {
                return iterator.iter!=iter;
            }
        }; //End iterator


        iterator begin() const {
            return iterator(*this,container.begin());
        }

        iterator end() const {
            return iterator(*this, container.end());
        }
    };
}