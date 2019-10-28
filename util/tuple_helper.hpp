#pragma once

#include <functional>

/**
 * @see https://stackoverflow.com/a/28998020/614660
 */
namespace Dometer::Util {
    template <std::size_t... S>
    struct Sequence {};

    template <std::size_t N, std::size_t... S>
    struct IndexSequence : IndexSequence<N - 1, N - 1, S...> {};

    template <std::size_t... S>
    struct IndexSequence<0, S...> {
        typedef Sequence<S...> type;
    };

	template <size_t N>
	struct TupleHelperImpl
	{
		template <typename F, typename T>
		static void visitAt(T& tup, size_t idx, F fun)
		{
            if (idx == N - 1)
                fun(std::get<N - 1>(tup));
			else
                TupleHelperImpl<N - 1>::visitAt(tup, idx, fun);
		}

        template <template <typename ...> class Tup1,
                  template <typename ...> class Tup2,
                  typename ...A, typename ...B,
                  std::size_t ...S>
        static auto zip(Tup1<A...> tup1, Tup2<B...> tup2, Sequence<S...> s) ->
                decltype(std::make_tuple(std::make_pair(std::get<S>(tup1), std::get<S>(tup2))...)) {
            return std::make_tuple(std::make_pair(std::get<S>(tup1), std::get<S>(tup2))...);
        }
	};
	 
	template <>
	struct TupleHelperImpl<0>
	{
		template <typename F, typename T>
		static void visitAt(T& tup, size_t idx, F fun) {
            assert(false);
        }
	};
	 
    struct TupleHelper {
        template <typename F, typename... Ts>
        static void visitAt(std::tuple<Ts...> const& tup, size_t idx, F fun)
        {
            TupleHelperImpl<sizeof...(Ts)>::visitAt(tup, idx, fun);
        }
         
        template <typename F, typename... Ts>
        static void visitAt(std::tuple<Ts...>& tup, size_t idx, F fun)
        {
            TupleHelperImpl<sizeof...(Ts)>::visitAt(tup, idx, fun);
        }

        template <template <typename ...> class Tup1,
                  template <typename ...> class Tup2,
                  typename... A, typename... B>
        static auto zip(Tup1<A...> tup1, Tup2<B...> tup2) ->
                decltype(TupleHelperImpl<sizeof...(A)>::zip(tup1, tup2,
                             typename IndexSequence<sizeof...(A)>::type())) {
            static_assert(sizeof...(A) == sizeof...(B));
            return TupleHelperImpl<sizeof...(A)>::zip(tup1, tup2,
                       typename IndexSequence<sizeof...(A)>::type());
        }
    };
}
