#pragma once

namespace csl::hio
{
    struct PacketHeader
    {
        /// <summary>
        /// Name of service
        /// </summary>
        ut::FixedString<64> ServiceName{};

        /// <summary>
        /// Name of command
        /// </summary>
        ut::FixedString<64> CommandName{};

    	/// <summary>
    	/// What is this? It's always set to 0
    	/// </summary>
    	uint Unk1; // ALways 0

        /// <summary>
        /// Full size of the data + header in bytes
        /// </summary>
        uint Size{};
    };
}