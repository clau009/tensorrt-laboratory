/* Copyright (c) 2018, NVIDIA CORPORATION. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#pragma once
#include <string>

#include "tensorrt/playground/core/memory/descriptor.h"
#include "tensorrt/playground/core/memory/host_memory.h"
#include "tensorrt/playground/core/memory/memory.h"

namespace yais {
namespace Memory {

class SystemV : public HostMemory, public IAllocatable
{
  protected:
    SystemV(int shm_id);
    SystemV(void* ptr, size_t size, bool allocated);

    SystemV(SystemV&& other) noexcept;
    SystemV& operator=(SystemV&& other) noexcept;

    SystemV(const SystemV&) = delete;
    SystemV& operator=(const SystemV&) = delete;

  public:
    virtual ~SystemV() override;
    const std::string& Type() const final override;

    static DescriptorHandle<SystemV> Attach(int shm_id);

    int ShmID() const;
    void DisableAttachment();

  protected:
    void* Allocate(size_t) final override;
    void Free() final override;

  private:
    int m_ShmID;
};

} // end namespace Memory
} // end namespace yais