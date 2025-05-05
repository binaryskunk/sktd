// Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
// See end of file for extended copyright information.

#ifndef INCLUDE_SKTD_SPAN_HH_
#define INCLUDE_SKTD_SPAN_HH_

#include <sktd/type_aliases.hh>

namespace sktd {

template <class T>
class span final {
 private:
  T* _data;
  u64 _size;

 public:
  constexpr span() noexcept : _data{nullptr}, _size{0} {}

  constexpr span(T* ptr, u64 count) : _data{ptr}, _size{count} {}

  constexpr span(T* first, const T* last)
      : _data{first}, _size{static_cast<u64>(last - first)} {}

  template <u64 N>
  constexpr explicit span(T (&arr)[N]) noexcept : _data{arr}, _size{N} {}

  constexpr auto at(u64 idx) const -> T& {
    const bool index_greater_than_span_size = idx > this->_size;
    const u64 fitted_idx = index_greater_than_span_size ? this->_size : idx;

    return this->_data[fitted_idx];
  }

  constexpr auto operator[](u64 idx) const -> T& { return this->at(idx); }

  constexpr auto front() const -> T& { return this->_data[0]; }

  constexpr auto back() const -> T& { return this->_data[this->_size - 1]; }

  constexpr auto data() const noexcept -> T* { return this->_data; }

  constexpr auto size() const noexcept -> u64 { return this->_size; }

  constexpr auto bytes() const noexcept -> u64 {
    return this->_size * sizeof(T);
  }

  constexpr auto empty() const noexcept -> bool { return this->_size == 0; }

  template <u64 count>
  constexpr auto first() const -> span<T> {
    const bool count_greater_than_size = count > this->_size;
    const u64 fitted_count = count_greater_than_size ? this->_size : count;

    return {this->_data, fitted_count};
  }

  constexpr auto first(u64 count) const -> span<T> {
    const bool count_greater_than_size = count > this->_size;
    const u64 fitted_count = count_greater_than_size ? this->_size : count;

    return {this->_data, fitted_count};
  }

  template <u64 count>
  constexpr auto last() const -> span<T> {
    const bool count_greater_than_size = count > this->_size;
    const u64 fitted_count = count_greater_than_size ? this->_size : count;

    return {this->_data + (this->_size - fitted_count), fitted_count};
  }

  constexpr auto last(u64 count) const -> span<T> {
    const bool count_greater_than_size = count > this->_size;
    const u64 fitted_count = count_greater_than_size ? this->_size : count;

    return {this->_data + (this->_size - fitted_count), fitted_count};
  }

  constexpr auto begin() const noexcept -> T* { return this->_data; }

  constexpr auto end() const noexcept -> T* {
    return this->_data + this->_size;
  }
};

}  // namespace sktd

#endif  // INCLUDE_SKTD_SPAN_HH_

/*
 * Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
 *
 * This file is part of sktd and is licensed under the
 * BinarySkunk's Public License (BSPL), version 1, as published by
 * Lavínia "BinarySkunk" Rodrigues.
 *
 * You should have received a copy of the BSPL along with this program.
 * If not, see <https://kernel32.xyz/licenses/bspl/v1/>.
 */
