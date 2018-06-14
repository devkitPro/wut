#pragma once
#include "utils.h"
#include "type_traits.h"
#include <utility>

template<typename Type>
class be_val
{
public:
   static_assert(!std::is_array<Type>::value,
                 "be_val invalid type: array");

   static_assert(!std::is_pointer<Type>::value,
                 "be_val invalid type: pointer");

   static_assert(sizeof(Type) == 1 || sizeof(Type) == 2 || sizeof(Type) == 4 || sizeof(Type) == 8,
                 "be_val invalid type size");

   using value_type = Type;

   be_val() = default;

   be_val(const value_type &value) :
      mStorage(byte_swap(value))
   {
   }

   value_type value() const
   {
      return byte_swap(mStorage);
   }

   void setValue(value_type value)
   {
      mStorage = byte_swap(value);
   }

   operator value_type() const
   {
      return value();
   }

   template<typename T = Type,
            typename = typename std::enable_if<std::is_convertible<T, bool>::value ||
                                               std::is_constructible<bool, T>::value
                                              >::type>
   explicit operator bool() const
   {
      return static_cast<bool>(value());
   }

   template<typename OtherType,
            typename = typename std::enable_if<std::is_convertible<Type, OtherType>::value ||
                                               std::is_constructible<OtherType, Type>::value ||
                                               std::is_convertible<Type, typename safe_underlying_type<OtherType>::type>::value
                                              >::type>
   explicit operator OtherType() const
   {
      return static_cast<OtherType>(value());
   }

   template<typename OtherType,
            typename = typename std::enable_if<std::is_constructible<value_type, const OtherType &>::value>::type>
   be_val & operator =(const OtherType &other)
   {
      setValue(value_type { other });
      return *this;
   }

   template<typename OtherType,
            typename = typename std::enable_if<std::is_constructible<value_type, const OtherType &>::value>::type>
   be_val & operator =(OtherType &&other)
   {
      setValue(value_type { std::forward<OtherType>(other) });
      return *this;
   }

   template<typename OtherType,
            typename = typename std::enable_if<std::is_constructible<value_type, const OtherType &>::value>::type>
   be_val & operator =(const be_val<OtherType> &other)
   {
      setValue(value_type { other.value() });
      return *this;
   }

   template<typename OtherType,
            typename = typename std::enable_if<std::is_constructible<value_type, const OtherType &>::value>::type>
   be_val & operator =(be_val<OtherType> &&other)
   {
      setValue(value_type { other.value() });
      return *this;
   }

   template<typename OtherType, typename K = value_type>
   auto operator ==(const OtherType &other)
      -> decltype(std::declval<const K>().operator ==(std::declval<const OtherType>())) const
   {
      return value() == other;
   }

   template<typename OtherType, typename K = value_type>
   auto operator !=(const OtherType &other)
      -> decltype(std::declval<const K>().operator !=(std::declval<const OtherType>())) const
   {
      return value() != other;
   }

   template<typename OtherType, typename K = value_type>
   auto operator >=(const OtherType &other)
      -> decltype(std::declval<const K>().operator >=(std::declval<const OtherType>())) const
   {
      return value() >= other;
   }

   template<typename OtherType, typename K = value_type>
   auto operator <=(const OtherType &other)
      -> decltype(std::declval<const K>().operator <=(std::declval<const OtherType>())) const
   {
      return value() <= other;
   }

   template<typename OtherType, typename K = value_type>
   auto operator >(const OtherType &other)
      -> decltype(std::declval<const K>().operator >(std::declval<const OtherType>())) const
   {
      return value() > other;
   }

   template<typename OtherType, typename K = value_type>
   auto operator <(const OtherType &other)
      -> decltype(std::declval<const K>().operator <(std::declval<const OtherType>())) const
   {
      return value() < other;
   }

   template<typename K = value_type>
   auto operator +()
      ->  decltype(std::declval<const K>(). operator+()) const
   {
      return +value();
   }

   template<typename K = value_type>
   auto operator -()
      -> decltype(std::declval<const K>(). operator-()) const
   {
      return -value();
   }

   template<typename OtherType, typename K = value_type>
   auto operator +(const OtherType &other)
      -> decltype(std::declval<const K>().operator +(std::declval<const OtherType>())) const
   {
      return value() + other;
   }

   template<typename OtherType, typename K = value_type>
   auto operator -(const OtherType &other)
      -> decltype(std::declval<const K>().operator -(std::declval<const OtherType>())) const
   {
      return value() - other;
   }

   template<typename OtherType, typename K = value_type>
   auto operator *(const OtherType &other)
      -> decltype(std::declval<const K>().operator *(std::declval<const OtherType>())) const
   {
      return value() * other;
   }

   template<typename OtherType, typename K = value_type>
   auto operator /(const OtherType &other)
      -> decltype(std::declval<const K>().operator /(std::declval<const OtherType>())) const
   {
      return value() / other;
   }

   template<typename OtherType, typename K = value_type>
   auto operator %(const OtherType &other)
      -> decltype(std::declval<const K>().operator %(std::declval<const OtherType>())) const
   {
      return value() % other;
   }

   template<typename OtherType, typename K = value_type>
   auto operator |(const OtherType &other)
      -> decltype(std::declval<const K>().operator |(std::declval<const OtherType>())) const
   {
      return value() | other;
   }

   template<typename OtherType, typename K = value_type>
   auto operator &(const OtherType &other)
      -> decltype(std::declval<const K>().operator &(std::declval<const OtherType>())) const
   {
      return value() & other;
   }

   template<typename OtherType, typename K = value_type>
   auto operator ^(const OtherType &other)
      -> decltype(std::declval<const K>().operator ^(std::declval<const OtherType>())) const
   {
      return value() ^ other;
   }

   template<typename OtherType, typename K = value_type>
   auto operator <<(const OtherType &other)
      -> decltype(std::declval<const K>().operator <<(std::declval<const OtherType>())) const
   {
      return value() << other;
   }

   template<typename OtherType, typename K = value_type>
   auto operator >>(const OtherType &other)
      -> decltype(std::declval<const K>().operator >>(std::declval<const OtherType>())) const
   {
      return value() >> other;
   }

   template<typename OtherType,
            typename = decltype(std::declval<const value_type>() + std::declval<const OtherType>())>
   be_val &operator +=(const OtherType &other)
   {
      *this = value() + other;
      return *this;
   }

   template<typename OtherType,
            typename = decltype(std::declval<const value_type>() - std::declval<const OtherType>())>
   be_val &operator -=(const OtherType &other)
   {
      *this = value() - other;
      return *this;
   }

   template<typename OtherType,
            typename = decltype(std::declval<const value_type>() * std::declval<const OtherType>())>
   be_val &operator *=(const OtherType &other)
   {
      *this = value() * other;
      return *this;
   }

   template<typename OtherType,
            typename = decltype(std::declval<const value_type>() / std::declval<const OtherType>())>
   be_val &operator /=(const OtherType &other)
   {
      *this = value() / other;
      return *this;
   }

   template<typename OtherType,
            typename = decltype(std::declval<const value_type>() % std::declval<const OtherType>())>
   be_val &operator %=(const OtherType &other)
   {
      *this = value() % other;
      return *this;
   }

   template<typename OtherType,
            typename = decltype(std::declval<const value_type>() | std::declval<const OtherType>())>
   be_val &operator |=(const OtherType &other)
   {
      *this = static_cast<Type>(value() | other);
      return *this;
   }

   template<typename OtherType,
            typename = decltype(std::declval<const value_type>() & std::declval<const OtherType>())>
   be_val &operator &=(const OtherType &other)
   {
      *this = static_cast<Type>(value() & other);
      return *this;
   }

   template<typename OtherType,
            typename = decltype(std::declval<const value_type>() ^ std::declval<const OtherType>())>
   be_val &operator ^=(const OtherType &other)
   {
      *this = static_cast<Type>(value() ^ other);
      return *this;
   }

   template<typename OtherType,
            typename = decltype(std::declval<const value_type>() << std::declval<const OtherType>())>
   be_val &operator <<=(const OtherType &other)
   {
      *this = value() << other;
      return *this;
   }

   template<typename OtherType,
            typename = decltype(std::declval<const value_type>() >> std::declval<const OtherType>())>
   be_val &operator >>=(const OtherType &other)
   {
      *this = value() >> other;
      return *this;
   }

   template<typename T = Type,
            typename = decltype(std::declval<const T>() + 1)>
   be_val &operator ++()
   {
      setValue(value() + 1);
      return *this;
   }

   template<typename T = Type,
            typename = decltype(std::declval<const T>() + 1)>
   be_val operator ++(int)
   {
      auto before = *this;
      setValue(value() + 1);
      return before;
   }

   template<typename T = Type,
            typename = decltype(std::declval<const T>() - 1)>
   be_val &operator --()
   {
      setValue(value() - 1);
      return *this;
   }

   template<typename T = Type,
            typename = decltype(std::declval<const T>() - 1)>
   be_val operator --(int)
   {
      auto before = *this;
      setValue(value() - 1);
      return before;
   }

   template<typename IndexType,
            typename K = value_type>
   auto operator [](const IndexType &index)
      -> decltype(std::declval<K>().operator [](std::declval<IndexType>()))
   {
      return value().operator [](index);
   }

   template<typename K = value_type>
   auto operator ->()
      -> decltype(std::declval<K>().operator ->())
   {
      return value().operator ->();
   }

   template<typename K = value_type>
   auto operator ->() const
      -> decltype(std::declval<const K>().operator ->())
   {
      return value().operator ->();
   }

   template<typename K = value_type>
   auto operator *()
      -> decltype(std::declval<K>().operator *())
   {
      return value().operator *();
   }

   template<typename K = value_type>
   auto operator *() const
      -> decltype(std::declval<const K>().operator *())
   {
      return value().operator ->();
   }

private:
   value_type mStorage;
};
