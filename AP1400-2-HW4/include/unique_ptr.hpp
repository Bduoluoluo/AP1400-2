#include "unique_ptr.h"

template <typename T>
UniquePtr<T>::UniquePtr (T* ptr) {
    this->_p = ptr;
}

template <typename T>
UniquePtr<T>::UniquePtr () {
    this->_p = nullptr;
}

template <typename T>
UniquePtr<T>::UniquePtr (UniquePtr<T>&& ptr) {
    this->_p = std::move(ptr._p);
    ptr._p = nullptr;
}

template <typename T>
UniquePtr<T>::~UniquePtr () {
    if (this->_p != nullptr)
        delete this->_p;
    this->_p = nullptr;
}

template <typename T>
T* UniquePtr<T>::get () const {
    return this->_p;
}

template <typename T>
void UniquePtr<T>::reset () {
    if (this->_p != nullptr)
        delete this->_p;
    this->_p = nullptr;
}

template <typename T>
void UniquePtr<T>::reset (T* ptr) {
    if (this->_p != nullptr)
        delete this->_p;
    this->_p = ptr;
}

template <typename T>
T* UniquePtr<T>::release () {
    T* ptr = this->_p;
    this->_p = nullptr;
    return ptr;
}

template <typename T>
T UniquePtr<T>::operator* () const {
    return *(this->_p);
}

template <typename T>
T* UniquePtr<T>::operator-> () const {
    return this->_p;
}

template <typename T>
UniquePtr<T>::operator bool () const {
    return this->_p != nullptr;
}

template <typename Type>
UniquePtr<Type> make_unique (Type value) {
    return UniquePtr<Type>(new Type(value));
}