/*
 *   Copyright (c) 2020 Project CHIP Authors
 *   All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#pragma once

#include "commands/common/Commands.h"
#include "commands/pairing/GetCommissionerNodeIdCommand.h"
#include "commands/pairing/GetCommissionerRootCertificateCommand.h"
#include "commands/pairing/IssueNOCChainCommand.h"
#include "commands/pairing/OpenCommissioningWindowCommand.h"
#include "commands/pairing/PairingCommand.h"

#include <app/server/Dnssd.h>
#include <commands/common/CredentialIssuerCommands.h>
#include <lib/dnssd/Resolver.h>

class Unpair : public PairingCommand
{
public:
    Unpair(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("unpair", PairingMode::None, PairingNetworkType::None, credsIssuerConfig)
    {}
};

class PairCode : public PairingCommand
{
public:
    PairCode(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("code", PairingMode::Code, PairingNetworkType::None, credsIssuerConfig)
    {}
};

class PairCodePase : public PairingCommand
{
public:
    PairCodePase(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("code-paseonly", PairingMode::CodePaseOnly, PairingNetworkType::None, credsIssuerConfig)
    {}
};

class PairCodeWifi : public PairingCommand
{
public:
    PairCodeWifi(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("code-wifi", PairingMode::Code, PairingNetworkType::WiFi, credsIssuerConfig)
    {}
};

class PairCodeThread : public PairingCommand
{
public:
    PairCodeThread(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("code-thread", PairingMode::Code, PairingNetworkType::Thread, credsIssuerConfig)
    {}
};

class PairCodeWiFiThread : public PairingCommand
{
public:
    PairCodeWiFiThread(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("code-wifi-thread", PairingMode::Code, PairingNetworkType::WiFiOrThread, credsIssuerConfig)
    {}
};

class PairOnNetwork : public PairingCommand
{
public:
    PairOnNetwork(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("onnetwork", PairingMode::OnNetwork, PairingNetworkType::None, credsIssuerConfig)
    {}
};

class PairOnNetworkShort : public PairingCommand
{
public:
    PairOnNetworkShort(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("onnetwork-short", PairingMode::OnNetwork, PairingNetworkType::None, credsIssuerConfig,
                       chip::Dnssd::DiscoveryFilterType::kShortDiscriminator)
    {}
};

class PairOnNetworkLong : public PairingCommand
{
public:
    PairOnNetworkLong(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("onnetwork-long", PairingMode::OnNetwork, PairingNetworkType::None, credsIssuerConfig,
                       chip::Dnssd::DiscoveryFilterType::kLongDiscriminator)
    {}
};

class PairOnNetworkVendor : public PairingCommand
{
public:
    PairOnNetworkVendor(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("onnetwork-vendor", PairingMode::OnNetwork, PairingNetworkType::None, credsIssuerConfig,
                       chip::Dnssd::DiscoveryFilterType::kVendorId)
    {}
};

class PairOnNetworkFabric : public PairingCommand
{
public:
    PairOnNetworkFabric(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("onnetwork-fabric", PairingMode::OnNetwork, PairingNetworkType::None, credsIssuerConfig,
                       chip::Dnssd::DiscoveryFilterType::kCompressedFabricId)
    {}
};

class PairOnNetworkCommissioningMode : public PairingCommand
{
public:
    PairOnNetworkCommissioningMode(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("onnetwork-commissioning-mode", PairingMode::OnNetwork, PairingNetworkType::None, credsIssuerConfig,
                       chip::Dnssd::DiscoveryFilterType::kCommissioningMode)
    {}
};

class PairOnNetworkCommissioner : public PairingCommand
{
public:
    PairOnNetworkCommissioner(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("onnetwork-commissioner", PairingMode::OnNetwork, PairingNetworkType::None, credsIssuerConfig,
                       chip::Dnssd::DiscoveryFilterType::kCommissioner)
    {}
};

class PairOnNetworkDeviceType : public PairingCommand
{
public:
    PairOnNetworkDeviceType(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("onnetwork-device-type", PairingMode::OnNetwork, PairingNetworkType::None, credsIssuerConfig,
                       chip::Dnssd::DiscoveryFilterType::kDeviceType)
    {}
};

class PairOnNetworkInstanceName : public PairingCommand
{
public:
    PairOnNetworkInstanceName(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("onnetwork-instance-name", PairingMode::OnNetwork, PairingNetworkType::None, credsIssuerConfig,
                       chip::Dnssd::DiscoveryFilterType::kInstanceName)
    {}
};

class PairBleWiFi : public PairingCommand
{
public:
    PairBleWiFi(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("ble-wifi", PairingMode::Ble, PairingNetworkType::WiFi, credsIssuerConfig)
    {}
};

class PairBleThread : public PairingCommand
{
public:
    PairBleThread(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("ble-thread", PairingMode::Ble, PairingNetworkType::Thread, credsIssuerConfig)
    {}
};

class PairNfcThread : public PairingCommand
{
public:
    PairNfcThread(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("nfc-thread", PairingMode::Nfc, PairingNetworkType::Thread, credsIssuerConfig)
    {}
};

class PairSoftAP : public PairingCommand
{
public:
    PairSoftAP(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("softap", PairingMode::SoftAP, PairingNetworkType::WiFi, credsIssuerConfig)
    {}
};

#if CHIP_DEVICE_CONFIG_ENABLE_WIFIPAF
class PairWiFiPAF : public PairingCommand
{
public:
    PairWiFiPAF(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("wifipaf-wifi", PairingMode::WiFiPAF, PairingNetworkType::WiFi, credsIssuerConfig)
    {}
};
#endif

class PairAlreadyDiscovered : public PairingCommand
{
public:
    PairAlreadyDiscovered(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("already-discovered", PairingMode::AlreadyDiscovered, PairingNetworkType::None, credsIssuerConfig)
    {}
};

class PairAlreadyDiscoveredByIndex : public PairingCommand
{
public:
    PairAlreadyDiscoveredByIndex(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("already-discovered-by-index", PairingMode::AlreadyDiscoveredByIndex, PairingNetworkType::None,
                       credsIssuerConfig)
    {}
};

class PairAlreadyDiscoveredByIndexWithWiFi : public PairingCommand
{
public:
    PairAlreadyDiscoveredByIndexWithWiFi(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("already-discovered-by-index-with-wifi", PairingMode::AlreadyDiscoveredByIndex, PairingNetworkType::WiFi,
                       credsIssuerConfig)
    {}
};

class PairAlreadyDiscoveredByIndexWithCode : public PairingCommand
{
public:
    PairAlreadyDiscoveredByIndexWithCode(CredentialIssuerCommands * credsIssuerConfig) :
        PairingCommand("already-discovered-by-index-with-code", PairingMode::AlreadyDiscoveredByIndexWithCode,
                       PairingNetworkType::None, credsIssuerConfig)
    {}
};

class StartUdcServerCommand : public CHIPCommand
{
public:
    StartUdcServerCommand(CredentialIssuerCommands * credsIssuerConfig) : CHIPCommand("start-udc-server", credsIssuerConfig) {}
    chip::System::Clock::Timeout GetWaitDuration() const override { return chip::System::Clock::Seconds16(300); }

    CHIP_ERROR RunCommand() override
    {
        chip::app::DnssdServer::Instance().StartServer(chip::Dnssd::CommissioningMode::kDisabled);
        return CHIP_NO_ERROR;
    }
};

void registerCommandsPairing(Commands & commands, CredentialIssuerCommands * credsIssuerConfig)
{
    const char * clusterName = "Pairing";

    commands_list clusterCommands = {
        make_unique<Unpair>(credsIssuerConfig),
        make_unique<PairCode>(credsIssuerConfig),
        make_unique<PairCodePase>(credsIssuerConfig),
        make_unique<PairCodeWifi>(credsIssuerConfig),
        make_unique<PairCodeThread>(credsIssuerConfig),
        make_unique<PairCodeWiFiThread>(credsIssuerConfig),
        make_unique<PairBleWiFi>(credsIssuerConfig),
        make_unique<PairBleThread>(credsIssuerConfig),
        make_unique<PairNfcThread>(credsIssuerConfig),
        make_unique<PairSoftAP>(credsIssuerConfig),
#if CHIP_DEVICE_CONFIG_ENABLE_WIFIPAF
        make_unique<PairWiFiPAF>(credsIssuerConfig),
#endif
        make_unique<PairAlreadyDiscovered>(credsIssuerConfig),
        make_unique<PairAlreadyDiscoveredByIndex>(credsIssuerConfig),
        make_unique<PairAlreadyDiscoveredByIndexWithWiFi>(credsIssuerConfig),
        make_unique<PairAlreadyDiscoveredByIndexWithCode>(credsIssuerConfig),
        make_unique<PairOnNetwork>(credsIssuerConfig),
        make_unique<PairOnNetworkShort>(credsIssuerConfig),
        make_unique<PairOnNetworkLong>(credsIssuerConfig),
        make_unique<PairOnNetworkVendor>(credsIssuerConfig),
        make_unique<PairOnNetworkCommissioningMode>(credsIssuerConfig),
        make_unique<PairOnNetworkCommissioner>(credsIssuerConfig),
        make_unique<PairOnNetworkDeviceType>(credsIssuerConfig),
        make_unique<PairOnNetworkInstanceName>(credsIssuerConfig),
        // TODO(#13973) - enable CommissionedListCommand once DNS Cache is implemented
        //        make_unique<CommissionedListCommand>(),
        make_unique<StartUdcServerCommand>(credsIssuerConfig),
        make_unique<OpenCommissioningWindowCommand>(credsIssuerConfig),
        make_unique<GetCommissionerNodeIdCommand>(credsIssuerConfig),
        make_unique<GetCommissionerRootCertificateCommand>(credsIssuerConfig),
        make_unique<IssueNOCChainCommand>(credsIssuerConfig),
    };

    commands.RegisterCommandSet(clusterName, clusterCommands, "Commands for commissioning devices.");
}
