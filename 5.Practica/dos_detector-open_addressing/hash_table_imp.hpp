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
  if (size() == 0) { // Evitar división por cero si la tabla está vacía.
    ret_v = 0.0f;
  } else {
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
  size_t i = 0;
  bool found_slot = false;
  std::uint64_t key_as_int = key_to_int_(k);
  while (!found_slot &&
         i < size()) { // Iterar como máximo 'size' veces (m intentos de prueba)
    idx = hash_->operator()(key_as_int, i);

    if (!entry(idx).is_valid() ||
        (entry(idx).is_valid() && entry(idx).key() == k)) {

      found_slot = true;
    } else {
      i++;
    }
  }
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
  const size_t current_size = size();
  // TODO
  // Remember: increment the number of used entries only when an
  //    empty entry was used.
  // Remember: you must call to rehash before inserting a new entry to avoid
  //    a load factor greater than 0.5.
  // Remember: if a rehashing was done (current_size != new size returned by
  //    rehash function), you need to find the new location of the inserted key.
  size_t current_table_size = size();
  size_t idx_after_potential_rehash;
  size_t tentative_idx = find_position(k);
  bool is_new_insertion =
      !entry(tentative_idx).is_valid() || entry(tentative_idx).key() != k;

  is_new_insertion = !entry(tentative_idx).is_valid();
  if (is_new_insertion && (static_cast<float>(used_entries_ + 1) /
                           static_cast<float>(current_table_size)) > 0.5f) {
    rehash();
    idx_after_potential_rehash = find_position(k);
  } else {
    idx_after_potential_rehash = tentative_idx;
  }

  if (!entry(idx_after_potential_rehash).is_valid()) {
    entry(idx_after_potential_rehash) = HashTableEntry<K, V>(k, v);
    used_entries_++;
  } else {

    entry(idx_after_potential_rehash).set_value(v);
  }

  ret_v = HashTableIterator<K, V>(this, idx_after_potential_rehash);
  //
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
  entry(iter.idx_).set_deleted();
  used_entries_--;
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
  // Family. Remember: reset the number of used entries to zero before inserting
  // the old valid entries in the new table.
  std::vector<HashTableEntry<K, V>> old_table = table_;
  size_t old_m = size();
  size_t new_m = (old_m == 0) ? 2 : old_m * 2;

  OACollisionResolution::Ref new_hash_func = hash_->pick_at_new(new_m);

  table_.assign(new_m, HashTableEntry<K, V>());

  hash_ = new_hash_func;

  used_entries_ = 0;
  for (size_t i = 0; i < old_table.size(); ++i) {
    if (old_table[i].is_valid()) {

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
