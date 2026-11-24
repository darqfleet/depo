#pragma once
template <typename T>
concept Streameble = requires(std::ostream& ostream, std::remove_reference_t<T>& obj) { ostream << obj; };

template <typename T>
concept Formatable = requires(const std::remove_reference_t<T>& obj) { std::format("{}", obj); };

template <typename T>
concept Loggable = Streameble<T> || Formatable<T>;
