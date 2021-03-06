namespace itertools{
    class range{
    private:
        int intBegin , intEnd;
    public:
        range(int b, int e): intBegin(b),intEnd(e){}
    private:
        class iterator{
            int current;
        public:
            iterator(int c):current(c){}

            bool operator!=(const iterator& rhs) const {
                return current != rhs.current;
            }
            int operator*() const {
                return current;
            }

            // ++i;
            iterator& operator++() {
                ++current;
                return *this;
            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            const iterator operator++(int) {
                iterator tmp= *this;
                ++current;
                return tmp;
            }

            bool operator==(const iterator& rhs) const {
                return current == rhs.current;
            }

        };

    public:
        iterator begin() const  {
            return iterator(intBegin);
        }

        iterator end() const {
            return iterator(intEnd);
        }
    };
}