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

#include "AmbientContextSensingDelegateImpl.h"
#include <lib/support/logging/CHIPLogging.h>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;

AmbientContextSensingDelegateImpl::AmbientContextSensingDelegateImpl() :
    mAmbientContextTypeSupportedList(mAmbientContextTypeSupportedBuf), mPredictedActivityList(mPredictActivityBuf)
{
    for (auto &v : mAmbientContextTypeSupportedBuf) v = SemanticTagType{};
    mAmbientContextTypeSupportedList = Span<SemanticTagType>(mAmbientContextTypeSupportedBuf, 0);
    for (auto &v : mPredictActivityBuf) v = AmbientContextSensingCluster::PredictActivity{};
    mPredictedActivityList           = Span<AmbientContextSensingCluster::PredictActivity>(mPredictActivityBuf, 0);
    for (auto &v : mAmbientContextTypeListUsed) v = false;
}

CHIP_ERROR AmbientContextSensingDelegateImpl::SetAmbientContextTypeSupported(const Span<SemanticTagType> & ACTypeList)
{
    VerifyOrReturnError(ACTypeList.size() <= kMaxACTypeSupported, CHIP_ERROR_INVALID_ARGUMENT);
    VerifyOrReturnError(ACTypeList.size() > 0, CHIP_ERROR_INVALID_ARGUMENT);
    std::copy(ACTypeList.begin(), ACTypeList.end(), mAmbientContextTypeSupportedBuf);
    mAmbientContextTypeSupportedList = Span<SemanticTagType>(mAmbientContextTypeSupportedBuf, ACTypeList.size());
    return CHIP_NO_ERROR;
}

CHIP_ERROR AmbientContextSensingDelegateImpl::SetPredictedActivity(const Span<PredictedActivityType> & predictedActivityList)
{
    VerifyOrReturnError(predictedActivityList.size() <= kMaxPredictedActivity, CHIP_ERROR_INVALID_ARGUMENT);

    // Copy the input predicted activity to local array
    for (size_t i = 0; i < predictedActivityList.size(); i++)
    {
        const auto & src = predictedActivityList[i];
        auto & dst       = mPredictActivityBuf[i];
        dst.mInfo        = src;
        // Copy tags
        if (!src.ambientContextType.HasValue())
        {
            dst.mOwnedTags.reset();
            dst.mInfo.ambientContextType.ClearValue();
            continue;
        }

        const auto & acTypeList = src.ambientContextType.Value();
        const auto tagCount     = acTypeList.size();
        VerifyOrReturnError(tagCount > 0, CHIP_ERROR_INVALID_ARGUMENT);
        VerifyOrReturnError(tagCount <= kMaxPredictedACType, CHIP_ERROR_INVALID_ARGUMENT);

        dst.mOwnedTags = std::make_unique<SemanticTagType[]>(tagCount);
        for (size_t t = 0; t < tagCount; t++)
        {
            dst.mOwnedTags[t] = acTypeList[t];
        }

        dst.mInfo.ambientContextType.SetValue(
            DataModel::List<const SemanticTagType>(dst.mOwnedTags.get(), static_cast<uint16_t>(tagCount)));
    }
    mPredictedActivityList = Span<AmbientContextSensingCluster::PredictActivity>(mPredictActivityBuf, predictedActivityList.size());

    return CHIP_NO_ERROR;
}

CHIP_ERROR AmbientContextSensingDelegateImpl::AddDetection(uint8_t & id)
{
    uint8_t i;
    for (i = 0; i < kMaxSimultaneousDetectionLimit; i++)
    {
        if (mAmbientContextTypeListUsed[i] == false)
        {
            break;
        }
    }
    VerifyOrReturnError((i < kMaxSimultaneousDetectionLimit), CHIP_ERROR_INCORRECT_STATE);
    mAmbientContextTypeListUsed[i] = true;
    id                             = i;

    return CHIP_NO_ERROR;
}

AmbientContextSensingCluster::AmbientContextSensed * AmbientContextSensingDelegateImpl::GetDetection(const uint8_t id)
{
    VerifyOrReturnError(id < kMaxSimultaneousDetectionLimit, nullptr);
    VerifyOrReturnError(mAmbientContextTypeListUsed[id] == true, nullptr);
    return &mAmbientContextTypeList[id];
}

CHIP_ERROR AmbientContextSensingDelegateImpl::DelDetection(const uint8_t & id)
{
    VerifyOrReturnError(id < kMaxSimultaneousDetectionLimit, CHIP_ERROR_INVALID_ARGUMENT);
    mAmbientContextTypeListUsed[id] = false;

    return CHIP_NO_ERROR;
}
