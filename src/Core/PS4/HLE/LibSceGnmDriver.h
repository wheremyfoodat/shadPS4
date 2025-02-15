#pragma once
#include "../Loader/SymbolsResolver.h"

namespace HLE::Libs::LibSceGnmDriver {

void LibSceGnmDriver_Register(SymbolsResolver* sym);

//functions
int sceGnmAddEqEvent(/* SceKernelEqueue eq, EqEventType id,*/ void* udata);
bool sceGnmAreSubmitsAllowed();
int /* WorkloadStatus*/ sceGnmBeginWorkload(uint64_t* workload /*, WorkloadStream stream*/);
int /* WorkloadStatus*/ sceGnmCreateWorkloadStream(/* WorkloadStream* workloadStream,*/ const char* name);
void sceGnmDebugHardwareStatus(/* HardwareStatus flag*/);
void sceGnmSetGsRingSizes(/* GsRingSizeSetup esgsRingSize, GsRingSizeSetup gsvsRingSize*/);
int32_t sceGnmSetWaveLimitMultipliers(uint16_t targetPipeMask, uint8_t gfxRatio, const uint8_t (*pipeRatios)[7]);
int /*MipStatsError*/ sceGnmSetupMipStatsReport(void* outputBuffer, uint32_t sizeInBytes, uint8_t intervalsBetweenReports,
                                          uint8_t numReportsBeforeReset /*, MipStatsResetForce mipStatsResetForce*/);
int sceGnmSubmitCommandBuffers(uint32_t count, void* dcb_gpu_addrs[], const uint32_t* dcb_sizes_in_bytes, void* ccb_gpu_addrs[],
                               const uint32_t* ccb_sizes_in_bytes);
int sceGnmSubmitAndFlipCommandBuffers(uint32_t count, void* dcb_gpu_addrs[], const uint32_t* dcb_sizes_in_bytes, void* ccb_gpu_addrs[],
                                      const uint32_t* ccb_sizes_in_bytes, int handle, int index, int flip_mode, int64_t flip_arg);
void sceGnmDingDong(u32 ring_id, u32 offset_dw);
bool sceRazorIsLoaded();
int sceGnmDeleteEqEvent(/* SceKernelEqueue eq, EqEventType id*/);
int32_t sceGnmSubmitDone();
int /* MipStatsError*/ sceGnmDisableMipStatsReport();
int sceGnmSubmitAndFlipCommandBuffersForWorkload();
int sceGnmSubmitCommandBuffersForWorkload();
int /* WorkloadStatus*/ sceGnmDestroyWorkloadStream(/*WorkloadStream workloadStream*/);
void sceGnmDingDongForWorkload();
void sceGnmDriverCaptureInProgress();
void sceGnmUnmapComputeQueue();
void sceGnmDriverTraceInProgress();
void sceGnmDriverTriggerCapture();
void sceGnmEndWorkload();
void sceGnmFlushGarlic();
void sceGnmGetEqEventType();
void sceGnmGetEqTimeStamp();
void sceGnmGetGpuBlockStatus();
void sceGnmGetGpuInfoStatus();
void sceGnmGetLastWaitedAddress();
void sceGnmGetNumTcaUnits();
void sceGnmGetOffChipTessellationBufferSize();
void sceGnmGetPhysicalCounterFromVirtualized();
void sceGnmGetProtectionFaultTimeStamp();
void sceGnmGetShaderProgramBaseAddress();
void sceGnmGetShaderStatus();
void sceGnmGetTheTessellationFactorRingBufferBaseAddress();
void sceGnmIsUserPaEnabled();
void sceGnmLogicalCuIndexToPhysicalCuIndex();
void sceGnmLogicalCuMaskToPhysicalCuMask();
void sceGnmMapComputeQueue();
void sceGnmMapComputeQueueWithPriority();
void sceRazorCaptureImmediate();
void sceGnmRequestFlipAndSubmitDone();
void sceGnmRequestFlipAndSubmitDoneForWorkload();
void sceGnmRequestMipStatsReportAndReset();
};  // namespace HLE::Libs::LibSceGnmDriver