#pragma once

struct WorldBounds {
	float m_minX;
	float m_maxX;
	float m_minY;
	float m_maxY;
	float m_minZ;
	float m_maxZ;
	float m_pad0;
	float m_pad1;
};

class World {
public:
	World();

	inline const WorldBounds& GetBounds() const { return m_bounds; }

private:
	const WorldBounds m_bounds;

};