// Copyright 2024 Ryabkov Vladislav

#include "omp/ryabkov_v_int_merge_batcher/include/int_merge_batcher.hpp"

namespace ryabkov_batcher {
void radix_sort(std::vector<int>& arr, int exp) {
  const int n = static_cast<int>(arr.size());
  std::vector<int> output(n);
  std::vector<int> count(10, 0);

#pragma omp parallel
  {
    std::vector<int> local_count(10, 0);
#pragma omp for
    for (int i = 0; i < n; i++) {
      local_count[(arr[i] / exp) % 10]++;
    }

#pragma omp critical
    {
      for (int i = 0; i < 10; i++) {
        count[i] += local_count[i];
      }
    }
  }

  for (int i = 1; i < 10; i++) {
    count[i] += count[i - 1];
  }

  for (int i = n - 1; i >= 0; i--) {
    output[count[(arr[i] / exp) % 10] - 1] = arr[i];
    count[(arr[i] / exp) % 10]--;
  }

#pragma omp parallel for
  for (int i = 0; i < n; i++) {
    arr[i] = output[i];
  }
}

void radix_sort(std::vector<int>& arr) {
  const int max_element = *std::max_element(arr.begin(), arr.end());

  for (int exp = 1; max_element / exp > 0; exp *= 10) {
    radix_sort(arr, exp);
  }
}

std::vector<int> batch_merge(const std::vector<int>& a1, const std::vector<int>& a2) {
  std::vector<int> merged(a1.size() + a2.size());
  int i = 0;
  int j = 0;

  for (int k = 0; k < static_cast<int>(merged.size()); ++k) {
    if (i < static_cast<int>(a1.size()) && (j >= static_cast<int>(a2.size()) || a1[i] < a2[j])) {
      merged[k] = a1[i++];
    } else {
      merged[k] = a2[j++];
    }
  }
  return merged;
}

std::vector<int> BatchSort(std::vector<int>& a1, std::vector<int>& a2) {
  std::vector<int> merged = batch_merge(a1, a2);

  for (int bit = 0; bit < static_cast<int>(sizeof(int) * 8); bit++) {
#pragma omp parallel for
    for (int i = 0; i < static_cast<int>(merged.size() / 2); i++) {
      if (((i % 2 == 0) && ((merged[2 * i] >> bit) & 1) != 0) ||
          ((i % 2 != 0) && ((merged[2 * i + 1] >> bit) & 1) != 0)) {
        std::swap(merged[2 * i], merged[2 * i + 1]);
      }
    }
  }

  radix_sort(merged);

  int n = static_cast<int>(merged.size() / 2);
  a1.assign(merged.begin(), merged.begin() + n);
  a2.assign(merged.begin() + n, merged.end());

  return merged;
}
}  // namespace ryabkov_batcher

bool ryabkov_batcher::SeqBatcher::pre_processing() {
  internal_order_test();

  if (!taskData) return false;

  inv.resize(taskData->inputs_count[0]);
  int* tmp_ptr_A = reinterpret_cast<int*>(taskData->inputs[0]);
  std::copy(tmp_ptr_A, tmp_ptr_A + taskData->inputs_count[0], inv.begin());

  a1.resize(inv.size() / 2);
  a2.resize(inv.size() / 2);

#pragma omp parallel for
  for (int i = 0; i < static_cast<int>(inv.size() / 2); ++i) {
    a1[i] = inv[i];
    a2[i] = inv[inv.size() / 2 + i];
  }

  return true;
}

bool ryabkov_batcher::SeqBatcher::validation() {
  internal_order_test();

  return taskData->inputs_count[0] == taskData->outputs_count[0];
}

bool ryabkov_batcher::SeqBatcher::run() {
  internal_order_test();

  result = ryabkov_batcher::BatchSort(a1, a2);
  return true;
}

bool ryabkov_batcher::SeqBatcher::post_processing() {
  internal_order_test();

  std::copy(result.begin(), result.end(), reinterpret_cast<int*>(taskData->outputs[0]));
  return true;
}
