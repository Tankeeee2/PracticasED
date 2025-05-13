/**
 * @file hash_table_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once

#include <cassert>

#include <hash_table.hpp>
#include <hash_table_iterator.hpp>

template <class K, class V>
HashTable<K, V>::HashTable(size_t m, const Key_to_uint64_t &key_to_int,
                           OACollisionResolution::Ref hash) {
  assert(m == hash->m());
  // TODO
  table_.resize(m);
  hash_ = hash;
  key_to_int_ = key_to_int;
  used_entries_ = 0;
  //
  assert(size() == m);
}

template <class K, class V> size_t HashTable<K, V>::size() const {

  // TODO
  return table_.size();
  //
}

template <class K, class V> float HashTable<K, V>::load_factor() const {
  float ret_v = 0.0f;
  // TODO
  if (size() != 0) {
    ret_v = static_cast<float>(used_entries_) / static_cast<float>(size());
  }
  //
  return ret_v;
}

template <class K, class V>
HashTableIterator<K, V> HashTable<K, V>::begin() const {
  HashTableIterator<K, V> ret_v;
  // TODO
  // Remember: the iterator should point to the first valid entry.
  // Hint: you must use const_cast to remove the const qualifier from this.
  size_t i;
  for (i = 0; i < size() && !entry(i).is_valid(); ++i)
    ;
  if (i < size())
    ret_v = HashTableIterator<K, V>(const_cast<HashTable<K, V> *>(this), i);
  else
    ret_v = end();
  //
  return ret_v;
}

template <class K, class V>
HashTableIterator<K, V> HashTable<K, V>::end() const {
  HashTableIterator<K, V> ret_v;
  // TODO
  // Remember: the iterator should point one position pass the end of the table.
  // Hint: you must use const_cast to remove the const qualifier from this.
  ret_v = HashTableIterator<K, V>(const_cast<HashTable<K, V> *>(this), size());
  //
  assert(!ret_v.is_valid());
  return ret_v;
}

template <class K, class V>
size_t HashTable<K, V>::find_position(K const &k) const {

  assert(load_factor() < 1.0f);
  size_t idx = 0;
  // TODO
  size_t table_capacity = size();
  std::uint64_t key_as_int = key_to_int_(k);
  size_t i = 0;
  bool found_slot = false;

  while (!found_slot && i < table_capacity) {
    idx = hash_->operator()(key_as_int, i);

    const HashTableEntry<K, V> &current_entry = entry(idx);

    if (current_entry.is_empty() ||
        (current_entry.is_valid() && current_entry.key() == k) ||
        (current_entry.is_deleted() && current_entry.key() == k)) {
      found_slot = true;
    } else {
      i++;
    }
  }

  //

  assert(0 <= idx && idx < size());

  return idx;
}

template <class K, class V>
HashTableIterator<K, V> HashTable<K, V>::find(K const &k) const {
  HashTableIterator<K, V> ret_v = end();
  // TODO
  // Hint: use find_position.
  // Hint: you must use const_cast to remove the const qualifier from this.
  size_t idx = find_position(k);
  if (entry(idx).is_valid() && entry(idx).key() == k) {
    ret_v = HashTableIterator<K, V>(const_cast<HashTable<K, V> *>(this), idx);
  }
  //
  assert(ret_v == end() || (ret_v.is_valid() && ret_v.key() == k));
  return ret_v;
}

template <class K, class V>
HashTableIterator<K, V> HashTable<K, V>::insert(K const &k, V const &v) {
  assert(load_factor() <= 0.5f);
  HashTableIterator<K, V> ret_v = end();

  // Buscar posición para la clave
  size_t idx = find_position(k);

  // Verificar si necesitamos rehash
  bool need_new_entry = entry(idx).is_empty() ||
                        (entry(idx).is_deleted() && entry(idx).key() != k);

  if (need_new_entry && ((used_entries_ + 1.0f) / size() > 0.5f)) {
    rehash();
    idx = find_position(k);
  }

  // Realizar la inserción
  if (entry(idx).is_valid() && !entry(idx).is_deleted()) {
    // La entrada ya existe y es válida, actualizar valor
    entry(idx).set_value(v);
  } else if (entry(idx).is_deleted() && entry(idx).key() == k) {
    // La entrada está eliminada pero tiene la misma clave, reutilizar
    entry(idx) = HashTableEntry<K, V>(k, v);
  } else {
    // La entrada está vacía o eliminada con otra clave, crear nueva
    entry(idx) = HashTableEntry<K, V>(k, v);
    used_entries_++;
  }

  ret_v = HashTableIterator<K, V>(this, idx);

  assert(ret_v.is_valid());
  assert(ret_v.key() == k);
  assert(ret_v.value() == v);
  assert(load_factor() <= 0.5f);
  return ret_v;
}

template <class K, class V>
void HashTable<K, V>::remove(HashTableIterator<K, V> &iter) {
#ifndef NDEBUG
  assert(iter.is_valid());
  K old_k = iter.key();
#endif
  // TODO
  // Remember: we are using a mark to sign "deleted".
  assert(iter.table() == this);
  if (entry(iter.idx_).is_valid() && !entry(iter.idx_).is_deleted()) {
    entry(iter.idx_).set_deleted();
    // used_entries_--;
  }
  iter = end();
  //
  assert(!iter.is_valid());
  assert(find(old_k) == end());
}

template <class K, class V> size_t HashTable<K, V>::rehash() {
  // TODO
  // Remember: rehash when load_factor > 0.5
  // Remember: we use a 2 factor to grown the current size.
  // Remember: a new hash function will be picked at random from the Universal
  // Family. Remember: reset the number of used entries to zero before
  // inserting the old valid entries in the new table.
  std::vector<HashTableEntry<K, V>> old_table = table_;
  size_t old_m = size();
  size_t new_m = (old_m == 0) ? 2 : old_m * 2;

  OACollisionResolution::Ref new_hash_func = hash_->pick_at_new(new_m);

  table_.assign(new_m, HashTableEntry<K, V>());

  hash_ = new_hash_func;

  used_entries_ = 0;
  for (size_t i = 0; i < old_table.size(); ++i) {
    if (old_table[i].is_valid() && !old_table[i].is_deleted()) {

      this->insert(old_table[i].key(), old_table[i].value());
    }
  }
  //
  assert(load_factor() <= 0.5);
  return size();
}

template <class K, class V>
HashTableEntry<K, V> const &HashTable<K, V>::entry(size_t idx) const {

  assert(idx < size());
  // TODO: recode according to your representation.
  return table_[idx];

  //
}

template <class K, class V>
HashTableEntry<K, V> &HashTable<K, V>::entry(size_t idx) {
  assert(idx < size());
  // TODO: recode according to your representation.
  return table_[idx];

  //
}
