#pragma once
#include <memory>
#include <type_traits>
namespace singleton {
    // Singleton without multi-thread safe options
    class badSingleton
    {
    public:
        static decltype(auto) getInstance()
        {
            // check if exists
            if (m_instance == nullptr)
#pragma warning(disable: 26409)
                m_instance = new badSingleton();
#pragma warning(default: 26409)
            return m_instance;

            /*
            Maybe you can add lock
            Lock lock;
            if (m_instance == nullptr)
                m_instance = new Singleton();
            return m_instance;
            */

            /*Double-checked locking(DCL)
            if (m_instance == nullptr)
            {
                Lock lock;
                if (m_instance == nullptr)
                    m_instance = new badSingleton();
            }
            return m_instance;
            
            */
        }
    private:
        static badSingleton* m_instance;
        badSingleton();
        badSingleton(const badSingleton& other);
    };
    badSingleton* badSingleton::m_instance = nullptr;

    // multi-thread safe for C++11 or later
    template<typename T>
    class goodSingleton {
    public:
        template<typename ...Args, 
        std::enable_if_t<std::is_convertible_v<Args&&, T> ||
            std::is_constructible_v<T, Args&&>,
            bool> = true>
        static T& getInstance(Args&&... args) 
            noexcept(std::is_nothrow_constructible_v<T, Args&&> ||
                     std::_Is_nothrow_convertible_v<Args&&, T>)
        {
            static T value(std::forward<Args>(args)...);
            return value;
        }
        goodSingleton() = delete;
        goodSingleton(const goodSingleton&) = delete;
        ~goodSingleton() = delete;
        goodSingleton& operator=(const goodSingleton&) = delete;
    };
}
