//
//  SmartPointer.hpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 20/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#ifndef SmartPointer_hpp
#define SmartPointer_hpp

template <class T>
class PointerStorage
{
public:
  typedef T* StoredType;
  typedef T* PointerType;
  typedef T& ReferenceType;
  
private:
  StoredType pointee;
  
public:
  PointerStorage()
  :
  pointee(Default())
  {
  }
  
  PointerStorage(const StoredType& p)
  :
  pointee(p)
  {
  }
  
  PointerType operator->() const
  {
    return pointee;
  }
  
  ReferenceType operator*() const
  {
    return *pointee;
  }
  
  friend inline PointerType GetImpl(const PointerStorage& sp)
  {
    return sp.pointee;
  }
  
  friend inline const StoredType& GetImplRef(const PointerStorage& sp)
  {
    return sp.pointee;
  }
  
  friend inline StoredType& GetImplRef(PointerStorage& sp)
  {
    return sp.pointee;
  }
  
protected:
  
  void Destroy()
  {
    delete pointee;
  }
  
  constexpr static StoredType Default()
  {
    return nullptr;
  }
};



template <class P>
class RefCounted
{
private:
  unsigned int* pCount;
protected:
  RefCounted()
  :
  pCount(new unsigned int(1))
  {
  }
  
  P Clone(const P& val)
  {
    ++*pCount;
    return val;
  }
  
  bool Release(const P&)
  {
    if (!--*pCount) {
      delete pCount;
      return true;
    }
    return false;
  }
  
  enum { destructiveCopy = false }; // see below
};

template <class P>
class SingleOwned
{
private:
protected:
  SingleOwned()
  {
  }
  
  void release()
  {
    
  }
};

template <
  typename T,
  template <class> class OwnershipPolicy,
//  class ConversionPolicy = DisallowConversion,
//  template <class> class CheckingPolicy = AssertCheck,
  template <class> class StoragePolicy = PointerStorage
>
class SmartPointer :
  public StoragePolicy<T>,
  public OwnershipPolicy<typename StoragePolicy<T>::StoredType>
//  public CheckingPolicy<typename StoragePolicy<T>::StoredType>,
//  public ConversionPolicy
{
  
public:
  
  ~SmartPointer()
  {
    if (OwnershipPolicy<T>::Release(GetImpl(*static_cast<StoragePolicy<T>*>(this))))
    {
      StoragePolicy<T>::Destroy();
    }
  }
};

#endif /* SmartPointer_hpp */
