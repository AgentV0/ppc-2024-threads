<<<<<<< HEAD
// Copyright 2024 Ryabkov Vladislav

=======
>>>>>>> origin/omp_ryabkov_v_int_merge_batcher
#include <gtest/gtest.h>

#include <vector>

#include "omp/ryabkov_v_int_merge_batcher/include/int_merge_batcher.hpp"

void run_test(const std::vector<int> &vect) {
  std::vector<int> result(vect.size(), 0);

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();

  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(const_cast<int *>(vect.data())));
  taskDataSeq->inputs_count.emplace_back(vect.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(result.data()));
  taskDataSeq->outputs_count.emplace_back(result.size());

  ryabkov_batcher::SeqBatcher testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();
  ASSERT_TRUE(std::is_sorted(result.begin(), result.end()));
}

TEST(ryabkov_v_bat_sort_omp, Test1) {
  std::vector<int> vect = ryabkov_batcher::GetRandomVector(10);  // generates a vector of size 10
  run_test(vect);
}

TEST(ryabkov_v_bat_sort_omp, Test2) {
  std::vector<int> vect = ryabkov_batcher::GetRandomVector(30);  // generates a vector of size 30
  run_test(vect);
}

TEST(ryabkov_v_bat_sort_omp, Test3) {
  std::vector<int> vect = ryabkov_batcher::GetRandomVector(40);  // generates a vector of size 40
  run_test(vect);
}

TEST(ryabkov_v_bat_sort_omp, Test4) {
  std::vector<int> vect = ryabkov_batcher::GetRandomVector(50);  // generates a vector of size 50
  run_test(vect);
}

TEST(ryabkov_v_bat_sort_omp, Test5) {
  std::vector<int> vect = ryabkov_batcher::GetRandomVector(100);  // generates a vector of size 100
  run_test(vect);
}
