#include "shared_ptr.h"

template <typename T>
SharedPtr<T>::SharedPtr (T* ptr) {
    this->_p = ptr;
    this->_count = new size_t(1);
}

template <typename T>
SharedPtr<T>::SharedPtr () {
    this->_p = nullptr;
    this->_count = nullptr;
}

template <typename T>
SharedPtr<T>::SharedPtr (const SharedPtr& ptr) {
    this->_p = ptr._p;
    this->_count = ptr._count;
    if (this->_count != nullptr)
        (*this->_count) ++;
}

template <typename T>
SharedPtr<T>::~SharedPtr () {
    if (this->_count != nullptr) {
        (*this->_count) --;
        if (*(this->_count) == 0) {
            delete this->_p;
            delete this->_count;
        }
    }
    this->_p = nullptr;
    this->_count = nullptr;
}

template <typename T>
size_t SharedPtr<T>::use_count () const {
    if (this->_count != nullptr) return *(this->_count);
    else return 0;
}

template <typename T>
T* SharedPtr<T>::get () const {
    return this->_p;
}

template <typename T>
void SharedPtr<T>::reset () {
    if (this->_count != nullptr) {
        (*this->_count) --;
        if (*(this->_count) == 0) {
            delete this->_p;
            delete this->_count;
        }
    }
    this->_p = nullptr;
    this->_count = nullptr;
}

template <typename T>
void SharedPtr<T>::reset (T* ptr) {
    if (this->_count != nullptr) {
        (*this->_count) --;
        if (*(this->_count) == 0) {
            delete this->_p;
            delete this->_count;
        }
    }
    this->_p = ptr;
    this->_count = new size_t(1);
}

template <typename T>
T SharedPtr<T>::operator* () const {
    return *(this->_p);
}

template <typename T>
T* SharedPtr<T>::operator-> () const {
    return this->_p;
}

template <typename T>
SharedPtr<T>::operator bool () const {
    return this->_p != nullptr;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator= (SharedPtr<T>& ptr) {
    if (this->_p != ptr._p) {
        this->_p = ptr._p;
        this->_count = ptr._count;
        if (this->_count != nullptr)
            (*this->_count) ++;
    }
    return *this;
}

template <typename Type>
SharedPtr<Type> make_shared (Type value) {
    return SharedPtr<Type>(new Type(value));
}