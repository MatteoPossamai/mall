#pragma once

#include <concepts>
#include <string>

template <typename T>
concept Memtable = requires(T t, std::string key, std::string value) {
    t.insert(key, value);
    t.remove(key);
    { t.get(key) } -> std::same_as<std::string>;
};