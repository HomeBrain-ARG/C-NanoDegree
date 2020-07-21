// Copyright 2020-present pytorch-cpp Authors

#include "corpus.h"
#include <torch/torch.h>
#include <fstream>
#include <sstream>
#include <exception>
#include <algorithm>
#include <iostream>
#include <string>

namespace data_utils {
    torch::Tensor Corpus::get_data(int64_t batch_size) {
        if (std::ifstream file{path_}) {
            std::vector<int64_t> ids;

            for (std::string line; std::getline(file, line);) {
                std::istringstream line_stream(line);

                for (std::string word; line_stream >> word;) {
                    ids.push_back(dictionary_.add_word(word));
                }
                // End of sequence marker
                ids.push_back(dictionary_.add_word("<eos>"));
            }

            int64_t num_batches = ids.size() / batch_size;
            return torch::from_blob(ids.data(), {batch_size, num_batches},
                torch::TensorOptions().dtype(torch::kInt64)).clone();
        } else {
            throw std::runtime_error("Could not read file at path: " + path_);
        }
    }
}  // namespace data_utils





















/*
namespace data_utils {
  torch::Tensor Corpus::get_data(int64_t batch_size) {
    std::ifstream filestream(path_);
    std::cout << "data utils file_name " << path_ << std::endl;
    std::string line;
    std::vector<int64_t> ids;
    if (filestream.is_open()) {
      while(std::getline(filestream, line)) {
          std::istringstream line_stream(line);
          std::cout << line << std::endl;
         
      }
      std::cout << "done" << std::endl;
    }
  }
}

          for (std::string word; line_stream >> word;) {
                  std::cout << word << std::endl;
                    ids.push_back(dictionary_.add_word(word));
                }
                // End of sequence marker
                ids.push_back(dictionary_.add_word("<eos>"));
            }

            int64_t num_batches = ids.size() / batch_size;
            return torch::from_blob(ids.data(), {batch_size, num_batches},
                torch::TensorOptions().dtype(torch::kInt64)).clone();
        } else {
            throw std::runtime_error("Could not read file at path: " + path_);
        }
    }
}  // namespace data_utils

*/
