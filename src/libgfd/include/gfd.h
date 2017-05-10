#pragma once
#include <wut.h>
#include <gx2/shaders.h>
#include <gx2/texture.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GFDHeader GFDHeader;
typedef struct GFDBlockHeader GFDBlockHeader;
typedef struct GFDRelocationHeader GFDRelocationHeader;

#define GFD_HEADER_MAGIC (0x47667832)
#define GFD_BLOCK_HEADER_MAGIC (0x424C4B7B)
#define GFD_RELOCATION_HEADER_MAGIC (0x7D424C4B)

#define GFD_FILE_VERSION_MAJOR (7)
#define GFD_FILE_VERSION_MINOR (1)
#define GFD_BLOCK_VERSION_MAJOR (1)

#define GFD_PATCH_MASK (0xFFF00000)
#define GFD_PATCH_DATA (0xD0600000)
#define GFD_PATCH_TEXT (0xCA700000)

typedef enum GFDBlockType
{
   GFD_BLOCK_END_OF_FILE                  = 1,
   GFD_BLOCK_PADDING                      = 2,
   GFD_BLOCK_VERTEX_SHADER_HEADER         = 3,
   GFD_BLOCK_VERTEX_SHADER_PROGRAM        = 5,
   GFD_BLOCK_PIXEL_SHADER_HEADER          = 6,
   GFD_BLOCK_PIXEL_SHADER_PROGRAM         = 7,
   GFD_BLOCK_GEOMETRY_SHADER_HEADER       = 8,
   GFD_BLOCK_GEOMETRY_SHADER_PROGRAM      = 9,
   GFD_BLOCK_GEOMETRY_SHADER_COPY_PROGRAM = 10,
   GFD_BLOCK_TEXTURE_HEADER               = 11,
   GFD_BLOCK_TEXTURE_IMAGE                = 12,
   GFD_BLOCK_TEXTURE_MIPMAP               = 13,
   GFD_BLOCK_COMPUTE_SHADER_HEADER        = 14,
   GFD_BLOCK_COMPUTE_SHADER_PROGRAM       = 15,
} GFDBlockType;

struct GFDHeader
{
   uint32_t magic;
   uint32_t headerSize;
   uint32_t majorVersion;
   uint32_t minorVersion;
   uint32_t gpuVersion;
   uint32_t align;
   uint32_t unk1;
   uint32_t unk2;
};
CHECK_OFFSET(GFDHeader, 0x00, magic);
CHECK_OFFSET(GFDHeader, 0x04, headerSize);
CHECK_OFFSET(GFDHeader, 0x08, majorVersion);
CHECK_OFFSET(GFDHeader, 0x0C, minorVersion);
CHECK_OFFSET(GFDHeader, 0x10, gpuVersion);
CHECK_OFFSET(GFDHeader, 0x14, align);
CHECK_OFFSET(GFDHeader, 0x18, unk1);
CHECK_OFFSET(GFDHeader, 0x1C, unk2);
CHECK_SIZE(GFDHeader, 0x20);

struct GFDBlockHeader
{
   uint32_t magic;
   uint32_t headerSize;
   uint32_t majorVersion;
   uint32_t minorVersion;
   GFDBlockType type;
   uint32_t dataSize;
   uint32_t id;
   uint32_t index;
};
CHECK_OFFSET(GFDBlockHeader, 0x00, magic);
CHECK_OFFSET(GFDBlockHeader, 0x04, headerSize);
CHECK_OFFSET(GFDBlockHeader, 0x08, majorVersion);
CHECK_OFFSET(GFDBlockHeader, 0x0C, minorVersion);
CHECK_OFFSET(GFDBlockHeader, 0x10, type);
CHECK_OFFSET(GFDBlockHeader, 0x14, dataSize);
CHECK_OFFSET(GFDBlockHeader, 0x18, id);
CHECK_OFFSET(GFDBlockHeader, 0x1C, index);
CHECK_SIZE(GFDHeader, 0x20);

struct GFDRelocationHeader
{
   uint32_t magic;
   uint32_t headerSize;
   uint32_t unk1;
   uint32_t dataSize;
   uint32_t dataOffset;
   uint32_t textSize;
   uint32_t textOffset;
   uint32_t patchBase;
   uint32_t patchCount;
   uint32_t patchOffset;
};
CHECK_OFFSET(GFDRelocationHeader, 0x00, magic);
CHECK_OFFSET(GFDRelocationHeader, 0x04, headerSize);
CHECK_OFFSET(GFDRelocationHeader, 0x08, unk1);
CHECK_OFFSET(GFDRelocationHeader, 0x0C, dataSize);
CHECK_OFFSET(GFDRelocationHeader, 0x10, dataOffset);
CHECK_OFFSET(GFDRelocationHeader, 0x14, textSize);
CHECK_OFFSET(GFDRelocationHeader, 0x18, textOffset);
CHECK_OFFSET(GFDRelocationHeader, 0x1C, patchBase);
CHECK_OFFSET(GFDRelocationHeader, 0x20, patchCount);
CHECK_OFFSET(GFDRelocationHeader, 0x24, patchOffset);
CHECK_SIZE(GFDRelocationHeader, 0x28);

uint32_t
GFDGetGeometryShaderCount(const void *file);

uint32_t
GFDGetGeometryShaderHeaderSize(uint32_t index,
                               const void *file);

uint32_t
GFDGetGeometryShaderProgramSize(uint32_t index,
                                const void *file);

uint32_t
GFDGetGeometryShaderCopyProgramSize(uint32_t index,
                                    const void *file);

BOOL
GFDGetGeometryShader(GX2GeometryShader *shader,
                     void *program,
                     void *copyProgram,
                     uint32_t index,
                     const void *file);

uint32_t
GFDGetPixelShaderCount(const void *file);

uint32_t
GFDGetPixelShaderHeaderSize(uint32_t index,
                            const void *file);

uint32_t
GFDGetPixelShaderProgramSize(uint32_t index,
                             const void *file);

BOOL
GFDGetPixelShader(GX2PixelShader *shader,
                  void *program,
                  uint32_t index,
                  const void *file);

uint32_t
GFDGetVertexShaderCount(const void *file);

uint32_t
GFDGetVertexShaderHeaderSize(uint32_t index,
                             const void *file);

uint32_t
GFDGetVertexShaderProgramSize(uint32_t index,
                              const void *file);

BOOL
GFDGetVertexShader(GX2VertexShader *shader,
                   void *program,
                   uint32_t index,
                   const void *file);

uint32_t
GFDGetTextureCount(const void *file);

uint32_t
GFDGetTextureHeaderSize(uint32_t index,
                        const void *file);

uint32_t
GFDGetTextureImageSize(uint32_t index,
                       const void *file);

uint32_t
GFDGetTextureMipImageSize(uint32_t index,
                          const void *file);

uint32_t
GFDGetTextureAlignmentSize(uint32_t index,
                           const void *file);

BOOL
GFDGetTexture(GX2Texture *texture,
              void *image,
              void *mipmap,
              uint32_t index,
              const void *file);

BOOL
GFDGetGX2RTexture(GX2Texture *texture,
                  uint32_t index,
                  const void *file);

const GX2Texture *
GFDGetTexturePointer(uint32_t index,
                     const void *file);

#ifdef __cplusplus
}
#endif
