/* Copyright 2016 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "bitmap_helpers.h"

using ::testing::ElementsAreArray;

namespace tflite {
namespace label_image {

bool verbose = false;
int input_floating = false;
float input_mean = 127.5;
float input_std = 127.5;

TEST(LabelImageTest, Lena) {
  std::string lena_file = "tensorflow/contrib/lite/examples/label_image/testdata/lena.bmp";
  int height, width, channels;
  uint8_t *data;

  data = read_bmp(lena_file, width, height, channels);
  ASSERT_EQ(height, 26);
  ASSERT_EQ(width, 51);
  ASSERT_EQ(channels, 3);
 
  uint8_t *out = new uint8_t[26*26*3];
  downsize<uint8_t>(out, data, 26, 51, 3, 26, 26, 3); 
  ASSERT_EQ(out[0], 0xe1);
  ASSERT_EQ(out[26*26*3 - 1], 0x4b);
}

}  // label_image
}  // tflite


int main(int argc, char** argv) {
  // On Linux, add: FLAGS_logtostderr = true;
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
