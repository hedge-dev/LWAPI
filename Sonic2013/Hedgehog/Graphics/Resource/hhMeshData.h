#pragma once

class IDirect3DIndexBuffer9;
class IDirect3DVertexBuffer9;
class IDirect3DVertexDeclaration9;

namespace hh::gfx::res
{
    struct ResMirageMaterialData;
    struct ResIndexBufferObjectData
    {
        IDirect3DIndexBuffer9* m_pIndexBuffer;
        uint32_t m_IndexSize; // Always 2
        uint32_t m_IndexCount;
        uint32_t m_Usage;
    };

    struct ResVertexStreamData
    {
        IDirect3DVertexBuffer9* m_pVertexBuffer;
        uint32_t m_Stride;
        uint32_t m_Unk1;
    };

    struct ResVertexBufferData
    {
        ResVertexStreamData* m_pStream;
        uint32_t m_Unk1;
        uint32_t m_Offset;
    };

    struct ResPrimitiveData
    {
        ResVertexBufferData* m_pVertexBuffers;
        uint32_t m_BufferCount;
        ResIndexBufferObjectData* m_pIndexBuffer;
        uint32_t m_StartIndex;
        uint32_t m_VertexCount;
    };

    struct ResMeshData
    {
        ResPrimitiveData* m_pPrimitive;
        IDirect3DVertexDeclaration9* m_pVertexDeclaration;
        D3DVERTEXELEMENT9 m_VertexElements[65];
        char* m_pBoneIndices;
        uint32_t m_PrimitiveCount;
        uint32_t m_BoneIndicesCount;
        char m_Unk1;
        char m_Unk2;
        char m_Unk3;
        ResMirageMaterialData* m_pMaterial;
        ResNameData m_MaterialName;
        ResNameData m_SlotName;
    };
}