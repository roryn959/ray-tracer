#import <Metal/Metal.h>
#import <Foundation/Foundation.h>

#include "Model/GpuExecutor.h"

struct GpuExecutor::Impl {
    id<MTLDevice> device;
    id<MTLCommandQueue> queue;
    id<MTLComputePipelineState> pipeline;
};

GpuExecutor::GpuExecutor(const World& world) :
	m_world{world},
	m_accumulator{},
	m_accumulationCount{1}
{
	@autoreleasepool {
		impl = new Impl{};
		m_accumulator = new Colour[NUM_PIXELS];

		InitialiseDevice();
		if (!impl->device) std::exit(1);

		InitialiseCommandQueue();
		if (!impl->queue) std::exit(1);

		CheckCommandBuffer();

		InitialisePipeline();
	}
}

GpuExecutor::~GpuExecutor() {
    delete impl;
	delete[] m_accumulator;
}

void GpuExecutor::InitialiseDevice() {
	impl->device = MTLCreateSystemDefaultDevice();
	if (impl->device) return;

	NSArray<id<MTLDevice>> *devices = nil;

	devices = MTLCopyAllDevices();
	if (!devices || devices.count == 0) {
		std::cerr << "Copy returned no devices.\n";
		std::exit(1);
	}

	impl->device = devices[0];
}

void GpuExecutor::InitialiseCommandQueue() {
	impl->queue = [impl->device newCommandQueue];
	if (!impl->queue) {
		std::cerr << "Failed to create command queue\n";
		impl->device = nil;
		std::exit(1);
	}
}

void GpuExecutor::CheckCommandBuffer() {
	id<MTLCommandBuffer> cb = [impl->queue commandBuffer];
	[cb commit];
	[cb waitUntilCompleted];

	if (cb.status != MTLCommandBufferStatusCompleted) {
		std::cerr << "Command buffer failure.\n";
		std::exit(1);
	}
}

void GpuExecutor::InitialisePipeline()
{
    NSURL* url = [NSURL fileURLWithPath:@"raytracer.metallib"];
	NSError* error = nil;
	id<MTLLibrary> library = [impl->device newLibraryWithURL:url error:&error];
    if (!library) {
        std::cerr << "Failed to load metallib: " << [[error localizedDescription] UTF8String] << '\n';
        return;
    }

    id<MTLFunction> kernel = [library newFunctionWithName:@"TraceRay"];
    if (!kernel) {
        std::cerr << "Kernel 'TraceRay' not found.\n";
        return;
    }

    impl->pipeline = [impl->device newComputePipelineStateWithFunction:kernel error:&error];
    if (!impl->pipeline) {
        std::cerr << "Failed to create pipeline: " << [[error localizedDescription] UTF8String] << '\n';
        return;
    }
}

void GpuExecutor::TraceRays(uint32_t* pixels) {
	size_t count = NUM_PIXELS;
	size_t byteSize = count * sizeof(Colour);

	id<MTLBuffer> gpuBuffer = [
		impl->device
		newBufferWithLength:byteSize
		options:MTLResourceStorageModeShared
	];

	uint numPlanes = m_world.GetPlanes().size();
	id<MTLBuffer> planeBuffer = [
		impl->device newBufferWithBytes:m_world.GetPlanes().data()
        length:sizeof(Plane) * numPlanes
        options:MTLResourceStorageModeShared
	];

	uint numCuboids = m_world.GetCuboids().size();
	id<MTLBuffer> cuboidBuffer = [
		impl->device newBufferWithBytes:m_world.GetCuboids().data()
        length:sizeof(Cuboid) * numCuboids
        options:MTLResourceStorageModeShared
	];

	uint numCuboidLights = m_world.GetCuboidLights().size();
	id<MTLBuffer> cuboidLightBuffer = [
		impl->device newBufferWithBytes:m_world.GetCuboidLights().data()
        length:sizeof(Cuboid) * numCuboidLights
        options:MTLResourceStorageModeShared
	];

	id<MTLCommandBuffer> cmd = [impl->queue commandBuffer];
    id<MTLComputeCommandEncoder> enc = [cmd computeCommandEncoder];

    MTLSize gridSize = MTLSizeMake(count, 1, 1);
    NSUInteger tgSize = impl->pipeline.maxTotalThreadsPerThreadgroup;
    if (tgSize > count) tgSize = count;
    MTLSize threadgroupSize = MTLSizeMake(tgSize, 1, 1);

	[enc setComputePipelineState:impl->pipeline];
    [enc setBuffer:gpuBuffer offset:0 atIndex:0];
	[enc setBytes:&m_accumulationCount length:sizeof(uint) atIndex:1];
	[enc setBuffer:planeBuffer offset:0 atIndex:2];
	[enc setBytes:&numPlanes length:sizeof(uint) atIndex:3];
	[enc setBuffer:cuboidBuffer offset:0 atIndex:4];
	[enc setBytes:&numCuboids length:sizeof(uint) atIndex:5];
	[enc setBuffer:cuboidLightBuffer offset:0 atIndex:6];
	[enc setBytes:&numCuboidLights length:sizeof(uint) atIndex:7];

    [enc dispatchThreads:gridSize threadsPerThreadgroup:threadgroupSize];

	[enc endEncoding];
    [cmd commit];
    [cmd waitUntilCompleted];

    if (cmd.status != MTLCommandBufferStatusCompleted) {
        std::cerr << "Compute dispatch failed.\n";
        return;
    }

	Colour* gpuColours = (Colour*)[gpuBuffer contents];

	for (int i = 0; i < NUM_PIXELS; ++i) {
		m_accumulator[i] = m_accumulator[i] + gpuColours[i];
	}

	for (int i = 0; i < NUM_PIXELS; ++i) {
		pixels[i] = ToUint32( GammaCorrect(m_accumulator[i] / m_accumulationCount) );
	}

	++m_accumulationCount;
}