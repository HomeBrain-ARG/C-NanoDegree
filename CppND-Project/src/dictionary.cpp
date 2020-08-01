// Copyright 2020-present pytorch-cpp Authors
#include "../include/dictionary.h"
#include <iostream>

namespace data_utils {
    int64_t Dictionary::add_word(const std::string& word) {
        auto it = word2idx_.find(word);

        if (it == word2idx_.end()) {
            idx2word_.push_back(word);

            auto new_index = idx2word_.size() - 1;
            word2idx_[word] = new_index;
            return new_index;
        }

        return it->second;
    }
    std::string Dictionary::word_at_index(int64_t index) const{
      return idx2word_[index];
    }
}  // namespace data_utils
