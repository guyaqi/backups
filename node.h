//
// Created by guyaqi5858 on 18-10-21.
//

#ifndef SODAENGINE_NODE_H
#define SODAENGINE_NODE_H

#include <vector>
using std::vector;

namespace soda{

/**
 * For class A, extend node<A>.
 *
 * Implement:
 *   1) T(const T&) // you should copy extra content about your node in copy constructor
 * @tparam T class to process node control
 */
    template <typename T>
    class node {
    private:
        node<T> *parent;
        vector<node<T>*> children;
    public:
        node();
        ~node<T>() = default;
        explicit node(node<T>* parent);

        node(const node &rhs);
        node& operator=(const node &rhs) = delete;

        T* copy_recursive() const;

        bool set_parent(T*);
        T* get_parent() const;

        bool has_child(T*) const;
        bool add_child(T*);
        bool remove_child(T*);
        vector<T*> get_children() const;
    };

    template<typename T>
    node<T>::node() : parent(nullptr), children() {}

    template<typename T>
    node<T>::node(node<T> *parent) : parent(parent), children() {
        parent->add_child((T*)this);
    }

    template<typename T>
    node<T>::node(const node &rhs) : parent(rhs.parent), children() {
        if(parent) {
            parent->add_child((T*)this);
        }
    }

    template<typename T>
    T *node<T>::copy_recursive() const {
        auto subtype = new T(*(T*)this);
        for(node<T>* child:children) {
            ((node<T>*)subtype)->add_child(child->copy_recursive());
        }
        return subtype;
    }

    template<typename T>
    bool node<T>::set_parent(T *new_parent) {
        for(node<T>* p=new_parent;p!=nullptr;p=p->parent) {
            if(this == new_parent->parent) return false;
        }
        if(this->parent) {
            this->parent->remove_child((T*)this);
        }
        this->parent = new_parent;
        this->parent->add_child((T*)this);
        return true;
    }

    template<typename T>
    T *node<T>::get_parent() const {
        return this->parent;
    }

    template<typename T>
    bool node<T>::has_child(T *child) const {
        for(const auto &one : children) {
            if(one == child) return true;
        }
        return false;
    }

    template<typename T>
    bool node<T>::add_child(T *child) {
        for(node<T>* p=parent;p!= nullptr;p=p->parent) {
            if(child == p->parent) return false;
        }
        auto t_child = (node<T>*)child;
        if(t_child->parent) {
            t_child->parent->remove_child(child);
        }
        children.push_back(t_child);
        t_child->parent = this;

        return true;
    }

    template<typename T>
    bool node<T>::remove_child(T *child) {
        for(auto it=children.begin();it!=children.end();it++) {
            if(*it == child) {
                children.erase(it);
                return true;
            }
        }
        return false;
    }

    template<typename T>
    vector<T*> node<T>::get_children() const {
        vector<T*> vec;
        for(node<T>* child: children) {
            vec.push_back((T*)child);
        }
        return vec;
    }
}


#endif //SODAENGINE_NODE_H
