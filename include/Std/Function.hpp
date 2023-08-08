#ifndef __STD_FUNCTION_HPP_
#define __STD_FUNCTION_HPP_

//Code by GPT-4

namespace xc {
    namespace Std {
    template<typename T>
    class UniquePtr {
        T* ptr;
    public:
        explicit UniquePtr(T* p = nullptr) : ptr(p) {}
        ~UniquePtr() { delete ptr; }
        T& operator*() const { return *ptr; }
        T* operator->() const { return ptr; }
        UniquePtr(UniquePtr&& u) : ptr(u.ptr) { u.ptr = nullptr; }
        UniquePtr& operator=(UniquePtr&& u) {
            if (this != &u) {
                delete ptr;
                ptr = u.ptr;
                u.ptr = nullptr;
            }
            return *this;
        }
        UniquePtr(UniquePtr&& u) : ptr(u.ptr) { u.ptr = nullptr; }
        UniquePtr& operator=(UniquePtr&& u) {
            if (this != &u) {
                delete ptr;
                ptr = u.ptr;
                u.ptr = nullptr;
            }
            return *this;
        }

        // Add reset and release methods
        void reset(T* p = nullptr) {
            delete ptr;
            ptr = p;
        }
        T* release() {
            T* p = ptr;
            ptr = nullptr;
            return p;
        }
    };

    template<typename T>
    struct RemoveReference {
        typedef T Type;
    };

    template<typename T>
    struct RemoveReference<T&> {
        typedef T Type;
    };

    template<typename T>
    struct RemoveReference<T&&> {
        typedef T Type;
    };

    template<typename T>
    T&& Move(T& obj) {
        return static_cast<T&&>(obj);
    }

    template<typename T>
    T&& Forward(typename RemoveReference<T>::type& param) {
        return static_cast<T&&>(param);
    }

    template<typename T>
    class Function;

    template<typename Ret, typename... Args>
    class Function<Ret(Args...)>
    {
        struct Base
        {
            virtual ~Base() {}
            virtual Ret operator()(Args...) = 0;
        };

        template<typename T>
        struct Wrapper : Base
        {
            T _f;
            Wrapper(T&& f) : _f(Move(f)) {}
            Ret operator()(Args... args) override
            {
                return _f(args...);
            }
        };

        UniquePtr<Base> _base;

    public:
        template<typename T>
        Function(T&& f) : _base(new Wrapper<T>(Forward<T>(f))) {}

        Ret operator()(Args... args)
        {
            return (*_base)(args...);
        }
    };
    }
}

#endif