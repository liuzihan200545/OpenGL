#pragma once

#include<format>
#include <source_location>

namespace utils {
    template <class... _Types>
    void printt(const std::format_string<_Types...> _Fmt, _Types&&... _Args) {
        std::cout << vformat(_Fmt.get(), std::make_format_args(_Args...)) << std::endl;
    }

    template<class Type>
    void print(Type t) {
        std::cout << t << std::endl;
    }

    template<class Type>
    void println(Type t) {
        std::cout << t;
    }

    template<class T0, class ...Args>
    void print(T0 t0, Args ... args) {
        println(t0);
        ((println(", "), println(args)), ...);
        println("\n");
    }
}

namespace mini_log {

#define foreach_log_level(f)                         \
    f(trace)                                         \
            f(debug)                                 \
                    f(info)                          \
                            f(critical)              \
                                    f(warning)       \
                                            f(error) \
                                                    f(fatal)

    enum class log_level : std::uint8_t {
#define _FUNCTION(name) name,
        foreach_log_level(_FUNCTION)
#undef _FUNCTION
    };

    namespace details {
        inline auto max_level = log_level::debug;

        inline std::string log_level_name(log_level level) {
            switch (level) {
#define _FUNCTION(name)   \
    case log_level::name: \
        return #name;
                foreach_log_level(_FUNCTION)
#undef _FUNCTION
            }
        }

        template<typename T>
        struct with_source_location {
        private:
            T inner;
            std::source_location loc;

        public:
            template<class U>
                requires std::constructible_from<T, U>
            consteval
                with_source_location(U&& inner, std::source_location loc = std::source_location::current()) : inner(
                    std::forward<U>(inner)), loc(std::move(loc)) {}

            constexpr T const& format() const { return inner; }

            constexpr std::source_location const& location() { return loc; }
        };

        template<typename... Args>
        inline void
            generic_log_info(log_level level, with_source_location<std::format_string<Args...>> fmt, Args &&...args) {
            if (level >= max_level) {
                auto const& loc = fmt.location();
                std::string _info = std::vformat(fmt.format().get(), std::make_format_args(args...));
                std::string info = std::format("{}:{} [{}] {}", loc.file_name(), loc.line(), log_level_name(level),
                    _info);
                std::cout << info << std::endl;
            }
        }
    }// namespace details
#define _FUNCTION(name)                                                                                      \
    template<typename... Args>                                                                               \
    inline void log_##name(details::with_source_location<std::format_string<Args...>> fmt, Args &&...args) { \
        generic_log_info(log_level::name, std::move(fmt), std::forward<Args>(args)...);                      \
    }

    foreach_log_level(_FUNCTION)

#undef _FUNCTION

        inline void set_g_max_log_level(log_level lev) {
        details::max_level = lev;
    }
}