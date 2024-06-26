/*
 *  Copyright (c) 2013 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "modules/remote_bitrate_estimator/remote_bitrate_estimator_single_stream.h"

#include <memory>

#include "api/environment/environment_factory.h"
#include "modules/remote_bitrate_estimator/remote_bitrate_estimator_unittest_helper.h"
#include "test/gtest.h"

namespace webrtc {

class RemoteBitrateEstimatorSingleTest : public RemoteBitrateEstimatorTest {
 public:
  RemoteBitrateEstimatorSingleTest() {}

  RemoteBitrateEstimatorSingleTest(const RemoteBitrateEstimatorSingleTest&) =
      delete;
  RemoteBitrateEstimatorSingleTest& operator=(
      const RemoteBitrateEstimatorSingleTest&) = delete;

  void SetUp() override {
    bitrate_estimator_ = std::make_unique<RemoteBitrateEstimatorSingleStream>(
        CreateEnvironment(&clock_), bitrate_observer_.get());
  }
};

TEST_F(RemoteBitrateEstimatorSingleTest, InitialBehavior) {
  InitialBehaviorTestHelper(508017);
}

TEST_F(RemoteBitrateEstimatorSingleTest, RateIncreaseReordering) {
  RateIncreaseReorderingTestHelper(506422);
}

TEST_F(RemoteBitrateEstimatorSingleTest, RateIncreaseRtpTimestamps) {
  RateIncreaseRtpTimestampsTestHelper(1267);
}

TEST_F(RemoteBitrateEstimatorSingleTest, CapacityDropOneStream) {
  CapacityDropTestHelper(1, false, 633, 0);
}

TEST_F(RemoteBitrateEstimatorSingleTest, CapacityDropOneStreamWrap) {
  CapacityDropTestHelper(1, true, 633, 0);
}

TEST_F(RemoteBitrateEstimatorSingleTest, CapacityDropTwoStreamsWrap) {
  CapacityDropTestHelper(2, true, 567, 0);
}

TEST_F(RemoteBitrateEstimatorSingleTest, CapacityDropThreeStreamsWrap) {
  CapacityDropTestHelper(3, true, 567, 0);
}

TEST_F(RemoteBitrateEstimatorSingleTest, CapacityDropThirteenStreamsWrap) {
  CapacityDropTestHelper(13, true, 767, 0);
}

TEST_F(RemoteBitrateEstimatorSingleTest, CapacityDropNineteenStreamsWrap) {
  CapacityDropTestHelper(19, true, 767, 0);
}

TEST_F(RemoteBitrateEstimatorSingleTest, CapacityDropThirtyStreamsWrap) {
  CapacityDropTestHelper(30, true, 733, 0);
}

TEST_F(RemoteBitrateEstimatorSingleTest, TestTimestampGrouping) {
  TestTimestampGroupingTestHelper();
}
}  // namespace webrtc
