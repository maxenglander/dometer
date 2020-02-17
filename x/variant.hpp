#pragma once

#include "mpark/variant.hpp"

namespace std::x {
    using mpark::get;
    using mpark::get_if;
    using mpark::in_place;
    using mpark::in_place_t;
    using mpark::in_place_index;
    using mpark::in_place_index_t;
    using mpark::in_place_type;
    using mpark::in_place_type_t;
    using mpark::variant;
    using mpark::visit;

	template <class... Fs>
	struct Overloaded;

	template <class F1>
	struct Overloaded<F1> : F1 {
		using F1::operator();

		Overloaded(F1&& head) : F1(std::forward<F1>(head)) {}
	};

	template <class F1, class... Fs>
	struct Overloaded<F1, Fs...> : F1, Overloaded<Fs...> {
		using F1::operator();
		using Overloaded<Fs...>::operator();

		Overloaded(F1&& head, Fs&&... rest)
			: F1(std::forward<F1>(head)),
			Overloaded<Fs...>(std::forward<Fs>(rest)...) {}
	};

	template <class... Fs>
	Overloaded<Fs...> overloaded(Fs&&... fs) {
		return Overloaded<Fs...>(std::forward<Fs>(fs)...);
	}
}
