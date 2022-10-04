#pragma once

namespace pcws {

// Quotient.

template<typename T>
auto ceiled_quotient(T dividend, T divisor) -> T;
template<typename T>
auto floored_quotient(T dividend, T divisor) -> T;
template<typename T>
auto rounded_quotient(T dividend, T divisor) -> T;
template<typename T>
auto truncated_quotient(T dividend, T divisor) -> T;

// Nearest multiple.

template<typename T>
auto ceiled(T i, T factor) -> T {
	return ceiled_quotient(i, factor) * factor;
}

//

template<typename T>
auto ceiled_quotient(T dividend, T divisor) -> T {
	if(dividend >= 0 == divisor>= 0) {
		return (dividend + divisor - 1) / divisor;
	} else {
		return dividend / divisor;
	}
}

template<typename T>
auto floored_quotient(T dividend, T divisor) -> T {
	if(dividend >= 0 == divisor >= 0) {
		return dividend / divisor;
	} else {
		return (dividend - divisor + 1) / divisor;
	}
}

template<typename T>
auto rounded_quotient(T dividend, T divisor) -> T {
	if(dividend >= 0 == divisor >= 0) {
		return (dividend + divisor / 2) / divisor;
	} else {
		return (dividend - (divisor - 1) / 2) / divisor;
	}
}

template<typename T>
auto truncated_quotient(T dividend, T divisor) -> T {
	return dividend / divisor;
}

}
