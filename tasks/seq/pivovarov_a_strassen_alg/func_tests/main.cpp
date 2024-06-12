// Copyright 2024 Pivovarov Alexey
#include <gtest/gtest.h>

#include <vector>

#include "seq/pivovarov_a_strassen_alg/include/ops_seq.hpp"

TEST(Pivovarov_a_strassen_alg_seq, Multiplication_0x0) {
  int n = 0;

  // Create data
  std::vector<double> in_A = createRndMatrix(n);
  std::vector<double> in_B = createRndMatrix(n);
  std::vector<double> out(n * n);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_A.data()));
  taskDataSeq->inputs_count.emplace_back(in_A.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_B.data()));
  taskDataSeq->inputs_count.emplace_back(in_B.size());

  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(const_cast<int *>(&n)));
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(const_cast<int *>(&n)));

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  std::vector<double> res = multiplyMatrix(in_A, in_B, n);

  // Create Task
  TestTaskSequentialPivovarovStrassen test(taskDataSeq);
  ASSERT_EQ(test.validation(), true);
  test.pre_processing();
  test.run();
  test.post_processing();

  for (size_t i = 0; i < res.size(); ++i) {
    ASSERT_EQ(std::round(res[i] * std::pow(10, 3)) / std::pow(10, 3),
              std::round(out[i] * std::pow(10, 3)) / std::pow(10, 3));
  }
}

TEST(Pivovarov_a_strassen_alg_seq, Multiplication_1x1) {
  int n = 1;

  // Create data
  std::vector<double> in_A = createRndMatrix(n);
  std::vector<double> in_B = createRndMatrix(n);
  std::vector<double> out(n * n);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_A.data()));
  taskDataSeq->inputs_count.emplace_back(in_A.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_B.data()));
  taskDataSeq->inputs_count.emplace_back(in_B.size());

  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(const_cast<int *>(&n)));
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(const_cast<int *>(&n)));

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  std::vector<double> res = multiplyMatrix(in_A, in_B, n);

  // Create Task
  TestTaskSequentialPivovarovStrassen test(taskDataSeq);
  ASSERT_EQ(test.validation(), true);
  test.pre_processing();
  test.run();
  test.post_processing();

  for (size_t i = 0; i < res.size(); ++i) {
    ASSERT_EQ(std::round(res[i] * std::pow(10, 3)) / std::pow(10, 3),
              std::round(out[i] * std::pow(10, 3)) / std::pow(10, 3));
  }
}

TEST(Pivovarov_a_strassen_alg_seq, Multiplication_2x2) {
  int n = 2;

  // Create data
  std::vector<double> in_A{1, 2, 3, 4};
  std::vector<double> in_B{6, 7, 8, 9};
  std::vector<double> out(n * n);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_A.data()));
  taskDataSeq->inputs_count.emplace_back(in_A.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_B.data()));
  taskDataSeq->inputs_count.emplace_back(in_B.size());

  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(const_cast<int *>(&n)));
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(const_cast<int *>(&n)));

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  std::vector<double> res = multiplyMatrix(in_A, in_B, n);

  // Create Task
  TestTaskSequentialPivovarovStrassen test(taskDataSeq);
  ASSERT_EQ(test.validation(), true);
  test.pre_processing();
  test.run();
  test.post_processing();

  for (size_t i = 0; i < res.size(); ++i) {
    ASSERT_EQ(std::round(res[i] * std::pow(10, 3)) / std::pow(10, 3),
              std::round(out[i] * std::pow(10, 3)) / std::pow(10, 3));
  }
}

TEST(Pivovarov_a_strassen_alg_seq, Multiplication_4x4) {
  int n = 4;

  // Create data
  std::vector<double> in_A = createRndMatrix(n);
  std::vector<double> in_B = createRndMatrix(n);
  std::vector<double> out(n * n);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_A.data()));
  taskDataSeq->inputs_count.emplace_back(in_A.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_B.data()));
  taskDataSeq->inputs_count.emplace_back(in_B.size());

  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(const_cast<int *>(&n)));
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(const_cast<int *>(&n)));

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  std::vector<double> res = multiplyMatrix(in_A, in_B, n);

  // Create Task
  TestTaskSequentialPivovarovStrassen test(taskDataSeq);
  ASSERT_EQ(test.validation(), true);
  test.pre_processing();
  test.run();
  test.post_processing();

  for (size_t i = 0; i < res.size(); ++i) {
    ASSERT_EQ(std::round(res[i] * std::pow(10, 3)) / std::pow(10, 3),
              std::round(out[i] * std::pow(10, 3)) / std::pow(10, 3));
  }
}

TEST(Pivovarov_a_strassen_alg_seq, Multiplication_8x8) {
  int n = 8;

  // Create data
  std::vector<double> in_A = createRndMatrix(n);
  std::vector<double> in_B = createRndMatrix(n);
  std::vector<double> out(n * n);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_A.data()));
  taskDataSeq->inputs_count.emplace_back(in_A.size());
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_B.data()));
  taskDataSeq->inputs_count.emplace_back(in_B.size());

  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(const_cast<int *>(&n)));
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(const_cast<int *>(&n)));

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(out.size());

  std::vector<double> res = multiplyMatrix(in_A, in_B, n);

  // Create Task
  TestTaskSequentialPivovarovStrassen test(taskDataSeq);
  ASSERT_EQ(test.validation(), true);
  test.pre_processing();
  test.run();
  test.post_processing();

  for (size_t i = 0; i < res.size(); ++i) {
    ASSERT_EQ(std::round(res[i] * std::pow(10, 3)) / std::pow(10, 3),
              std::round(out[i] * std::pow(10, 3)) / std::pow(10, 3));
  }
}
