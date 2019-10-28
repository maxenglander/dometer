#pragma once

/**
 * @see https://stackoverflow.com/a/28998020/614660
 */
namespace Dometer::Util {
	template <size_t I>
	struct TupleHelperImpl
	{
		template <typename T, typename F>
		static constexpr decltype(auto) applyAt(T& tup, size_t idx, F fun)
		{
			if (idx == I - 1) return fun(std::get<I - 1>(tup));
			else return TupleHelperImpl<I - 1>::applyAt(tup, idx, fun);
		}
	};
	 
	template <>
	struct TupleHelperImpl<0>
	{
		template <typename T, typename F>
		static constexpr decltype(auto) applyAt(T& tup, size_t idx, F fun) { assert(false); }
	};
	 
    struct TupleHelper {
        template <typename F, typename... Ts>
        constexpr decltype(auto) applyAt(std::tuple<Ts...> const& tup, size_t idx, F fun)
        {
            return TupleHelperImpl<sizeof...(Ts)>::applyAt(tup, idx, fun);
        }
         
        template <typename F, typename... Ts>
        constexpr decltype(auto) applyAt(std::tuple<Ts...>& tup, size_t idx, F fun)
        {
            return TupleHelperImpl<sizeof...(Ts)>::applyAt(tup, idx, fun);
        }
    };
}
