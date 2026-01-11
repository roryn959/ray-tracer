#pragma once

struct WorldBounds {
	float m_lowerBoundX;
	float m_upperBoundX;
	float m_lowerBoundY;
	float m_upperBoundY;
	float m_lowerBoundZ;
	float m_upperBoundZ;
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