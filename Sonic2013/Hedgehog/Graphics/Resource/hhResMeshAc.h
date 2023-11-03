#pragma once

class IDirect3DIndexBuffer9;
class IDirect3DVertexBuffer9;
class IDirect3DVertexDeclaration9;

namespace hh::gfx::res
{
    struct ResMirageMaterialData;
    struct ResIndexBufferObjectData
    {
        IDirect3DIndexBuffer9* pIndexBuffer;
        uint32_t IndexSize; // Always 2
        uint32_t IndexCount;
        uint32_t Usage;
    };

    struct ResVertexStreamData
    {
        IDirect3DVertexBuffer9* pVertexBuffer;
        uint32_t Stride;
        uint32_t Unk1;
    };

    struct ResVertexBufferData
    {
        ResVertexStreamData* pStream;
        uint32_t Unk1;
        uint32_t Offset;
    };

    struct ResPrimitiveData
    {
        ResVertexBufferData* pVertexBuffers;
        uint32_t BufferCount;
        ResIndexBufferObjectData* pIndexBuffer;
        uint32_t StartIndex;
        uint32_t VertexCount;
    };

    struct ResMeshData
    {
        ResPrimitiveData* pPrimitive;
        IDirect3DVertexDeclaration9* pVertexDeclaration;
        D3DVERTEXELEMENT9 VertexElements[65];
        char* pBoneIndices;
        uint32_t PrimitiveCount;
        uint32_t BoneIndicesCount;
        char Unk1;
        char Unk2;
        char Unk3;
        ResMirageMaterialData* pMaterial;
        ResNameData MaterialName;
        ResNameData SlotName;
    };

    class ResMesh : public ut::ResCommon<ResMeshData>
    {

    };
}