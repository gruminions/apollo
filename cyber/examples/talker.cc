/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
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
#include <sstream>

#include "cyber/cyber.h"
#include "cyber/message/raw_message.h"
#include "cyber/time/rate.h"
#include "cyber/time/time.h"

using apollo::cyber::Rate;
using apollo::cyber::Time;
using apollo::cyber::message::RawMessage;

int main(int argc, char *argv[]) {
  // init cyber framework
  apollo::cyber::Init(argv[0]);
  // create talker node
  auto talker_node = apollo::cyber::CreateNode("talker");
  // create talker
  auto talker = talker_node->CreateWriter<RawMessage>("channel/chatter");

  int msg_len = 1000;
  if (argc > 1) {
    msg_len = atoi(argv[1]);
  }

  int msg_num = 1000;
  if (argc > 2) {
    msg_num = atoi(argv[2]);
  }

  double freq = 100.0;
  if (argc > 3) {
    freq = atof(argv[3]);
  }

  std::cout << "message length: " << msg_len << "\n"
            << "message number: " << msg_num << "\n"
            << "message frequency: " << freq << std::endl;

  Rate rate(freq);
  const std::string foo_content(msg_len, 'c');
  int count = 0;

  std::this_thread::sleep_for(
      std::chrono::seconds(2));  // sleep for mutual discovery

  while (apollo::cyber::OK()) {
    auto msg = std::make_shared<RawMessage>();
    msg->message = foo_content;

    std::stringstream ss;
    ss << '+' << Time::Now().ToNanosecond();
    msg->message.append(ss.str());

    talker->Write(msg);
    rate.Sleep();

    ++count;
    if (count == msg_num) {
      std::cout << "talk over" << std::endl;
      break;
    }
  }

  return 0;
}
