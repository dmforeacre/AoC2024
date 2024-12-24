// Memoizer function from https://stackoverflow.com/a/60903898

#include <map>
#include <tuple>
#include <functional>
#include <mutex>

template<typename Function, typename... Args>
auto invoke_memoized(Function function, Args... args)
{
    using key_type   = std::tuple<Args...>;
    using value_type = std::invoke_result_t<Function, Args...>;

    static_assert(! std::is_same_v<Function, std::function<value_type(Args...)>>,
        "cannot memoize on std::function (use a lambda instead)");

    static_assert(! std::is_same_v<Function, value_type(*)(Args...)>,
        "cannot memoize on function pointer (use a lambda instead)");

    static std::mutex mutex;
    static std::map<key_type, value_type> cache;

    auto key  = std::tuple(args...);
    auto lock = std::lock_guard<std::mutex>(mutex);

    if (cache.count(key))
    {
        return cache[key];
    }
    return cache[key] = std::apply(function, key);
}