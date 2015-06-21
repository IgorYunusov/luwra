/* Luwra
 * Minimal-overhead Lua wrapper for C++
 *
 * Copyright (C) 2015, Ole Krüger <ole@vprsm.de>
 */

#ifndef LUWRA_FUNCTIONS_H_
#define LUWRA_FUNCTIONS_H_

#include "common.hpp"
#include "types.hpp"
#include "stack.hpp"

LUWRA_NS_BEGIN

namespace internal {
	template <typename T>
	struct FunctionWrapper {
		static_assert(
			sizeof(T) == -1,
			"The FunctionWrapper template expects a function signature as parameter"
		);
	};

	template <>
	struct FunctionWrapper<void()> {
		template <void(*function_pointer)()> static
		int invoke(State*) {
			function_pointer();
			return 0;
		}
	};

	template <typename R>
	struct FunctionWrapper<R()> {
		template <R(*function_pointer)()> static
		int invoke(State* state) {
			return push(state, function_pointer());
		}
	};

	template <typename... A>
	struct FunctionWrapper<void(A...)> {
		template <void (*function_pointer)(A...)> static
		int invoke(State* state) {
			apply(state, function_pointer);
			return 0;
		}
	};

	template <typename R, typename... A>
	struct FunctionWrapper<R(A...)> {
		template <R (*function_pointer)(A...)> static
		int invoke(State* state) {
			return push(
				state,
				apply(state, function_pointer)
			);
		}
	};
}

/**
 * Assuming its parameters can be retrieved from the Lua stack, ordinary functions can be wrapped
 * using the `wrap_function` instance in order to produce a C function which can be used by the
 * Lua VM.
 *
 * Assuming your function has the following signature:
 *
 *   R my_fun(A0, A1 ... An);
 *
 * Generate a Lua-compatible like so:
 *
 *   CFunction wrapped_fun = wrap_function<R(A0, A1 ... An), my_fun>;
 */
template <
	typename S,
	S* function_pointer
>
constexpr CFunction wrap_function =
	&internal::FunctionWrapper<S>::template invoke<function_pointer>;

LUWRA_NS_END

#endif
