#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

#ifndef DBG_ITERABLE_LENGTH
#define DBG_ITERABLE_LENGTH 20
#endif

namespace dbg {

template <typename T>
class type_tag {};

template <typename T>
auto get_type_name(type_tag<T>) {
    std::string name, prefix, suffix;

#ifdef __clang__
    name = __PRETTY_FUNCTION__;
    prefix = "auto dbg::get_type_name(type_tag<T>) [T = ";
    suffix = "]";
#elif defined(__GNUC__)
    name = __PRETTY_FUNCTION__;
    prefix = "auto dbg::get_type_name(type_tag<T>) [with T = ";
    suffix = "]";
#elif defined(_MSC_VER)
    name = __FUNCSIG__;
    prefix = "auto __cdecl dbg::get_type_name<";
    suffix = " >)";
#endif

    return name.substr(prefix.size(),
        name.size() - prefix.size() - suffix.size());
}

template <typename T>
std::string type_name() {
    if (std::is_volatile<T>::value && std::is_pointer<T>::value) {
        return type_name<typename std::remove_volatile<T>::type>() +
            " volatile";
    }
    if (std::is_volatile<T>::value) {
        return "volatile " +
            type_name<typename std::remove_volatile<T>::type>();
    }
    if (std::is_const<T>::value && std::is_pointer<T>::value) {
        return type_name<typename std::remove_const<T>::type>() + " const";
    }
    if (std::is_const<T>::value) {
        return "const " + type_name<typename std::remove_const<T>::type>();
    }
    if (std::is_pointer<T>::value) {
        return type_name<typename std::remove_pointer<T>::type>() + "*";
    }
    if (std::is_lvalue_reference<T>::value) {
        return type_name<typename std::remove_reference<T>::type>() + "&";
    }
    if (std::is_rvalue_reference<T>::value) {
        return type_name<typename std::remove_reference<T>::type>() + "&&";
    }
    return get_type_name(type_tag<T>{});
}

inline std::string get_type_name(type_tag<short>) {
    return "short";
}

inline std::string get_type_name(type_tag<unsigned short>) {
    return "unsigned short";
}

inline std::string get_type_name(type_tag<long>) {
    return "long";
}

inline std::string get_type_name(type_tag<unsigned long>) {
    return "unsigned long";
}

inline std::string get_type_name(type_tag<long long>) {
    return "long long";
}

inline std::string get_type_name(type_tag<unsigned long long>) {
    return "unsigned long long";
}

inline std::string get_type_name(type_tag<std::string>) {
  return "std::string";
}

template <typename T>
std::string get_type_name(type_tag<std::vector<T, std::allocator<T>>>) {
    return "std::vector<" + type_name<T>() + ">";
}

template <typename T, typename U>
std::string get_type_name(type_tag<std::pair<T, U>>) {
    return "std::pair<" + type_name<T>() + ", " + type_name<U>() + ">";
}

template <typename... T>
std::string get_type_name(type_tag<std::tuple<T...>>) {
    std::string result;
    auto unused = {(result += type_name<T>() + ", ", 0)..., 0};
    static_cast<void>(unused);
    if (sizeof...(T) > 0) {
        result.pop_back();
        result.pop_back();
    }
    return "std::tuple<" + result + ">";
}

namespace detail {

namespace {
using std::begin;
using std::end;
using std::size;
}  // namespace

template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<decltype(begin(std::declval<const T&>())),
    decltype(end(std::declval<const T&>())),
    decltype(size(std::declval<const T&>()))>>
        : std::true_type {};

template <typename T, typename = void>
struct is_printable : std::false_type {};

template <typename T>
struct is_printable<T, typename std::enable_if_t<std::is_same_v<
    decltype(std::cout << std::declval<const T&>()), std::ostream&>>>
        : std::true_type {};

}  // namespace detail

// pretty_print forward declarations

template <typename T>
inline void pretty_print(std::ostream& stream, const T& value, std::true_type);

template <typename T>
inline void pretty_print(std::ostream&, const T&, std::false_type);

template <typename T>
inline typename std::enable_if<!detail::is_iterable<T>::value, bool>::type
pretty_print(std::ostream& stream, const T& value);

inline bool pretty_print(std::ostream& stream, const char* const& value);

template <size_t N>
inline bool pretty_print(std::ostream& stream, const char (&value)[N]);

inline bool pretty_print(std::ostream& stream, const std::string& value);

template <typename... Ts>
inline bool pretty_print(std::ostream& stream, const std::tuple<Ts...>& value);

template <>
inline bool pretty_print(std::ostream& stream, const std::tuple<>&);

template <typename T, typename U>
inline bool pretty_print(std::ostream& stream, const std::pair<T, U>& value);

template <typename T>
inline bool pretty_print(std::ostream& stream, const std::stack<T>& value);

template <typename T>
inline bool pretty_print(std::ostream& stream, const std::queue<T>& value);

template <typename T>
inline bool pretty_print(std::ostream& stream, const std::deque<T>& value);

template <typename T>
inline bool pretty_print(std::ostream& stream,
        const std::priority_queue<T>& value);

template <typename T>
inline typename std::enable_if<detail::is_iterable<T>::value, bool>::type
pretty_print(std::ostream& stream, const T& value);

// pretty_print definitions

template <typename T>
inline void pretty_print(std::ostream& stream, const T& value, std::true_type) {
    stream << value;
}

template <typename T>
inline void pretty_print(std::ostream&, const T&, std::false_type) {
    static_assert(detail::is_printable<T>::value,
        "Type does not support the << ostream operator");
}

template <typename T>
inline typename std::enable_if<!detail::is_iterable<T>::value, bool>::type
pretty_print(std::ostream& stream, const T& value) {
    pretty_print(stream, value, typename detail::is_printable<T>::type {});
    return true;
}

inline bool pretty_print(std::ostream& stream, const char* const& value) {
    stream << '"' << value << '"';
    return true;
}

template <size_t N>
inline bool pretty_print(std::ostream& stream, const char (&value)[N]) {
    stream << value;
    return false;
}

inline bool pretty_print(std::ostream& stream, const std::string& value) {
    stream << '"' << value << '"';
    return true;
}

template <size_t I>
struct pretty_print_tuple {
    template <typename... T>
    static void print(std::ostream& stream, const std::tuple<T...>& tuple) {
        pretty_print_tuple<I - 1>::print(stream, tuple);
        stream << ", ";
        pretty_print(stream, std::get<I>(tuple));
    }
};

template <>
struct pretty_print_tuple<0> {
    template <typename... T>
    static void print(std::ostream& stream, const std::tuple<T...>& tuple) {
        pretty_print(stream, std::get<0>(tuple));
    }
};

template <typename... T>
inline bool pretty_print(std::ostream& stream, const std::tuple<T...>& value) {
    stream << "{";
    pretty_print_tuple<sizeof...(T) - 1>::print(stream, value);
    stream << "}";
    return true;
}

template <>
inline bool pretty_print(std::ostream& stream, const std::tuple<>&) {
    stream << "{}";
    return true;
}

template <typename T, typename U>
inline bool pretty_print(std::ostream& stream, const std::pair<T, U>& value) {
    stream << "{";
    pretty_print(stream, value.first);
    stream << ", ";
    pretty_print(stream, value.second);
    stream << "}";
    return true;
}

template <typename T>
inline void pretty_print_stack(std::ostream& stream, T stack) {
    std::vector<typename T::value_type> vec;
    while (!stack.empty()) {
        vec.push_back(stack.top());
        stack.pop();
    }
    std::reverse(vec.begin(), vec.end());
    pretty_print(stream, vec);
}

template <typename T>
inline bool pretty_print(std::ostream& stream, const std::stack<T>& value) {
    pretty_print_stack(stream, value);
    return true;
}

template <typename T>
inline bool pretty_print(std::ostream& stream,
        const std::priority_queue<T>& value) {
    pretty_print_stack(stream, value);
    return true;
}

template <typename T>
inline void pretty_print_queue(std::ostream& stream, T queue) {
    std::vector<typename T::value_type> vec;
    while (!queue.empty()) {
        vec.push_back(queue.front());
        queue.pop();
    }
    pretty_print(stream, vec);
}

template <typename T>
inline bool pretty_print(std::ostream& stream, const std::queue<T>& value) {
    pretty_print_queue(stream, value);
    return true;
}

template <typename T>
inline void pretty_print_deque(std::ostream& stream, T queue) {
    std::vector<typename T::value_type> vec;
    while (!queue.empty()) {
        vec.push_back(queue.back());
        queue.pop_back();
    }
    reverse(vec.begin(), vec.end());
    pretty_print(stream, vec);
}

template <typename T>
inline bool pretty_print(std::ostream& stream, const std::deque<T>& value) {
   pretty_print_deque(stream, value);
    return true;
}

template <typename T>
inline typename std::enable_if<detail::is_iterable<T>::value, bool>::type
pretty_print(std::ostream& stream, const T& value) {
    using std::begin;
    using std::end;
    using std::size;

    const size_t sz = size(value);
    const size_t n = std::min((size_t) DBG_ITERABLE_LENGTH, sz);
    size_t i = 0;

    stream << "{";
    for (auto it = begin(value); i < n; ++it, ++i) {
        pretty_print(stream, *it);
        if (i != n - 1) {
            stream << ", ";
        }
    }
    if (sz > n) {
        stream << ", ... " << "(size: " << sz << ")";
    }
    stream << "}";
    return true;
}

template <typename T, typename... U>
struct last {
    using type = typename last<U...>::type;
};

template <typename T>
struct last<T> {
    using type = T;
};

template <typename... T>
using last_t = typename last<T...>::type;

class DebugOutput {
  public:
    using expr_t = const char*;

    DebugOutput(const char* filepath, int line, const char* function_name) {
        std::stringstream ss;
        ss << ansi(ANSI_DEBUG) << "[" << line << "] " << ansi(ANSI_RESET);
        location = ss.str();
    }

    template <typename... T>
    auto print(std::initializer_list<expr_t> exprs,
            std::initializer_list<std::string> types,
            T&&... values) -> last_t<T...> {
        if (exprs.size() != sizeof...(values)) {
            std::cerr << location << ansi(ANSI_WARN) <<
                "The number of arguments mismatch, " <<
                "please check unprotected comma" <<
                ansi(ANSI_RESET) << std::endl;
        }
        auto&& ret = print_impl(exprs.begin(), types.begin(),
            std::forward<T>(values)...);
        std::cerr << std::endl;
        return ret;
    }

  private:
    template <typename T>
    T&& print_impl(const expr_t* expr, const std::string* type, T&& value) {
        const T& ref = value;
        std::stringstream stream_value;
        const bool print_expr_and_type = pretty_print(stream_value, ref);

        std::stringstream output;
        output << location;
        if (print_expr_and_type) {
            output << ansi(ANSI_EXPRESSION) <<
                *expr << ansi(ANSI_RESET) << " = ";
        }
        output << ansi(ANSI_VALUE) << stream_value.str() << ansi(ANSI_RESET);
        if (print_expr_and_type) {
            output << " (" << ansi(ANSI_TYPE) <<
                *type << ansi(ANSI_RESET) << ")";
        }
        output << std::endl;
        std::cerr << output.str();

        return std::forward<T>(value);
    }

    template <typename T, typename... U>
    auto print_impl(const expr_t* exprs, const std::string* types, T&& value,
            U&&... rest) -> last_t<T, U...> {
        print_impl(exprs, types, std::forward<T>(value));
        return print_impl(exprs + 1, types + 1, std::forward<U>(rest)...);
    }

    const char* ansi(const char* code) const {
#ifdef DBG_NO_COLORIZED_OUTPUT
    return ANSI_EMPTY;
#else
    return code;
#endif
    }

    std::string location;

    static constexpr const char* const ANSI_EMPTY = "";
    static constexpr const char* const ANSI_DEBUG = "\x1b[02m";
    static constexpr const char* const ANSI_WARN = "\x1b[33m";
    static constexpr const char* const ANSI_EXPRESSION = "\x1b[36m";
    static constexpr const char* const ANSI_VALUE = "\x1b[01m";
    static constexpr const char* const ANSI_TYPE = "\x1b[32m";
    static constexpr const char* const ANSI_RESET = "\x1b[0m";
};

}  // namespace dbg

#define DBG_IDENTITY(x) x
#define DBG_CALL(fn, args) DBG_IDENTITY(fn args)

#define DBG_CAT_IMPL(_1, _2) _1##_2
#define DBG_CAT(_1, _2) DBG_CAT_IMPL(_1, _2)

#define DBG_16TH_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, \
                      _14, _15, _16, ...) _16

#define DBG_16TH(args) DBG_CALL(DBG_16TH_IMPL, args)
#define DBG_NARG(...) \
  DBG_16TH((__VA_ARGS__, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))

// DBG_VARIADIC_CALL(fn, data, e1, e2, ...) => fn_N(data, (e1, e2, ...))
#define DBG_VARIADIC_CALL(fn, data, ...) \
  DBG_CAT(fn##_, DBG_NARG(__VA_ARGS__))(data, (__VA_ARGS__))

// (e1, e2, e3, ...) => e1
#define DBG_HEAD_IMPL(_1, ...) _1
#define DBG_HEAD(args) DBG_CALL(DBG_HEAD_IMPL, args)

// (e1, e2, e3, ...) => (e2, e3, ...)
#define DBG_TAIL_IMPL(_1, ...) (__VA_ARGS__)
#define DBG_TAIL(args) DBG_CALL(DBG_TAIL_IMPL, args)

#define DBG_MAP_1(fn, args) DBG_CALL(fn, args)
#define DBG_MAP_2(fn, args) fn(DBG_HEAD(args)), DBG_MAP_1(fn, DBG_TAIL(args))
#define DBG_MAP_3(fn, args) fn(DBG_HEAD(args)), DBG_MAP_2(fn, DBG_TAIL(args))
#define DBG_MAP_4(fn, args) fn(DBG_HEAD(args)), DBG_MAP_3(fn, DBG_TAIL(args))
#define DBG_MAP_5(fn, args) fn(DBG_HEAD(args)), DBG_MAP_4(fn, DBG_TAIL(args))
#define DBG_MAP_6(fn, args) fn(DBG_HEAD(args)), DBG_MAP_5(fn, DBG_TAIL(args))
#define DBG_MAP_7(fn, args) fn(DBG_HEAD(args)), DBG_MAP_6(fn, DBG_TAIL(args))
#define DBG_MAP_8(fn, args) fn(DBG_HEAD(args)), DBG_MAP_7(fn, DBG_TAIL(args))
#define DBG_MAP_9(fn, args) fn(DBG_HEAD(args)), DBG_MAP_8(fn, DBG_TAIL(args))
#define DBG_MAP_10(fn, args) fn(DBG_HEAD(args)), DBG_MAP_9(fn, DBG_TAIL(args))
#define DBG_MAP_11(fn, args) fn(DBG_HEAD(args)), DBG_MAP_10(fn, DBG_TAIL(args))
#define DBG_MAP_12(fn, args) fn(DBG_HEAD(args)), DBG_MAP_11(fn, DBG_TAIL(args))
#define DBG_MAP_13(fn, args) fn(DBG_HEAD(args)), DBG_MAP_12(fn, DBG_TAIL(args))
#define DBG_MAP_14(fn, args) fn(DBG_HEAD(args)), DBG_MAP_13(fn, DBG_TAIL(args))
#define DBG_MAP_15(fn, args) fn(DBG_HEAD(args)), DBG_MAP_14(fn, DBG_TAIL(args))
#define DBG_MAP_16(fn, args) fn(DBG_HEAD(args)), DBG_MAP_15(fn, DBG_TAIL(args))

// DBG_MAP(fn, e1, e2, e3, ...) => fn(e1), fn(e2), fn(e3), ...
#define DBG_MAP(fn, ...) DBG_VARIADIC_CALL(DBG_MAP, fn, __VA_ARGS__)

#define DBG_STRINGIFY_IMPL(x) #x
#define DBG_STRINGIFY(x) DBG_STRINGIFY_IMPL(x)

#define DBG_TYPE_NAME(x) dbg::type_name<decltype(x)>()

#define dbg(...)                                    \
  dbg::DebugOutput(__FILE__, __LINE__, __func__)    \
      .print({DBG_MAP(DBG_STRINGIFY, __VA_ARGS__)}, \
             {DBG_MAP(DBG_TYPE_NAME, __VA_ARGS__)}, __VA_ARGS__)
