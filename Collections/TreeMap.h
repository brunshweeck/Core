//
// Created by brunshweeck on 15/03/2023.
//

#ifndef CORE_TREEMAP_H
#define CORE_TREEMAP_H


#include "OrderedMap.h"
#include "../Function/NaturalOrderComparator.h"
#include "../KeyError.h"

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

    CORE_FAST static gbool RED = false;
    CORE_FAST static gbool BLACK = true;

    template<class T, gbool = Class<T>::isAbstract() || !Class<T>::template isConstruct<T const &>()>
    class Maker;

    class Entry;

    using Node = typename Class<TreeMap<K, V>::Entry>::Pointer;

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
            try { return *new T(obj); } catch (std::bad_alloc const &) { throw MemoryError(); }
        }
    };

    class Entry : public Map<K, V>::Entry {
        K const &_key;
        V *_value;
        Node left = nullptr;
        Node right = nullptr;
        Node parent = nullptr;
        gbool color = BLACK;
    public:
        /**
         * Construct new entry
         * \param key
         * \param value
         * \param parent (nullable value)
         */
        CORE_EXPLICIT Entry(const K &key, V &value, Node parent) : _key(key), _value(value), parent(parent) {}

        /**
         * Return key of this entry
         */
        const K &key() override {
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
            if (this != &obj)
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
            try { return *new Entry(*this); } catch (...) { throw MemoryError(); }
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

        Iterator<const V> &&iterator() const override {
            //
        }

        gbool contains(const V &obj) const override {
            return self.containsValue(obj);
        }

        gbool remove(const V &obj) override {
            for (Node node = checkNode(root); node != nullptr; node = checkSuccessor(node)) {
                if (obj.equals(node->value())) {
                    removeInTree(node->parent, node->key());
                    return true;
                }
            }
            return false;
        }

        void clear() override {
            self.clear();
        }
    };

    class Keys : public Set<K> {
        TreeMap<K, V>& self;
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

        Iterator<const K> &&iterator() const override {
            //
        }
    };

    class Entries : public Set<typename Map<K, V>::Entry> {
        TreeMap<K, V>& self;
    public:
        CORE_EXPLICIT Entries(TreeMap<K, V> &self) : self(self) {}

        Iterator<const typename Map<K, V>::Entry> &&iterator() const override {
            //
        }

        gbool contains(const typename Map<K, V>::Entry &obj) const override {
            Node node = checkNode(obj.key());
            if(node != nullptr)
                return testEquality(obj.value(), node->value());
            return false;
        }

        void clear() override {
            self.clear();
        }

        gint size() const override {
            return self.len;
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
    template<class _ = K, Class<gbool>::Require<Class<Comparable<K>>::template isSuper<_>()> = true>
    CORE_IMPLICIT TreeMap(): cmp(NaturalOrderComparator<K>::INSTANCE) {}

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
    CORE_EXPLICIT TreeMap(Map<_K, _V> const &m): cmp(NaturalOrderComparator<K>::INSTANCE) {
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
    CORE_EXPLICIT TreeMap(OrderedMap<_K, _V> const &m): cmp(m.comparator()) {
        addAll(m);
    }

    CORE_IMPLICIT TreeMap(TreeMap<K, V> const &m) {}

    CORE_IMPLICIT TreeMap(TreeMap<K, V> &&m) {}

    TreeMap &operator=(TreeMap<K, V> const &m) {}

    TreeMap &operator=(TreeMap<K, V> &&m) CORE_NOTHROW {}

    V &add(const K &key, const V &value) override {
        return addInTree(root, Maker<K>::copyOf(key), Maker<V>::copyOf(value));
    }

    void addAll(const Map<K, V> &m) override {
        if (this != &m) {
            if (Class<TreeMap<K, V>>::hasInstance(m) && len == 0) {
                TreeMap<K, V> const &map = (TreeMap<K, V> const &) m;
                root = copyOfTree(map.root);
                len = map.len;
            } else {
                Iterator<typename Map<K, V>::Entry const> &&it = m.iterator();
                while (it.hasNext()) {
                    typename Map<K, V>::Entry const &entry = it.next();
                    addInTree(root, entry.key(), entry.value());
                }
            }
        }
    }

    V &remove(const K &key) override {
        return removeInTree(root, key);
    }

    gbool remove(const K &key, const V &value) override {
        return 0;
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

    void forEach(const BiConsumer<const K &, const V &> &action) const override {
        gint oldSize = len;
        for (Node node = checkFirstNode(); node != nullptr; node = checkSuccessor(node)) {
            action.accept(node->key(), node->value());
            if (len != oldSize)
                throw MemoryError("Concurrent Modification");
        }
    }

    void forEach(const BiConsumer<const K &, V &> &action) override {
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
        try { return *new TreeMap<K, V>(*this); } catch (...) { throw MemoryError(); }
    }

    //

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
                    if (node1 != node->rigth)
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

    V &addInTree(Node dst, K const &k, V &v) {
        if (root == nullptr) {
            try { root = new Entry(k, v); } catch (...) { throw MemoryError(); }
            len += 1;
            return root->value();
        } else
            while (true) {
                gint res = cmp.compare(k, dst->key());
                if (res < 0) {
                    if (dst->left == nullptr) {
                        try { dst->left = new Entry(k, v); } catch (...) { throw MemoryError(); }
                        len += 1;
                        return dst->right->value();
                    } else
                        dst = dst->left;
                } else if (res > 0) {
                    if (dst->right == nullptr) {
                        try { dst->right = new Entry(k, v); } catch (...) { throw MemoryError(); }
                        len += 1;
                        return dst->right->value();
                    } else
                        dst = dst->right;
                } else {
                    return dst->setValue(v);
                }
            }

    }

    V &removeInTree(Node src, K const &k) {
        while (src != nullptr) {
            gint res = cmp.compare(k, src->key());
            if (res < 0) {
                src = src->left;
            } else if (res > 0) {
                src = src->right;
            } else {
                len -= 1;
                Node parent = src->parent;
                Node left = src->left;
                Node right = src->right;
                left->parent = right->parent = nullptr;
                if (parent != nullptr) {
                    if (src == parent->left) {
                        if (right != nullptr) {
                            parent->left = right;
                            right->parent = parent;
                            linkNode(right, left);
                        } else {
                            parent->left = left;
                        }
                    } else {
                        if (right != nullptr) {
                            parent->right = right;
                            right->parent = parent;
                            linkNode(right, left);
                        } else {
                            parent->right = left;
                        }
                    }
                } else {
                    linkNode(nullptr, right);
                    linkNode(root, left);
                }
                V &oldValue = src->_value;
                src->left = src->parent = src->right = nullptr;
                delete src;
                return oldValue;
            }
        }
        throw KeyError(k);
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
        Node dst;
        try { dst = new Entry(src->key(), src->value()); } catch (...) { throw MemoryError(); }
        Node node = dst;
        while (src != nullptr) {
            node->left = copyOfTree(src->left);
            try { node->right = new Entry(src->key(), src->value()); } catch (...) { throw MemoryError(); }
            node = node->right;
            src = src->right;
        }
    }
};


#endif //CORE_TREEMAP_H
