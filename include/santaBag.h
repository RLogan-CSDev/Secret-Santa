#ifndef SANTABAG_H
#define SANTABAG_H

#include "bagADT.h"

template <typename E>
class SantaBag : public Bag<E> {
public:
    SantaBag();
    virtual ~SantaBag();
    virtual bool addItem(const E& item) override;
    virtual bool removeItem(E& item) override;
    virtual bool findItem(E& item) override;
    virtual int getSize() override;
    virtual bool isEmpty() override;
private:

};


#endif // SANTABAG_H
