#pragma once

#include <functional>

/**
 * @see https://stackoverflow.com/a/28998020/614660
 */
namespace dometer::util {
    template <std::size_t... S>
    struct sequence {};

    template <std::size_t N, std::size_t... S>
    struct index_sequence : index_sequence<N - 1, N - 1, S...> {};

    template <std::size_t... S>
    struct index_sequence<0, S...> {
        typedef sequence<S...> type;
    };

	template <size_t N>
	struct tuple_helper_impl
	{
		template <typename F, typename T>
		static void visit_at(T& tup, size_t idx, F fun)
		{
            if (idx == N - 1)
                fun(std::get<N - 1>(tup));
			else
                tuple_helper_impl<N - 1>::visit_at(tup, idx, fun);
		}

        template <template <typename ...> class Tup1,
                  template <typename ...> class Tup2,
                  typename ...A, typename ...B,
                  std::size_t ...S>
        static auto zip(Tup1<A...> tup1, Tup2<B...> tup2, sequence<S...> s) ->
                decltype(std::make_tuple(std::make_pair(std::get<S>(tup1), std::get<S>(tup2))...)) {
            return std::make_tuple(std::make_pair(std::get<S>(tup1), std::get<S>(tup2))...);
        }
	};
	 
	template <>
	struct tuple_helper_impl<0>
	{
		template <typename F, typename T>
		static void visit_at(T& tup, size_t idx, F fun) {
            assert(false);
        }
	};
	 
    struct tuple_helper {
        template <typename F, typename... Ts>
        static void visit_at(std::tuple<Ts...> const& tup, size_t idx, F fun)
        {
            tuple_helper_impl<sizeof...(Ts)>::visit_at(tup, idx, fun);
        }
         
        template <typename F, typename... Ts>
        static void visit_at(std::tuple<Ts...>& tup, size_t idx, F fun)
        {
            tuple_helper_impl<sizeof...(Ts)>::visit_at(tup, idx, fun);
        }

        template <template <typename ...> class Tup1,
                  template <typename ...> class Tup2,
                  typename... A, typename... B>
        static auto zip(Tup1<A...> tup1, Tup2<B...> tup2) ->
                decltype(tuple_helper_impl<sizeof...(A)>::zip(tup1, tup2,
                             typename index_sequence<sizeof...(A)>::type())) {
            static_assert(sizeof...(A) == sizeof...(B));
            return tuple_helper_impl<sizeof...(A)>::zip(tup1, tup2,
                       typename index_sequence<sizeof...(A)>::type());
        }
    };
}
