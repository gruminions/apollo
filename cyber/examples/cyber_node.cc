/******************************************************************************
 * Copyright 2019 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include <iostream>
#include <vector>

#include "cyber/cyber.h"

int main(int argc, char* argv[]) {
  // init cyber framework
  apollo::cyber::Init(argv[0]);

  auto topology = apollo::cyber::service_discovery::TopologyManager::Instance();
  auto node_mgr = topology->node_manager();

  while (apollo::cyber::OK()) {
    std::vector<apollo::cyber::proto::RoleAttributes> nodes;
    node_mgr->GetNodes(&nodes);
    std::cout << "-----------------------------" << std::endl;
    std::cout << "node amount: " << nodes.size() << std::endl;
    std::cout << "node list:" << std::endl;
    for (const auto& node_attr : nodes) {
      std::cout << "  node name: " << node_attr.node_name() << std::endl;
      std::cout << "    host name: " << node_attr.host_name() << std::endl;
      std::cout << "    process id: " << node_attr.process_id() << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }
  return 0;
}
