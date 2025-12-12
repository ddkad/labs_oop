#pragma once

#include <coroutine>
#include <exception>

template<typename T>
struct Generator {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    struct promise_type {
        T value;

        Generator get_return_object() { 
            return Generator(handle_type::from_promise(*this)); 
        }

        std::suspend_always initial_suspend() { return {}; }

        std::suspend_always final_suspend() noexcept { return {}; }
        
        std::suspend_always yield_value(T v) {
            value = v;
            return {};
        }
        
        void return_void() {}
        
        void unhandled_exception() { 
            std::terminate(); 
        }
    };

    handle_type h;

    Generator(handle_type h) : h(h) {}

    ~Generator() { 
        if (h) h.destroy(); 
    }

    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;

    Generator(Generator&& other) noexcept : h(other.h) {
        other.h = nullptr;
    }
    Generator& operator=(Generator&& other) noexcept {
        if (this != &other) {
            if (h) h.destroy();
            h = other.h;
            other.h = nullptr;
        }
        return *this;
    }

    struct iterator {
        handle_type h;

        bool operator!=(std::default_sentinel_t) const { 
            return !h.done(); 
        }
        
        void operator++() { 
            h.resume(); 
        }
        
        T operator*() const { 
            return h.promise().value; 
        }
    };

    iterator begin() { 
        if (h) h.resume(); 
        return {h}; 
    }
    
    std::default_sentinel_t end() { 
        return {}; 
    }
};