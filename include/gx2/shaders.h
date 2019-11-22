#pragma once
#include <string.h>
#include <wut.h>
#include "enum.h"
#include "sampler.h"
#include "gx2r/buffer.h"

/**
 * \defgroup gx2_shader Shaders
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GX2AttribVar GX2AttribVar;
typedef struct GX2AttribStream GX2AttribStream;
typedef struct GX2FetchShader GX2FetchShader;
typedef struct GX2GeometryShader GX2GeometryShader;
typedef struct GX2LoopVar GX2LoopVar;
typedef struct GX2PixelShader GX2PixelShader;
typedef struct GX2SamplerVar GX2SamplerVar;
typedef struct GX2UniformBlock GX2UniformBlock;
typedef struct GX2UniformVar GX2UniformVar;
typedef struct GX2UniformInitialValue GX2UniformInitialValue;
typedef struct GX2VertexShader GX2VertexShader;

struct GX2FetchShader
{
   GX2FetchShaderType type;

   struct
   {
      uint32_t sq_pgm_resources_fs;
   } regs;

   uint32_t size;
   void *program;
   uint32_t attribCount;
   uint32_t numDivisors;
   uint32_t divisors[2];
};
WUT_CHECK_OFFSET(GX2FetchShader, 0x0, type);
WUT_CHECK_OFFSET(GX2FetchShader, 0x4, regs.sq_pgm_resources_fs);
WUT_CHECK_OFFSET(GX2FetchShader, 0x8, size);
WUT_CHECK_OFFSET(GX2FetchShader, 0xc, program);
WUT_CHECK_OFFSET(GX2FetchShader, 0x10, attribCount);
WUT_CHECK_OFFSET(GX2FetchShader, 0x14, numDivisors);
WUT_CHECK_OFFSET(GX2FetchShader, 0x18, divisors);
WUT_CHECK_SIZE(GX2FetchShader, 0x20);

struct GX2UniformBlock
{
   const char *name;
   uint32_t offset;
   uint32_t size;
};
WUT_CHECK_OFFSET(GX2UniformBlock, 0x00, name);
WUT_CHECK_OFFSET(GX2UniformBlock, 0x04, offset);
WUT_CHECK_OFFSET(GX2UniformBlock, 0x08, size);
WUT_CHECK_SIZE(GX2UniformBlock, 0x0C);

struct GX2UniformVar
{
   const char *name;
   GX2ShaderVarType type;
   uint32_t count;
   uint32_t offset;
   int32_t block;
};
WUT_CHECK_OFFSET(GX2UniformVar, 0x00, name);
WUT_CHECK_OFFSET(GX2UniformVar, 0x04, type);
WUT_CHECK_OFFSET(GX2UniformVar, 0x08, count);
WUT_CHECK_OFFSET(GX2UniformVar, 0x0C, offset);
WUT_CHECK_OFFSET(GX2UniformVar, 0x10, block);
WUT_CHECK_SIZE(GX2UniformVar, 0x14);

struct GX2UniformInitialValue
{
   float value[4];
   uint32_t offset;
};
WUT_CHECK_OFFSET(GX2UniformInitialValue, 0x00, value);
WUT_CHECK_OFFSET(GX2UniformInitialValue, 0x10, offset);
WUT_CHECK_SIZE(GX2UniformInitialValue, 0x14);

struct GX2LoopVar
{
   uint32_t offset;
   uint32_t value;
};
WUT_CHECK_OFFSET(GX2LoopVar, 0x00, offset);
WUT_CHECK_OFFSET(GX2LoopVar, 0x04, value);
WUT_CHECK_SIZE(GX2LoopVar, 0x08);

struct GX2SamplerVar
{
   const char *name;
   GX2SamplerVarType type;
   uint32_t location;
};
WUT_CHECK_OFFSET(GX2SamplerVar, 0x00, name);
WUT_CHECK_OFFSET(GX2SamplerVar, 0x04, type);
WUT_CHECK_OFFSET(GX2SamplerVar, 0x08, location);
WUT_CHECK_SIZE(GX2SamplerVar, 0x0C);

struct GX2AttribVar
{
   const char *name;
   GX2ShaderVarType type;
   uint32_t count;
   uint32_t location;
};
WUT_CHECK_OFFSET(GX2AttribVar, 0x00, name);
WUT_CHECK_OFFSET(GX2AttribVar, 0x04, type);
WUT_CHECK_OFFSET(GX2AttribVar, 0x08, count);
WUT_CHECK_OFFSET(GX2AttribVar, 0x0C, location);
WUT_CHECK_SIZE(GX2AttribVar, 0x10);

struct GX2VertexShader
{
   struct
   {
      uint32_t sq_pgm_resources_vs;
      uint32_t vgt_primitiveid_en;
      uint32_t spi_vs_out_config;
      uint32_t num_spi_vs_out_id;
      uint32_t spi_vs_out_id[10];
      uint32_t pa_cl_vs_out_cntl;
      uint32_t sq_vtx_semantic_clear;
      uint32_t num_sq_vtx_semantic;
      uint32_t sq_vtx_semantic[32];
      uint32_t vgt_strmout_buffer_en;
      uint32_t vgt_vertex_reuse_block_cntl;
      uint32_t vgt_hos_reuse_depth;
   } regs;

   uint32_t size;
   void *program;
   GX2ShaderMode mode;

   uint32_t uniformBlockCount;
   GX2UniformBlock *uniformBlocks;

   uint32_t uniformVarCount;
   GX2UniformVar *uniformVars;

   uint32_t initialValueCount;
   GX2UniformInitialValue *initialValues;

   uint32_t loopVarCount;
   GX2LoopVar *loopVars;

   uint32_t samplerVarCount;
   GX2SamplerVar *samplerVars;

   uint32_t attribVarCount;
   GX2AttribVar *attribVars;

   uint32_t ringItemsize;

   BOOL hasStreamOut;
   uint32_t streamOutStride[4];

   GX2RBuffer gx2rBuffer;
};
WUT_CHECK_OFFSET(GX2VertexShader, 0x00, regs.sq_pgm_resources_vs);
WUT_CHECK_OFFSET(GX2VertexShader, 0x04, regs.vgt_primitiveid_en);
WUT_CHECK_OFFSET(GX2VertexShader, 0x08, regs.spi_vs_out_config);
WUT_CHECK_OFFSET(GX2VertexShader, 0x0C, regs.num_spi_vs_out_id);
WUT_CHECK_OFFSET(GX2VertexShader, 0x10, regs.spi_vs_out_id);
WUT_CHECK_OFFSET(GX2VertexShader, 0x38, regs.pa_cl_vs_out_cntl);
WUT_CHECK_OFFSET(GX2VertexShader, 0x3C, regs.sq_vtx_semantic_clear);
WUT_CHECK_OFFSET(GX2VertexShader, 0x40, regs.num_sq_vtx_semantic);
WUT_CHECK_OFFSET(GX2VertexShader, 0x44, regs.sq_vtx_semantic);
WUT_CHECK_OFFSET(GX2VertexShader, 0xC4, regs.vgt_strmout_buffer_en);
WUT_CHECK_OFFSET(GX2VertexShader, 0xC8, regs.vgt_vertex_reuse_block_cntl);
WUT_CHECK_OFFSET(GX2VertexShader, 0xCC, regs.vgt_hos_reuse_depth);
WUT_CHECK_OFFSET(GX2VertexShader, 0xD0, size);
WUT_CHECK_OFFSET(GX2VertexShader, 0xD4, program);
WUT_CHECK_OFFSET(GX2VertexShader, 0xD8, mode);
WUT_CHECK_OFFSET(GX2VertexShader, 0xDc, uniformBlockCount);
WUT_CHECK_OFFSET(GX2VertexShader, 0xE0, uniformBlocks);
WUT_CHECK_OFFSET(GX2VertexShader, 0xE4, uniformVarCount);
WUT_CHECK_OFFSET(GX2VertexShader, 0xE8, uniformVars);
WUT_CHECK_OFFSET(GX2VertexShader, 0xEc, initialValueCount);
WUT_CHECK_OFFSET(GX2VertexShader, 0xF0, initialValues);
WUT_CHECK_OFFSET(GX2VertexShader, 0xF4, loopVarCount);
WUT_CHECK_OFFSET(GX2VertexShader, 0xF8, loopVars);
WUT_CHECK_OFFSET(GX2VertexShader, 0xFc, samplerVarCount);
WUT_CHECK_OFFSET(GX2VertexShader, 0x100, samplerVars);
WUT_CHECK_OFFSET(GX2VertexShader, 0x104, attribVarCount);
WUT_CHECK_OFFSET(GX2VertexShader, 0x108, attribVars);
WUT_CHECK_OFFSET(GX2VertexShader, 0x10c, ringItemsize);
WUT_CHECK_OFFSET(GX2VertexShader, 0x110, hasStreamOut);
WUT_CHECK_OFFSET(GX2VertexShader, 0x114, streamOutStride);
WUT_CHECK_OFFSET(GX2VertexShader, 0x124, gx2rBuffer);
WUT_CHECK_SIZE(GX2VertexShader, 0x134);

struct GX2PixelShader
{
   struct
   {
      uint32_t sq_pgm_resources_ps;
      uint32_t sq_pgm_exports_ps;
      uint32_t spi_ps_in_control_0;
      uint32_t spi_ps_in_control_1;
      uint32_t num_spi_ps_input_cntl;
      uint32_t spi_ps_input_cntls[32];
      uint32_t cb_shader_mask;
      uint32_t cb_shader_control;
      uint32_t db_shader_control;
      uint32_t spi_input_z;
   } regs;

   uint32_t size;
   void *program;
   GX2ShaderMode mode;

   uint32_t uniformBlockCount;
   GX2UniformBlock *uniformBlocks;

   uint32_t uniformVarCount;
   GX2UniformVar *uniformVars;

   uint32_t initialValueCount;
   GX2UniformInitialValue *initialValues;

   uint32_t loopVarCount;
   GX2LoopVar *loopVars;

   uint32_t samplerVarCount;
   GX2SamplerVar *samplerVars;

   GX2RBuffer gx2rBuffer;
};
WUT_CHECK_OFFSET(GX2PixelShader, 0x00, regs.sq_pgm_resources_ps);
WUT_CHECK_OFFSET(GX2PixelShader, 0x04, regs.sq_pgm_exports_ps);
WUT_CHECK_OFFSET(GX2PixelShader, 0x08, regs.spi_ps_in_control_0);
WUT_CHECK_OFFSET(GX2PixelShader, 0x0C, regs.spi_ps_in_control_1);
WUT_CHECK_OFFSET(GX2PixelShader, 0x10, regs.num_spi_ps_input_cntl);
WUT_CHECK_OFFSET(GX2PixelShader, 0x14, regs.spi_ps_input_cntls);
WUT_CHECK_OFFSET(GX2PixelShader, 0x94, regs.cb_shader_mask);
WUT_CHECK_OFFSET(GX2PixelShader, 0x98, regs.cb_shader_control);
WUT_CHECK_OFFSET(GX2PixelShader, 0x9C, regs.db_shader_control);
WUT_CHECK_OFFSET(GX2PixelShader, 0xA0, regs.spi_input_z);
WUT_CHECK_OFFSET(GX2PixelShader, 0xA4, size);
WUT_CHECK_OFFSET(GX2PixelShader, 0xA8, program);
WUT_CHECK_OFFSET(GX2PixelShader, 0xAC, mode);
WUT_CHECK_OFFSET(GX2PixelShader, 0xB0, uniformBlockCount);
WUT_CHECK_OFFSET(GX2PixelShader, 0xB4, uniformBlocks);
WUT_CHECK_OFFSET(GX2PixelShader, 0xB8, uniformVarCount);
WUT_CHECK_OFFSET(GX2PixelShader, 0xBC, uniformVars);
WUT_CHECK_OFFSET(GX2PixelShader, 0xC0, initialValueCount);
WUT_CHECK_OFFSET(GX2PixelShader, 0xC4, initialValues);
WUT_CHECK_OFFSET(GX2PixelShader, 0xC8, loopVarCount);
WUT_CHECK_OFFSET(GX2PixelShader, 0xCC, loopVars);
WUT_CHECK_OFFSET(GX2PixelShader, 0xD0, samplerVarCount);
WUT_CHECK_OFFSET(GX2PixelShader, 0xD4, samplerVars);
WUT_CHECK_OFFSET(GX2PixelShader, 0xD8, gx2rBuffer);
WUT_CHECK_SIZE(GX2PixelShader, 0xE8);

struct GX2GeometryShader
{
   struct
   {
      uint32_t sq_pgm_resources_gs;
      uint32_t vgt_gs_out_prim_type;
      uint32_t vgt_gs_mode;
      uint32_t pa_cl_vs_out_cntl;
      uint32_t sq_pgm_resources_vs;
      uint32_t sq_gs_vert_itemsize;
      uint32_t spi_vs_out_config;
      uint32_t num_spi_vs_out_id;
      uint32_t spi_vs_out_id[10];
      uint32_t vgt_strmout_buffer_en;
   } regs;

   uint32_t size;
   void *program;
   uint32_t vertexProgramSize;
   void *vertexProgram;
   GX2ShaderMode mode;

   uint32_t uniformBlockCount;
   GX2UniformBlock *uniformBlocks;

   uint32_t uniformVarCount;
   GX2UniformVar *uniformVars;

   uint32_t initialValueCount;
   GX2UniformInitialValue *initialValues;

   uint32_t loopVarCount;
   GX2LoopVar *loopVars;

   uint32_t samplerVarCount;
   GX2SamplerVar *samplerVars;

   uint32_t ringItemSize;
   BOOL hasStreamOut;
   uint32_t streamOutStride[4];

   GX2RBuffer gx2rBuffer;
};
WUT_CHECK_OFFSET(GX2GeometryShader, 0x00, regs.sq_pgm_resources_gs);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x04, regs.vgt_gs_out_prim_type);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x08, regs.vgt_gs_mode);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x0C, regs.pa_cl_vs_out_cntl);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x10, regs.sq_pgm_resources_vs);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x14, regs.sq_gs_vert_itemsize);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x18, regs.spi_vs_out_config);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x1C, regs.num_spi_vs_out_id);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x20, regs.spi_vs_out_id);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x48, regs.vgt_strmout_buffer_en);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x4C, size);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x50, program);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x54, vertexProgramSize);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x58, vertexProgram);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x5C, mode);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x60, uniformBlockCount);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x64, uniformBlocks);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x68, uniformVarCount);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x6C, uniformVars);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x70, initialValueCount);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x74, initialValues);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x78, loopVarCount);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x7C, loopVars);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x80, samplerVarCount);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x84, samplerVars);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x88, ringItemSize);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x8C, hasStreamOut);
WUT_CHECK_OFFSET(GX2GeometryShader, 0x90, streamOutStride);
WUT_CHECK_OFFSET(GX2GeometryShader, 0xA0, gx2rBuffer);
WUT_CHECK_SIZE(GX2GeometryShader, 0xB0);

struct GX2AttribStream
{
   uint32_t location;
   uint32_t buffer;
   uint32_t offset;
   GX2AttribFormat format;
   GX2AttribIndexType type;
   uint32_t aluDivisor;
   uint32_t mask;
   GX2EndianSwapMode endianSwap;
};
WUT_CHECK_OFFSET(GX2AttribStream, 0x0, location);
WUT_CHECK_OFFSET(GX2AttribStream, 0x4, buffer);
WUT_CHECK_OFFSET(GX2AttribStream, 0x8, offset);
WUT_CHECK_OFFSET(GX2AttribStream, 0xc, format);
WUT_CHECK_OFFSET(GX2AttribStream, 0x10, type);
WUT_CHECK_OFFSET(GX2AttribStream, 0x14, aluDivisor);
WUT_CHECK_OFFSET(GX2AttribStream, 0x18, mask);
WUT_CHECK_OFFSET(GX2AttribStream, 0x1c, endianSwap);
WUT_CHECK_SIZE(GX2AttribStream, 0x20);

uint32_t
GX2CalcGeometryShaderInputRingBufferSize(uint32_t ringItemSize);

uint32_t
GX2CalcGeometryShaderOutputRingBufferSize(uint32_t ringItemSize);

uint32_t
GX2CalcFetchShaderSizeEx(uint32_t attribs,
                         GX2FetchShaderType fetchShaderType,
                         GX2TessellationMode tesellationMode);

void
GX2InitFetchShaderEx(GX2FetchShader *fetchShader,
                     uint8_t *buffer,
                     uint32_t attribCount,
                     const GX2AttribStream *attribs,
                     GX2FetchShaderType type,
                     GX2TessellationMode tessMode);

void
GX2SetFetchShader(const GX2FetchShader *shader);

void
GX2SetVertexShader(const GX2VertexShader *shader);

void
GX2SetPixelShader(const GX2PixelShader *shader);

void
GX2SetGeometryShader(const GX2GeometryShader *shader);

void
GX2SetVertexSampler(const GX2Sampler *sampler,
                    uint32_t id);

void
GX2SetPixelSampler(const GX2Sampler *sampler,
                   uint32_t id);

void
GX2SetGeometrySampler(const GX2Sampler *sampler,
                      uint32_t id);

void
GX2SetVertexUniformReg(uint32_t offset,
                       uint32_t count,
                       const void *data);

void
GX2SetPixelUniformReg(uint32_t offset,
                      uint32_t count,
                      const void *data);

void
GX2SetVertexUniformBlock(uint32_t location,
                         uint32_t size,
                         const void *data);

void
GX2SetPixelUniformBlock(uint32_t location,
                        uint32_t size,
                        const void *data);

void
GX2SetGeometryUniformBlock(uint32_t location,
                           uint32_t size,
                           const void *data);

void
GX2SetShaderModeEx(GX2ShaderMode mode,
                   uint32_t numVsGpr, uint32_t numVsStackEntries,
                   uint32_t numGsGpr, uint32_t numGsStackEntries,
                   uint32_t numPsGpr, uint32_t numPsStackEntries);

void
GX2SetStreamOutEnable(BOOL enable);

void
GX2SetGeometryShaderInputRingBuffer(const void *buffer,
                                    uint32_t size);

void
GX2SetGeometryShaderOutputRingBuffer(void *buffer,
                                     uint32_t size);

uint32_t
GX2GetPixelShaderGPRs(const GX2PixelShader *shader);

uint32_t
GX2GetPixelShaderStackEntries(const GX2PixelShader *shader);

uint32_t
GX2GetVertexShaderGPRs(const GX2VertexShader *shader);

uint32_t
GX2GetVertexShaderStackEntries(const GX2VertexShader *shader);

uint32_t
GX2GetGeometryShaderGPRs(const GX2GeometryShader *shader);

uint32_t
GX2GetGeometryShaderStackEntries(const GX2GeometryShader *shader);

static inline GX2UniformBlock *
GX2GetGeometryUniformBlock(const GX2GeometryShader *shader,
                           const char *name)
{
   for (uint32_t i = 0; i < shader->uniformBlockCount; ++i) {
      if (strcmp(name, shader->uniformBlocks[i].name) == 0) {
         return &shader->uniformBlocks[i];
      }
   }

   return NULL;
}

static inline GX2UniformBlock *
GX2GetPixelUniformBlock(const GX2PixelShader *shader,
                        const char *name)
{
   for (uint32_t i = 0; i < shader->uniformBlockCount; ++i) {
      if (strcmp(name, shader->uniformBlocks[i].name) == 0) {
         return &shader->uniformBlocks[i];
      }
   }

   return NULL;
}

static inline GX2UniformBlock *
GX2GetVertexUniformBlock(const GX2VertexShader *shader,
                         const char *name)
{
   for (uint32_t i = 0; i < shader->uniformBlockCount; ++i) {
      if (strcmp(name, shader->uniformBlocks[i].name) == 0) {
         return &shader->uniformBlocks[i];
      }
   }

   return NULL;
}

static inline GX2UniformVar *
GX2GetGeometryUniformVar(const GX2GeometryShader *shader,
                         const char *name)
{
   for (uint32_t i = 0; i < shader->uniformVarCount; ++i) {
      if (strcmp(name, shader->uniformVars[i].name) == 0) {
         return &shader->uniformVars[i];
      }
   }

   return NULL;
}

static inline GX2UniformVar *
GX2GetPixelUniformVar(const GX2PixelShader *shader,
                      const char *name)
{
   for (uint32_t i = 0; i < shader->uniformVarCount; ++i) {
      if (strcmp(name, shader->uniformVars[i].name) == 0) {
         return &shader->uniformVars[i];
      }
   }

   return NULL;
}

static inline GX2UniformVar *
GX2GetVertexUniformVar(const GX2VertexShader *shader,
                       const char *name)
{
   for (uint32_t i = 0; i < shader->uniformVarCount; ++i) {
      if (strcmp(name, shader->uniformVars[i].name) == 0) {
         return &shader->uniformVars[i];
      }
   }

   return NULL;
}

#ifdef __cplusplus
}
#endif

/** @} */
