#include "egpch.h"
#include "Conversions.h"

namespace Engine::Maths
{
    unsigned int RGBtoHex(const Vector3<uint8_t>& color)
    {
        return (color.z << 16) | (color.y << 8) | (color.x);
    }
}

