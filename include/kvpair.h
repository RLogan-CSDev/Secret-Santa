#ifndef KVPAIR_H
#define KVPAIR_H

// Container for a key-value pair
template<typename Key, typename E>
class KVPair {
public:
    // Constructors
    KVPair() {}
    KVPair(Key kval, E eval) { k = kval; e = eval; }
    KVPair(const KVPair& o) { k = o.k; e = o.e; } // Copy Constructor
    void operator =(const KVPair& o) { k = o.k; o.e; } // Assignment operator

    // Data member access functions
    Key key() { return k; }
    void setKey(const Key& ink) { k = ink; }
    E value() { return e; }
    void setValue(const E& ine) { e = ine; }

private:
    Key k;
    E e;
};

#endif // KVPAIR_H
