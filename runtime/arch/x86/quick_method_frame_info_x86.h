/*
 * Copyright (C) 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ART_RUNTIME_ARCH_X86_QUICK_METHOD_FRAME_INFO_X86_H_
#define ART_RUNTIME_ARCH_X86_QUICK_METHOD_FRAME_INFO_X86_H_

#include "arch/instruction_set.h"
#include "base/bit_utils.h"
#include "base/callee_save_type.h"
#include "base/enums.h"
#include "quick/quick_method_frame_info.h"
#include "registers_x86.h"

namespace art {
namespace x86 {

enum XMM {
  XMM0 = 0,
  XMM1 = 1,
  XMM2 = 2,
  XMM3 = 3,
  XMM4 = 4,
  XMM5 = 5,
  XMM6 = 6,
  XMM7 = 7,
};

static constexpr uint32_t kX86CalleeSaveAlwaysSpills =
    (1 << art::x86::kNumberOfCpuRegisters);  // Fake return address callee save.
static constexpr uint32_t kX86CalleeSaveRefSpills =
    (1 << art::x86::EBP) | (1 << art::x86::ESI) | (1 << art::x86::EDI);
static constexpr uint32_t kX86CalleeSaveArgSpills =
    (1 << art::x86::ECX) | (1 << art::x86::EDX) | (1 << art::x86::EBX);
static constexpr uint32_t kX86CalleeSaveEverythingSpills =
    (1 << art::x86::EAX) | (1 << art::x86::ECX) | (1 << art::x86::EDX) | (1 << art::x86::EBX);

static constexpr uint32_t kX86CalleeSaveFpArgSpills =
    (1 << art::x86::XMM0) | (1 << art::x86::XMM1) |
    (1 << art::x86::XMM2) | (1 << art::x86::XMM3);
static constexpr uint32_t kX86CalleeSaveFpEverythingSpills =
    (1 << art::x86::XMM0) | (1 << art::x86::XMM1) |
    (1 << art::x86::XMM2) | (1 << art::x86::XMM3) |
    (1 << art::x86::XMM4) | (1 << art::x86::XMM5) |
    (1 << art::x86::XMM6) | (1 << art::x86::XMM7);

constexpr uint32_t X86CalleeSaveCoreSpills(CalleeSaveType type) {
  return kX86CalleeSaveAlwaysSpills | kX86CalleeSaveRefSpills |
      (type == CalleeSaveType::kSaveRefsAndArgs ? kX86CalleeSaveArgSpills : 0) |
      (type == CalleeSaveType::kSaveEverything ? kX86CalleeSaveEverythingSpills : 0);
}

constexpr uint32_t X86CalleeSaveFpSpills(CalleeSaveType type) {
    return (type == CalleeSaveType::kSaveRefsAndArgs ? kX86CalleeSaveFpArgSpills : 0) |
           (type == CalleeSaveType::kSaveEverything ? kX86CalleeSaveFpEverythingSpills : 0);
}

constexpr uint32_t X86CalleeSaveFrameSize(CalleeSaveType type) {
  return RoundUp((POPCOUNT(X86CalleeSaveCoreSpills(type)) /* gprs */ +
                  2 * POPCOUNT(X86CalleeSaveFpSpills(type)) /* fprs */ +
                  1 /* Method* */) * static_cast<size_t>(kX86PointerSize), kStackAlignment);
}

constexpr QuickMethodFrameInfo X86CalleeSaveMethodFrameInfo(CalleeSaveType type) {
  return QuickMethodFrameInfo(X86CalleeSaveFrameSize(type),
                              X86CalleeSaveCoreSpills(type),
                              X86CalleeSaveFpSpills(type));
}

}  // namespace x86
}  // namespace art

#endif  // ART_RUNTIME_ARCH_X86_QUICK_METHOD_FRAME_INFO_X86_H_
