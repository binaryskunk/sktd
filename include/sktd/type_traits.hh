// Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
// See end of file for extended copyright information.

#ifndef SKTD_TYPE_TRAITS_HH
#define SKTD_TYPE_TRAITS_HH

namespace sktd {

template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> {
  using type = T;
};

template <bool B, class T = void>
using enable_if_t = typename enable_if<B, T>::type;

template <class T>
struct remove_reference {
  using type = T;
};

template <class T>
struct remove_reference<T&> {
  using type = T;
};

template <class T>
struct remove_reference<T&&> {
  using type = T;
};

template <class T>
using remove_reference_t = typename remove_reference<T>::type;

template <class T>
struct remove_cv {
  using type = T;
};

template <class T>
struct remove_cv<const T> {
  using type = T;
};

template <class T>
struct remove_cv<volatile T> {
  using type = T;
};

template <class T>
struct remove_cv<const volatile T> {
  using type = T;
};

template <class T>
using remove_cv_t = typename remove_cv<T>::type;

namespace {

template <class T, T v>
struct integral_constant {
  static constexpr T value = v;

  using value_type = T;
  using type = integral_constant;

  constexpr operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; }
};

}  // namespace

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template <class...>
using void_t = void;

template <class T>
struct add_rvalue_reference {
  using type = T&&;
};

template <class T>
struct add_rvalue_reference<T&> {
  using type = T&;
};

template <class T>
struct add_rvalue_reference<T const> {
  using type = T const&&;
};

template <class T>
struct add_rvalue_reference<T const&> {
  using type = T const&;
};

template <class T>
typename add_rvalue_reference<T>::type declval() noexcept;

template <class T, typename = void>
struct is_default_constructible : false_type {};

template <class T>
struct is_default_constructible<T, void_t<decltype(T())>> : true_type {};

template <class T>
inline constexpr bool is_default_constructible_v =
    is_default_constructible<T>::value;

template <class T, typename = void>
struct is_copy_constructible : false_type {};

template <class T>
struct is_copy_constructible<T, void_t<decltype(T(declval<const T&>()))>>
    : true_type {};

template <class T>
inline constexpr bool is_copy_constructible_v = is_copy_constructible<T>::value;

template <class T, typename = void>
struct is_move_constructible : false_type {};

template <class T>
struct is_move_constructible<T, void_t<decltype(T(declval<T&&>()))>>
    : true_type {};

template <class T>
inline constexpr bool is_move_constructible_v = is_move_constructible<T>::value;

template <class T, class U>
struct is_same : false_type {};

template <class T>
struct is_same<T, T> : true_type {};

template <class T, class U>
inline constexpr bool is_same_v = is_same<T, U>::value;

template <class T>
struct decay {
  using type = remove_cv_t<remove_reference_t<T>>;
};

template <class T>
using decay_t = typename decay<T>::type;

namespace internal {

template <class Base>
auto is_base_of_test_func(Base*) -> true_type;

template <class Base>
auto is_base_of_test_func(...) -> false_type;

}  // namespace internal

template <class Base, class Derived>
struct is_base_of {
  template <class T>
  static auto test(T*) -> decltype(internal::is_base_of_test_func<Base>(
      static_cast<T*>(nullptr)));

  static auto test(...) -> false_type;

  using type = decltype(test(static_cast<Derived*>(nullptr)));
  static constexpr bool value = type::value;
};

template <class Base, class Derived>
inline constexpr bool is_base_of_v = is_base_of<Base, Derived>::value;

namespace {

template <class From, class To>
struct is_convertible_helper {
  template <class F, class T,
            typename = decltype(declval<F>(), static_cast<T>(declval<F>()))>
  static auto test(int) -> true_type;

  template <class, class>
  static auto test(...) -> false_type;

  using type = decltype(test<From, To>(0));
  static constexpr bool value = type::value;
};

}  // namespace

template <class From, class To>
struct is_convertible : is_convertible_helper<From, To>::type {};

template <class From, class To>
inline constexpr bool is_convertible_v = is_convertible<From, To>::value;

template <class Derived, class Base>
concept derived_from =
    is_base_of_v<Base, Derived> &&
    is_convertible_v<const volatile Derived*, const volatile Base*>;

template <class T>
struct remove_cvref {
  using type = remove_cv_t<remove_reference_t<T>>;
};

template <class T>
using remove_cvref_t = typename remove_cvref<T>::type;

}  // namespace sktd

#endif

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
