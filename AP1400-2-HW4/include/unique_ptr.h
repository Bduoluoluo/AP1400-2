#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T>
class UniquePtr {
public:
    UniquePtr (T* ptr);
    UniquePtr ();
    UniquePtr (const UniquePtr<T>& ptr) = delete;
    UniquePtr (UniquePtr<T>&& ptr);
    ~UniquePtr ();

    T* get () const;
    void reset ();
    void reset (T* ptr);
    T* release ();
    T operator* () const;
    T* operator-> () const;
    operator bool () const;
    UniquePtr<T>& operator= (UniquePtr<T>& ptr) = delete;

    template <typename Type>
    friend Type* make_unique (Type value);
private:
    T* _p;
};

#include "unique_ptr.hpp"

#endif //UNIQUE_PTR