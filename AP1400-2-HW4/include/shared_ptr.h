#ifndef SHARED_PTR
#define SHARED_PTR

#include <iostream>

template <typename T>
class SharedPtr {
public:
    SharedPtr (T* ptr);
    SharedPtr ();
    SharedPtr (const SharedPtr<T>& ptr);
    ~SharedPtr ();

    size_t use_count () const;
    T* get () const;
    void reset ();
    void reset (T* ptr);
    T operator* () const;
    T* operator-> () const;
    operator bool () const;
    SharedPtr<T>& operator= (SharedPtr<T>& ptr);

    template <typename Type>
    friend Type* make_shared (Type value);
private:
    T* _p;
    size_t* _count;
};

#include "shared_ptr.hpp"

#endif //SHARED_PTR