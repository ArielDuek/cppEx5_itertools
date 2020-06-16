namespace itertools{
    template<class T >
    class accumulate{
    protected:
        T container;
    public:
        accumulate(T c):container(c){}

        class iterator {

        private:
            accumulate<T> acc;
        public:
            iterator(accumulate<T> a): acc(a){}

            T& operator*() const {
                //return *pointer_to_current_node;
                return pointer_to_current_node->m_value;
            }

            T* operator->() const {
                return &(pointer_to_current_node->m_value);
            }

            // ++i;
            iterator& operator++() {
                //++pointer_to_current_node;
                pointer_to_current_node = pointer_to_current_node->m_next;
                return *this;
            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            const iterator operator++(int) {
                iterator tmp= *this;
                pointer_to_current_node= pointer_to_current_node->m_next;
                return tmp;
            }

            bool operator==(const iterator& rhs) const {
                return pointer_to_current_node == rhs.pointer_to_current_node;
            }

            bool operator!=(const iterator& rhs) const {
                return pointer_to_current_node != rhs.pointer_to_current_node;
            }
        };  // END OF CLASS ITERATOR
        
    };
}