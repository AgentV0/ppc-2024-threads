// Copyright 2024 Ryabkov Vladislav
#include <gtest/gtest.h>

#include <vector>

#include "seq/ryabkov_v_int_merge_batcher_1/include/int_merge_batcher.hpp"

void run_test(const std::vector<int> &vect) {

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();

  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(const_cast<int *>(vect.data())));
  taskDataSeq->inputs_count.emplace_back(vect.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(result.data()));
  taskDataSeq->outputs_count.emplace_back(result.size());

  SeqBatcher testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
  ASSERT_TRUE(std::is_sorted(result.begin(), result.end()));
}

TEST(ryabkov_v_bat_sort_seq, Test1) {
  std::vector<int> result(vect.size(), 0);
  std::vector<int> vect = GetRandomVector(20);  // generates a vector of size 20
  run_test(vect);
}

TEST(ryabkov_v_bat_sort_seq, Test2) {
  std::vector<int> result(vect.size(), 0);
  std::vector<int> vect = GetRandomVector(40);  // generates a vector of size 40
  run_test(vect);
}

TEST(ryabkov_v_bat_sort_seq, Test3) {
  std::vector<int> result(vect.size(), 0);
  std::vector<int> vect = GetRandomVector(60);  // generates a vector of size 60
  run_test(vect);
}

TEST(ryabkov_v_bat_sort_seq, Test4) {
  std::vector<int> result(vect.size(), 0);
  std::vector<int> vect = GetRandomVector(80);  // generates a vector of size 80
  run_test(vect);
}

TEST(ryabkov_v_bat_sort_seq, Test5) {
  std::vector<int> result(vect.size(), 0);
  std::vector<int> vect = GetRandomVector(100);  // generates a vector of size 100
  run_test(vect);
}
