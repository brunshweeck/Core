//
// Created by brunshweeck on 15/03/2023.
//

#ifndef CORE_TREEMAP_H
#define CORE_TREEMAP_H


#include "../Function/NaturalOrderComparator.h"
#include "../KeyError.h"
#include "OrderedMap.h"


/**
 * A Red-Black tree based navigable map
 * \tparam K The key type
 * \tparam V The value type
 */
template<class K, class V>
class TreeMap : public OrderedMap<K, V> {
private:
    CORE_TEMPLATE_REQUIREMENT(K)
    CORE_TEMPLATE_REQUIREMENT(V)

    template<class T, gbool = Class<T>::isAbstract() || !Class<T>::template isConstruct<T const &>()>
    class Maker;

    class Entry;

    using Node = typename Class<TreeMap<K, V>::Entry>::Pointer;

    template<class _K, class _V>
    using AbstractEntry = typename Map<_K, _V>::Entry;

    template<class T>
    class Maker<T, true> {
    public:
        static T &copyOf(T const &obj) {
            return (T &) obj.clone();
        }
    };

    template<class T>
    class Maker<T, false> {
    public:
        static T &copyOf(T const &obj) {
            if (Object::isPerfectlyInstanceOf<T>(obj))
                try {
                    return *new T(obj);
                } catch (std::bad_alloc const &) { throw MemoryError(); }
            else {
                Object const &o = obj;
                return (T &) o.clone();
            }
        }
    };

    class Entry : public Map<K, V>::Entry {
    public:
        K const &_key;
        V *_value;
        Node left = nullptr;
        Node right = nullptr;
        Node parent = nullptr;
        /**
         * Construct new entry
         * \param key
         * \param value
         * \param parent (nullable value)
         */
        CORE_EXPLICIT Entry(const K &key, V &value, Node parent) : _key(key), _value(&value), parent(parent) {}

        /**
         * Return key of this entry
         */
        const K &key() const override {
            return _key;
        }

        /**
         * Return value of this entry
         */
        const V &value() const override {
            return *_value;
        }

        /**
         * Return value of this entry
         */
        V &value() override {
            return *_value;
        }

        /**
         * Replaces the value currently associated with the key with the given value
         * \param obj The new value
         */
        V &setValue(const V &obj) override {
            V &old = *_value;
            if (_value != &obj)
                _value = &Maker<V>::copyOf(obj);
            return old;
        }

        /**
         * Compares giving object with this entry
         * \param obj object to be compared
         */
        gbool equals(const Object &obj) const override {
            if (this == &obj)
                return true;
            if (!Class<Entry>::hasInstance(obj))
                return false;
            typename Map<K, V>::Entry const &entry = (Entry const &) obj;
            if (_key != entry.key())
                return false;
            return value().equals(entry.value());
        }

        /**
         * Return copy of this entry
         */
        Object &clone() const override {
            try {
                return *new Entry(*this);
            } catch (...) { throw MemoryError(); }
        }

        /**
         * Return string representation of this entry
         */
        String toString() const override {
            return _key.toString() + ": " + _value->toString();
        }
    };

    class Values : public Collection<V> {
        TreeMap<K, V> &self;

    public:
        CORE_EXPLICIT Values(TreeMap<K, V> &self) : self(self) {}

        gint size() const override {
            return self.len;
        }

        Iterator2<V> &iterator2() const override {
            return (ValuesItr2 &) ValuesItr2(self).clone();
        }

        Iterator2<V> &iterator2() override {
            return (ValuesItr2 &) ValuesItr2(self).clone();
        }

        gbool contains(const V &obj) const override {
            return self.containsValue(obj);
        }

        gbool remove(const V &obj) override {
            for (Node node = self.checkFirstNode(); node != nullptr; node = self.checkSuccessor(node)) {
                if (obj.equals(node->value())) {
                    self.removeInTree(node->parent == nullptr ? self.root : node->parent, node->key());
                    return true;
                }
            }
            return false;
        }

        void clear() override {
            self.clear();
        }

        Object &clone() const override {
            try {
                return *new Values(self);
            } catch (...) { throw MemoryError(); }
        }
    };

    class Keys : public Set<K> {
        TreeMap<K, V> &self;

    public:
        CORE_EXPLICIT Keys(TreeMap<K, V> &self) : self(self) {}

        gbool contains(const K &obj) const override {
            return self.containsKey(obj);
        }

        void clear() override {
            self.clear();
        }

        gint size() const override {
            return self.len;
        }

        Iterator2<K> &iterator2() const override {
            return (KeysItr2 &) KeysItr2(self).clone();
        }
        Iterator2<K> &iterator2() override {
            return (KeysItr2 &) KeysItr2(self).clone();
        }

        Object &clone() const override {
            try {
                return *new Keys(self);
            } catch (...) { throw MemoryError(); }
        }
    };

    class Entries : public Set<AbstractEntry<K, V>> {
        TreeMap<K, V> &self;

    public:
        CORE_EXPLICIT Entries(TreeMap<K, V> &self) : self(self) {}

        Iterator2<AbstractEntry<K, V>> &iterator2() const override {
            return (Iterator2<AbstractEntry<K, V>> &) EntriesItr2(self).clone();
        }

        Iterator2<AbstractEntry<K, V>> &iterator2() override {
            return (Iterator2<AbstractEntry<K, V>> &) EntriesItr2(self).clone();
        }

        gbool contains(const typename Map<K, V>::Entry &obj) const override {
            Node node = self.checkNode(obj.key());
            if (node != nullptr)
                return testEquality(obj.value(), node->value());
            return false;
        }

        void clear() override {
            self.clear();
        }

        gint size() const override {
            return self.len;
        }

        Object &clone() const override {
            try {
                return *new Entries(self);
            } catch (...) { throw MemoryError(); }
        }
    };

    template<class U>
    class Itr : public Iterator<U> {
    public:
        TreeMap &self;
        Node successor = nullptr;
        Node lastNode = nullptr;

        CORE_EXPLICIT Itr(TreeMap &self) : self(self) {}

        gbool hasNext() const override {
            return successor != nullptr;
        }

        void remove() override {
            if (lastNode == nullptr)
                throw StateError("No such item");
            if(lastNode->parent == nullptr)
                self.removeInTree(self.root, lastNode->key());
            else
                self.removeInTree(lastNode->parent, lastNode->key());
            lastNode = nullptr;
        }

        Node nextEntry() {
            if (!hasNext())
                throw StateError("No such item");
            lastNode = successor;
            successor = self.checkSuccessor(successor);
            return lastNode;
        }

        gbool equals(const Object &obj) const override {
            if (this == &obj)
                return true;
            if (!Class<Itr>::hasInstance(obj))
                return false;
            Itr const &it = (Itr const &) obj;
            return &it.self == &self && it.successor == successor;
        }
    };

    template<class U>
    class Itr2 : public Iterator2<U> {
    public:
        TreeMap &self;
        Node successor = nullptr;
        Node lastNode = nullptr;

        CORE_EXPLICIT Itr2(TreeMap &self) : self(self) {}

        gbool hasNext() const override {
            return successor != nullptr;
        }

        void remove() override {
            if (lastNode == nullptr)
                throw StateError("No such item");
            if(lastNode->parent == nullptr)
                self.removeInTree(self.root, lastNode->key());
            else
                self.removeInTree(lastNode->parent, lastNode->key());
            lastNode = nullptr;
        }

        Node nextEntry() {
            if (!hasNext())
                throw StateError("No such item");
            lastNode = successor;
            successor = self.checkSuccessor(successor);
            return lastNode;
        }

        gbool equals(const Object &obj) const override {
            if (this == &obj)
                return true;
            if (!Class<Itr2>::hasInstance(obj))
                return false;
            Itr2 const &it = (Itr2 const &) obj;
            return &it.self == &self && it.successor == successor;
        }
    };

    class KeysItr2 : public Itr2<K> {
    public:
        CORE_EXPLICIT KeysItr2(TreeMap &self) : Itr2<K>(self) {}

        const K &next() override {
            return this->nextEntry()->key();
        }

        gbool equals(const Object &obj) const override {
            return Itr2<K>::equals(obj) && Class<KeysItr2>::hasInstance(obj);
        }

        Object &clone() const override {
            try {
                return *new KeysItr2(Itr2<K>::self);
            } catch (...) { throw MemoryError(); }
        }
    };

    class ValuesItr2 : public Itr2<V> {
    public:
        CORE_EXPLICIT ValuesItr2(TreeMap &self) : Itr2<V>(self) {}

        const V &next() override {
            return this->nextEntry()->value();
        }

        gbool equals(const Object &obj) const override {
            return Itr2<V>::equals(obj) && Class<ValuesItr2>::hasInstance(obj);
        }

        Object &clone() const override {
            try {
                return *new ValuesItr2(Itr2<V>::self);
            } catch (...) { throw MemoryError(); }
        }
    };

    class EntriesItr : public Itr<AbstractEntry<K, V>> {
    public:
        CORE_EXPLICIT EntriesItr(TreeMap &self) : Itr<AbstractEntry<K, V>>(self) {}

        AbstractEntry<K, V> &next() override {
            return *this->nextEntry();
        }

        gbool equals(const Object &obj) const override {
            return Itr<AbstractEntry<K, V>>::equals(obj) && Class<EntriesItr2>::hasInstance(obj);
        }

        Object &clone() const override {
            try {
                return *new EntriesItr(Itr<AbstractEntry<K, V>>::self);
            } catch (...) { throw MemoryError(); }
        }
    };

    class EntriesItr2 : public Itr2<AbstractEntry<K, V>> {
    public:
        CORE_EXPLICIT EntriesItr2(TreeMap &self) : Itr2<AbstractEntry<K, V>>(self) {}

        AbstractEntry<K, V> &next() override {
            return *Itr2<AbstractEntry<K, V>>::nextEntry();
        }

        gbool equals(const Object &obj) const override {
            return Itr2<AbstractEntry<K, V>>::equals(obj) && Class<EntriesItr2>::hasInstance(obj);
        }

        Object &clone() const override {
            try {
                return *new EntriesItr2(this->self);
            } catch (...) { throw MemoryError(); }
        }
    };

    Comparator<K> const &cmp;
    Node root = nullptr;

    /**
     * Number of entry
     */
    gint len = 0;

public:
    /**
     * Constructs a new, empty tree map, using the natural ordering of its key.
     * All keys inserted into the map must implement the comparable class
     */
    template<class = K /*, Class<gbool>::Require<Class<Comparable<K>>::template isSuper<_>()> = true*/>
    CORE_IMPLICIT TreeMap() : cmp(NaturalOrderComparator<K>::INSTANCE) {}

    /**
     * Constructs a new, empty tree map, ordered according to the given comparator.
     * All keys inserted into the map must be mutually comparable by the given comparator
     * \param comparator the comparator that will be used to order this map.
     */
    CORE_EXPLICIT TreeMap(const Comparator<K> &comparator) : cmp(comparator) {}

    /**
     * Constructs a new tree map containing the same mappings as the given
     * map, ordered according to the <em>natural ordering of its keys.
     * \param m the map whose mappings are to be placed in this map
     */
    template<class _K, class _V,
             Class<gbool>::Require<Class<K>::template isSuper<_K>()> = true,
             Class<gbool>::Require<Class<V>::template isSuper<_V>()> = true,
             Class<gbool>::Require<Class<Comparable<_K>>::template isSuper<_K>()> = true>
    CORE_EXPLICIT TreeMap(Map<_K, _V> const &m) : cmp(NaturalOrderComparator<K>::INSTANCE) {
        addAll(m);
    }

    /**
     * Constructs a new tree map containing the same mappings and
     * using the same ordering as the specified ordered map.  This
     * method runs in linear time.
     * \param m the ordered map whose mappings are to be placed in this map,
     *          and whose comparator is to be used to sort this map
     */
    template<class _K, class _V,
             Class<gbool>::Require<Class<K>::template isSuper<_K>()> = true,
             Class<gbool>::Require<Class<V>::template isSuper<_V>()> = true>
    CORE_EXPLICIT TreeMap(OrderedMap<_K, _V> const &m) : cmp(m.comparator()) {
        addAll(m);
    }

    CORE_IMPLICIT TreeMap(TreeMap<K, V> const &m) : TreeMap((OrderedMap<K, V> const &) m) {}

    CORE_IMPLICIT TreeMap(TreeMap<K, V> &&m) {
        swap(root, m.root);
        swap(len, m.len);
    }

    TreeMap &operator=(TreeMap<K, V> const &m) {
        if (this != &m) {
            addAll(m);
        }
        return *this;
    }

    TreeMap &operator=(TreeMap<K, V> &&m) CORE_NOTHROW {
        if (this != &m) {
            swap(root, m.root);
            swap(len, m.len);
        }
        return *this;
    }

    V &add(const K &key, const V &value) override {
        return addInTree(key, value, true);
    }

    void addAll(const Map<K, V> &m) override {
        if (this != &m) {
            if (Class<TreeMap<K, V>>::hasInstance(m) && len == 0) {
                TreeMap<K, V> const &map = (TreeMap<K, V> const &) m;
                root = copyOfTree(map.root);
                len = map.len;
            } else {
                Iterator2<AbstractEntry<K, V>> &it = m.iterator2();
                while (it.hasNext()) {
                    typename Map<K, V>::Entry const &entry = it.next();
                    add(entry.key(), entry.value());
                }
            }
        }
    }

    V &remove(const K &key) override {
        return removeInTree(root, key);
    }

    /**
     * Removes the entry for the specified key only if it is currently mapped to the specified value.
     */
    gbool remove(const K &key, const V &value) override {
        Node node = checkNode(key);
        if (node == nullptr)
            return false;
        if (!value.equals(node->value()))
            return false;
        removeInTree(node->parent == nullptr ? root : node->parent, key);
        return true;
    }

    const V &get(const K &key) const override {
        Node node = checkNode(key);
        if (node == nullptr)
            throw KeyError(key);
        return node->value();
    }

    V &get(const K &key) override {
        Node node = checkNode(key);
        if (node == nullptr)
            throw KeyError(key);
        return node->value();
    }

    typename Map<K, V>::Entry const &getEntry(K const &key) const {
        Node node = checkNode(key);
        if (node == nullptr)
            throw KeyError(key);
        return *node;
    }

    typename Map<K, V>::Entry &getEntry(K const &key) {
        Node node = checkNode(key);
        if (node == nullptr)
            throw KeyError(key);
        return *node;
    }

    void forEach(const BiConsumer<K const &, const V &> &action) const override {
        gint oldSize = len;
        for (Node node = checkFirstNode(); node != nullptr; node = checkSuccessor(node)) {
            action.accept(node->key(), node->value());
            if (len != oldSize)
                throw MemoryError("Concurrent Modification");
        }
    }

    void forEach(const BiConsumer<K const &, V &> &action) override {
        gint oldSize = len;
        for (Node node = checkFirstNode(); node != nullptr; node = checkSuccessor(node)) {
            action.accept(node->key(), node->value());
            if (len != oldSize)
                throw MemoryError("Concurrent Modification");
        }
    }

    gbool containsKey(const K &key) const override {
        return checkNode(key) != nullptr;
    }

    gbool containsValue(const V &value) const override {
        for (Node node = checkFirstNode(); node != nullptr; node = checkSuccessor(node))
            if (testEquality(value, node->value()))
                return true;
        return false;
    }

    /**
     * Returns the number of key-value mappings in this map.
     */
    gint size() const override {
        return len;
    }

    const Comparator<K> &comparator() const override {
        return cmp;
    }

    Object &clone() const override {
        try {
            return *new TreeMap<K, V>(*this);
        } catch (...) { throw MemoryError(); }
    }

    gbool equals(const Object &obj) const override {
        if (this == &obj)
            return true;
        if (!Class<TreeMap>::hasInstance(obj))
            return false;
        TreeMap const &m = (TreeMap const &) m;
        if (len != m.len)
            return false;
        for (Node node = checkFirstNode(); node != nullptr; node = checkSuccessor(node))
            if (!m.contains(node->key(), node->value()))
                return false;
        return true;
    }

    const V &getOrDefault(const K &key, const V &defaultValue) const override {
        Node node = checkNode(key);
        if (node == nullptr)
            return defaultValue;
        return node->value();
    }

    V &getOrDefault(const K &key, V &defaultValue) override {
        Node node = checkNode(key);
        if (node == nullptr)
            return defaultValue;
        return node->value();
    }

    gbool isEmpty() const override {
        return len != 0;
    }

    gbool contains(const K &key, const V &value) const override {
        Node node = checkNode(key);
        if (node == nullptr)
            return false;
        return value.equals(node->value());
    }

    String toString() const override {
        if (isEmpty())
            return "{}";
        String string = "{";
        Node node = checkFirstNode();
        Node node1 = nullptr;
        for (; node != nullptr; node = node1) {
            node1 = checkSuccessor(node);
            string += node->key().toString() + ": " + node->value().toString();
            if (node1 != nullptr)
                string += ", ";
        }
        string += "}";
        return string;
    }

    Iterator2<AbstractEntry<K, V>> &iterator2() const override {
        try {
            return *new EntriesItr2((TreeMap &) *this);
        } catch (...) { throw MemoryError(); }
    }

    Iterator2<AbstractEntry<K, V>> &iterator2() override {
        try {
            return *new EntriesItr2(*this);
        } catch (...) { throw MemoryError(); }
    }

    Iterator<AbstractEntry<K, V>> &iterator() override {
        try {
            return *new EntriesItr(*this);
        } catch (...) { throw MemoryError(); }
    }

    void clear() override {
        Node node = checkFirstNode();
        Node node1 = nullptr;
        while(node != nullptr){
            node1 = checkSuccessor(node);
            removeInTree(node->parent == nullptr ? root : node->parent, node->key());
            node = node1;
        }
    }

    Set<K> &keys() const override {
        try {
            return *new Keys((TreeMap &) *this);
        } catch (...) { throw MemoryError(); }
    }

    Collection<V> &values() const override {
        try {
            return *new Values((TreeMap &) *this);
        } catch (...) { throw MemoryError(); }
    }

    Set<AbstractEntry<K, V>> &entries() const override {
        try {
            return *new Entries((TreeMap &) *this);
        } catch (...) { throw MemoryError(); }
    }

    virtual ~TreeMap() {
        clear();
        root = nullptr;
        len = 0;
    }

protected:
    /**
     * Return entry
     */
    Node checkNode(K const &key) const {
        Node node = root;
        Comparator<K> const &comparator = cmp;
        while (node != nullptr) {
            gint res = comparator.compare(key, node->_key);
            if (res < 0)
                node = node->left;
            else if (res)
                node = node->right;
            else
                return node;
        }
        return nullptr;
    }

    /**
     * Return successor of specified node
     */
    Node checkSuccessor(Node node) const {
        if (node != nullptr) {
            if (node->right != nullptr) {
                node = node->right;
                while (node->left != nullptr)
                    node = node->left;
                return node;
            } else {
                Node node1 = node;
                node = node->parent;
                while (node != nullptr) {
                    if (node1 != node->right)
                        break;
                    node1 = node;
                    node = node->parent;
                }
                return node;
            }
        }
        return nullptr;
    }

    /**
     * Return predecessor of specified node
     */
    Node checkPredecessor(Node node) const {
        if (node != nullptr) {
            if (node->left != nullptr) {
                node = node->left;
                while (node->right != nullptr)
                    node = node->right;
                return node;
            } else {
                Node node1 = node;
                node = node->parent;
                while (node != nullptr) {
                    if (node1 != node->left)
                        break;
                    node1 = node;
                    node = node->parent;
                    break;
                }
                return node;
            }
        }
        return nullptr;
    }

    /**
     * Return Parent of specified key in this map
     */
    Node checkAncestor(Node src, K const &key, gint &contains, gint &pos) {
        contains = false;
        Node node = src;
        Node node1 = nullptr;
        pos = 0;
        while (node != nullptr) {
            gint res = cmp.compare(key, node->key());
            if (res < 0) {
                node1 = node;
                pos = 1;
                node = node->left;
            } else if (res > 0) {
                node1 = node;
                pos = 2;
                node = node->right;
            } else {
                contains = true;
                break;
            }
        }
        return node1;
    }

    /**
     * Return first node of this map
     */
    Node checkFirstNode() const {
        Node node = root;
        if (node != nullptr)
            while (node->left != nullptr)
                node = node->left;
        return node;
    }

    /**
     * Return last node of this map
     */
    Node checkLastNode() const {
        Node node = root;
        if (node != nullptr)
            while (node->right != nullptr)
                node = node->right;
        return node;
    }

    /**
     * Return true if the two specified objects are equals
     */
    static gbool testEquality(Object const &obj1, Object const &obj2) {
        return obj1.equals(obj2);
    }

    V &addInTree(K const &k, V const &v, gbool copy = false) {
        gint searchSatus;
        gint leftOrRight = 0;
        Node node = checkAncestor(root, k, searchSatus, leftOrRight);
        if (searchSatus == 0) {
            Node newNode = copy ? new Entry(Maker<K>::copyOf(k), Maker<V>::copyOf(v), node) : new Entry(k, (V &) v, node);
            (leftOrRight == 0 ? root : leftOrRight == 1 ? node->left
                                                        : node->right) = newNode;
            len += 1;
            return newNode->value();
        } else {
            Node oldNode = leftOrRight == 0 ? root : leftOrRight == 1 ? node->left
                                                                      : node->right;
            V &oldValue = oldNode->value();
            if (copy)
                oldNode->setValue(v);
            else
                oldNode->_value = &(V &) v;
            return oldValue;
        }
    }

    V &removeInTree(Node src, K const &k) {
        gint searchStatus;
        gint leftOrRight;
        Node node = checkAncestor(src, k, searchStatus, leftOrRight);
        if (searchStatus == 0)
            throw KeyError(k);
        Node oldNode = leftOrRight == 1 ? node->left : leftOrRight == 2 ? node->right
                                                                        : root;
        Node left = nullptr;
        Node right = nullptr;
        swap(left, oldNode->left);
        swap(right, oldNode->right);
        oldNode->parent = nullptr;
        (leftOrRight == 0 ? root : leftOrRight == 1 ? node->left
                                                    : node->right) = right;
        if (right != nullptr) {
            right->parent = node;
            node = right;
        }
        if (left != nullptr) {
            Node node1 = checkAncestor(node, left->key(), searchStatus, leftOrRight);
            if (searchStatus == 1)
                throw StateError("InternalError");
            (leftOrRight == 0 ? root : leftOrRight == 1 ? node->left
                                                        : node->right) = left;
        }
        len -= 1;
        V &oldValue = oldNode->value();
        oldNode->_value = nullptr;
        delete oldNode;
        return oldValue;
    }

    void linkNode(Node dst, Node src) {
        if (dst == nullptr) {
            root = src;
        } else if (src != nullptr) {
            while (dst != nullptr) {
                gint res = cmp.compare(src->_key, dst->_key);
                if (res < 0) {
                    if (dst->left == nullptr) {
                        dst->left = src;
                        break;
                    } else
                        dst = dst->left;
                } else if (res > 0) {
                    if (dst->right == nullptr) {
                        dst->right = src;
                        break;
                    } else
                        dst = dst->right;
                } else
                    break;
            }
        }
    }

    Node copyOfTree(Node src) {
        if (src == nullptr)
            return nullptr;
        Node dst;
        // copy of root
        try {
            dst = new Entry(src->key(), src->value(), nullptr);
        } catch (...) { throw MemoryError(); }
        // copy left of root
        dst->left = copyOfTree(src->left);
        if (dst->left != nullptr)
            dst->left->parent = dst;
        Node node = dst;
        // goto root linked successor (right of root)
        while ((src = src->right) != nullptr) {
            // copy right of root
            try {
                node->right = new Entry(src->key(), src->value(), node);
            } catch (...) { throw MemoryError(); }
            node = node->right;
            // restart operation
            node->left = copyOfTree(src->left);
        }
    }

    template<class T, class U>
    static void swap(T &t, U &u) {
        T t2 = t;
        t = u;
        u = t2;
    }
};

#if __cpp_deduction_guides > 201565

TreeMap()->TreeMap<Object, Object>;

template<class K, class V>
TreeMap(Map<K, V> const &) -> TreeMap<K, V>;

template<class K>
TreeMap(Comparator<K> const &) -> TreeMap<K, Object>;

#endif


#endif//CORE_TREEMAP_H
