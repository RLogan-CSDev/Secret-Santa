#ifndef BAGADT_H
#define BAGADT_H

template <typename E>
class Bag {
public:
    Bag();
    virtual ~Bag();
    virtual bool addItem(const E& item) = 0;
    virtual bool removeItem(E& item) = 0;
    virtual bool findItem(E& item) = 0;
    virtual int getSize() = 0;
    virtual bool isEmpty() = 0;
private:

};


#endif // BAGADT_H
