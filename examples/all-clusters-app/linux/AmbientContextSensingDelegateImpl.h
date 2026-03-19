/**
 *
 *    Copyright (c) 2026 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include <app/clusters/ambient-context-sensing-server/AmbientContextSensingCluster.h>

namespace chip {
namespace app {
namespace Clusters {

class AmbientContextSensingDelegateImpl : public AmbientContextSensingDelegate
{
public:
    AmbientContextSensingDelegateImpl();
    ~AmbientContextSensingDelegateImpl() = default;
    CHIP_ERROR SetAmbientContextTypeSupported(const Span<SemanticTagType> & ACTypeList) override;
    Span<SemanticTagType> & GetAmbientContextTypeSupported() override { return mAmbientContextTypeSupportedList; };

    CHIP_ERROR SetPredictedActivity(const Span<PredictedActivityType> & predictedActivityList) override;
    Span<AmbientContextSensingCluster::PredictActivity> & GetPredictedActivity() override { return mPredictedActivityList; };

    CHIP_ERROR AddDetection(uint8_t & id) override;
    AmbientContextSensingCluster::AmbientContextSensed * GetDetection(const uint8_t id) override;
    CHIP_ERROR DelDetection(const uint8_t & id) override;

    AmbientContextSensingDelegateImpl(const AmbientContextSensingDelegateImpl &)             = delete;
    AmbientContextSensingDelegateImpl & operator=(const AmbientContextSensingDelegateImpl &) = delete;
    AmbientContextSensingDelegateImpl(AmbientContextSensingDelegateImpl &&)                  = delete;
    AmbientContextSensingDelegateImpl & operator=(AmbientContextSensingDelegateImpl &&)      = delete;

private:
    SemanticTagType mAmbientContextTypeSupportedBuf[kMaxACTypeSupported];
    Span<SemanticTagType> mAmbientContextTypeSupportedList;

    AmbientContextSensingCluster::PredictActivity mPredictActivityBuf[kMaxPredictedActivity];
    Span<AmbientContextSensingCluster::PredictActivity> mPredictedActivityList;

    // From spec, constraint of AmbientContextType is 1 to SimultaneousDetectionLimit.
    AmbientContextSensingCluster::AmbientContextSensed mAmbientContextTypeList[kMaxSimultaneousDetectionLimit];
    bool mAmbientContextTypeListUsed[kMaxSimultaneousDetectionLimit];
};

} // namespace Clusters
} // namespace app
} // namespace chip
