/// Copyright 2014 Google Inc. All rights reserved.
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///    http://www.apache.org/licenses/LICENSE-2.0
///
///    Unless required by applicable law or agreed to in writing, software
///    distributed under the License is distributed on an "AS IS" BASIS,
///    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
///    See the License for the specific language governing permissions and
///    limitations under the License.

/// Common defines between kernel <-> userspace

#ifndef SANTA__COMMON__KERNELCOMMON_H
#define SANTA__COMMON__KERNELCOMMON_H

// Defines the lengths of paths and SHA-1's passed around.
#define MAX_PATH_LEN 1024
#define MAX_SHA1_LEN 20
#define MAX_SHA1_STRING 41
#define MAX_VNODE_ID_STR 21

// Defines the name of the userclient class and the driver bundle ID.
#define USERCLIENT_CLASS "com_google_SantaDriver"
#define USERCLIENT_ID "com.google.santa-driver"

// List of methods supported by the driver.
enum SantaDriverMethods {
  kSantaUserClientOpen,
  kSantaUserClientClose,
  kSantaUserClientAllowBinary,
  kSantaUserClientDenyBinary,
  kSantaUserClientClearCache,
  kSantaUserClientCacheCount,

  // Any methods supported by the driver should be added above this line to
  // ensure this remains the count of methods.
  kSantaUserClientNMethods,
};

// Enum defining actions that can be passed down the IODataQueue and in
// response methods.
typedef enum {
  ACTION_UNSET = 0,

  // CHECKBW
  ACTION_REQUEST_CHECKBW = 10,
  ACTION_RESPOND_CHECKBW_ALLOW = 11,
  ACTION_RESPOND_CHECKBW_DENY = 12,

  // SHUTDOWN
  ACTION_REQUEST_SHUTDOWN = 60,

  // ERROR
  ACTION_ERROR = 99,
} santa_action_t;

// Message struct that is sent down the IODataQueue.
typedef struct {
  santa_action_t action;
  uid_t userId;
  pid_t pid;
  char sha1[MAX_SHA1_STRING];
  char path[MAX_PATH_LEN];
  uint64_t vnode_id;
} santa_message_t;

#endif  // SANTA__COMMON__KERNELCOMMON_H
