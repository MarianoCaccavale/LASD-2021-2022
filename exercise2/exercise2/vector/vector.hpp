
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public LinearContainer<Data>,
               virtual public PreOrderMappableContainer<Data>,
               virtual public PostOrderMappableContainer<Data>,
               virtual public PreOrderFoldableContainer<Data>,
               virtual public PostOrderFoldableContainer<Data> {
                // Must extend LinearContainer<Data>,
                //             PreOrderMappableContainer<Data>,
                //             PostOrderMappableContainer<Data>,
                //             PreOrderFoldableContainer<Data>,
                //             PostOrderFoldableContainer<Data>

private:

  // ...

protected:

  using Container::size;

  Data* Elementi = nullptr;

  // ...

public:

  // Default constructor
  Vector() = default;

  /* ************************************************************************ */

  // Specific constructors
  Vector(const unsigned long); // A vector with a given initial dimension
  Vector(const LinearContainer<Data>&); // A vector obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector&);

  // Move constructor
  Vector(Vector&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  Vector& operator=(const Vector& elem);

  // Move assignment
  Vector& operator=(Vector&& elem) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector&) const noexcept;
  inline bool operator!=(const Vector&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void Resize(const unsigned long); // Resize the vector to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  Data& Front() const override;
  Data& Back() const override;

  Data& operator[](const unsigned long) const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;
  void Map(MapFunctor, void*) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from PreOrderMappableContainer)

  void MapPreOrder(const MapFunctor, void*) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from PostOrderMappableContainer)

  void MapPostOrder(const MapFunctor, void*) override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;
  void Fold(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from PreOrderFoldableContainer)

  void FoldPreOrder(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from PostOrderFoldableContainer)

  void FoldPostOrder(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
