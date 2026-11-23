#pragma once
#include <iosfwd>

template<typename T>
concept Streameble = requires(std::ostream& ostream, std::remove_reference_t<T>& obj)
{
  ostream << obj;
};

template<typename T>
concept Formatabled = requires(const std::remove_reference_t<T>& obj)
{
  std::format("{}", obj);
};

template<typename T>
concept Loggable = Streameble<T> || Formatabled<T>;