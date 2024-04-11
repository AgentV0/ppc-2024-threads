// Copyright 2024 Ryabkov Vladislav
#include "seq/ryabkov_v_int_merge_batcher_1/include/int_merge_batcher.hpp"

void radix_sort(std::vector<int>& arr, int exp) {
  const std::size_t n = arr.size();
  std::vector<int> output(n);
  std::vector<int> count(10, 0);

  for (std::size_t i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;

  for (int i = 1; i < 10; i++) count[i] += count[i - 1];

  for (int i = static_cast<int>(n) - 1; i >= 0; i--) {
    output[count[(arr[i] / exp) % 10] - 1] = arr[i];
    count[(arr[i] / exp) % 10]--;
  }

  for (std::size_t i = 0; i < n; i++) arr[i] = output[i];
}

void radix_sort(std::vector<int>& arr) {
  const int max_element = *std::max_element(arr.begin(), arr.end());

  for (int exp = 1; max_element / exp > 0; exp *= 10) radix_sort(arr, exp);
}

std::vector<int> batch_merge(const std::vector<int>& a1, const std::vector<int>& a2) {
  std::vector<int> merged(a1.size() + a2.size());
  std::size_t i = 0, j = 0;

  for (std::size_t k = 0; k < merged.size(); ++k) {
    if (((k & 1) == 0 && i < a1.size()) || ((k & 1) == 1 && j >= a2.size())) {
      merged[k] = a1[i++];
    } else {
      merged[k] = a2[j++];
    }
  }
  return merged;
}

std::vector<int> BatchSort(std::vector<int>& a1, std::vector<int>& a2) {
  radix_sort(a1);
  radix_sort(a2);

  const std::size_t n = a1.size();
  std::vector<int> result(n * 2);

  for (size_t bit = 0; bit < sizeof(int) * 8; bit++) {
    for (std::size_t i = 0; i < n; i += 2) {
      if ((a1[i] >> bit) & 1) {
        std::swap(a1[i], a1[i + 1]);
      }
      if ((a2[i] >> bit) & 1) {
        std::swap(a2[i], a2[i + 1]);
      }
    }
    auto merged = batch_merge(a1, a2);
    for (std::size_t i = 0; i < n; i++) {
      if ((merged[i * 2] >> bit) & 1) {
        std::swap(merged[i * 2], merged[i * 2 + 1]);
      }
    }
    a1.assign(merged.begin(), merged.begin() + n);
    a2.assign(merged.begin() + n, merged.end());
  }

  std::copy(a1.begin(), a1.end(), result.begin());
  std::copy(a2.begin(), a2.end(), result.begin() + n);
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

  for (std::size_t i = 0; i < inv.size() / 2; ++i) {
    a1[i] = inv[i];
    a2[i] = inv[inv.size() / 2 + i];
  }

  return true;
}

bool SeqBatcher::validation() {
  internal_order_test();

  return taskData->inputs_count[0] == taskData->outputs_count[0];
  ;
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
