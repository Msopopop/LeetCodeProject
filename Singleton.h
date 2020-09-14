#pragma once
namespace singleton {
    // Singleton without multi-thread safe options
    class badSingleton
    {
    public:
        static badSingleton* getInstance()
        {
            // check if exists
            if (m_instance == nullptr)
                m_instance = new badSingleton();
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
    class goodSingletonForModernCpp {
    public:
        static T& getInstance() {
            static T value;
            return value;
        }
        goodSingletonForModernCpp() = delete;
        goodSingletonForModernCpp(const goodSingletonForModernCpp&) = delete;
        ~goodSingletonForModernCpp() = delete;
        goodSingletonForModernCpp& operator=(const goodSingletonForModernCpp&) = delete;
    };
}
