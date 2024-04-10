// Copyright 2024 Ryabkov Vladislav

#include "seq/ryabkov_v_int_merge_batcher1/include/int_merge_batcher.hpp"

using namespace std::chrono_literals

using len_t = std::size_t;

namespace ryabkov_batcher {
void MergeAndCorrect(std::vector<int>& result, const std::vector<int>& a1, const std::vector<int>& a2) {
  len_t i = 0, j = 0, k = 0;

  while (j < a1.size() && k < a2.size()) {
    if (a1[j] <= a2[k]) {
      result[i++] = a1[j++];
    } else {
      result[i++] = a2[k++];
    }
  }
  while (j < a1.size()) {
    result[i++] = a1[j++];
  }
  while (k < a2.size()) {
    result[i++] = a2[k++];
  }
}

std::vector<int> BatchSort(const std::vector<int>& a1, const std::vector<int>& a2) {
  std::vector<int> result(a1.size() + a2.size());
  len_t i = 0, j = 0, k = 0;

  while (j < a1.size() && k < a2.size()) {
    if (a1[j] <= a2[k]) {
      result[i++] = a1[j++];
    } else {
      result[i++] = a2[k++];
    }
  }
  while (j < a1.size()) {
    result[i++] = a1[j++];
  }
  while (k < a2.size()) {
    result[i++] = a2[k++];
  }

  return result;
}

bool SeqBatcher::pre_processing() {
  internal_order_test();

  if (!taskData) return false;

  inv.resize(taskData->inputs_count[0]);
  int* tmp_ptr_A = reinterpret_cast<int*>(taskData->inputs[0]);
  std::copy(tmp_ptr_A, tmp_ptr_A + taskData->inputs_count[0], inv.begin());

  a1.resize(inv.size() / 2);
  a2.resize(inv.size() / 2);

  for (len_t i = 0; i < inv.size() / 2; ++i) {
    a1[i] = inv[i];
    a2[i] = inv[inv.size() / 2 + i];
  }

  std::sort(a1.begin(), a1.end());
  std::sort(a2.begin(), a2.end());

  return true;
}

bool SeqBatcher::validation() {
  internal_order_test();

  return std::is_sorted(a1.begin(), a1.end()) && std::is_sorted(a2.begin(), a2.end());
}

bool SeqBatcher::run() {
  internal_order_test();

  result = BatchSort(a1, a2);
  return true;
}

bool SeqBatcher::post_processing() {
  internal_order_test();

  std::copy(result.begin(), result.end(), reinterpret_cast<int*>(taskData->outputs[0]));
  return true;
}
}  // namespace ryabkov_batcher