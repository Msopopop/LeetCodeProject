#pragma once
namespace singleton {
    // Singleton without multi-thread safe options
    class Singleton
    {
    public:
        static Singleton* getInstance()
        {
            // check if exists
            if (m_instance == nullptr)
                m_instance = new Singleton();
            return m_instance;
        }
    private:
        static Singleton* m_instance;
        Singleton();
        Singleton(const Singleton& other);
    };
    Singleton* Singleton::m_instance = nullptr;

    // multi-thread safe for C++11
    template<typename T>
    class goodSingleton {
    public:
        static T& getInstance() {
            static T value;
            return value;
        }
        goodSingleton() = delete;
        goodSingleton(const goodSingleton&) = delete;
        ~goodSingleton() = delete;
        goodSingleton& operator=(const goodSingleton&) = delete;
    };
}
