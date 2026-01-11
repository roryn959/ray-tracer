#include <metal_stdlib>
using namespace metal;

kernel void multiply_by_five(
    device int* data [[ buffer(0) ]],
    uint id [[ thread_position_in_grid ]]
) {
    data[id] += 1;
}
