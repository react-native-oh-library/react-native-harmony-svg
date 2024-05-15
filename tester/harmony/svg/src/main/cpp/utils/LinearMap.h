// from ArkUI "frameworks/base/utils/linear_map.h"
#pragma once

#include <algorithm>
#include <cstring>

namespace rnoh {
namespace svg {

template<typename T>
struct LinearMapNode {
    const char* key;
    T value;
};

// the key type K must can be compared.
template<typename K, typename V>
struct LinearEnumMapNode {
    K key;
    V value;
};

// these binary search functions in linear map, so the map must be sorted by key.
template<typename T>
int64_t BinarySearchFindIndex(const LinearMapNode<T>* vec, size_t length, const char* key)
{
    auto it = std::lower_bound(
        vec, vec + length, key, [](LinearMapNode<T> lhs, const char* key) { return strcmp(lhs.key, key) < 0; });
    if (it == vec + length || strcmp(it->key, key) != 0) {
        return -1;
    } else {
        return it - vec;
    }
}

template<typename K, typename V>
int64_t BinarySearchFindIndex(const LinearEnumMapNode<K, V>* vec, size_t length, K key)
{
    auto it =
        std::lower_bound(vec, vec + length, key, [](LinearEnumMapNode<K, V> lhs, K key) { return lhs.key < key; });
    if (it == vec + length || it->key != key) {
        return -1;
    } else {
        return it - vec;
    }
}
} // namespace svg
} // namespace rnoh
