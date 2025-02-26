/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#include <Atom/RHI.Reflect/Format.h>
#include <Atom/RHI/IndexBufferView.h>
#include <AzCore/Utils/TypeHash.h>

namespace AZ::RHI
{
    class MultiDeviceBuffer;

    uint32_t GetIndexFormatSize(IndexFormat indexFormat);

    //! A multi-device class representing a view onto a MultiDeviceBuffer holding indices, distinct from
    //! actual view classes (like BufferView), there is no representation on the API level.
    //! Its device-specific buffers are provided to the RHI back-end at draw time.
    class alignas(8) MultiDeviceIndexBufferView
    {
    public:
        MultiDeviceIndexBufferView() = default;

        MultiDeviceIndexBufferView(const MultiDeviceBuffer& buffer, uint32_t byteOffset, uint32_t byteCount, IndexFormat format);

        //! Returns the device-specific IndexBufferView for the given index
        IndexBufferView GetDeviceIndexBufferView(int deviceIndex) const;

        //! Returns the hash of the view. This hash is precomputed at creation time.
        HashValue64 GetHash() const;

        //! Returns the buffer associated with the data in the view.
        const MultiDeviceBuffer* GetBuffer() const;

        //! Returns the byte offset into the buffer returned by GetBuffer
        uint32_t GetByteOffset() const;

        //! Returns the number of bytes in the view.
        uint32_t GetByteCount() const;

        //! Returns the format of each index in the view.
        IndexFormat GetIndexFormat() const;

    private:
        HashValue64 m_hash = HashValue64{ 0 };
        const MultiDeviceBuffer* m_mdBuffer = nullptr;
        uint32_t m_byteOffset = 0;
        uint32_t m_byteCount = 0;
        IndexFormat m_format = IndexFormat::Uint32;
    };
} // namespace AZ::RHI
