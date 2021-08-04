#pragma once

namespace csl::hio
{
    struct PacketHeader
    {
        /// <summary>
        /// Name of service
        /// </summary>
        ut::FixedString<64> m_ServiceName{};

        /// <summary>
        /// Name of command
        /// </summary>
        ut::FixedString<64> m_CommandName{};

    	/// <summary>
    	/// What is this? It's always set to 0
    	/// </summary>
    	uint m_Unk1; // ALways 0

        /// <summary>
        /// Full size of the data + header in bytes
        /// </summary>
        uint m_Size{};
    };
}